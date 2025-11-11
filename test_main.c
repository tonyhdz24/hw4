#include <stdio.h>
#include "thread_helper.h"

void *foo(void *arg)
{
    printf("Created an new thread 🪡");
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("Running test\n");
    pthread_t *threads = thread_helper_create(1, foo, 0);

    return 0;
}
