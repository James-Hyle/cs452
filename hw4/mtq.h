#ifndef MTQ_H
#define MTQ_H

#include "deq.h"
#include "error.h"
#include <pthread.h>

// mtq: wrapper for deq
// dq: Deq
// mutex: lock for mtq
// full: tells client data is available at head
// empty: tells client data is not available
// capacity: number of moles mtq can hold

typedef struct mtq {
  Deq dq;
  pthread_mutex_t mutex;
  pthread_cond_t occupied, empty;
  unsigned int capacity;
} *mtq;

extern mtq mtq_new(int size);
extern void mtq_tail_put(mtq q, Data d);
extern Data mtq_head_get(mtq q);
extern void mtq_run(void *(*func)(void *), void *arg, int n);
extern void mtq_wait(int n);

#endif
