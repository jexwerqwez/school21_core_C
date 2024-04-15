#ifndef SRC_S21_CALCULATION_H_
#define SRC_S21_CALCULATION_H_

#include "s21_parser.h"

double calculate_rpn(stack_ty **, double);
int calculate_variable(double, void **, stack_ty **, int);
int calculate_operation(void *, stack_ty **, int);
int calculate_function(void *, stack_ty **, int);
#endif