#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_math.h"

START_TEST(s21_abs_test) {
  int a = -0;
  int b = +5;
  int c = -1016835847;
  int d = 9876543;
  ck_assert_int_eq(s21_abs(a), abs(a));
  ck_assert_int_eq(s21_abs(b), abs(b));
  ck_assert_int_eq(s21_abs(c), abs(c));
  ck_assert_int_eq(s21_abs(d), abs(d));
}
END_TEST

START_TEST(s21_fabs_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -1234567891234567.12345678;
  double d = 9876543.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  ck_assert_ldouble_eq(s21_fabs(a), fabs(a));
  ck_assert_ldouble_eq(s21_fabs(b), fabs(b));
  ck_assert_ldouble_eq(s21_fabs(c), fabs(c));
  ck_assert_ldouble_eq(s21_fabs(d), fabs(d));
  ck_assert_ldouble_eq(s21_fabs(e), fabs(e));
  ck_assert_ldouble_eq(s21_fabs(-e), fabs(-e));
  ck_assert_double_nan(s21_fabs(f));
  ck_assert_double_nan(s21_fabs(-f));
}
END_TEST

START_TEST(s21_exp_test) {
  double a = -0.00000000000;
  double b = +0.12345678908765;
  double c = -1234567891234567.12345678;
  double d = 9876543.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  ck_assert_ldouble_eq_tol(s21_exp(a), exp(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(b), exp(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(c), exp(c), 1e-6);
  ck_assert_double_eq(s21_exp(d), exp(d));
  ck_assert_ldouble_eq(s21_exp(e), exp(e));
  ck_assert_ldouble_eq(s21_exp(-e), exp(-e));
  ck_assert_double_nan(s21_exp(f));
  ck_assert_ldouble_nan(s21_exp(-f));
}
END_TEST

START_TEST(s21_ceil_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -1234567891234567.12345678;
  double d = 9876549.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  ck_assert_ldouble_eq_tol(s21_ceil(a), ceil(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(b), ceil(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(c), ceil(c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_ceil(d), ceil(d), 1e-6);
  ck_assert_ldouble_eq(s21_ceil(e), ceil(e));
  ck_assert_ldouble_eq(s21_ceil(-e), ceil(-e));
  ck_assert_double_nan(s21_ceil(f));
  ck_assert_ldouble_nan(s21_ceil(-f));
}
END_TEST

START_TEST(s21_floor_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -1234567891234567.52345678;
  double d = 9876543.500000000;
  double e = S21_INF;
  double f = S21_NAN;
  ck_assert_ldouble_eq_tol(s21_floor(a), floor(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(b), floor(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(c), floor(c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(d), floor(d), 1e-6);
  ck_assert_ldouble_eq(s21_floor(e), floor(e));
  ck_assert_ldouble_eq(s21_floor(-e), floor(-e));
  ck_assert_double_nan(s21_floor(f));
  ck_assert_double_nan(s21_floor(-f));
}
END_TEST

START_TEST(s21_log_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -1234567891234567.12345678;
  double d = 9876543.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  double g = S21_E;
  ck_assert_ldouble_eq(s21_log(a), log(a));
  ck_assert_ldouble_eq_tol(s21_log(b), log(b), 1e-6);
  ck_assert_double_nan(s21_log(c));
  ck_assert_ldouble_eq_tol(s21_log(d), log(d), 1e-6);
  ck_assert_ldouble_eq(s21_log(e), log(e));
  ck_assert_ldouble_nan(s21_log(-e));
  ck_assert_double_nan(s21_log(f));
  ck_assert_double_nan(s21_log(-f));
  ck_assert_ldouble_eq_tol(s21_log(g), log(g), 1e-6);
  ck_assert_ldouble_nan(s21_log(-g));
}
END_TEST

START_TEST(s21_fmod_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -123456.123456;
  double d = 08654.4000000000;
  double e = S21_INF;
  double f = S21_NAN;
  ck_assert_double_nan(s21_fmod(a, a));
  ck_assert_ldouble_eq_tol(s21_fmod(a, b), fmod(a, b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(a, c), fmod(a, c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(a, d), fmod(a, d), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(a, e), fmod(a, e), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(a, -e), fmod(a, -e), 1e-6);
  ck_assert_double_nan(s21_fmod(a, f));
  ck_assert_double_nan(s21_fmod(a, -f));

  ck_assert_double_nan(s21_fmod(b, a));
  ck_assert_ldouble_eq_tol(s21_fmod(b, b), fmod(b, b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(b, c), fmod(b, c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(b, d), fmod(b, d), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(b, e), fmod(b, e), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(b, -e), fmod(b, -e), 1e-6);
  ck_assert_double_nan(s21_fmod(b, f));
  ck_assert_double_nan(s21_fmod(b, -f));

  ck_assert_double_nan(s21_fmod(c, a));
  ck_assert_ldouble_eq_tol(s21_fmod(c, b), fmod(c, b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(c, c), fmod(c, c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(c, d), fmod(c, d), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(c, e), fmod(c, e), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(c, -e), fmod(c, -e), 1e-6);
  ck_assert_double_nan(s21_fmod(c, f));
  ck_assert_double_nan(s21_fmod(c, -f));

  ck_assert_double_nan(s21_fmod(d, a));
  ck_assert_ldouble_eq_tol(s21_fmod(d, b), fmod(d, b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(d, c), fmod(d, c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(d, d), fmod(d, d), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(d, e), fmod(d, e), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(d, -e), fmod(d, -e), 1e-6);
  ck_assert_double_nan(s21_fmod(d, f));
  ck_assert_double_nan(s21_fmod(d, -f));

  ck_assert_double_nan(s21_fmod(e, a));
  ck_assert_double_nan(s21_fmod(-e, a));
  ck_assert_double_nan(s21_fmod(e, b));
  ck_assert_double_nan(s21_fmod(-e, b));
  ck_assert_double_nan(s21_fmod(e, c));
  ck_assert_double_nan(s21_fmod(-e, c));
  ck_assert_double_nan(s21_fmod(e, d));
  ck_assert_double_nan(s21_fmod(-e, d));
  ck_assert_double_nan(s21_fmod(e, e));
  ck_assert_double_nan(s21_fmod(e, -e));
  ck_assert_double_nan(s21_fmod(e, f));

  ck_assert_double_nan(s21_fmod(f, a));
  ck_assert_double_nan(s21_fmod(f, b));
  ck_assert_double_nan(s21_fmod(f, c));
  ck_assert_double_nan(s21_fmod(f, d));
  ck_assert_double_nan(s21_fmod(-f, d));
  ck_assert_double_nan(s21_fmod(-f, -d));
  ck_assert_double_nan(s21_fmod(f, e));
  ck_assert_double_nan(s21_fmod(f, f));
}
END_TEST

START_TEST(s21_pow_test) {
  double a = -0.00000000000;
  double b = -124.12345678908765;
  double c = -1234567891234567.12345678;
  double d = 987654.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  double g = 2.4;
  ck_assert_ldouble_eq_tol(s21_pow(a, a), pow(a, a), 1e-6);
  ck_assert_ldouble_eq(s21_pow(a, b), pow(a, b));
  ck_assert_ldouble_eq(s21_pow(a, c), pow(a, c));
  ck_assert_ldouble_eq_tol(s21_pow(a, d), pow(a, d), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(a, e), pow(a, e), 1e-6);
  ck_assert_ldouble_eq(s21_pow(a, -e), pow(a, -e));
  ck_assert_double_nan(s21_pow(a, f));
  ck_assert_double_nan(s21_pow(a, -f));
  ck_assert_ldouble_eq_tol(s21_pow(a, g), pow(a, g), 1e-6);

  ck_assert_ldouble_eq_tol(s21_pow(b, a), pow(b, a), 1e-6);
  ck_assert_ldouble_nan(s21_pow(b, b));
  ck_assert_ldouble_eq_tol(s21_pow(b, c), pow(b, c), 1e-6);
  ck_assert_ldouble_eq(s21_pow(b, d), pow(b, d));
  ck_assert_ldouble_eq(s21_pow(b, e), pow(b, e));
  ck_assert_ldouble_eq(s21_pow(b, -e), pow(b, -e));
  ck_assert_double_nan(s21_pow(b, f));
  ck_assert_double_nan(s21_pow(b, -f));
  ck_assert_ldouble_nan(s21_pow(b, g));

  ck_assert_ldouble_eq_tol(s21_pow(c, a), pow(c, a), 1e-6);
  ck_assert_ldouble_nan(s21_pow(c, b));
  ck_assert_ldouble_eq_tol(s21_pow(c, c), pow(c, c), 1e-6);
  ck_assert_ldouble_eq(s21_pow(c, d), pow(c, d));
  ck_assert_ldouble_eq(s21_pow(c, e), pow(c, e));
  ck_assert_ldouble_eq(s21_pow(c, -e), pow(c, -e));
  ck_assert_double_nan(s21_pow(c, f));
  ck_assert_double_nan(s21_pow(c, -f));
  ck_assert_ldouble_nan(s21_pow(c, g));

  ck_assert_ldouble_eq_tol(s21_pow(d, a), pow(d, a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(d, b), pow(d, b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(d, c), pow(d, c), 1e-6);
  ck_assert_ldouble_eq(s21_pow(d, d), pow(d, d));
  ck_assert_ldouble_eq(s21_pow(d, e), pow(d, e));
  ck_assert_ldouble_eq(s21_pow(d, -e), pow(d, -e));
  ck_assert_double_nan(s21_pow(d, f));
  ck_assert_double_nan(s21_pow(d, -f));

  ck_assert_ldouble_eq_tol(s21_pow(e, a), pow(e, a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(e, b), pow(e, b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(e, c), pow(e, c), 1e-6);
  ck_assert_ldouble_eq(s21_pow(e, d), pow(e, d));
  ck_assert_ldouble_eq(s21_pow(e, e), pow(e, e));
  ck_assert_ldouble_eq(s21_pow(e, -e), pow(e, -e));
  ck_assert_double_nan(s21_pow(e, f));
  ck_assert_double_nan(s21_pow(e, -f));
  ck_assert_ldouble_eq(s21_pow(e, g), pow(e, g));
  ck_assert_ldouble_eq(s21_pow(-e, g), pow(-e, g));
}
END_TEST

START_TEST(s21_sin_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -234790.123456;
  double d = 123456;
  double e = -S21_INF;
  double f = S21_NAN;
  double g = S21_PI / 2;
  ck_assert_ldouble_eq_tol(s21_sin(a), sin(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(b), sin(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(c), sin(c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(d), sin(d), 1e-6);
  ck_assert_double_nan(s21_sin(e));
  ck_assert_double_nan(s21_sin(f));
  ck_assert_ldouble_eq_tol(s21_sin(g), sin(g), 1e-6);
  for (double i = -2 * S21_PI; i <= 2 * S21_PI; i += 0.01)
    ck_assert_ldouble_eq_tol(s21_sin(i), sin(i), 1e-6);
}
END_TEST

START_TEST(s21_cos_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -2347.123456;
  double d = 98765.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  double g = S21_PI / 2.0;
  ck_assert_ldouble_eq_tol(s21_cos(a), cos(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(b), cos(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(c), cos(c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(d), cos(d), 1e-6);
  ck_assert_double_nan(s21_cos(e));
  ck_assert_double_nan(s21_cos(f));
  ck_assert_ldouble_eq_tol(s21_cos(g), cos(g), 1e-6);
  for (double i = -2 * S21_PI; i <= 2 * S21_PI; i += 0.01)
    ck_assert_ldouble_eq_tol(s21_cos(i), cos(i), 1e-6);
}
END_TEST

START_TEST(s21_sqrt_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -1234567891234567.12345678;
  double d = 9876543.000000000;
  double e = S21_INF;
  double f = S21_NAN;
  ck_assert_ldouble_eq_tol(s21_sqrt(a), sqrt(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(b), sqrt(b), 1e-6);
  ck_assert_double_nan(s21_sqrt(c));
  ck_assert_ldouble_eq_tol(s21_sqrt(d), sqrt(d), 1e-6);
  ck_assert_ldouble_eq(s21_sqrt(e), sqrt(e));
  ck_assert_double_nan(s21_sqrt(f));
}
END_TEST

START_TEST(s21_tan_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -2347.123456;
  double d = 01234.000000000;
  double e = -S21_INF;
  double f = S21_NAN;
  double g = S21_PI / 2.0;
  double h = 1.0;
  ck_assert_ldouble_eq_tol(s21_tan(a), tan(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(b), tan(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(c), tan(c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(d), tan(d), 1e-6);
  ck_assert_ldouble_nan(s21_tan(e));
  ck_assert_ldouble_nan(s21_tan(f));
  ck_assert_ldouble_eq_tol(s21_tan(g), tan(g), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-g), tan(-g), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(h), tan(h), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-h), tan(-h), 1e-6);
  for (double i = -2 * S21_PI; i <= 2 * S21_PI; i += 0.01)
    ck_assert_ldouble_eq_tol(s21_tan(i), tan(i), 1e-6);
}

START_TEST(s21_asin_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -234790.123456;
  double d = 1.0;
  double e = -S21_INF;
  double f = S21_NAN;
  double g = -0.987654321;
  ck_assert_ldouble_eq_tol(s21_asin(a), asin(a), 1e-6);
  ck_assert_ldouble_nan(s21_asin(b));
  ck_assert_ldouble_nan(s21_asin(c));
  ck_assert_ldouble_eq_tol(s21_asin(d), asin(d), 1e-6);
  ck_assert_double_nan(s21_asin(e));
  ck_assert_double_nan(s21_asin(f));
  ck_assert_ldouble_eq_tol(s21_asin(g), asin(g), 1e-6);
}
END_TEST

START_TEST(s21_atan_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -234790.123456;
  double d = 123456.000000;
  double e = -S21_INF;
  double f = S21_NAN;
  double g = S21_PI / 2.0;
  double h = 1.0;
  ck_assert_ldouble_eq_tol(s21_atan(a), atan(a), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(b), atan(b), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(c), atan(c), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(d), atan(d), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(e), atan(e), 1e-6);
  ck_assert_ldouble_nan(s21_atan(f));
  ck_assert_ldouble_nan(s21_atan(-f));
  ck_assert_ldouble_eq_tol(s21_atan(g), atan(g), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-g), atan(-g), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(h), atan(h), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-h), atan(-h), 1e-6);
}
END_TEST

START_TEST(s21_acos_test) {
  double a = -0.00000000000;
  double b = +5.12345678908765;
  double c = -234790.123456;
  double d = S21_PI / 4.0;
  double e = -S21_INF;
  double f = S21_NAN;
  double g = -0.00987654321;
  ck_assert_ldouble_eq_tol(s21_acos(a), acos(a), 1e-6);
  ck_assert_ldouble_nan(s21_acos(b));
  ck_assert_ldouble_nan(s21_acos(c));
  ck_assert_ldouble_eq_tol(s21_acos(d), acos(d), 1e-6);
  ck_assert_double_nan(s21_acos(e));
  ck_assert_double_nan(s21_acos(f));
  ck_assert_ldouble_eq_tol(s21_acos(g), acos(g), 1e-6);
}
END_TEST

Suite *Create_suite() {
  Suite *suite = suite_create("s21_math tests");
  TCase *tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, s21_abs_test);
  tcase_add_test(tcase_core, s21_fabs_test);
  tcase_add_test(tcase_core, s21_exp_test);
  tcase_add_test(tcase_core, s21_ceil_test);
  tcase_add_test(tcase_core, s21_floor_test);
  tcase_add_test(tcase_core, s21_log_test);
  tcase_add_test(tcase_core, s21_fmod_test);
  tcase_add_test(tcase_core, s21_pow_test);
  tcase_add_test(tcase_core, s21_sqrt_test);
  tcase_add_test(tcase_core, s21_sin_test);
  tcase_add_test(tcase_core, s21_cos_test);
  tcase_add_test(tcase_core, s21_tan_test);
  tcase_add_test(tcase_core, s21_asin_test);
  tcase_add_test(tcase_core, s21_acos_test);
  tcase_add_test(tcase_core, s21_atan_test);
  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = Create_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  if (failed_count != 0) {
    printf("Failed tests: %d\n", failed_count);
    return EXIT_FAILURE;
  } else {
    printf("Success\n");
  }
  return EXIT_SUCCESS;
}
