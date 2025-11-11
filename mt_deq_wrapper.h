#include "deq.h"
#include "error.h"
#include <pthread.h>
typedef struct Mtq
{
    Deq deq;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
    int capacity;
    int count;
    pthread_mutex_t mutex_lock;
} *Mtq;

typedef void *Data;

// Initializes a new mulit threaded queue
//

/**
 * @brief Initializes a new multi threaded queue wrapper
 *
 * @param capacity An optional capacity parameter that set the maximum size of the MTQ, Defaults to 0 meaning the MTQ is unbounded
 *
 * @return A multi threaded queue
 */
extern Mtq mtq_new(int capacity);

extern Data mtq_head_get(Mtq mtq);
extern void mtq_tail_put(Mtq mtq, Data d);

extern void mtq_free(Mtq mtq);
