#include <check.h>

#include "s21_matrix.h"

void s21_init_matrix(double count, matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; count++, j++) A->matrix[i][j] = count;
  }
}

START_TEST(s21_create_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);

  res = s21_create_matrix(-5, 5, &A);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);

  res = s21_create_matrix(5, -5, &A);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);

  res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);

  res = s21_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);

  res = s21_create_matrix(5, 0, &A);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);

  res = s21_create_matrix(7, 7, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);

  res = s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);

  res = s21_create_matrix(2, 14, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_remove_matrix_test) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(6, 6, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = MATRIX_ERROR;
  }
  ck_assert_int_eq(res, OK);

  res = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = MATRIX_ERROR;
  }
  ck_assert_int_eq(res, OK);

  res = s21_create_matrix(3, 12, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = MATRIX_ERROR;
  }
  ck_assert_int_eq(res, OK);

  res = s21_create_matrix(12, 3, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = MATRIX_ERROR;
  }
  ck_assert_int_eq(res, OK);

  res = s21_create_matrix(-1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, MATRIX_ERROR);
}
END_TEST

START_TEST(s21_eq_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_init_matrix(12.555, &A);

  s21_create_matrix(3, 2, &B);
  s21_init_matrix(12.555, &B);

  res = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(res, SUCCESS);

  B.matrix[2][1] = 7;

  res = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(res, FAILURE);

  s21_init_matrix(12.555, &A);
  s21_init_matrix(-12.555, &B);
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_create_matrix(3, 2, &A);
  s21_init_matrix(0, &A);

  s21_create_matrix(2, 3, &B);
  s21_init_matrix(0, &B);

  res = s21_eq_matrix(&B, &A);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_sum_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);
  double count = 2;
  for (int i = 0; i < X.rows; i++) {
    for (int j = 0; j < X.columns; j++) {
      X.matrix[i][j] = count;
      count += 2;
    }
  }

  res = s21_eq_matrix(&X, &Z);
  ck_assert_int_eq(res, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(-3.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(5.0, &B);

  s21_sum_matrix(&A, &B, &Z);
  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);

  s21_create_matrix(4, 2, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 2, &B);
  s21_init_matrix(1.0, &B);

  s21_sum_matrix(&A, &B, &Z);

  s21_create_matrix(4, 2, &X);
  count = 2;
  for (int i = 0; i < X.rows; i++) {
    for (int j = 0; j < X.columns; j++) {
      X.matrix[i][j] = count;
      count += 2;
    }
  }

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sum_matrix_err) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 2, &A);

  s21_create_matrix(4, 3, &B);

  res = s21_sum_matrix(&A, &B, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, CALC_ERROR);

  s21_create_matrix(-4, -2, &A);

  s21_create_matrix(4, 3, &B);

  res = s21_sum_matrix(&A, &B, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, CALC_ERROR);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_sub_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  for (int i = 0; i < X.rows; i++) {
    for (int j = 0; j < X.columns; j++) {
      X.matrix[i][j] = 0;
    }
  }

  res = s21_eq_matrix(&X, &Z);
  ck_assert_int_eq(res, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  s21_init_matrix(-3.0, &A);
  s21_init_matrix(5.0, &B);
  s21_sub_matrix(&A, &B, &Z);

  for (int i = 0; i < X.rows; i++) {
    for (int j = 0; j < X.columns; j++) {
      X.matrix[i][j] = -8;
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);

  s21_create_matrix(4, 2, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 2, &B);
  s21_init_matrix(1.0, &B);

  s21_sub_matrix(&A, &B, &Z);

  s21_create_matrix(4, 2, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 0.0;
  X.matrix[1][0] = 0.0;
  X.matrix[1][1] = 0.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 0.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 0.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);

  s21_create_matrix(4, 2, &A);
  s21_init_matrix(-1.0, &A);

  s21_create_matrix(4, 2, &B);
  s21_init_matrix(3.0, &B);

  s21_sub_matrix(&A, &B, &Z);

  s21_create_matrix(4, 2, &X);

  X.matrix[0][0] = -4.0;
  X.matrix[0][1] = -4.0;
  X.matrix[1][0] = -4.0;
  X.matrix[1][1] = -4.0;
  X.matrix[2][0] = -4.0;
  X.matrix[2][1] = -4.0;
  X.matrix[3][0] = -4.0;
  X.matrix[3][1] = -4.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_sub_matrix_err) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 2, &A);

  s21_create_matrix(4, 3, &B);

  res = s21_sub_matrix(&A, &B, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, CALC_ERROR);
}
END_TEST

START_TEST(s21_mult_number_test1) {
  int res = 0;
  double number = 3.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);

  s21_init_matrix(1.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(4, 4, &X);

  double count = 3;
  for (int i = 0; i < X.rows; i++) {
    for (int j = 0; j < X.columns; j++) {
      X.matrix[i][j] = count;
      count += 3;
    }
  }

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_test2) {
  int res = 0;
  double number = 5.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 5.0;
  X.matrix[0][1] = 10.0;
  X.matrix[0][2] = 15.0;
  X.matrix[0][3] = 20.0;
  X.matrix[1][0] = 25.0;
  X.matrix[1][1] = 30.0;
  X.matrix[1][2] = 35.0;
  X.matrix[1][3] = 40.0;
  X.matrix[2][0] = 45.0;
  X.matrix[2][1] = 50.0;
  X.matrix[2][2] = 55.0;
  X.matrix[2][3] = 60.0;
  X.matrix[3][0] = 65.0;
  X.matrix[3][1] = 70.0;
  X.matrix[3][2] = 75.0;
  X.matrix[3][3] = 80.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_test3) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 2, &A);
  s21_init_matrix(2.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(4, 2, &X);

  X.matrix[0][0] = 4.0;
  X.matrix[0][1] = 6.0;
  X.matrix[1][0] = 8.0;
  X.matrix[1][1] = 10.0;
  X.matrix[2][0] = 12.0;
  X.matrix[2][1] = 14.0;
  X.matrix[3][0] = 16.0;
  X.matrix[3][1] = 18.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_test4) {
  int res = 0;
  double number = -2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 2, &A);
  s21_init_matrix(2.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(4, 2, &X);

  X.matrix[0][0] = -4.0;
  X.matrix[0][1] = -6.0;
  X.matrix[1][0] = -8.0;
  X.matrix[1][1] = -10.0;
  X.matrix[2][0] = -12.0;
  X.matrix[2][1] = -14.0;
  X.matrix[3][0] = -16.0;
  X.matrix[3][1] = -18.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_test5) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(1, 1, &A);
  s21_init_matrix(2.0, &A);

  s21_mult_number(&A, number, &Z);

  s21_create_matrix(1, 1, &X);

  X.matrix[0][0] = 4.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_number_test6) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(0, 0, &A);

  res = s21_mult_number(&A, number, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, MATRIX_ERROR);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 90.0;
  X.matrix[0][1] = 100.0;
  X.matrix[0][2] = 110.0;
  X.matrix[0][3] = 120.0;
  X.matrix[1][0] = 202.0;
  X.matrix[1][1] = 228.0;
  X.matrix[1][2] = 254.0;
  X.matrix[1][3] = 280.0;
  X.matrix[2][0] = 314.0;
  X.matrix[2][1] = 356.0;
  X.matrix[2][2] = 398.0;
  X.matrix[2][3] = 440.0;
  X.matrix[3][0] = 426.0;
  X.matrix[3][1] = 484.0;
  X.matrix[3][2] = 542.0;
  X.matrix[3][3] = 600.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);

  s21_create_matrix(4, 4, &A);
  s21_init_matrix(1.0, &A);

  s21_create_matrix(4, 4, &B);
  s21_init_matrix(-5.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 30.0;
  X.matrix[0][1] = 40.0;
  X.matrix[0][2] = 50.0;
  X.matrix[0][3] = 60.0;
  X.matrix[1][0] = 46.0;
  X.matrix[1][1] = 72.0;
  X.matrix[1][2] = 98.0;
  X.matrix[1][3] = 124.0;
  X.matrix[2][0] = 62.0;
  X.matrix[2][1] = 104.0;
  X.matrix[2][2] = 146.0;
  X.matrix[2][3] = 188.0;
  X.matrix[3][0] = 78.0;
  X.matrix[3][1] = 136.0;
  X.matrix[3][2] = 194.0;
  X.matrix[3][3] = 252.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);

  s21_create_matrix(4, 2, &A);
  s21_init_matrix(-5.0, &A);

  s21_create_matrix(2, 4, &B);
  s21_init_matrix(1.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = -25.0;
  X.matrix[0][1] = -34.0;
  X.matrix[0][2] = -43.0;
  X.matrix[0][3] = -52.0;
  X.matrix[1][0] = -13.0;
  X.matrix[1][1] = -18.0;
  X.matrix[1][2] = -23.0;
  X.matrix[1][3] = -28.0;
  X.matrix[2][0] = -1.0;
  X.matrix[2][1] = -2.0;
  X.matrix[2][2] = -3.0;
  X.matrix[2][3] = -4.0;
  X.matrix[3][0] = 11.0;
  X.matrix[3][1] = 14.0;
  X.matrix[3][2] = 17.0;
  X.matrix[3][3] = 20.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);

  s21_create_matrix(1, 1, &A);
  s21_init_matrix(-5.0, &A);

  s21_create_matrix(1, 1, &B);
  s21_init_matrix(1.0, &B);

  s21_mult_matrix(&A, &B, &Z);

  s21_create_matrix(1, 1, &X);

  X.matrix[0][0] = -5.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_mult_matrix_err) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  res = s21_mult_matrix(&A, &B, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, MATRIX_ERROR);

  s21_create_matrix(2, 3, &A);
  s21_init_matrix(-5.0, &A);

  s21_create_matrix(2, 2, &B);
  s21_init_matrix(1.0, &B);

  res = s21_mult_matrix(&A, &B, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, CALC_ERROR);
}
END_TEST

START_TEST(s21_transpose_test1) {
  int res = 0;
  matrix_t A = {0};

  res = s21_transpose(&A, &A);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_transpose_test2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 4, &A);
  s21_init_matrix(1.0, &A);
  res = s21_transpose(&A, &B);
  res = s21_eq_matrix(&A, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_transpose_test3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t T = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 3, &A);
  s21_init_matrix(1.0, &A);
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 5.0;
  B.matrix[2][0] = 3.0;
  B.matrix[2][1] = 6.0;

  res = s21_transpose(&A, &T);
  res = s21_eq_matrix(&T, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&T);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_determinant_test1) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {NULL, 0, 0};

  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, MATRIX_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test2) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);

  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test3) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(1, 1, &A);
  s21_init_matrix(1.0, &A);

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, 1.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test4) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = -677700.0;
  A.matrix[0][1] = 654.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = -0.00001;

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, -1301.223);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test5) {
  double determ = 0.0;
  matrix_t A = {0};

  s21_create_matrix(8, 8, &A);
  s21_init_matrix(1.0, &A);

  s21_determinant(&A, &determ);
  ck_assert_double_eq(determ, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_test1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 112.0;
  A.matrix[0][1] = 243.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = -8.0;
  A.matrix[1][0] = 47.0;
  A.matrix[1][1] = 51.0;
  A.matrix[1][2] = -66.0;
  A.matrix[1][3] = 99.0;
  A.matrix[2][0] = -74.0;
  A.matrix[2][1] = 85.0;
  A.matrix[2][2] = 97.0;
  A.matrix[2][3] = 63.0;
  A.matrix[3][0] = -13.0;
  A.matrix[3][1] = 79.0;
  A.matrix[3][2] = -99.0;
  A.matrix[3][3] = -121.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = -2879514.0;
  X.matrix[0][1] = -1236631.0;
  X.matrix[0][2] = -1685096.0;
  X.matrix[0][3] = 880697.0;
  X.matrix[1][0] = 1162090.0;
  X.matrix[1][1] = -714015.0;
  X.matrix[1][2] = 4046255.0;
  X.matrix[1][3] = -3901600.0;
  X.matrix[2][0] = 4362897.0;
  X.matrix[2][1] = -2049432.0;
  X.matrix[2][2] = -532912.0;
  X.matrix[2][3] = -1370781.0;
  X.matrix[3][0] = 3412773.0;
  X.matrix[3][1] = -1569493.0;
  X.matrix[3][2] = 3144517.0;
  X.matrix[3][3] = 1284666.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_calc_complements_test2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = -30.0;
  X.matrix[0][2] = -108.0;
  X.matrix[0][3] = 106.0;
  X.matrix[1][0] = 138.0;
  X.matrix[1][1] = -726.0;
  X.matrix[1][2] = -1137.0;
  X.matrix[1][3] = 1061.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 12.0;
  X.matrix[2][2] = 57.0;
  X.matrix[2][3] = -47.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 6.0;
  X.matrix[3][2] = -75.0;
  X.matrix[3][3] = 57.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_calc_complements_test3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 3, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;

  res = s21_calc_complements(&A, &Z);

  s21_remove_matrix(&A);

  ck_assert_int_eq(res, CALC_ERROR);
}
END_TEST

START_TEST(s21_calc_complements_test4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  res = s21_calc_complements(&A, &Z);

  ck_assert_int_eq(res, MATRIX_ERROR);
}
END_TEST

START_TEST(s21_inverse_matrix_test1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 1.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = -5.0 / 23.0;
  X.matrix[1][1] = -121.0 / 23.0;
  X.matrix[1][2] = 2.0 / 23.0;
  X.matrix[1][3] = 1.0 / 23.0;
  X.matrix[2][0] = -18.0 / 23.0;
  X.matrix[2][1] = -379.0 / 46.0;
  X.matrix[2][2] = 19.0 / 46.0;
  X.matrix[2][3] = -25.0 / 46.0;
  X.matrix[3][0] = 53.0 / 69.0;
  X.matrix[3][1] = 1061.0 / 138.0;
  X.matrix[3][2] = -47.0 / 138.0;
  X.matrix[3][3] = 19.0 / 46.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&Z);
  s21_remove_matrix(&A);
  s21_remove_matrix(&X);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_inverse_matrix_test2) {
  int res;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2;

  res = s21_inverse_matrix(&A, &Z);

  ck_assert_int_eq(Z.matrix[0][0] == (1.0 / A.matrix[0][0]), 1);
  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&Z);
}
END_TEST

START_TEST(s21_inverse_matrix_test3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 3, &A);
  s21_init_matrix(1.0, &A);

  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 2, &A);
  s21_init_matrix(1.0, &A);

  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 3, &A);
  s21_init_matrix(1.0, &A);
  s21_remove_matrix(&A);

  res = s21_inverse_matrix(&A, &Z);

  ck_assert_int_eq(res, MATRIX_ERROR);
}
END_TEST

START_TEST(s21_inverse_matrix_test6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 8.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(3, 3, &X);

  X.matrix[0][0] = -3.0 / 5.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 1.0 / 5.0;
  ;
  X.matrix[1][0] = -4.0 / 5.0;
  X.matrix[1][1] = 1.0;
  X.matrix[1][2] = -2.0 / 5.0;
  X.matrix[2][0] = 16.0 / 15.0;
  X.matrix[2][1] = -2.0 / 3.0;
  X.matrix[2][2] = 1.0 / 5.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, s21_create_matrix_test);

  tcase_add_test(tc_core, s21_remove_matrix_test);

  tcase_add_test(tc_core, s21_eq_matrix_test);

  tcase_add_test(tc_core, s21_sum_matrix_test);
  tcase_add_test(tc_core, s21_sum_matrix_err);

  tcase_add_test(tc_core, s21_sub_matrix_test);
  tcase_add_test(tc_core, s21_sub_matrix_err);

  tcase_add_test(tc_core, s21_mult_number_test1);
  tcase_add_test(tc_core, s21_mult_number_test2);
  tcase_add_test(tc_core, s21_mult_number_test3);
  tcase_add_test(tc_core, s21_mult_number_test4);
  tcase_add_test(tc_core, s21_mult_number_test5);
  tcase_add_test(tc_core, s21_mult_number_test6);

  tcase_add_test(tc_core, s21_mult_matrix_test);
  tcase_add_test(tc_core, s21_mult_matrix_err);

  tcase_add_test(tc_core, s21_transpose_test1);
  tcase_add_test(tc_core, s21_transpose_test2);
  tcase_add_test(tc_core, s21_transpose_test3);

  tcase_add_test(tc_core, s21_determinant_test1);
  tcase_add_test(tc_core, s21_determinant_test2);
  tcase_add_test(tc_core, s21_determinant_test3);
  tcase_add_test(tc_core, s21_determinant_test4);
  tcase_add_test(tc_core, s21_determinant_test5);

  tcase_add_test(tc_core, s21_calc_complements_test1);
  tcase_add_test(tc_core, s21_calc_complements_test2);
  tcase_add_test(tc_core, s21_calc_complements_test3);
  tcase_add_test(tc_core, s21_calc_complements_test4);

  tcase_add_test(tc_core, s21_inverse_matrix_test1);
  tcase_add_test(tc_core, s21_inverse_matrix_test2);
  tcase_add_test(tc_core, s21_inverse_matrix_test3);
  tcase_add_test(tc_core, s21_inverse_matrix_test4);
  tcase_add_test(tc_core, s21_inverse_matrix_test5);
  tcase_add_test(tc_core, s21_inverse_matrix_test6);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}