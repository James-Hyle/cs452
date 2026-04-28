#include "scanner.h"
#include <stdio.h>

int main(void) {
  char buf[100];
  ssize_t n;

  File f = {
      .seps = (char *)defaults,
      .sep_len = sizeof(defaults),
      .data = "foo bar baz",
      .data_len = 11,
      .pos = 0,
      .eot = 0,
  };

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 3\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 0\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 3\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 0\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 3\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected 0\n", n);

  n = scanner_read(&f, buf, sizeof(buf));
  printf("read() = %zd expected -1\n", n);

  return 0;
}
