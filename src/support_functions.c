#include "decimal.h"

void zero_decimal(decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int int_number(int index) { return index / 32; }

int bit_number(int index) { return index % 32; }

int get_bit(decimal dec, int bitindex) {
  int mask = 1 << bit_number(bitindex);
  return !!(dec.bits[int_number(bitindex)] & mask);
}

int set_bit(decimal *decl, int bitindex, int number) {
  int mask = 1u << bit_number(bitindex);
  int result = 0;
  if (int_number(bitindex) < 4 && number) {
    result = !!(decl->bits[int_number(bitindex)] |= mask);
  } else if (int_number(bitindex) < 4 && number == 0) {
    result = !!(decl->bits[int_number(bitindex)] &= ~mask);
  }
  return result;
}

int get_sign(decimal value) { return get_bit(value, 127); }

void set_sign(decimal *dst) { dst->bits[3] = dst->bits[3] | 1u << 31; }

int get_scale(decimal dst) {
  int mask = 127 << 16;
  int scale = (mask & dst.bits[3]) >> 16;
  return scale;
}

int get_exp(decimal value) { return (value.bits[3] & 0x00FF0000) >> 16; }

void set_scale(decimal *dst,
               int scale) {  // устанавливаем скейл (int scale) в децимал на
                             // который указатель
  int sign = 0;
  sign = get_sign(*dst);  // узнаем знак децимала
  dst->bits[3] = 0;       // обнуляем скейл децимала
  scale <<= 16;  // то же самое что умножить scale на 2 ы 16 степени перемещаем
                 // его на 16 бит как просят в задании
  dst->bits[3] =
      scale |
      dst->bits[3];  // зачем-то применяетс операция или с нулем я думаю что это
                     // равноценно тому чтобы просто приравнять к скейлу
  if (sign)
    set_sign(
        dst);  // если число отрицательное устанавливаем что оно отрицательное
               // (потому что при обнулении скейла это могло потеряться)
}

void copy_decimal(decimal *d1, decimal d2) {
  for (int i = 127; i >= 0; i--) {
    set_bit(d1, i, get_bit(d2, i));  // перемещаем биты из одного в другой
  }
}

int find_one(big_decimal value, int index_now, int *index_one) {
  // находим индекс единицы, у которой будем занимать десяток
  int res = 0;
  while (res != 1) {
    if (get_bit_big(value, index_now) == 1) {
      *index_one = index_now;
      res = 1;
    }
    index_now += 1;
  }
  return 0;
}
int change_to_zero(big_decimal *value, int index_one, int index_now) {
  for (int i = index_now + 1; i < index_one; i++) {
    set_bit_big(value, i, 1);
  }
  set_bit_big(value, index_one, 0);
  return 0;
}
