#include "mt_deq_wrapper.h"
#include "deq.h"

#include <stdio.h>
#include <stdlib.h>


// TODO
extern Mtq mtq_new(int capacity)
{
    // Allocate memory for struct
    Mtq mtq = (Mtq)malloc(sizeof(*mtq));

    if (!mtq)
    {
        ERROR("malloc() failed");
    }
    // Init struct variables
    mtq->deq = deq_new();
    mtq->capacity = capacity;
    mtq->count = 0;
    // INIT pthread variables
    if (pthread_cond_init(&mtq->not_empty, NULL) != 0)
    {
        ERROR("pthread_cond_init() for not_empty failed");
    }
    if (pthread_cond_init(&mtq->not_full, NULL) != 0)
    {
        ERROR("pthread_cond_init() for not_full failed");
    };
    if (pthread_mutex_init(&mtq->mutex_lock, NULL) != 0)
    {
        ERROR("pthread_mutex_init() for mutex_lock failed");
    };

    return mtq;
};

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