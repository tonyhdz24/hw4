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
  Deq q = (Deq)arg[0];
  Lawn l = (Lawn)arg[1];
  deq_tail_put(q, mole_new(l, 0, 0));
  return NULL;
}
static void *consume(void *a)
{
  void **args = a;

  Deq q = (Deq)args[0];
  // Get mole at the head of the queue
  Mole m = deq_head_get(q);
  // whack mole
  mole_whack(m);

  return NULL;
}

int main()
{

  // =======================================
  // Testing
  // =======================================
  printf("Multi-threaded wrapper init...\n");
  Mtq mtq = mtq_new(4);

  printf("Multi-threaded wrapper done..\n");

  // =======================================
  // Array to store arguments for produce
  void *args[2];
  // Creating a single thread queue
  Deq single_queue = deq_new();
  srandom(time(0));
  const int n = 10;
  Lawn lawn = lawn_new(0, 0);

  // Adding the queue & lawn to args array
  args[0] = single_queue;
  args[1] = lawn;

  // for (int i = 1; i <= n; i++)
  // {
  //   Old code
  //   produce(args);
  //   consume(args);
  // }
  // New
  // Creating produce threads
  pthread_t *produce_threadIDs = thread_helper_create(n, produce, args);
  // Creating consume threads
  pthread_t *consume_threadIDs = thread_helper_create(n, consume, args);

  thread_helper_join(n, produce_threadIDs);
  thread_helper_join(n, consume_threadIDs);
  // freeing resources
  deq_del(single_queue, 0);
  lawn_free(lawn);
}
