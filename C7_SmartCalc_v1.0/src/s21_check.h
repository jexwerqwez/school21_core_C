#ifndef SRC_S21_CHECK_H_
#define SRC_S21_CHECK_H_
#include <ctype.h>
#include <stdio.h>

#include "string.h"

#define SUCCESS 1
#define ERROR 0
#define NUMBER 2
#define VARIABLE 3
#define FUNCTION 4
#define OPERATION 5
#define RBRACKET 6
#define LBRACKET 7

void flag_nember_proccessing(const char*, char*, char*, int*, int*, int*);
void flag_function_processing(const char*, int*, int*, int*);
int expression_processing(int, int, int, char*, char*, const char*, int*);
int is_function(const char*, int*);
void replace_mod(char*);
int is_valid_expression(const char*);

#endif
