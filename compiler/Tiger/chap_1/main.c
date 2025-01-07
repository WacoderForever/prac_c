#include "util.h"
#include "slp.h"
#include "prog1.h"
#include <stdio.h>

/**
 * 1. Write a function int maxargs(A_stm) that tells the maximum number of
 * arguments of any print statement within any subexpression of a given
 * statement. For example,maxargs(prog) is 2.
 */
int maxargs(A_stm);

int maxargs_exp(A_exp e) {
  switch (e->kind) {
    case A_idExp:  return 0;
    case A_numExp: return 0;
    case A_opExp:
      return maxargs_exp(e->u.op.left) + maxargs_exp(e->u.op.right);
    case A_eseqExp:
      return maxargs(e->u.eseq.stm) + maxargs_exp(e->u.eseq.exp);
  }
}

int maxargs_exp_list(A_expList el) {
  if (el->kind == A_lastExpList)
    return maxargs_exp(el->u.last);
  else
    return maxargs_exp(el->u.pair.head) + maxargs_exp_list(el->u.pair.tail);
}

int maxargs(A_stm s) {
  switch (s->kind) {
    case A_compoundStm:
      return maxargs(s->u.compound.stm1) + maxargs(s->u.compound.stm2);
    case A_assignStm:
      return maxargs_exp(s->u.assign.exp);
    case A_printStm:
      return 1 + maxargs_exp_list(s->u.print.exps);
  }
}
