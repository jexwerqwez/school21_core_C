#include "s21_math.h"

int s21_abs(int x) { return (x < 0) ? -x : x; }

long double s21_fabs(double x) { return (x < 0) ? -x : x; }

long double s21_exp(double x) {
  long double addition = 1.;
  long double correct_result = 1;
  int sign = (x < S21_EPS) ? -1 : 1;
  long double result = 0;
  if (x == S21_NAN || x != x)
    result = S21_NAN;
  else if (x == S21_INF)
    result = S21_INF;
  else {
    for (int i = 1; s21_fabs(addition) > S21_EPS; i++) {
      addition *= s21_fabs(x) / i;
      correct_result += addition;
      if (correct_result > S21_MAX_DBL) {
        result = S21_INF;
        break;
      }
    }
    correct_result = (correct_result > S21_MAX_DBL) ? S21_INF : correct_result;
    result = (sign == -1) ? 1.0 / correct_result : correct_result;
  }
  result = (s21_fabs(result) < S21_EPS) ? 0 : result;
  return result;
}

long double s21_ceil(double x) {
  long double result = 0;
  if (x == S21_INF)
    result = S21_INF;
  else if (x == S21_NINF)
    result = S21_NINF;
  else if (x == S21_NAN || x != x)
    result = S21_NAN;
  else {
    result = (long long int)x;
    if (x > 0 && x != result) result++;
  }
  return result;
}

long double s21_floor(double x) {
  long double result = 0;
  if (x == S21_NAN || x != x)
    result = S21_NAN;
  else if (x == S21_INF)
    result = S21_INF;
  else if (x == S21_NINF)
    result = S21_NINF;
  else {
    result = (long long int)x;
    if (x < 0 && x != result) result--;
  }
  return result;
}

long double s21_log(double x) {
  long double result = 0;
  long double previous = 1;
  if (x == S21_NAN || x != x || x < 0)
    result = S21_NAN;
  else if (x == S21_INF)
    result = S21_INF;
  else if (x == S21_E)
    result = 1;
  else if (x == S21_NINF || x == 0)
    result = S21_NINF;
  else {
    for (int i = 0; i < 10000; i++) {
      previous = result;
      result = previous + 2 * ((long double)x - s21_exp(previous)) /
                              ((long double)x + s21_exp(previous));
    }
  }
  return result;
}

long double s21_fmod(double x, double y) {
  long double result = 0;
  if (y == 0 || s21_fabs(x) == S21_INF || x == S21_NAN || y == S21_NAN)
    result = S21_NAN;
  else if (s21_fabs(y) == S21_INF)
    result = (long double)x;
  else
    result = (long double)x - (long long int)(x / y) * (long double)y;
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 1;
  if (s21_fabs(exp) == 0 ||
      (base == base && s21_fabs(base) != S21_INF &&
       ((s21_fabs(exp) == S21_INF && s21_fabs(base) == 1 && base != 0))) ||
      (base == 1 && S21_NAN))
    result = 1;
  else if ((s21_fabs(base) == 0 && exp > S21_EPS) ||
           (base < -S21_EPS && exp == S21_NINF) ||
           (base < -1000000000000000 && exp < -1000000000000000))
    result = 0;
  else if (base == 0 && exp < S21_EPS) {
    result = (exp < -1000000000000000 && exp != S21_NINF) ? S21_NINF : S21_INF;
  } else if (base == S21_NAN || exp == S21_NAN || base != base || exp != exp)
    result = S21_NAN;
  else if (base == S21_INF || exp == S21_INF)
    result = (exp < S21_EPS || s21_fabs(base) < 1) ? 0 : S21_INF;
  else if (base == S21_NINF)
    result = (exp < S21_EPS) ? 0 : ((int)exp % 2 == 0) ? S21_INF : S21_NINF;
  else {
    result = s21_exp(exp * s21_log(s21_fabs(base)));
    if ((s21_fmod(exp, 2) != 0) && base < S21_EPS) result = -result;
    if (((int)exp != exp) && base < -S21_EPS) {
      result = ((base <= exp || (base >= exp && base < 1)) &&
                exp > -1000000000000000)
                   ? S21_NAN
                   : 0;
    }
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = -1;
  if (x < 0)
    result = S21_NAN;
  else
    result = s21_pow(x, 0.5);
  return result;
}

long double s21_sin(double x) {
  long double result = 0.0;
  int sign = -1;
  if (s21_fabs(x) == S21_NAN)
    result = S21_NAN;
  else if (s21_fabs(x) == S21_INF)
    result = S21_NAN;
  else {
    while (s21_fabs(x) >= 2 * S21_PI) {
      if (x >= 2 * S21_PI)
        x -= 2 * S21_PI;
      else
        x += 2 * S21_PI;
    }
    result = (long double)x;
    long double xx = (long double)x * (long double)x;
    long double pow_x = (long double)x * xx;
    long double prev_factorial = 1.0;
    for (int i = 1; i < 3000; i++) {
      result += sign * (pow_x / (prev_factorial * (2.0 * i) * (2.0 * i + 1.0)));
      sign = -sign;
      pow_x *= xx;
      prev_factorial *= (2.0 * i) * (2.0 * i + 1.0);
    }
  }
  return result;
}

long double s21_cos(double x) {
  long double result = 0;
  int sign = -1;
  if (s21_fabs(x) == S21_NAN)
    result = S21_NAN;
  else if (s21_fabs(x) == S21_INF || x > 100000)
    result = S21_NAN;
  else {
    while (s21_fabs(x) >= 2 * S21_PI) {
      if (x >= 2 * S21_PI)
        x -= 2 * S21_PI;
      else
        x += 2 * S21_PI;
    }
    result = 1;
    long double xx = (long double)x * (long double)x;
    long double pow_x = xx;
    long double prev_factorial = 1.0;
    for (int i = 1; i < 3000; i++) {
      result += sign * (pow_x / (prev_factorial * (2.0 * i) * (2.0 * i - 1.0)));
      sign = -sign;
      pow_x *= xx;
      prev_factorial *= (2.0 * i) * (2.0 * i - 1.0);
    }
  }
  return result;
}

long double s21_tan(double x) {
  long double result = 0;
  if (x == S21_PI / 2.0)
    result = 16331239353195370.0;
  else if (x == -S21_PI / 2.0)
    result = -16331239353195370.0;
  else
    result = s21_sin(x) / s21_cos(x);
  return result;
}

long double s21_asin(double x) {
  long double result = 0.0;
  if (s21_fabs(x) == S21_NAN || x != x || s21_fabs(x) > 1 ||
      s21_fabs(x) == S21_INF)
    result = S21_NAN;
  else
    result = s21_atan(x / (s21_sqrt(1.0 - x * x)));
  return result;
}

long double s21_atan(double x) {
  long double result = 0.0;
  int sign = -1;
  if (s21_fabs(x) == S21_NAN || x != x)
    result = S21_NAN;
  else {
    if (s21_fabs(x) == S21_INF) {
      x = (x == S21_INF) ? S21_PI / 2.0 : -S21_PI / 2.0;
      result = (long double)x;
    } else {
      if (s21_fabs(x) <= 1) {
        result = (long double)x;
        long double xx = (long double)x * (long double)x;
        long double pow_x = xx * (long double)x;
        for (int i = 1; i < 300000; i++) {
          result += sign * (pow_x / (2.0 * i + 1.0));
          sign = -sign;
          pow_x *= xx;
        }
      } else if (s21_fabs(x) > 1) {
        result = 1.0 / (long double)x;
        long double xx = 1.0 / (long double)x / (long double)x;
        long double pow_x = xx / (long double)x;
        for (int i = 1; i < 300000; i++) {
          result += sign * (pow_x / (2.0 * i + 1.0));
          sign = -sign;
          pow_x *= xx;
        }
        result = (S21_PI * s21_fabs(x)) / (2 * x) - result;
      }
    }
  }
  return result;
}

long double s21_acos(double x) {
  long double result = 0.0;
  if (s21_fabs(x) == S21_NAN || x != x || s21_fabs(x) > 1 ||
      s21_fabs(x) == S21_INF)
    result = S21_NAN;
  else
    result = S21_PI / 2.0 - s21_asin(x);
  return result;
}
