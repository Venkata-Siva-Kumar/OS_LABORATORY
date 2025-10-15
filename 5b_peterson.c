#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

volatile int flag[2];
volatile int turn;
#define ITER 5

void *process_func(void *arg) {
    int i = *((int *)arg);
    int j = 1 - i;

    for (int iter = 0; iter < ITER; ++iter) {
        flag[i] = 1;
        turn = j;
        while (flag[j] && turn == j) {
            usleep(100);
        }

        // Critical Section
        printf("[Process %d] Enter cs (iteration %d)\n", i, iter + 1);
        usleep(200000);
        printf("[Process %d] Exit cs (iteration %d)\n", i, iter + 1);

        flag[i] = 0;
        usleep(100000);
    }
    return NULL;
}

int main(void) {
    pthread_t t0, t1;
    int id0 = 0, id1 = 1;

    flag[0] = flag[1] = 0;
    turn = 0;

    if (pthread_create(&t0, NULL, process_func, &id0) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&t1, NULL, process_func, &id1) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("All processes finished.\n");
    return 0;
}