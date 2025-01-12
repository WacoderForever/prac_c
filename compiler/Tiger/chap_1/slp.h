typedef struct A_stm_*     A_stm;
typedef struct A_exp_*     A_exp;
typedef struct A_expList_* A_expList;
typedef enum{A_plus,A_minus,A_times,A_div}A_binop;

struct A_stm_ {
    enum{A_compoundStm,A_assignStm,A_printStm}kind;
    union{
        struct{A_stm stm1,stm2;}compound;
        struct{string id;A_exp exp;}assign;
        struct{A_expList exps;}print;
    }u;
};

A_stm A_CompoundStm(A_stm stm1,A_stm stm2);
A_stm A_AssignStm(string id,A_exp exp);
A_stm A_PrintStm(A_expList exps);

struct A_exp_{
    enum{A_opExp,A_numExp,A_eseqExp,A_idExp}kind;
    union{
        struct{A_exp left;A_binop oper;A_exp right;}op;
        int num;
        struct{A_stm stm;A_exp exp;}eseq;
        string id;
    }u;
};

A_exp A_OpExp(A_exp left,A_binop oper,A_exp right);
A_exp A_NumExp(int n);
A_exp A_EseqExp(A_stm stm,A_exp exp);
A_exp A_IdExp(string id);

struct A_expList_{
    enum{A_pairExpList,A_lastExpList}kind;
    union{
        struct{A_exp head;A_expList tail;}pair;
        A_exp last;
    }u;
};

A_expList A_PairExpList(A_exp head,A_expList tail);
A_expList A_LastExpList(A_exp last);