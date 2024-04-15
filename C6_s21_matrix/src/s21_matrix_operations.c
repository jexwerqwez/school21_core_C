#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret_flag = CALC_ERROR;
  int is_null = OK;
  if (A == NULL || A->matrix == NULL) {
    ret_flag = MATRIX_ERROR;
    is_null = 1;
  }
  if (s21_create_matrix(A->columns, A->rows, result) == OK && !is_null) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
    ret_flag = OK;
  }
  return ret_flag;
}

int s21_calc_minor(matrix_t *A, int row, int col, matrix_t *minor) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int minor_row = 0;
  for (int k = 0; k < num_rows; k++) {
    if (k == row) {
      continue;
    }
    int minor_col = 0;
    for (int l = 0; l < num_columns; l++) {
      if (l == col) {
        continue;
      }
      minor->matrix[minor_row][minor_col] = A->matrix[k][l];
      minor_col++;
    }
    minor_row++;
  }
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int flag = CALC_ERROR;
  if (A == NULL || A->matrix == NULL) {
    flag = MATRIX_ERROR;
  } else if (num_rows == num_columns) {
    s21_create_matrix(A->rows, A->columns, result);
    flag = OK;
    if (num_rows == 1) {
      result->matrix[0][0] = 1.0;
    } else {
      for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
          matrix_t minor = {0};
          if (s21_create_matrix(num_rows - 1, num_columns - 1, &minor) != OK) {
            flag = MATRIX_ERROR;
            break;
          }
          if (s21_calc_minor(A, i, j, &minor) != OK) {
            flag = MATRIX_ERROR;
            s21_remove_matrix(&minor);
            break;
          }
          double minor_determinant = 0;
          if (s21_determinant(&minor, &minor_determinant) != OK) {
            flag = MATRIX_ERROR;
            s21_remove_matrix(&minor);
            break;
          }
          s21_remove_matrix(&minor);
          double complement = pow(-1, i + j) * minor_determinant;
          result->matrix[i][j] = complement;
        }
        if (flag != OK) {
          break;
        }
      }
    }
  }
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int flag = MATRIX_ERROR;
  if (num_rows != num_columns) {
    flag = CALC_ERROR;
  } else {
    *result = 0;
    if (num_rows == 1) {
      *result = A->matrix[0][0];
      flag = OK;
    } else {
      int sign = 1;
      for (int i = 0; i < num_rows; i++) {
        matrix_t minor = {0};
        if (s21_create_matrix(num_rows - 1, num_columns - 1, &minor) == OK) {
          if (s21_calc_minor(A, i, 0, &minor) != OK) {
            flag = MATRIX_ERROR;
            s21_remove_matrix(&minor);
            break;
          }
          double minor_determinant = 0;
          if (s21_determinant(&minor, &minor_determinant) != OK) {
            flag = MATRIX_ERROR;
            s21_remove_matrix(&minor);
            break;
          }
          s21_remove_matrix(&minor);
          flag = OK;
          *result += sign * A->matrix[i][0] * minor_determinant;
          sign *= -1;
        }
      }
    }
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int flag = MATRIX_ERROR;
  if (num_rows != num_columns) {
    flag = CALC_ERROR;
  } else if (A != NULL && A->matrix != NULL && A->rows >= 0 &&
             A->columns >= 0) {
    double determinant = 0;
    if (s21_determinant(A, &determinant) != OK || fabs(determinant) < 1e-6) {
      flag = CALC_ERROR;
    } else {
      matrix_t complements = {0}, transposed_complements = {0};
      flag = OK;
      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transposed_complements);
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] =
              transposed_complements.matrix[i][j] / determinant;
        }
      }
      s21_remove_matrix(&complements);
      s21_remove_matrix(&transposed_complements);
    }
  }
  return flag;
}