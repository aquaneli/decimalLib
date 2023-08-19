#include "decimal.h"

void convert_to_big_decimal(decimal value_1, big_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
}

void convert_to_small_decimal(decimal *value_1, big_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
}

void normalization(big_decimal *value_1, big_decimal *value_2, int diff) {
  if (diff > 0) {
    increase_scale_big_decimal(value_2, diff);
  } else if (diff < 0) {
    increase_scale_big_decimal(value_1, -diff);
  }
}

void increase_scale_big_decimal(big_decimal *dst, int n) {
  big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    big_mul(*dst, ten, &tmp);
    *dst = tmp;
    zero_big_decimal(&tmp);
  }
}

void decreace_scale_big_decimal(big_decimal *dst, int n) {
  big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    div_big_decimal(*dst, ten, &tmp);
    *dst = tmp;
    zero_big_decimal(&tmp);
  }
}

void zero_big_decimal(big_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = dst->bits[4] =
      dst->bits[5] = dst->bits[6] = dst->bits[7] = 0;
}

int get_bit_big(big_decimal dst, int index) {
  int mask = 1u << (index % 32);

  return (dst.bits[index / 32] & mask) != 0;
}

void set_bit_big(big_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}

int post_normalization(big_decimal *result, int scale) {
  int dop = 0;
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (scale == 1 && result->bits[3]) dop = 1;
    decreace_scale_big_decimal(result, 1);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 && get_bit_big(*result, 0))
    set_bit_big(result, 0, 0);
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7]))
    scale = -1;
  return scale;
}

void find_highest_bit_big_decimal(big_decimal v1, big_decimal v2, int *bit_1,
                                  int *bit_2) {
  for (int i = 255; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && get_bit_big(v1, i)) *bit_1 = i;
    if (*bit_2 == 0 && get_bit_big(v2, i)) *bit_2 = i;
  }
}

int is_big_decimal_not_empty(big_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2] + dst.bits[3] + dst.bits[4] +
         dst.bits[5] + dst.bits[6] + dst.bits[7];
}

int shift_big_dec_left(big_decimal *dst, int num) {
  int error = 0;
  int buffer[8] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = get_bit_big(*dst, (i + 1) * 32 - 1);
    }
    for (int i = 7; i > 0 && !error; i--) {
      if (get_bit_big(*dst, 255)) error = 1;
      dst->bits[i] <<= 1;
      set_bit_big(dst, i * 32, buffer[i - 1]);
    }
    dst->bits[0] <<= 1;
  }
  return error;
}

int equation_bits_big_decimal(big_decimal *value_1, big_decimal *value_2) {
  int scale = 0;
  while (is_greater_big_decimal(*value_2, *value_1)) {
    increase_scale_big_decimal(value_1, 1);
    scale++;
  }
  while (is_greater_or_equal_big_decimal(*value_1, *value_2)) {
    shift_big_dec_left(value_2, 1);
  }
  shift_big_dec_right(value_2, 1);
  return scale;
}

void shift_big_dec_right(big_decimal *dst, int num) {
  int buffer[7] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = get_bit_big(*dst, (i + 1) * 32);
    }
    for (int i = 0; i < 7; i++) {
      dst->bits[i] >>= 1;
      set_bit_big(dst, (i + 1) * 32 - 1, buffer[i]);
    }
    dst->bits[7] >>= 1;
  }
}

int is_greater_or_equal_big_decimal(big_decimal value_1, big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !out && !result; i--) {
    if (value_1.bits[i] != 0 || value_2.bits[i] != 0) {
      if (value_1.bits[i] >= value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

int is_decimal_not_empty(decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2] + dst.bits[3] + dst.bits[4] +
         dst.bits[5] + dst.bits[6] + dst.bits[7];
}

int is_greater_big_decimal(big_decimal value_1, big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

int div_big_decimal(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  zero_big_decimal(result);
  int res_func = 0, exp = 0, stp = 0;

  int bits_c_1 = search_scale_big_decimal(value_1);
  int bits_c_2 = search_scale_big_decimal(value_2);
  int diff = bits_c_1 - bits_c_2;

  normalization(&value_1, &value_2, diff);

  while (is_greater_or_equal_big_decimal(value_1, value_2)) {
    exp = search_deg_big_decimal(&value_1, value_2);
    shift_bits_left_res_big_decimal(result, &exp);
  }

  big_decimal null_d = {{0, 0, 0, 0}};
  big_decimal mul_dec = {{10, 0, 0, 0}};

  for (int i = 0; i < 8 && is_greater_big_decimal(value_1, null_d); i++) {
    while (is_greater_big_decimal(value_2, value_1)) {
      big_mul(value_1, mul_dec, &value_1);
      stp++;
    }

    if (search_bits_big_decimal(value_1) < 256)
      big_mul(*result, mul_dec, result);

    while (is_greater_or_equal_big_decimal(value_1, value_2)) {
      exp = search_deg_big_decimal(&value_1, value_2);
      shift_bits_left_res_big_decimal(result, &exp);
    }
  }

  return res_func;
}

int search_bits_big_decimal(big_decimal value) {
  int bits_c = 0, count = 0;  // до первого вхождения числа.
  for (int i = 6; i >= 0 && !count; i--)
    for (int j = 0; j < 32 && !count; j++) {
      if ((value.bits[i] & (0b10000000000000000000000000000000 >> j))) count++;
      if (!count) bits_c++;
    }
  return bits_c;
}

int search_scale_big_decimal(big_decimal value) {
  int exp = 0;
  if (((value.bits[7] & MASK_SUB) >> 31) == 1)
    exp = (value.bits[7] ^ (1 << 31)) >> 16;
  else
    exp = value.bits[7] >> 16;
  return exp;
}

int search_sign_big_decimal(big_decimal *value_1, big_decimal *value_2) {
  int code = 0;
  if ((value_1->bits[7] >> 31) && (value_2->bits[7] >> 31)) {
    set_bit_big(value_1, 255, 0);
    set_bit_big(value_2, 255, 0);
    code = 0;
  } else if ((value_1->bits[7] >> 31) && !(value_2->bits[7] >> 31)) {
    set_bit_big(value_1, 255, 0);
    code = 1;
  } else if (!(value_1->bits[7] >> 31) && (value_2->bits[7] >> 31)) {
    set_bit_big(value_2, 255, 0);
    code = 1;
  }
  return code;
}

/* Ищем ближайшую степень к делимому */
int search_deg_big_decimal(big_decimal *value_1, big_decimal value_2) {
  int bits_c_1 = search_bits_big_decimal(*value_1);
  int bits_c_2 = search_bits_big_decimal(value_2);
  int bits_count = bits_c_1 - bits_c_2;
  if (bits_count < 0) bits_count = -bits_count;
  shift_bits_left_big_decimal(&value_2, &bits_count);

  while (is_greater_big_decimal(value_2, *value_1)) {
    shift_bits_right_big_decimal(&value_2);
    bits_count--;
  }

  sub_big_dec(*value_1, value_2, value_1);
  return bits_count;
}

void shift_bits_left_res_big_decimal(big_decimal *result, int *exp) {
  big_decimal exp_res = {0};
  exp_res.bits[0] = exp_res.bits[0] | 1;
  shift_bits_left_big_decimal(&exp_res, exp);
  add_big_dec(exp_res, *result, result);
}

void shift_bits_left_big_decimal(big_decimal *value, int *bits_count) {
  int count = 0;
  while (*bits_count >= count) {
    value->bits[6] = value->bits[6] << 1;
    if ((value->bits[5] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[6] = value->bits[6] | 1;

    value->bits[5] = value->bits[5] << 1;
    if ((value->bits[4] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[5] = value->bits[5] | 1;

    value->bits[4] = value->bits[4] << 1;
    if ((value->bits[3] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[4] = value->bits[4] | 1;

    value->bits[3] = value->bits[3] << 1;
    if ((value->bits[2] & 0b10000000000000000000000000000000) >> 31 == 1)
      value->bits[3] = value->bits[3] | 1;

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

int exp_research_big_decimal(big_decimal value) {
  int exp = 0;
  if ((value.bits[7] & MASK_SUB) >> 31 == 1)
    exp = (value.bits[7] ^ (1 << 31)) >> 16;
  else
    exp = value.bits[7] >> 16;
  return exp;
}

void shift_bits_right_big_decimal(big_decimal *value) {
  value->bits[0] = value->bits[0] >> 1;
  if ((value->bits[1] & 1) == 1)
    value->bits[0] = value->bits[0] | 0b10000000000000000000000000000000;

  value->bits[1] = value->bits[1] >> 1;
  if ((value->bits[2] & 1) == 1)
    value->bits[1] = value->bits[1] | 0b10000000000000000000000000000000;

  value->bits[2] = value->bits[2] >> 1;
  if ((value->bits[3] & 1) == 1)
    value->bits[2] = value->bits[2] | 0b10000000000000000000000000000000;

  value->bits[3] = value->bits[3] >> 1;
  if ((value->bits[4] & 1) == 1)
    value->bits[3] = value->bits[3] | 0b10000000000000000000000000000000;

  value->bits[4] = value->bits[4] >> 1;
  if ((value->bits[3] & 1) == 1)
    value->bits[4] = value->bits[4] | 0b10000000000000000000000000000000;

  value->bits[5] = value->bits[5] >> 1;
  if ((value->bits[4] & 1) == 1)
    value->bits[5] = value->bits[5] | 0b10000000000000000000000000000000;

  value->bits[6] = value->bits[6] >> 1;
}
