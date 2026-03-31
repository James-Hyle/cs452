#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "deq.h"
#include "mtq.h"
#include "lawn.h"
#include "mole.h"
#define LAWNIMP
#include "lawnimp.h"
#undef LAWNIMP

static void *produce(void *a) {
  void **arg = a;
  mtq q = (mtq)arg[0];
  Lawn l = (Lawn)arg[1];
  mtq_tail_put(q, mole_new(l, 0, 0));
  return 0;
}

static void *consume(void *a) {
  void **arg = a;
  mtq q = (mtq)arg[0];
  mole_whack(mtq_head_get(q));
  return 0;
}

int main(int argc, char *argv[]) {
  // guard
  if (argc < 2) {
    ERROR("usage: ./wam <nThreads>\n");
    return 1;
  }
  
  // get capacity from user
  int nThreads = atoi(argv[1]);
  
  // guard
  if (nThreads == 0) {
    ERROR("usage: ./wam <nThreads>\n");
    return 1;
  }

  srandom(time(0));
  mtq q = mtq_new(4);
  Lawn lawn = lawn_new(0, 0);

  void *args[2];
  args[0] = q;
  args[1] = lawn;

  mtq_run(produce, args, nThreads);
  mtq_run(consume, args, nThreads);
  mtq_wait(nThreads * 2);

  lawn_free(lawn);
  return 0;
}
