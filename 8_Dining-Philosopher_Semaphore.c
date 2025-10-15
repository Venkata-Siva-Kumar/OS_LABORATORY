// Dinning Philosopher using semaphore
/* dining_simple.c
   Minimal deadlock-free Dining Philosophers using pthreads + semaphores.
   Compile: gcc -pthread dining_simple.c -o dining_simple
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5      // number of philosophers
#define TIMES 2  // times each philosopher will eat (small for demo)

sem_t forks[N]; // one semaphore per fork
sem_t room;     // allows at most N-1 philosophers to try

void *philosopher(void *arg) {
    int id = *(int*)arg;
    free(arg);

    for (int i = 0; i < TIMES; ++i) {
        // thinking
        printf("P%d is THINKING\n", id);
        usleep(100000); // 0.1s

        // enter room (prevent deadlock)
        sem_wait(&room);

        // pick forks
        sem_wait(&forks[id]);            // left
        sem_wait(&forks[(id + 1) % N]);  // right

        // eating
        printf("P%d is EATING (meal %d)\n", id, i + 1);
        // OS CSE308 SASTRA Deemed University 
        // By Dr. P. Venkateswari AP / CSE / SRC Page 7
        usleep(120000); // 0.12s

        // put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        // leave room
        sem_post(&room);
    }

    printf("P%d DONE\n", id);
    return NULL;
}

int main(void) {
    pthread_t t[N];

    // init forks (available = 1)
    for (int i = 0; i < N; ++i)
        sem_init(&forks[i], 0, 1);

    // room allows at most N-1 philosophers at once
    sem_init(&room, 0, N - 1);

    // create threads
    for (int i = 0; i < N; ++i) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&t[i], NULL, philosopher, id);
    }

    // wait for them to finish
    for (int i = 0; i < N; ++i)
        pthread_join(t[i], NULL);

    // cleanup
    for (int i = 0; i < N; ++i)
        sem_destroy(&forks[i]);

    sem_destroy(&room);

    printf("All finished. Exiting.\n");
    return 0;
}
