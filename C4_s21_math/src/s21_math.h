#ifndef _S21_MATH_H_
#define _S21_MATH_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define S21_PI 3.14159265358979323846264338327950288
#define S21_E 2.71828182845904523536028747135266250
#define S21_INF 1.0 / 0.0
#define S21_NINF -1.0 / 0.0
#define S21_EPS 1e-100
#define S21_NAN __builtin_nanf("")
#define S21_NNAN -S21_NAN
#define S21_MAX_DBL 1.7976931348623158e+308
#define ACCURACY 1000000
int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
#endif