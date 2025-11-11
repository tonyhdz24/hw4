#include <stdlib.h>
#include <stdio.h>
#include "thread_helper.h"
#include "error.h"

// Thread_helper_create
pthread_t *thread_helper_create(int n, void *(*func)(void *), void *arg)
{
    // 1. Allocate array of n pthread_t
    pthread_t *threadsIDs = malloc(n * sizeof(pthread_t));

    // Check if malloc was successful
    if (!threadsIDs)
    {
        ERROR("malloc failed");
        return 0;
    }
    // 2. Loop n times
    for (int i = 0; i < n; i++)
    {
        //      - Call pthread_create for thread i

        pthread_t threadID; // where the ID of the new thread will be stored
        int thread_creation_status = pthread_create(&threadID, NULL, func, arg);
        // check if the thread creation was successful
        if (thread_creation_status != 0)
        {
            // TODO user the ERROR.h to handle errors more gracefuly
            ERROR("pthread_create failed");
            return 0;
        }

        //      - Store thread ID in array[i]
        // printf("DEBUG Succesfully Created thread\n");
        // printf("DEBUG Created thread ID: %lu\n", (unsigned long)threadID);
        threadsIDs[i] = threadID;
    }
    // printf("DEBUG Succesfully Created thread ID array\n");

    return threadsIDs;
}

extern void thread_helper_join(int n, pthread_t *threads)
{
    for (int i = 0; i < n; i++)
    {
        // Check that the thread was joined successfully
        if (pthread_join(threads[i], 0) != 0)
        {
            ERROR("Thread joining failed");
        }
    }

    // Free thread array from memory
    free(threads);
}
