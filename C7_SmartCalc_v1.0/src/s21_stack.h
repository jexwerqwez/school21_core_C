#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define ERROR 0

#define MEMORY -1
#define INPUT -2
#define M_PI 3.14159265358979323846

typedef enum { NUMBER, VALUE, OPERATION, FUNCTION, VARIABLE } type_t;

typedef struct s21_stack {
  int priority;  // приоритет
  void *value;   // число
  struct s21_stack *prev;
  type_t data_type;
} stack_ty;

int pop(stack_ty **, int *, void **, type_t *);
int push(stack_ty **, int, void *, type_t);
void reverse_stack(stack_ty *, stack_ty **);
void destroy_stack(stack_ty **);
void print_stack(stack_ty *);
void simple_destroy_stack(stack_ty **);
#endif  // SRC_S21_STACK_H_
