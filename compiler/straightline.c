typedef char* string;
typedef A_stm_ *A_stm;
typedef A_exp_ *A_exp;
typedef A_expList *A_expList;
typedef enum{A_plus,A_sub,A_minus,A_times,A_div} A_Binop;

struct A_stm_{
    enum {A_CompoundStm,A_AssignStm,A_PrintStm}kind;
    union{
        struct{A_stm stm1,stm2;}compound;
        struct{string id;A_exp;}assign;
        struct{A_expList exps;}print;
    }u;
};

A_stm A_CompoundStm(A_stm stm1, A_stm stm2);
A_stm A_AssignStm(string id,A_exp exp);
A_stm A_PrintStm(A_expList exps);

struct A_exp_{
    enum{idExp,numExp,opExp,eseqExp}kind;
    union{
        string id;
        int num;
        struct{A_exp leftExp;A_Binop oper;A_exp rightExp;}op;
        struct{A_stm stm,A_exp exp;}eseq;
    }u;
} 

A_exp idExp(string id);
A_exp numExp(int num);
A_exp opExp(A_exp leftExp,A_Binop op,A_exp rightExp);
A_exp eseqExp(A_stm stm, A_exp exp);

struct A_expList_{
    enum{A_pairExpList,A_lastExpList}kind;
    union{
        struct{A_exp leftExp; A_exp rightExp}pair;
        A_exp last;
    }u;
}

A_expList A_pairExpList(A_exp leftExp,A_exp rightExp);
A_expList A_lastExpList(A_exp exp);
