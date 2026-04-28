#ifndef SCANNER_H
#define SCANNER_H

#include <string.h>
#include <unistd.h>

typedef struct {
  char *seps;
  size_t sep_len;
  int sep_mode;
  int eot;
  char *data;
  size_t data_len;
  size_t pos;
} File;

static const char defaults[] = {' ', '\t', '\n', ':'};

static int is_sep(File *file, char c) {
  size_t i;
  for (i = 0; i < file->sep_len; i++)
    if (file->seps[i] == c)
      return 1;
  return 0;
}

static ssize_t scanner_read(File *file, char *buf, size_t count) {
  size_t start, n;

  if (count == 0)
    return 0;

  if (file->eot) {
    file->eot = 0;
    return 0;
  }

  while (file->pos < file->data_len && is_sep(file, file->data[file->pos]))
    file->pos++;

  if (file->pos >= file->data_len)
    return -1;

  start = file->pos;
  n = 0;
  while (file->pos < file->data_len && !is_sep(file, file->data[file->pos]) &&
         n < count) {
    file->pos++;
    n++;
  }

  if (file->pos >= file->data_len || is_sep(file, file->data[file->pos]))
    file->eot = 1;

  memcpy(buf, file->data + start, n);
  return (ssize_t)n;
}

#endif
