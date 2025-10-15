#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 3

typedef struct {
    int id, priority;
} ThreadInfo;

void* thread_task(void *arg) {
    ThreadInfo* info = (ThreadInfo*)arg;
    int i = 0, j = 0;

    for (i = 0; i < 5; i++) {
        printf("Thread %d running with priority %d\n", info->id, info->priority);
        for (j = 0; j < info->priority; j++) {
            printf("--> Thread %d executing slice %d\n", info->id, j + 1);
            usleep(200000); // 0.2 sec
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREAD_COUNT];
    ThreadInfo infos[THREAD_COUNT];

    infos[0].id = 1;
    infos[1].id = 2;
    infos[2].id = 3;

    infos[0].priority = 3;
    infos[1].priority = 2;
    infos[2].priority = 1;

    int i = 0;
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, thread_task, (void*)&infos[i]);
    }

    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads finished Execution\n");
    return 0;
}