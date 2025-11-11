#include "mt_deq_wrapper.h"
#include "deq.h"
#include <pthread.h>

typedef struct
{
    Deq deq;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
    int capacity;
    int count;
    pthread_mutex_t mutex_lock;
} *Mtq;


// extern Mtq mtq_new(int capacity);

// extern Data mtq_head_get(Mtq mtq);
// 1. Lock mutex
// 2. while count == 0 (queue is empty)
//      Wait on "not_empty" CV (releases lock while waiting)
// 3. Get item from deq
// 4. Decrement count
// 5. Signal "not_full" CV (wake up a waiting producer)
// 6. Unlock mutex
// 7. Return item

// extern void mtq_tail_put(Mtq mtq, Data d);
// 1. Lock mutex
// 2. while count >= capacity AND capacity > 0  (queue is full)
//      Wat in "not full" CV (releases lock while waiting)
// 3. Add item to deq
// 4. incrmeent count
// 5. Signal "not_empty" CV (wake up a waiting consumer)
// 6. Unlock mutex

// Q4 - We use while instead of IF becasue we want the thread to wait for the CV to signal. If we used IF instead then it would check and them just move on not waitng for the CV to actually signal 