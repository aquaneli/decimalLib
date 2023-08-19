#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK_SUB 0b10000000000111000000000000000000

typedef struct {
  unsigned int bits[4];
} decimal;

typedef struct {
  unsigned int bits[8];
} big_decimal;

// арифметика
int dec_add(decimal value_1, decimal value_2, decimal *result);
int dec_sub(decimal value_1, decimal value_2, decimal *result);
int dec_mul(decimal value_1, decimal value_2, decimal *result);
int dec_div(decimal value_1, decimal value_2, decimal *result);
int dec_mod(decimal value_1, decimal value_2, decimal *result);

// Сравнение
int is_less(decimal, decimal);
int is_less_or_equal(decimal, decimal);
int is_greater(decimal, decimal);
int is_greater_or_equal(decimal, decimal);
int is_equal(decimal, decimal);
int is_not_equal(decimal, decimal);

// Преобразователи
int from_int_to_decimal(int src, decimal *dst);
int from_float_to_decimal(float src, decimal *dst);
int from_decimal_to_int(decimal src, int *dst);
int from_decimal_to_float(decimal src, float *dst);
int from_decimal_to_double(decimal src, long double *dst);

// Доп. функции
int dec_floor(decimal value, decimal *result);
int dec_round(decimal value, decimal *result);
int truncate(decimal value, decimal *result);
int negate(decimal value, decimal *result);

// Битовые операции
int get_bit(decimal value, int bitindex);
int set_bit(decimal *decl, int bitindex, int number);
int int_number(int index);
int bit_number(int index);
int get_sign(decimal value);
void zero_decimal(decimal *dst);
void set_sign(decimal *dst);
int get_scale(decimal dst);
int get_exp(decimal value);
void set_scale(decimal *dst, int scale);

void copy_decimal(decimal *d1, decimal d2);
int is_decimal_not_empty(decimal dst);

// big decimal functions
void convert_to_big_decimal(decimal value_1, big_decimal *value_2);
void convert_to_small_decimal(decimal *value_1, big_decimal value_2);
void normalization(big_decimal *value_1, big_decimal *value_2, int diff);
int post_normalization(big_decimal *result, int scale);
void add_big_dec(big_decimal value_1, big_decimal value_2, big_decimal *result);
void shift_left(big_decimal *value);
int bit_mul(big_decimal value_1, big_decimal value_2, big_decimal *result);
int big_mul(big_decimal value_1, big_decimal value_2, big_decimal *result);
int get_bit_big(big_decimal dst, int index);
void set_bit_big(big_decimal *dst, int index, int bit);
int is_greater_big_decimal(big_decimal value_1, big_decimal value_2);
int is_greater_or_equal_big_decimal(big_decimal value_1, big_decimal value_2);
void shift_left(big_decimal *value);
int big_sub(decimal value_1, decimal value_2, decimal *result);
int sub_big_dec(big_decimal value_1, big_decimal value_2, big_decimal *result);
void decreace_scale_big_decimal(big_decimal *dst, int n);
void increase_scale_big_decimal(big_decimal *dst, int n);
void zero_big_decimal(big_decimal *dst);
void add_big_dec(big_decimal value_1, big_decimal value_2, big_decimal *result);
int find_one(big_decimal value, int index_now, int *index_one);
int change_to_zero(big_decimal *value, int index_one, int index_now);
int compare(decimal a, decimal b);
int div_big_decimal(big_decimal value_1, big_decimal value_2,
                    big_decimal *result);
void find_highest_bit_big_decimal(big_decimal v1, big_decimal v2, int *bit_1,
                                  int *bit_2);
int shift_big_dec_left(big_decimal *dst, int num);
int equation_bits_big_decimal(big_decimal *value_1, big_decimal *value_2);
void shift_big_dec_right(big_decimal *dst, int num);
int is_big_decimal_not_empty(big_decimal dst);

int search_sign(decimal *value_1, decimal *value_2);
int search_deg(decimal *value_1, decimal value_2);
int search_scale(decimal value);
int exp_research(decimal value);
void shift_bits_right(decimal *value);
int search_bits(decimal value);
void shift_bits_left_res(decimal *result, int *exp);
void shift_bits_left(decimal *value, int *bits_count);

int search_scale_big_decimal(big_decimal value);
int search_sign_big_decimal(big_decimal *value_1, big_decimal *value_2);
int search_deg_big_decimal(big_decimal *value_1, big_decimal value_2);
void shift_bits_left_res_big_decimal(big_decimal *result, int *exp);
int search_bits_big_decimal(big_decimal value);
void shift_bits_left_big_decimal(big_decimal *value, int *bits_count);
void shift_bits_right_big_decimal(big_decimal *value);

#endif  // SRC_DECIMAL_H_