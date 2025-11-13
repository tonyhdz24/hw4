#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "thread_helper.h"
#include "mt_deq_wrapper.h"

// Doubly link Queue from HW1
#include "deq.h"

static void *produce(void *a)
{
  void **arg = a;
  Mtq q = (Mtq)arg[0];
  Lawn l = (Lawn)arg[1];
  mtq_tail_put(q, mole_new(l, 0, 0));
  return NULL;
}
static void *consume(void *a)
{
  void **args = a;

  Mtq q = (Mtq)args[0];
  // Get mole at the head of the queue
  Mole m = mtq_head_get(q);
  // whack mole
  mole_whack(m);

  return NULL;
}

int main()
{
  // Array to store arguments for produce
  void *args[2];
  // Creating a single thread queue
  // Deq single_queue = deq_new();
  Mtq multi_queue = mtq_new(4);
  srandom(time(0));
  const int n = 10;
  Lawn lawn = lawn_new(0, 0);

  // Adding the queue & lawn to args array
  args[0] = multi_queue;
  args[1] = lawn;

  // Creating threads
  pthread_t *produce_threadIDs = thread_helper_create(n, produce, args);
  pthread_t *consume_threadIDs = thread_helper_create(n, consume, args);

  // Joining threads
  thread_helper_join(n, produce_threadIDs);
  thread_helper_join(n, consume_threadIDs);

  // freeing resources
  mtq_free(multi_queue);
  lawn_free(lawn);
}
