#include "decimal.h"

int from_int_to_decimal(int src, decimal *dst) {
  int flag = 0;
  zero_decimal(dst);
  if (src < 0) {
    set_sign(dst);
    src *= -1;
  }
  if (src > INT_MAX) {
    flag = 1;
  } else {
    dst->bits[0] = src;
  }
  return flag;
}

int from_decimal_to_int(decimal src, int *dst) {
  int error = 0;
  int scale = get_scale(src);
  int sign = get_sign(src);
  if (src.bits[1] || src.bits[2]) {
    error = 1;
  } else {
    *dst = src.bits[0];
    if (scale > 0 && scale <= 28) {
      *dst /= pow(10, scale);
    }
  }
  if (sign == 1) {
    *dst *= -1;
  }
  return error;
}

int from_float_to_decimal(float src, decimal *dst) {
  zero_decimal(dst);
  int flag = 0;
  if (isinf(src) || isnan(src)) {
    flag = 1;
  } else {
    zero_decimal(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src *= -1;
    }
    long int new_value = (long int)src;
    long int exp = 0;
    while (src - ((float)new_value / (long int)(pow(10, exp))) != 0) {
      exp++;
      new_value = src * (long int)(pow(10, exp));
    }
    from_int_to_decimal(new_value, dst);
    if (sign) {
      set_sign(dst);
    }
    dst->bits[3] += exp << 16;
  }
  return flag;
}

int from_decimal_to_float(decimal src, float *dst) {
  int flag = 0;
  if (dst) {
    *dst = 0;
    int minus = 1;
    long double buff = 0, bits = 1;
    int exp = get_exp(src);
    if (get_sign(src) == 1) minus = -1;
    for (int k = 0; k < 96; k++) {
      if (get_bit(src, k)) {
        buff += bits;
      }
      bits *= 2;
    }
    for (int k = 0; k < exp; k++) {
      buff /= 10;
    }
    *dst = minus * buff;
  } else {
    flag = 1;
  }
  return flag;
}

int from_decimal_to_double(decimal src, long double *dst) {
  long double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += get_bit(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -get_scale(src));
  if (get_bit(src, 127)) temp = temp * (-1);
  *dst = temp;
  return 0;
}
