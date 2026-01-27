#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4

void *worker(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d is running\n", id);
    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    int err;

    /* Create threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;

        err = pthread_create(&threads[i], NULL, worker, &ids[i]);
        if (err != 0) {
            fprintf(stderr, "pthread_create failed: %s\n", strerror(err));
            return EXIT_FAILURE;
        }
    }

    /* Join threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        err = pthread_join(threads[i], NULL);
        if (err != 0) {
            fprintf(stderr, "pthread_join failed: %s\n", strerror(err));
            return EXIT_FAILURE;
        }
    }

    printf("All threads have finished\n");
    return EXIT_SUCCESS;
}
