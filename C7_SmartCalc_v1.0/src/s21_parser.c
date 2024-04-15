#include "s21_parser.h"

char* numbers_array = "0123456789.";
char* operations_array = "()+-*/^%";
int operations_priority[] = {0, 0, 1, 1, 2, 2, 3, 4};
char* functions[] = {"sin",  "cos",  "tan", "asin", "acos",
                     "atan", "sqrt", "ln",  "log"};
int num_functions = sizeof(functions) / sizeof(functions[0]);

void parser(const char* infix, stack_ty** postfix_stack) {
  stack_ty* operator_stack = NULL;
  int length = strlen(infix);
  int i = 0;
  setlocale(LC_NUMERIC, "C");
  while (i < length) {
    if (infix[i] == ' ') {
      i++;
      continue;
    }
    if (strchr(numbers_array, infix[i]) != NULL) {
      i = number_processing(infix, postfix_stack, i);
    } else if (strchr(operations_array, infix[i]) != NULL) {
      i = operation_processing(infix, postfix_stack, &operator_stack, i);
    } else if (isalpha(infix[i]) && infix[i] != 'x') {
      i = function_processing(&infix, &operator_stack, i);
    } else if (infix[i] == 'x') {
      i = variable_processing(&postfix_stack, i);
    } else {
      i++;
    }
  }
  operator_stack_processing(&operator_stack, postfix_stack);
}

int number_processing(const char* infix, stack_ty** postfix_stack, int i) {
  double* number = (double*)malloc(sizeof(*number));
  if (sscanf(infix + i, "%lf", number) == 1) {
    push(postfix_stack, 0, number, NUMBER);
    i += strspn(infix + i, numbers_array);
  } else {
    free(number);
  }
  return i;
}

int operation_processing(const char* infix, stack_ty** postfix_stack,
                         stack_ty** operator_stack, int i) {
  int operation_priority =
      operations_priority[strchr(operations_array, infix[i]) -
                          operations_array];
  char* operation = (char*)malloc(sizeof(*operation) + 1);
  *operation = infix[i];
  operation[1] = '\0';
  if (infix[i] == '(') {
    push(operator_stack, operation_priority, operation, OPERATION);
    i++;
  } else if (infix[i] == ')') {
    i = right_bracket_processing(operator_stack, postfix_stack, &operation, i);
  } else if ((infix[i] == '+' || infix[i] == '-') &&
             (i == 0 || (i > 0 && infix[i - 1] != ')'))) {
    if (i == 0 || strchr(operations_array, infix[i - 1]) != NULL ||
        infix[i - 1] == '(') {
      double* number = (double*)malloc(sizeof(*number));
      *number = 0;
      push(postfix_stack, 0, number, NUMBER);
    }
    i = not_right_bracket_processing(operation_priority, operator_stack,
                                     postfix_stack, operation, i);
  } else {
    i = not_right_bracket_processing(operation_priority, operator_stack,
                                     postfix_stack, operation, i);
  }
  return i;
}

int function_processing(const char** infix, stack_ty** operator_stack, int i) {
  int j;
  for (j = 0; j < num_functions; j++) {
    if (strncmp(*infix + i, functions[j], strlen(functions[j])) == 0) {
      char* function = (char*)malloc(sizeof(char) * strlen(functions[j]) + 1);
      strncpy(function, *infix + i, strlen(functions[j]));
      function[strlen(functions[j])] = '\0';
      push(operator_stack, 5, function, FUNCTION);
      i += strlen(functions[j]);
      break;
    }
  }
  if (j == num_functions) {
    i++;
  }
  return i;
}

int variable_processing(stack_ty*** postfix_stack, int i) {
  char* var = (char*)malloc(sizeof(*var) + 1);
  *var = 'x';
  var[1] = '\0';
  push(*postfix_stack, 3, var, VARIABLE);
  i++;
  return i;
}

int right_bracket_processing(stack_ty** operator_stack,
                             stack_ty** postfix_stack, char** operation,
                             int i) {
  while (*operator_stack != NULL && *(char*)((*operator_stack)->value) != '(') {
    int operator_priority_temp;
    void* operator_value;
    type_t operator_type;
    pop(operator_stack, &operator_priority_temp, &operator_value,
        &operator_type);
    push(postfix_stack, operator_priority_temp, operator_value, operator_type);
  }
  if (*operator_stack != NULL) {
    int operator_priority_temp;
    void* operator_value;
    type_t operator_type;
    pop(operator_stack, &operator_priority_temp, &operator_value,
        &operator_type);
    free(operator_value);
  }
  free(*operation);
  i++;
  return i;
}

int not_right_bracket_processing(int operation_priority,
                                 stack_ty** operator_stack,
                                 stack_ty** postfix_stack, char* operation,
                                 int i) {
  while (*operator_stack != NULL &&
         (operation_priority < (*operator_stack)->priority ||
          (operation_priority == (*operator_stack)->priority &&
           *operation != '^'))) {
    int operator_priority_temp;
    void* operator_value;
    type_t operator_type;
    pop(operator_stack, &operator_priority_temp, &operator_value,
        &operator_type);
    push(postfix_stack, operator_priority_temp, operator_value, operator_type);
  }
  push(operator_stack, operation_priority, operation, OPERATION);
  i++;
  return i;
}

void operator_stack_processing(stack_ty** operator_stack,
                               stack_ty** postfix_stack) {
  while (*operator_stack != NULL) {
    int operator_priority_temp;
    void* operator_value;
    type_t operator_type;
    pop(operator_stack, &operator_priority_temp, &operator_value,
        &operator_type);
    push(postfix_stack, operator_priority_temp, operator_value, operator_type);
  }
}
