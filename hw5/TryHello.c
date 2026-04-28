#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
  int fd = open("/dev/Hello", O_RDWR);
  if (fd < 0)
    ERR("open() failed");

  char buf[64];
  ssize_t n;

  if (write(fd, "hello", 5) < 0)
    ERR("write() failed");

  n = read(fd, buf, sizeof(buf));
  printf("read() = %zd expected 5\n", n);

  n = read(fd, buf, sizeof(buf));
  printf("read() = %zd expected 0\n", n);

  n = read(fd, buf, sizeof(buf));
  printf("read() = %zd expected -1\n", n);

  close(fd);
  return 0;
}
