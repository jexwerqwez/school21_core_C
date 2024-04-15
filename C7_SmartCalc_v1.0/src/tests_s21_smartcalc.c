#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_calculation.h"
#include "s21_check.h"

double build_expr(char* expr, double x) {
  stack_ty* input_stack = NULL;
  stack_ty* reversed_stack = NULL;
  double number = 0;
  replace_mod(expr);
  if (is_valid_expression(expr)) {
    parser(expr, &input_stack);
    reverse_stack(input_stack, &reversed_stack);
    number = calculate_rpn(&reversed_stack, x);
    // print_stack(input_stack);
    simple_destroy_stack(&input_stack);
    destroy_stack(&reversed_stack);
  } else {
    number = ERROR;
  }
  return number;
}

START_TEST(test_sin) {
  char expr[] = "sin(x)*x";
  for (double i = -10; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = sin(i) * i;
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_cos) {
  char expr[] = "-cos(x)";
  for (double i = -10; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = -cos(i);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_tan) {
  char* expr = "tan(x)/1/0.5";
  for (double i = -10; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = tan(i) / 1 / 0.5;
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_acos) {
  char* expr = "acos(x)-cos(x)";
  for (double i = -1; i < 1; i += 0.1) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = acos(i) - cos(i);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_asin) {
  char* expr = "asin(x) + 1";
  for (double i = -1; i < 1; i += 0.1) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = asin(i) + 1;
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_atan) {
  char* expr = "atan(x + 7)";
  for (double i = -10; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = atan(i + 7);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_sqrt) {
  char* expr = "sqrt(x * x * x)";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = sqrt(i * i * i);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_ln) {
  char* expr = "-ln(x)";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = -log(i);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_log) {
  char* expr = "+log(x)";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = +log10(i);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_plus) {
  char* expr = "+x+5+100000000000+142.4142412";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = i + 5 + 100000000000 + 142.4142412;
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_minus) {
  char* expr = "-x-5-(100000000000-142.4142412)";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = -i - 5 - (100000000000 - 142.4142412);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_div) {
  char* expr = "x/5/0.5/142.4142412";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = i / 5 / 0.5 / 142.4142412;
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_mul) {
  char* expr = "-x*(5*(0.00004*142.4142412))";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = -i * (5 * (0.00004 * 142.4142412));
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_pow) {
  char* expr = "x^2^0.1";
  double poww = pow(2, 0.1);
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = pow(i, poww);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_mod) {
  char expr[] = "19 mod x";
  for (int i = 1; i < 10; i++) {
    double s21_smartcalc_result = build_expr(expr, i);
    double math_result = 19 % i;
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_hard_expr1) {
  char* expr1 = "(sin(x))^2 + (cos(x))^2";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr1, i);
    double math_result = pow(sin(i), 2) + pow(cos(i), 2);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
  char* expr2 = "sin(x) + (sqrt(4^2))^3 - 3^x";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr2, i);
    double math_result = sin(i) + pow(sqrt(16), 3) - pow(3, i);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }
}
END_TEST

START_TEST(test_hard_expr2) {
  char* expr1 = "((2 + tan(x)) * ln(x) / sqrt(x)) ^ 2";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr1, i);
    double math_result = pow((((2 + tan(i)) * log(i)) / sqrt(i)), 2);
    ck_assert_double_eq(s21_smartcalc_result, math_result);
  }

  char* expr2 = "(2^2^2^2 - sqrt(5)/asin(0.5) - x)^(-1*log(2))";
  for (double i = 0; i < 10; i += 0.01) {
    double s21_smartcalc_result = build_expr(expr2, i);
    double math_result =
        pow((65536 - sqrt(5) / asin(0.5) - i), (-1 * log10(2)));
    ck_assert_ldouble_eq_tol(s21_smartcalc_result, math_result, 1e-7);
  }
}
END_TEST

START_TEST(test_error) {
  char* expr1 = "((()))";
  char* expr2 = "sin(x + 5";
  char* expr3 = "aatan";
  char* expr4 = "5+++5";
  char* expr5 = "a^";
  char* expr6 = "----x";
  char* expr7 = "(5+4+(4+4)";
  double s21_smartcalc_result = build_expr(expr1, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
  s21_smartcalc_result = build_expr(expr2, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
  s21_smartcalc_result = build_expr(expr3, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
  s21_smartcalc_result = build_expr(expr4, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
  s21_smartcalc_result = build_expr(expr5, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
  s21_smartcalc_result = build_expr(expr6, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
  s21_smartcalc_result = build_expr(expr7, 0);
  ck_assert_double_eq(s21_smartcalc_result, ERROR);
}
END_TEST

Suite* Create_suite() {
  Suite* suite = suite_create("s21_math tests");
  TCase* tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, test_sin);
  tcase_add_test(tcase_core, test_cos);
  tcase_add_test(tcase_core, test_tan);
  tcase_add_test(tcase_core, test_acos);
  tcase_add_test(tcase_core, test_asin);
  tcase_add_test(tcase_core, test_atan);
  tcase_add_test(tcase_core, test_sqrt);
  tcase_add_test(tcase_core, test_ln);
  tcase_add_test(tcase_core, test_log);
  tcase_add_test(tcase_core, test_plus);
  tcase_add_test(tcase_core, test_minus);
  tcase_add_test(tcase_core, test_mul);
  tcase_add_test(tcase_core, test_div);
  tcase_add_test(tcase_core, test_pow);
  tcase_add_test(tcase_core, test_mod);
  tcase_add_test(tcase_core, test_hard_expr1);
  tcase_add_test(tcase_core, test_hard_expr2);
  tcase_add_test(tcase_core, test_error);
  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite* suite = Create_suite();
  SRunner* suite_runner = srunner_create(suite);
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
