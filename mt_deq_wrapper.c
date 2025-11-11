#include "mt_deq_wrapper.h"
#include "deq.h"

#include <stdio.h>
#include <stdlib.h>

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
extern Data mtq_head_get(Mtq mtq)
{
    // 1. Lock mutex
    if (pthread_mutex_lock(&mtq->mutex_lock) != 0)
    {
        ERROR("pthread_mutex_lock() Failed....");
    }
    // 2. while count == 0 (queue is empty)
    while (mtq->count == 0)
    {
        // Wait on "not_empty" CV (releases lock while waiting)
        pthread_cond_wait(&mtq->not_empty, &mtq->mutex_lock);
    }
    // 3. Get item from deq
    Data returned_thread = deq_head_get(mtq->deq);
    // 4. Decrement count
    mtq->count -= 1;
    // 5. Signal "not_full" CV (wake up a waiting producer)
    pthread_cond_signal(&mtq->not_full);
    // 6. Unlock mutex
    pthread_mutex_unlock(&mtq->mutex_lock);
    // 7. Return item
    return returned_thread;
}

extern void mtq_tail_put(Mtq mtq, Data d)
{
    // 1. Lock mutex
    pthread_mutex_lock(&mtq->mutex_lock);
    // 2. while count >= capacity AND capacity > 0  (queue is full)
    while (mtq->count >= mtq->capacity && mtq->capacity > 0)
    {
        //      Wat in "not full" CV (releases lock while waiting)
        pthread_cond_wait(&mtq->not_full, &mtq->mutex_lock);
    }
    // 3. Add item to deq
    deq_tail_put(mtq->deq, d);
    // 4. incrmeent count
    mtq->count += 1;
    // 5. Signal "not_empty" CV (wake up a waiting consumer)
    pthread_cond_signal(&mtq->not_empty);

    pthread_mutex_unlock(&mtq->mutex_lock);
};

extern void mtq_free(Mtq mtq)
{
    // Deallocate internal deq
    deq_del(mtq->deq, NULL);
    // Deallocate mtq
    free(mtq);
}