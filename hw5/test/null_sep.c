#include "scanner.h"
#include <stdio.h>

int main(void) {
  char buf[64];
  ssize_t n;
  char seps[] = {'\0'};

  File f = {
      .seps = seps,
      .sep_len = 1,
      .data = "ab\0cd",
      .data_len = 5,
      .pos = 0,
      .eot = 0,
  };

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 2\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 0\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 2\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 0\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected -1\n", n);

  return 0;
}
