#include <pthread.h>
// For the thread_helper we need 2 functions
// 1. A function to create n number of threads that each call a given function
// 2. A function to join (wait for) those n threads to finsh

/**
 * @brief Helper function to create n number of threads that each call a given function
 * @param n Number of threads to create
 * @param func Pointer to the function each thread will run
 * @param arg Argument to pass to each thread
 * @return Array of thread IDs
 */

extern pthread_t *thread_helper_create(int n, void *(*func)(void *), void *arg);

/**
 * @brief A function to join (wait for) those n threads to finsh
 * @param n Number of threads to join
 * @param threads Array of thread IDs
 */
extern void thread_helper_join(int n, pthread_t *threads);