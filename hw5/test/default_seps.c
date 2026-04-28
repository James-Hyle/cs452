#include "scanner.h"
#include <stdio.h>

int main(void) {
  char buf[100];
  ssize_t n;

  File f = {
      .seps = (char *)defaults,
      .sep_len = sizeof(defaults),
      .data = "   ",
      .data_len = 3,
      .pos = 0,
      .eot = 0,
  };

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected -1\n", n);

  return 0;
}
