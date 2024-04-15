#ifndef SRC_S21_PARSER_H_
#define SRC_S21_PARSER_H_

#include "s21_stack.h"

void parser(const char *, stack_ty **);
int number_processing(const char *, stack_ty **, int);
int operation_processing(const char *, stack_ty **, stack_ty **, int);
int function_processing(const char **, stack_ty **, int);
int variable_processing(stack_ty ***, int);
int right_bracket_processing(stack_ty **, stack_ty **, char **, int);
int not_right_bracket_processing(int, stack_ty **, stack_ty **, char *, int);
void operator_stack_processing(stack_ty **, stack_ty **);
#endif  // SRC_S21_SMARTCALC_H_