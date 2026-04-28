#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd = open("/tmp/test1", O_RDONLY);
  if (fd < 0)
    ERR("open() failed");
  enum { size = 5 };
  char buf[size + 1];
  for (int len; (len = read(fd, buf, size));) {
    buf[len] = 0;
    printf("%s", buf);
  }
  close(fd);
  return 0;
}
