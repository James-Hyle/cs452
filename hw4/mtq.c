#include "mtq.h"
#include <pthread.h>

// array for threads
static pthread_t threads[100];
static int thread_count = 0;

// get length of inner queue
static int mtq_len(mtq q) {
  return deq_len(q->dq);
}

// create new mtq
mtq mtq_new(int size) {
  // allocate mtq based on struct
  mtq q = (mtq)malloc(sizeof(*q));
  // guard
  if (!q)
    ERROR("Malloc Fail!");
  // create new inner deq
  q->dq = deq_new();
  // initialize lock and condition variables
  pthread_mutex_init(&q->mutex, 0);
  pthread_cond_init(&q->occupied, 0);
  pthread_cond_init(&q->empty, 0);
  // set capacity of mtq
  q->capacity = size;
  return q;
}

// put data at end of queue
void mtq_tail_put(mtq q, Data d) {
  // lock data structure while putting data inside
  pthread_mutex_lock(&q->mutex);
  // wait for mtq to have space available
  while (q->capacity > 0 && mtq_len(q) >= q->capacity)
    pthread_cond_wait(&q->occupied, &q->mutex);

  // put data at end of queue
  deq_tail_put(q->dq, d);
  // signal that queue has stuff in it
  pthread_cond_signal(&q->empty);
  pthread_mutex_unlock(&q->mutex);
}

// get data from head of queue
Data mtq_head_get(mtq q) {
  // lock while retrieving data from queue
  pthread_mutex_lock(&q->mutex);
  // wait until not empty
  while (deq_len(q->dq) == 0)
    pthread_cond_wait(&q->empty, &q->mutex);

  // retrieve data from head
  Data d = deq_head_get(q->dq);
  // signal waiting producer
  pthread_cond_signal(&q->occupied);
  // unlock queue for next access
  pthread_mutex_unlock(&q->mutex);
  return d;
}

// spawn n threads 
void mtq_run(void *(*func)(void *), void *arg, int n) {
  for (int i = 0; i < n; i++)
    pthread_create(&threads[thread_count++], NULL, func, arg);
}

// wait for n threads to finish
void mtq_wait(int n) {
  for (int i = 0; i < n; i++)
    pthread_join(threads[--thread_count], NULL);
}
