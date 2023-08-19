#include "decimal.h"

int dec_add(decimal value_1, decimal value_2, decimal *result) {
  zero_decimal(result);
  int result_sign = 0;
  int error = 0;
  int biggest_scale = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (sign_1 == 1 && sign_2 == 1) {
    result_sign = 1;
  }
  if (sign_1 != sign_2) {  // сложение чисел с разным знаком
    set_bit(&value_1, 127, 0);
    set_bit(&value_2, 127, 0);
    if (sign_1 == 1) {
      dec_sub(value_2, value_1, result);
    } else {
      dec_sub(value_1, value_2, result);
    }
  } else {
    big_decimal a = {0};
    big_decimal b = {0};
    big_decimal res = {0};
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);
    int differemce = scale_1 - scale_2;
    if (differemce > 0) {
      biggest_scale = scale_1;
    } else {
      biggest_scale = scale_2;
    }
    convert_to_big_decimal(value_1, &a);
    convert_to_big_decimal(value_2, &b);
    normalization(&a, &b, differemce);
    add_big_dec(a, b, &res);
    int scale = 0;
    scale = post_normalization(&res, biggest_scale);
    if (scale >= 0) {
      convert_to_small_decimal(result, res);
      set_scale(result, scale);
    } else {
      error = 1;
    }
    if (result_sign == 1) {
      set_sign(result);
    }
  }
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) zero_decimal(result);

  return error;
}

void add_big_dec(big_decimal value_1, big_decimal value_2,
                 big_decimal *result) {
  int temp = 0;
  for (int i = 0; i < 256; i++) {
    int number1 = 0;
    number1 = get_bit_big(value_1, i);
    int number2 = 0;
    number2 = get_bit_big(value_2, i);
    if (number1 == 1 && number2 == 1) {
      if (temp == 0) {
        temp = 1;
        // res = 0;
        set_bit_big(result, i, 0);
      } else {
        temp = 1;
        set_bit_big(result, i, 1);
      }
    } else if ((number1 == 1 && number2 == 0) ||
               (number1 == 0 && number2 == 1)) {
      if (temp == 0) {
        temp = 0;
        set_bit_big(result, i, 1);
      } else {
        temp = 1;
        set_bit_big(result, i, 0);
      }
    } else {
      if (temp == 0) {
        temp = 0;
        set_bit_big(result, i, 0);
      } else {
        temp = 0;
        set_bit_big(result, i, 1);
      }
    }
  }
}

int dec_mul(decimal value_1, decimal value_2, decimal *result) {
  big_decimal a = {0}, b = {0}, res = {0};
  int error = 0;
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  int res_scale = scale_1 + scale_2;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int res_sign = 0;
  if (sign_1 != sign_2) {
    res_sign = 1;
  }
  convert_to_big_decimal(value_1, &a);
  convert_to_big_decimal(value_2, &b);
  error = big_mul(a, b, &res);
  convert_to_small_decimal(result, res);
  set_scale(result, res_scale);
  if (res_sign == 1) {
    set_sign(result);
  }
  return error;
}

int big_mul(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  int error = 0;
  big_decimal temp = {0};
  if (bit_mul(value_1, value_2, &temp)) {
    error = 1;
  } else {
    *result = temp;
  }
  return error;
}

int bit_mul(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  big_decimal temp = {0};
  int error = 0;
  for (int i = 0; i < 256; i++) {
    if (get_bit_big(value_2, i)) {
      add_big_dec(temp, value_1, &temp);
      shift_left(&value_1);
    } else {
      shift_left(&value_1);
    }
  }
  temp.bits[8] = result->bits[8];
  *result = temp;
  return error;
}

void shift_left(big_decimal *value) {
  int bit[7];
  for (int i = 31, j = 0; j < 7; i += 32, j++) bit[j] = get_bit_big(*value, i);
  for (int i = 0; i < 8; i++) value->bits[i] <<= 1;
  for (int i = 32, j = 0; j < 7; i += 32, j++)
    if (bit[j]) set_bit_big(value, i, 1);
}

int dec_sub(decimal value_1, decimal value_2, decimal *result) {
  zero_decimal(result);
  int result_sign = 0;
  int error = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  if (sign_1 == 0 && sign_2 == 1) {
    set_bit(&value_2, 127, 0);
    error = dec_add(value_1, value_2, result);
  } else if (sign_1 == 1 && sign_2 == 0) {
    if (sign_1 == 1) {
      result_sign = 1;
    }
    set_bit(&value_1, 127, 0);
    error = dec_add(value_1, value_2, result);
  } else if (sign_1 == 1 && sign_2 == 1) {
    decimal temp = value_1;
    value_1 = value_2;
    value_2 = temp;
    set_bit(&value_1, 127, 0);
    set_bit(&value_2, 127, 0);
    error = big_sub(value_1, value_2, result);
  } else {
    error = big_sub(value_1, value_2, result);
  }
  if (result_sign == 1) {
    set_sign(result);
  }
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

int big_sub(decimal value_1, decimal value_2, decimal *result) {
  int error = 0;
  int scale = 0;
  big_decimal a = {0};
  big_decimal b = {0};
  big_decimal res = {0};
  int bigger_scale = 0;
  convert_to_big_decimal(value_1, &a);
  convert_to_big_decimal(value_2, &b);

  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  int difference = scale_1 - scale_2;

  if (difference > 0) {
    set_scale(&value_2, scale_1);
    bigger_scale = scale_1;
  } else {
    set_scale(&value_1, scale_2);
    bigger_scale = scale_2;
  }
  if (difference != 0) {
    normalization(&a, &b, difference);
  }
  if (is_greater_big_decimal(b, a)) {
    big_decimal temporary = a;
    a = b;
    b = temporary;
    set_sign(result);
  }
  sub_big_dec(a, b, &res);
  scale = post_normalization(&res, bigger_scale);
  if (scale >= 0) {
    convert_to_small_decimal(result, res);
    set_scale(result, scale);
  } else {
    error = 1;
  }
  return error;
}

int sub_big_dec(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  for (int i = 0; i < 256; i++) {
    int number1 = get_bit_big(value_1, i);
    int number2 = get_bit_big(value_2, i);
    if (number1 == 0 && number2 == 1) {
      int index_one = 0;
      set_bit_big(result, i, 1);
      find_one(value_1, i, &index_one);
      change_to_zero(&value_1, index_one, i);
    } else {
      if (number1 == 1 && number2 == 0) {
        set_bit_big(result, i, 1);
      } else {
        set_bit_big(result, i, 0);
      }
    }
  }
  return 0;
}

int dec_mod(decimal value_1, decimal value_2, decimal *result) {
  zero_decimal(result);
  int error = 0;
  decimal res = {{0, 0, 0, 0}};
  error = dec_div(value_1, value_2, &res);
  if (error == 0) {
    error = dec_mul(value_2, res, &res);
    error = dec_sub(value_1, res, result);
  }
  *result = res;
  return error;
}

int dec_div(decimal value_1, decimal value_2, decimal *result) {
  zero_decimal(result);
  int res_func = 0, exp = 0, stp = 0;
  big_decimal value_1_big = {0}, value_2_big = {0};

  if (search_bits(value_2) > 95) {
    res_func = 3;
  } else {
    int bits_c_1 = search_scale(value_1);
    int bits_c_2 = search_scale(value_2);

    int diff = bits_c_1 - bits_c_2;
    int code = search_sign(&value_1, &value_2);

    convert_to_big_decimal(value_1, &value_1_big);
    convert_to_big_decimal(value_2, &value_2_big);
    normalization(&value_1_big, &value_2_big, diff);
    convert_to_small_decimal(&value_1, value_1_big);
    convert_to_small_decimal(&value_2, value_2_big);

    if (diff < 0) {
      diff = -diff;
      value_1.bits[3] = ((value_1.bits[3] >> 16) + diff) << 16;
    } else if (diff > 0) {
      value_2.bits[3] = ((value_2.bits[3] >> 16) + diff) << 16;
    }

    while (is_greater_or_equal(value_1, value_2) ||
           is_equal(value_1, value_2)) {
      exp = search_deg(&value_1, value_2);
      shift_bits_left_res(result, &exp);
    }

    if (search_bits(value_1) <= 95) {
      decimal null_d = {{0, 0, 0, 0}};
      decimal mul_dec = {{10, 0, 0, 0}};
      for (int i = 0; i < 8 && is_not_equal(value_1, null_d); i++) {
        while (is_less(value_1, value_2)) {
          dec_mul(value_1, mul_dec, &value_1);
          stp++;
        }
        if (search_bits(value_1) < 96) dec_mul(*result, mul_dec, result);
        while (is_greater(value_1, value_2) || is_equal(value_1, value_2)) {
          exp = search_deg(&value_1, value_2);
          shift_bits_left_res(result, &exp);
        }
      }
    }
    result->bits[3] = ((result->bits[3] >> 16) | stp) << 16;
    if (code) result->bits[3] = result->bits[3] | 2147483648;
  }
  return res_func;
}

int search_sign(decimal *value_1, decimal *value_2) {
  int code = 0;

  if ((value_1->bits[3] >> 31) && (value_2->bits[3] >> 31)) {
    value_1->bits[3] = set_bit(value_1, 127, 0);
    value_2->bits[3] = set_bit(value_2, 127, 0);
    code = 0;
  } else if ((value_1->bits[3] >> 31) && !(value_2->bits[3] >> 31)) {
    value_1->bits[3] = set_bit(value_1, 127, 0);
    code = 1;
  } else if (!(value_1->bits[3] >> 31) && (value_2->bits[3] >> 31)) {
    value_2->bits[3] = set_bit(value_2, 127, 0);
    code = 1;
  }
  return code;
}

void shift_bits_left_res(decimal *result, int *exp) {
  decimal exp_res = {0};
  exp_res.bits[0] = exp_res.bits[0] | 1;
  shift_bits_left(&exp_res, exp);
  dec_add(exp_res, *result, result);
}

int search_deg(decimal *value_1, decimal value_2) {
  /* Ищем ближайшую степень к делимому */
  int bits_c_1 = search_bits(*value_1);
  int bits_c_2 = search_bits(value_2);
  int bits_count = bits_c_1 - bits_c_2;
  if (bits_count < 0) bits_count = -bits_count;
  shift_bits_left(&value_2, &bits_count);
  while (is_less(*value_1, value_2)) {
    shift_bits_right(&value_2);
    bits_count--;
  }
  dec_sub(*value_1, value_2, value_1);
  return bits_count;
}

int search_scale(decimal value) {
  int exp = 0;
  if ((value.bits[3] & MASK_SUB) >> 31 == 1)
    exp = (value.bits[3] ^ (1 << 31)) >> 16;
  else
    exp = value.bits[3] >> 16;
  return exp;
}

int search_bits(decimal value) {
  int bits_c = 0, count = 0;  // до первого вхождения числа.
  for (int i = 2; i >= 0 && !count; i--)
    for (int j = 0; j < 32 && !count; j++) {
      if ((value.bits[i] & (0b10000000000000000000000000000000 >> j))) count++;
      if (!count) bits_c++;
    }
  return bits_c;
}

int exp_research(decimal value) {
  int exp = 0;
  if ((value.bits[3] & MASK_SUB) >> 31 == 1)
    exp = (value.bits[3] ^ (1 << 31)) >> 16;
  else
    exp = value.bits[3] >> 16;
  return exp;
}

void shift_bits_right(decimal *value) {
  value->bits[0] = value->bits[0] >> 1;
  if ((value->bits[1] & 1) == 1)
    value->bits[0] = value->bits[0] | 0b10000000000000000000000000000000;

  value->bits[1] = value->bits[1] >> 1;
  if ((value->bits[2] & 1) == 1)
    value->bits[1] = value->bits[1] | 0b10000000000000000000000000000000;

  value->bits[2] = value->bits[2] >> 1;
}

void shift_bits_left(decimal *value, int *bits_count) {
  int count = 0;
  while (*bits_count >= count) {
    value->bits[2] = value->bits[2] << 1;
    if ((value->bits[1] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[2] = value->bits[2] | 1;
    value->bits[1] = value->bits[1] << 1;
    if ((value->bits[0] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[1] = value->bits[1] | 1;
    value->bits[0] = value->bits[0] << 1;
    count++;
  }
}
