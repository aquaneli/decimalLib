#include "decimal_tests.h"

START_TEST(less_0) {
  decimal first = {{4412, 5675, 1254, 0b10000000000000000000000000000000}};
  decimal second = {{4412, 5675, 1254, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(is_less(first, second), 1);
}
END_TEST

START_TEST(less_1) {
  decimal first = {{4412, 5675, 1254, 0b00000000000000000000000000000000}};
  decimal second = {{4412, 5675, 1254, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(is_less(first, second), 0);
}
END_TEST

START_TEST(less_2) {
  decimal first = {{0, 0, 0, 0b00000000000000000000000000000000}};
  decimal second = {{0, 0, 0, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(is_less(first, second), 0);
}
END_TEST

START_TEST(less_3) {
  decimal first = {{0, 0, 0, 0b10000000000000000000000000000000}};
  decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(is_less(first, second), 0);
}
END_TEST

START_TEST(less_4) {
  decimal first = {{0, 0, 0, 0b10000000000000000000000000000000}};
  decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(is_less(first, second), 0);
}
END_TEST

START_TEST(less_5) {
  decimal first = {{4412, 5675, 1254, 0b00000011000000000000000000000000}};
  decimal second = {{4412, 5675, 1254, 0b00000101000000000000000000000000}};
  ck_assert_int_eq(is_less(first, second), 0);
}
END_TEST

START_TEST(less_6) {
  decimal first = {{4422, 5515, 9254, 0b10000000000000110000000000000000}};
  decimal second = {{6312, 5616, 1844, 0b10000000000001010000000000000000}};
  ck_assert_int_eq(is_less(first, second), 1);
}
END_TEST

START_TEST(less_7) {
  decimal first = {{4412, 5775, 1254, 0b00000000000001110000000000000000}};
  decimal second = {{4412, 5675, 1254, 0b00000000000001110000000000000000}};
  ck_assert_int_eq(is_less(first, second), 0);
}
END_TEST

START_TEST(less_8) {
  decimal first = {{4412, 5775, 1254, 0b00000000000010000000000000000000}};
  decimal second = {{4412, 5775, 1254, 0b00000000000001110000000000000000}};
  ck_assert_int_eq(is_less(first, second), 1);
}
END_TEST

START_TEST(less_9) {
  decimal first = {
      {2147483646, 2147483647, 2147483647, 0b00000000000001110000000000000000}};
  decimal second = {
      {2147483647, 2147483647, 2147483647, 0b00000000000001110000000000000000}};
  ck_assert_int_eq(is_less(first, second), 1);
}
END_TEST

START_TEST(less_10) {
  decimal first = {{0, 0, 0, 0b10000000000000000000000000000000}};
  decimal second = {{0, 0, 0, 0b00000000000000000000000000000000}};
  ck_assert_int_eq(is_equal(first, second), 1);
}
END_TEST

START_TEST(is_less_or_equal_0) {
  decimal a = {{1, 0, 0, 0}};
  decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_1) {
  decimal a = {{1, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_2) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_3) {
  decimal a = {{UINT_MAX - 1, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_4) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_5) {
  decimal a = {{UINT_MAX, 1, 0, 0}};
  decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_6) {
  decimal a = {{UINT_MAX, UINT_MAX - 1, 0, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_7) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_8) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_9) {
  decimal a = {{0, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{0, UINT_MAX, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_10) {
  decimal a = {{0, 0, UINT_MAX, 0}};
  decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_11) {
  decimal a = {{0, 0, 0, 0}};
  decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_12) {
  // 2596
  decimal src1 = {0};
  decimal src2 = {0};
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_13) {
  // 3172
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_14) {
  // 3190
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_15) {
  // 3208
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_16) {
  // 3226
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_17) {
  // 3244
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_18) {
  // 3262
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_19) {
  // 3280
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_20) {
  // 3298
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_21) {
  // 3316
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_22) {
  // 3334
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_23) {
  // 3352
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_24) {
  // 3370
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_25) {
  // 3388
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_26) {
  // 3406
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 18446744073709551615;
  // src2 = 1;

  src1.bits[0] = 0b11111111111111111111111111111111;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_27) {
  // 3424
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 18446744073709551615.0;
  // src2 = 965453154;

  src1.bits[0] = 0b11111111111111111111111111110110;
  src1.bits[1] = 0b11111111111111111111111111111111;
  src1.bits[2] = 0b00000000000000000000000000001001;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[0] = 0b00111001100010111010010101100010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_28) {
  // 3442
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = -545454512454545.35265454545645;
  // src2 = 54564654;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  src2.bits[0] = 0b00000011010000001001011100101110;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_less_or_equal_29) {
  // 3478
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 7961327845421.879754123131254;
  // src2 = 0;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_less_or_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_greater_0) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_1) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_2) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_3) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_4) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_5) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_6) {
  int num1 = -3;
  int num2 = 3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_7) {
  float num1 = -3.232446546;
  float num2 = -3.2;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_8) {
  float num1 = -345.232446546;
  float num2 = -3.2;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater_9) {
  float num1 = -3.232323233232323233;
  float num2 = -34545124.232446543232446543;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(is_greater_10) {
  decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec6 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(is_greater(dec5, dec6), 1);
  ck_assert_int_eq(is_greater(dec6, dec5), 0);

  decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(is_greater(dec7, dec8), 0);
  ck_assert_int_eq(is_greater(dec8, dec7), 1);

  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2
  ck_assert_int_eq(is_greater(dec1, dec2), 1);
  ck_assert_int_eq(is_greater(dec2, dec1), 0);

  decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //   -1.2
  ck_assert_int_eq(is_greater(dec3, dec4), 0);
  ck_assert_int_eq(is_greater(dec4, dec3), 1);
}
END_TEST

START_TEST(is_greater_11) {
  decimal a = {{2, 0, 0, 0}};
  decimal b = {{1, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
  // Возвращаемое значение : 0 - 0   1 - TRUE
}
END_TEST

START_TEST(is_greater_12) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_13) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX - 1, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_14) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_15) {
  decimal a = {{UINT_MAX, 0, 0, 0}};
  decimal b = {{UINT_MAX, 1, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_16) {
  decimal a = {{UINT_MAX, 1, 0, 0}};
  decimal b = {{UINT_MAX, 0, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_17) {
  decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  decimal b = {{UINT_MAX, UINT_MAX - 1, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_18) {
  decimal a = {{UINT_MAX, UINT_MAX, 0, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_19) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_20) {
  decimal a = {{UINT_MAX, UINT_MAX, UINT_MAX - 1, 0}};
  decimal b = {{UINT_MAX, UINT_MAX, 0, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_21) {
  decimal a = {{0, UINT_MAX, UINT_MAX, 0}};
  decimal b = {{0, UINT_MAX, UINT_MAX - 1, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_22) {
  decimal a = {{0, 0, UINT_MAX, 0}};
  decimal b = {{0, 0, UINT_MAX - 1, 0}};
  ck_assert_int_eq(is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_23) {
  decimal a = {{0, 0, 0, 0}};
  decimal b = {{0, 0, UINT_MAX, 0}};
  ck_assert_int_eq(is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_24) {
  // 3820
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_greater_25) {
  // 3838
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_greater_26) {
  // 3856
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_greater_27) {
  // 3874
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_greater_28) {
  // 3892
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_greater_29) {
  // 3910
  decimal src1 = {0};
  decimal src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(greater_or_equal_0) {
  float num1 = 1.375323;
  float num2 = 1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_or_equal_1) {
  int num1 = 2;
  int num2 = 1;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_2) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_3) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_4) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_or_equal_5) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_6) {
  int num1 = 10;
  int num2 = 3;
  decimal dec1 = {0}, dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_7) {
  float num1 = 10423546.34534534;
  float num2 = 3.34534534;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_8) {
  float num1 = -3.34534534;
  float num2 = 3.34534534;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_or_equal_9) {
  float num1 = 1042634.34534534;
  float num2 = 10424546.34534534;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_or_equal_10) {
  float num1 = 10426.34534534;
  float num2 = 104234.345345;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_or_equal_11) {
  float num1 = 1042.5667777;
  float num2 = 1042.345345;
  decimal dec1 = {0}, dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_greater_or_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_or_equal_12) {
  decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec6 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //
  ck_assert_int_eq(is_greater_or_equal(dec5, dec6), 1);
  ck_assert_int_eq(is_greater_or_equal(dec6, dec5), 0);

  decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(is_greater_or_equal(dec7, dec8), 0);
  ck_assert_int_eq(is_greater_or_equal(dec8, dec7), 1);

  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};
  ck_assert_int_eq(is_greater_or_equal(dec1, dec2), 1);
  ck_assert_int_eq(is_greater_or_equal(dec2, dec1), 0);

  decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  decimal dec4 = {{12, 0, 0, 0b10000000000000010000000000000000}};  //

  ck_assert_int_eq(is_greater_or_equal(dec3, dec4), 0);
  ck_assert_int_eq(is_greater_or_equal(dec4, dec3), 1);

  decimal dec9 = {{12345, 0, 0, 0}};
  decimal dec10 = {{12345, 0, 0, 0}};
  ck_assert_int_eq(is_greater_or_equal(dec9, dec10), 1);
  ck_assert_int_eq(is_greater_or_equal(dec10, dec9), 1);

  decimal dec11 = {{0, 0, 0, 0}};
  decimal dec12 = {{0, 0, 0, 0}};
  ck_assert_int_eq(is_greater_or_equal(dec11, dec12), 1);
  ck_assert_int_eq(is_greater_or_equal(dec12, dec11), 1);
}
END_TEST

START_TEST(is_equal_0) {
  // 5116
  decimal src1 = {0}, src2 = {0};
  // src1 = 2;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_1) {
  // 5134
  decimal src1 = {0}, src2 = {0};
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_2) {
  // 5152
  decimal src1 = {0}, src2 = {0};
  // src1 = 3;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_3) {
  // 5170
  decimal src1 = {0}, src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_4) {
  // 5188
  decimal src1 = {0}, src2 = {0};
  // src1 = 0;
  // src2 = 3;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_5) {
  // 5206
  decimal src1 = {0}, src2 = {0};
  // src1 = 2;
  // src2 = 0;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000000;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_6) {
  // 5224
  decimal src1 = {0}, src2 = {0};
  // src1 = 6521;
  // src2 = 74121;

  src1.bits[0] = 0b00000000000000000001100101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000010010000110001001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_7) {
  // 5242
  decimal src1 = {0}, src2 = {0};
  // src1 = 4;
  // src2 = 97623323;

  src1.bits[0] = 0b00000000000000000000000000000100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000101110100011001110100011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_8) {
  // 5260
  decimal src1 = {0}, src2 = {0};
  // src1 = 65658654;
  // src2 = 5;

  src1.bits[0] = 0b00000011111010011101111100011110;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000101;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_9) {
  // 5278
  decimal src1 = {0}, src2 = {0};
  // src1 = -364748;
  // src2 = 1;

  src1.bits[0] = 0b00000000000001011001000011001100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_10) {
  // 5296
  decimal src1 = {0}, src2 = {0};
  // src1 = 1;
  // src2 = 98745654321;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b11111101101100110001110000110001;
  src2.bits[1] = 0b00000000000000000000000000010110;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_11) {
  // 5314
  decimal src1 = {0}, src2 = {0};
  // src1 = -9878798789;
  // src2 = -3;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(is_equal_12) {
  // 5332
  decimal src1 = {0}, src2 = {0};
  // src1 = 9999999999999999999;
  // src2 = 1;

  src1.bits[0] = 0b10001001111001111111111111111111;
  src1.bits[1] = 0b10001010110001110010001100000100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;

  src2.bits[0] = 0b00000000000000000000000000000001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = is_equal(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(not_equal_0) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  decimal dec1 = {0};
  decimal dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(not_equal_1) {
  float num1 = 1.39;
  float num2 = 1.39;
  decimal dec1 = {0};
  decimal dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(not_equal_2) {
  float num1 = 1.39;
  float num2 = -1.39;
  decimal dec1 = {0};
  decimal dec2 = {0};
  from_float_to_decimal(num1, &dec1);
  from_float_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(not_equal_3) {
  int num1 = 0;
  int num2 = 0;
  decimal dec1 = {0};
  decimal dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(not_equal_4) {
  int num1 = 3;
  int num2 = 9;
  decimal dec1 = {0};
  decimal dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(not_equal_5) {
  int num1 = -3;
  int num2 = -3;
  decimal dec1 = {0};
  decimal dec2 = {0};
  from_int_to_decimal(num1, &dec1);
  from_int_to_decimal(num2, &dec2);
  int res = is_not_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(not_equal_6) {
  decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  decimal dec2 = {{12, 0, 0, 0b10000000000000010000000000000000}};  // -1.2;
  ck_assert_int_eq(is_not_equal(dec1, dec2), 1);
}
END_TEST
START_TEST(not_equal_7) {
  decimal dec3 = {
      {120000, 0, 0, 0b00000000000001000000000000000000}};  //  12.0000
  decimal dec4 = {{12, 0, 0, 0b00000000000000000000000000000000}};  //
  ck_assert_int_eq(is_not_equal(dec3, dec4), 0);
}
END_TEST
START_TEST(not_equal_8) {
  decimal dec5 = {{0, 0, 0, 0b00000000000000000000000000000000}};   //  0
  decimal dec6 = {{00, 0, 0, 0b00000000000000010000000000000000}};  //
  ck_assert_int_eq(is_not_equal(dec5, dec6), 0);
}
END_TEST
START_TEST(not_equal_9) {
  decimal dec7 = {{0, 0, 0, 0b00000000000000000000000000000000}};  //   0
  decimal dec8 = {{0, 0, 0, 0b10000000000000000000000000000000}};  //  -0;
  ck_assert_int_eq(is_not_equal(dec7, dec8), 0);
}
END_TEST

Suite *comparison_suite(void) {
  Suite *s;
  TCase *tc1_1;

  s = suite_create("S21 Comparison");
  tc1_1 = tcase_create("Core");
  suite_add_tcase(s, tc1_1);

  // Меньше
  tcase_add_test(tc1_1, less_0);
  tcase_add_test(tc1_1, less_1);
  tcase_add_test(tc1_1, less_2);
  tcase_add_test(tc1_1, less_3);
  tcase_add_test(tc1_1, less_4);
  tcase_add_test(tc1_1, less_5);
  tcase_add_test(tc1_1, less_6);
  tcase_add_test(tc1_1, less_7);
  tcase_add_test(tc1_1, less_8);
  tcase_add_test(tc1_1, less_9);
  tcase_add_test(tc1_1, less_10);

  // Меньше или равно
  tcase_add_test(tc1_1, is_less_or_equal_0);
  tcase_add_test(tc1_1, is_less_or_equal_1);
  tcase_add_test(tc1_1, is_less_or_equal_2);
  tcase_add_test(tc1_1, is_less_or_equal_3);
  tcase_add_test(tc1_1, is_less_or_equal_4);
  tcase_add_test(tc1_1, is_less_or_equal_5);
  tcase_add_test(tc1_1, is_less_or_equal_6);
  tcase_add_test(tc1_1, is_less_or_equal_7);
  tcase_add_test(tc1_1, is_less_or_equal_8);
  tcase_add_test(tc1_1, is_less_or_equal_9);
  tcase_add_test(tc1_1, is_less_or_equal_10);
  tcase_add_test(tc1_1, is_less_or_equal_11);
  tcase_add_test(tc1_1, is_less_or_equal_12);
  tcase_add_test(tc1_1, is_less_or_equal_13);
  tcase_add_test(tc1_1, is_less_or_equal_14);
  tcase_add_test(tc1_1, is_less_or_equal_15);
  tcase_add_test(tc1_1, is_less_or_equal_16);
  tcase_add_test(tc1_1, is_less_or_equal_17);
  tcase_add_test(tc1_1, is_less_or_equal_18);
  tcase_add_test(tc1_1, is_less_or_equal_19);
  tcase_add_test(tc1_1, is_less_or_equal_20);
  tcase_add_test(tc1_1, is_less_or_equal_21);
  tcase_add_test(tc1_1, is_less_or_equal_22);
  tcase_add_test(tc1_1, is_less_or_equal_23);
  tcase_add_test(tc1_1, is_less_or_equal_24);
  tcase_add_test(tc1_1, is_less_or_equal_25);
  tcase_add_test(tc1_1, is_less_or_equal_26);
  tcase_add_test(tc1_1, is_less_or_equal_27);
  tcase_add_test(tc1_1, is_less_or_equal_28);
  tcase_add_test(tc1_1, is_less_or_equal_29);

  // Больше
  tcase_add_test(tc1_1, is_greater_0);
  tcase_add_test(tc1_1, is_greater_1);
  tcase_add_test(tc1_1, is_greater_2);
  tcase_add_test(tc1_1, is_greater_3);
  tcase_add_test(tc1_1, is_greater_4);
  tcase_add_test(tc1_1, is_greater_5);
  tcase_add_test(tc1_1, is_greater_6);
  tcase_add_test(tc1_1, is_greater_7);
  tcase_add_test(tc1_1, is_greater_8);
  tcase_add_test(tc1_1, is_greater_9);
  tcase_add_test(tc1_1, is_greater_10);
  tcase_add_test(tc1_1, is_greater_11);
  tcase_add_test(tc1_1, is_greater_12);
  tcase_add_test(tc1_1, is_greater_13);
  tcase_add_test(tc1_1, is_greater_14);
  tcase_add_test(tc1_1, is_greater_15);
  tcase_add_test(tc1_1, is_greater_16);
  tcase_add_test(tc1_1, is_greater_17);
  tcase_add_test(tc1_1, is_greater_18);
  tcase_add_test(tc1_1, is_greater_19);
  tcase_add_test(tc1_1, is_greater_20);
  tcase_add_test(tc1_1, is_greater_21);
  tcase_add_test(tc1_1, is_greater_22);
  tcase_add_test(tc1_1, is_greater_23);
  tcase_add_test(tc1_1, is_greater_24);
  tcase_add_test(tc1_1, is_greater_25);
  tcase_add_test(tc1_1, is_greater_26);
  tcase_add_test(tc1_1, is_greater_27);
  tcase_add_test(tc1_1, is_greater_28);
  tcase_add_test(tc1_1, is_greater_29);

  // Больше или равно
  tcase_add_test(tc1_1, greater_or_equal_0);
  tcase_add_test(tc1_1, greater_or_equal_1);
  tcase_add_test(tc1_1, greater_or_equal_2);
  tcase_add_test(tc1_1, greater_or_equal_3);
  tcase_add_test(tc1_1, greater_or_equal_4);
  tcase_add_test(tc1_1, greater_or_equal_5);
  tcase_add_test(tc1_1, greater_or_equal_6);
  tcase_add_test(tc1_1, greater_or_equal_7);
  tcase_add_test(tc1_1, greater_or_equal_8);
  tcase_add_test(tc1_1, greater_or_equal_9);
  tcase_add_test(tc1_1, greater_or_equal_10);
  tcase_add_test(tc1_1, greater_or_equal_11);
  tcase_add_test(tc1_1, greater_or_equal_12);
  // Равно
  tcase_add_test(tc1_1, is_equal_0);
  tcase_add_test(tc1_1, is_equal_1);
  tcase_add_test(tc1_1, is_equal_2);
  tcase_add_test(tc1_1, is_equal_3);
  tcase_add_test(tc1_1, is_equal_4);
  tcase_add_test(tc1_1, is_equal_5);
  tcase_add_test(tc1_1, is_equal_6);
  tcase_add_test(tc1_1, is_equal_7);
  tcase_add_test(tc1_1, is_equal_8);
  tcase_add_test(tc1_1, is_equal_9);
  tcase_add_test(tc1_1, is_equal_10);
  tcase_add_test(tc1_1, is_equal_11);
  tcase_add_test(tc1_1, is_equal_12);
  // Не равно
  tcase_add_test(tc1_1, not_equal_0);
  tcase_add_test(tc1_1, not_equal_1);
  tcase_add_test(tc1_1, not_equal_2);
  tcase_add_test(tc1_1, not_equal_3);
  tcase_add_test(tc1_1, not_equal_4);
  tcase_add_test(tc1_1, not_equal_5);
  tcase_add_test(tc1_1, not_equal_6);
  tcase_add_test(tc1_1, not_equal_7);
  tcase_add_test(tc1_1, not_equal_8);
  tcase_add_test(tc1_1, not_equal_9);

  return s;
}

int test_comparison() {
  int no_failed = 0;
  Suite *s;
  SRunner *sr;

  s = comparison_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  no_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return no_failed;
}