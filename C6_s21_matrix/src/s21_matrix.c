#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_flag = CALC_ERROR;
  if (rows > 0 && columns > 0) {
    if ((result->matrix = (double **)malloc(rows * sizeof(double *)))) {
      result->rows = rows;
      result->columns = columns;
      for (int i = 0; i < rows; i++) {
        if (!(result->matrix[i] = (double *)malloc(columns * sizeof(double)))) {
          for (int k = 0; k < i; k++) free(result->matrix[k]);
          free(result->matrix);
          return_flag = MATRIX_ERROR;
        }
      }
    }
    if (return_flag == CALC_ERROR) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = 0;
        }
      }
      return_flag = OK;
    }
  } else {
    return_flag = MATRIX_ERROR;
  }
  return return_flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}