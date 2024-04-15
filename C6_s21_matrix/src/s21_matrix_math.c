#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int neq_flag = FAILURE;
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          neq_flag = FAILURE;
          break;
        } else {
          neq_flag = SUCCESS;
        }
        if (neq_flag == FAILURE) {
          break;
        }
      }
    }
  }
  return neq_flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_flag = CALC_ERROR;
  short is_onesize = (A->rows == B->rows) && (A->columns == B->columns);
  if (is_onesize && (s21_create_matrix(A->rows, A->columns, result) == OK)) {
    ret_flag = OK;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return ret_flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_flag = CALC_ERROR;
  short is_onesize = (A->rows == B->rows) && (A->columns == B->columns);
  if (is_onesize && (s21_create_matrix(A->rows, A->columns, result) == OK)) {
    ret_flag = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return ret_flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret_flag = MATRIX_ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    ret_flag = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return ret_flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_flag = CALC_ERROR;
  int is_null = OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    ret_flag = MATRIX_ERROR;
    is_null = 1;
  }
  if ((A->columns == B->rows) &&
      (s21_create_matrix(A->rows, B->columns, result) == OK) && !is_null) {
    ret_flag = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return ret_flag;
}
