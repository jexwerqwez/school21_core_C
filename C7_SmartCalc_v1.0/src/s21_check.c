#include "s21_check.h"

int is_valid_expression(const char* expression) {
  char *numbers_array = "0123456789.", *operations_array = "()+-*/^%";
  int length = strlen(expression), brackets = 0, flag = -1, exit_code = SUCCESS;
  if (expression[0] == '-' || expression[0] == '+') {
    flag = OPERATION;
  } else if (strchr(numbers_array, expression[0]) != NULL) {
    flag = NUMBER;
  } else if (expression[0] == 'x') {
    flag = VARIABLE;
  }
  exit_code = expression_processing(flag, length, exit_code, operations_array,
                                    numbers_array, expression, &brackets);
  exit_code = (brackets == 0 && exit_code != ERROR) ? SUCCESS : ERROR;
  return exit_code;
}

void flag_nember_proccessing(const char* expression, char* operations_array,
                             char* numbers_array, int* flag, int* exit_code,
                             int* i) {
  if (strchr(operations_array, expression[*i]) != NULL) {
    *flag = OPERATION;
  } else if (strchr(numbers_array, expression[*i]) != NULL) {
    *flag = NUMBER;
  } else if (expression[*i + 1] != '\0') {
    *exit_code = ERROR;
  }
}

void flag_function_processing(const char* expression, int* i, int* exit_code,
                              int* flag) {
  if (expression[*i + 1] != '(') {
    *exit_code = ERROR;
  } else {
    *flag = LBRACKET;
  }
}

int expression_processing(int flag, int length, int exit_code,
                          char* operations_array, char* numbers_array,
                          const char* expression, int* brackets) {
  for (int i = 0; i < length; i++) {
    if (exit_code == ERROR) {
      break;
    } else if (expression[i] == ' ' ||
               (i == 0 && flag != -1 && expression[i + 1] != '\0')) {
      continue;
    } else if (expression[i] == '/' && expression[i + 1] == '0' &&
               (expression[i + 2] != '.' ||
                strchr(numbers_array, expression[i + 3]) == NULL)) {
      exit_code = ERROR;
    } else if (expression[i + 1] == '\0' &&
               strchr(operations_array, expression[i]) != NULL &&
               expression[i] != ')') {
      exit_code = ERROR;
    } else if (expression[i] == '(') {
      (*brackets)++;
      flag = LBRACKET;
    } else if (expression[i] == ')') {
      if (brackets == 0 || ((expression[i + 1] == '\0') && flag == OPERATION)) {
        exit_code = ERROR;
      }
      (*brackets)--;
      flag = RBRACKET;
    } else if (is_function(expression, &i)) {
      flag_function_processing(expression, &i, &exit_code, &flag);
    } else if (flag == NUMBER) {
      flag_nember_proccessing(expression, operations_array, numbers_array,
                              &flag, &exit_code, &i);
    } else if ((flag == VARIABLE || flag == RBRACKET) &&
               (strchr(operations_array, expression[i]) != NULL)) {
      flag = OPERATION;
    } else if ((flag == LBRACKET || flag == OPERATION) &&
               is_function(expression, &i)) {
      flag = FUNCTION;
    } else if (flag == LBRACKET &&
               (expression[i] == '-' || expression[i] == '+')) {
      flag = OPERATION;
    } else if (((flag == LBRACKET || flag == OPERATION) &&
                (strchr(numbers_array, expression[i]) != NULL ||
                 expression[i] == 'x')) ||
               expression[i] == 'x') {
      flag = (expression[i] == 'x') ? VARIABLE : NUMBER;
    } else {
      exit_code = ERROR;
    }
  }
  return exit_code;
}

int is_function(const char* expression, int* index) {
  char* functions[] = {"sin",  "cos",  "tan", "asin", "acos",
                       "atan", "sqrt", "ln",  "log",  "mod"};
  int exit_code = ERROR;
  int num_functions = sizeof(functions) / sizeof(functions[0]);
  for (int i = 0; i < num_functions; i++) {
    int f_count = 0;
    for (int j = 0; j < (int)strlen(functions[i]); j++) {
      if (expression[*index + j] == functions[i][j]) {
        f_count++;
      }
    }
    if (f_count == (int)strlen(functions[i])) {
      exit_code = SUCCESS;
      *index += strlen(functions[i]) - 1;
      break;
    }
  }
  return exit_code;
}

void replace_mod(char* str) {
  char* search = "mod";
  char* replace = "%";
  char tmp[256] = "";
  char* pos = strstr(str, search);
  if (pos == NULL) {
    return;
  }
  strncpy(tmp, str, pos - str);
  strcat(tmp, replace);
  strcat(tmp, pos + strlen(search));
  strcpy(str, tmp);
}
