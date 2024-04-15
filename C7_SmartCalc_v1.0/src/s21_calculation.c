#include "s21_calculation.h"

double calculate_rpn(stack_ty** postfix_stack, double x_value) {
  double result = ERROR;
  stack_ty* evaluation_stack = NULL;
  while (*postfix_stack != NULL) {
    int priority;
    void* value;
    type_t data_type;
    pop(postfix_stack, &priority, &value, &data_type);
    if (data_type == NUMBER) {
      push(&evaluation_stack, priority, value, NUMBER);
    } else if (data_type == VARIABLE) {
      calculate_variable(x_value, &value, &evaluation_stack, priority);
    } else if (data_type == OPERATION) {
      calculate_operation(value, &evaluation_stack, priority);
    } else if (data_type == FUNCTION) {
      calculate_function(value, &evaluation_stack, priority);
    }
  }
  if (evaluation_stack != NULL) {
    result = *(double*)evaluation_stack->value;
    destroy_stack(&evaluation_stack);
  }
  return result;
}

int calculate_variable(double x_value, void** value,
                       stack_ty** evaluation_stack, int priority) {
  int exit_code = SUCCESS;
  double* x_value_copy = (double*)malloc(sizeof(double));
  if (x_value_copy == NULL) {
    exit_code = ERROR;
  } else {
    *x_value_copy = x_value;
    if (push(evaluation_stack, priority, x_value_copy, NUMBER) != SUCCESS) {
      free(x_value_copy);
      exit_code = ERROR;
    }
    free(*value);
  }
  return exit_code;
}

int calculate_operation(void* value, stack_ty** evaluation_stack,
                        int priority) {
  int first_priority, second_priority, exit_code = SUCCESS;
  void *first_value, *second_value;
  type_t first_data_type, second_data_type;
  pop(evaluation_stack, &second_priority, &second_value, &second_data_type);
  pop(evaluation_stack, &first_priority, &first_value, &first_data_type);
  double result = 0;
  char operator= *(char*) value;
  switch (operator) {
    case '+':
      result = *(double*)first_value + *(double*)second_value;
      break;
    case '-':
      result = *(double*)first_value - *(double*)second_value;
      break;
    case '*':
      result = *(double*)first_value * *(double*)second_value;
      break;
    case '/':
      result = *(double*)first_value / *(double*)second_value;
      break;
    case '^':
      result = pow(*(double*)first_value, *(double*)second_value);
      break;
    case '%':
      if (*(double*)second_value != 0) {
        result = (int)*(double*)first_value % (int)*(double*)second_value;
      }
      break;
  }
  free(first_value);
  free(second_value);
  double* result_copy = (double*)malloc(sizeof(*result_copy));
  if (result_copy == NULL) {
    exit_code = ERROR;
  } else {
    *result_copy = result;
    if (push(evaluation_stack, priority, result_copy, NUMBER) != SUCCESS) {
      free(result_copy);
      exit_code = ERROR;
    }
    free(value);
  }
  return exit_code;
}

int calculate_function(void* value, stack_ty** evaluation_stack, int priority) {
  int arg_priority;
  void* arg_value;
  type_t arg_data_type;
  pop(evaluation_stack, &arg_priority, &arg_value, &arg_data_type);
  double result = 0;
  char* function = (char*)value;
  int exit_code = SUCCESS;
  if (strcmp(function, "sin") == 0) {
    result = sin(*(double*)arg_value);
  } else if (strcmp(function, "cos") == 0) {
    result = cos(*(double*)arg_value);
  } else if (strcmp(function, "tan") == 0) {
    result = tan(*(double*)arg_value);
  } else if (strcmp(function, "asin") == 0) {
    result = asin(*(double*)arg_value);
  } else if (strcmp(function, "acos") == 0) {
    result = acos(*(double*)arg_value);
  } else if (strcmp(function, "atan") == 0) {
    result = atan(*(double*)arg_value);
  } else if (strcmp(function, "sqrt") == 0) {
    result = sqrt(*(double*)arg_value);
  } else if (strcmp(function, "ln") == 0) {
    result = log(*(double*)arg_value);
  } else if (strcmp(function, "log") == 0) {
    result = log10(*(double*)arg_value);
  }
  free(arg_value);
  double* result_copy = (double*)malloc(sizeof(double));
  if (result_copy == NULL) {
    exit_code = ERROR;
  } else {
    *result_copy = result;
    if (push(evaluation_stack, priority, result_copy, NUMBER) != SUCCESS) {
      free(result_copy);
      exit_code = ERROR;
    }
    free(value);
  }
  return exit_code;
}
