#include "s21_stack.h"

int push(stack_ty **stack, int priority, void *value, type_t data_type) {
  stack_ty *temp = (stack_ty *)malloc(sizeof(stack_ty));
  int exit_code = SUCCESS;
  if (temp == NULL) {
    exit_code = ERROR;
  } else {
    temp->priority = priority;
    temp->value = value;
    temp->data_type = data_type;
    temp->prev = *stack;
    *stack = temp;
  }
  return exit_code;
}

int pop(stack_ty **stack, int *priority, void **value, type_t *data_type) {
  int exit_code = SUCCESS;
  if (stack == NULL) {
    exit_code = ERROR;
  } else {
    stack_ty *temp = (*stack)->prev;
    *priority = (*stack)->priority;
    *value = (*stack)->value;
    *data_type = (*stack)->data_type;
    free(*stack);
    *stack = temp;
  }
  return exit_code;
}

void reverse_stack(stack_ty *old_v, stack_ty **new_v) {
  stack_ty *temp = old_v;
  while (temp != NULL) {
    push(new_v, temp->priority, temp->value, temp->data_type);
    temp = temp->prev;
  }
}

void destroy_stack(stack_ty **stack) {
  while (*stack != NULL) {
    free((*stack)->value);
    stack_ty *temp = *stack;
    *stack = (*stack)->prev;
    free(temp);
  }
}

void simple_destroy_stack(stack_ty **stack) {
  while (*stack != NULL) {
    stack_ty *temp = *stack;
    *stack = (*stack)->prev;
    free(temp);
  }
}
