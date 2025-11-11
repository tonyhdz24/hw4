#include "thread_helper.h"

// Thread_helper_create
pthread_t *thread_helper_create(int n, void *(*func)(void *), void *arg)
{
    // 1. Allocate array of n pthread_t

    pthread_t *threads = (pthread_t *)malloc(n);
    // Check if malloc was successful
    if (!threads)
    {
        // TODO user the ERROR.h to handle errors more gracefuly
        return 0;
    }
    // 2. Loop n times
    for (int i = 0; i < n; i++)
    {
        //      - Call pthread_create for thread i

        pthread_t thread; // where the ID of the new thread will be stored
        int thread_creation_status = pthread_create(&thread, NULL, func, NULL);
        // check if the thread creation was successful
        if (!thread_creation_status)
        {
            // TODO user the ERROR.h to handle errors more gracefuly
            return 0;
        }

        //      - Store thread ID in array[i]
        

        //      - Each thread runs func(arg)
    }
}

// 1. Allocate array of n pthread_t
// 2. Loop n times:
//      - Call pthread_create for thread i
//      - Store thread ID in array[i]
//      - Each thread runs func(arg)
// 3. Return the array

// **Questions:**
// 1. What happens if `pthread_create` fails? (Should you check the return value?)

//      Yes we'd have to know if any fail because then there wouldnt be n number threads and that might cause problems. We'd have to check but Im not sure what to do if a thread creating fails. I think the whole program should exit

// 2. All threads get the **same** arg - is that what we want? (Yes! All producers share the same queue/lawn)
//      Yes all threads will need the samye args

// thread_helper_join
// 1. loop n times"
//      - Call pthread_join on thread[i]
// 2. Free the threads array
// Questions:
// Should this function free the array, or should main do it?
//      This function should free the array, I think that havig all things associated with the threads being handled by the thread helper instead of main makes things cleaner and more straigh forward
// What if pthread_join fails?
//      Again I think that the whole program should gracfuly exit

// Next steps

// Now Implement!
// You have everything you need:

// Fix the include to <pthread.h>
// Implement thread_helper_create:

// malloc array
// loop and pthread_create
// check for errors, ERROR if problems
// return array

// Implement thread_helper_join:

// loop and pthread_join
// check for errors, ERROR if problems
// free the array

// Go code it up! Then show me your thread_helper.c and let's review it.
// What does your implementation look like?Retry