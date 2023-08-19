#include "decimal.h"
#include "limits.h"

int negate(decimal value, decimal *result) {
  zero_decimal(result);
  int sign = get_sign(value);
  *result = value;
  if (sign == 1) {
    set_bit(result, 127, 0);
  } else {
    set_bit(result, 127, 1);
  }
  return 0;
}

int truncate(decimal value, decimal *result) {
  zero_decimal(result);
  long double difference = 0.0;
  if (get_scale(value)) {
    long double fl_to_int = 0.0;
    from_decimal_to_double(value, &fl_to_int);
    fl_to_int = trunc(fl_to_int);
    if (fl_to_int < 0.0) {
      set_bit(result, 127, 1);
      fl_to_int *= -1;
    }
    for (int i = 0; fl_to_int >= 1 && i < 96; i++) {
      fl_to_int = floor(fl_to_int) / 2;
      difference = fl_to_int - floor(fl_to_int);
      if (difference > 0.0) {
        set_bit(result, i, 1);
      } else {
        set_bit(result, i, 0);
      }
    }
    set_scale(result, 0);
  } else {
    copy_decimal(result, value);
  }
  return 0;
}

int dec_floor(decimal value, decimal *result) {
  zero_decimal(result);
  int error = 0;
  int scale = get_scale(value);
  int sign = get_sign(value);
  decimal one = {{1, 0, 0, 0}};
  if (scale != 0) {
    error = truncate(value, result);
    if (error == 0 && sign == 1 && !is_equal(*result, value)) {
      error = dec_sub(*result, one, result);
    }
  } else {
    copy_decimal(result, value);
  }
  if (error != 0) {
    error = 1;
  }
  return error;
}

int dec_round(decimal value, decimal *result) {
  zero_decimal(result);
  int error = 0;
  int scale = get_scale(value);
  long double new_float = 0.0;
  long double difference = 0.0;
  if (scale != 0) {
    error = from_decimal_to_double(value, &new_float);
    new_float = round(new_float);
    if (new_float < 0.0) {
      set_bit(result, 127, 1);
      new_float *= -1;
    }
    for (int i = 0; new_float >= 1 && i < 96; i++) {
      new_float = floor(new_float) / 2;
      difference = new_float - floor(new_float);
      if (difference > 0.0) {
        set_bit(result, i, 1);
      } else {
        set_bit(result, i, 0);
      }
    }
    set_scale(result, 0);
  } else {
    copy_decimal(result, value);
  }
  if (error != 0) {
    error = 1;
  }
  return error;
}
