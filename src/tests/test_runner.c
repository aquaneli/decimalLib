#include "decimal_tests.h"

int main() {
  int no_failed = 0;

  no_failed |= test_arithmetic();
  no_failed |= test_comparison();
  no_failed |= test_conversion();
  no_failed |= test_other();

  return (no_failed == 0) ? 0 : 1;
}
