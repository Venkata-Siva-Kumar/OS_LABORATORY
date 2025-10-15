#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

/* Simulation of semaphores/mutex using integers (as in original approach) */
int mutex = 1;     // binary semaphore (1 = unlocked, 0 = locked)
int full = 0;      // number of full slots
int empty = BUFFER_SIZE; // number of empty slots

/* Bounded circular buffer */
int buffer[BUFFER_SIZE];
int in = 0;  // next write index
int out = 0; // next read index

/* simple item counter (for producing item numbers) */
int produced_count = 0;

void producer() {
    /* try to enter critical section */
    if (mutex == 1 && empty > 0) {
        --mutex; // lock

        /* produce an item */
        produced_count++;
        int item = produced_count;

        /* store in buffer (circular) */
        buffer[in] = item;
        printf("\nProducer produces item %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        ++full;
        --empty;

        ++mutex; // unlock
    } else {
        printf("\nCannot produce: Buffer is full or locked.\n");
    }
}

void consumer() {
    /* try to enter critical section */
    if (mutex == 1 && full > 0) {
        --mutex; // lock

        /* consume an item */
        int item = buffer[out];
        printf("\nConsumer consumes item %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        --full;
        ++empty;

        ++mutex; // unlock
    } else {
        printf("\nCannot consume: Buffer is empty or locked.\n");
    }
}

int main() {
    int choice;
    printf("Producer-Consumer simulation (buffer size = %d)\n", BUFFER_SIZE);

    while (1) {
        printf("\nMenu:\n");
        printf(" 1. Produce\n");
        printf(" 2. Consume\n");
        printf(" 3. Show buffer\n");
        printf(" 4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            /* handle non-integer input */
            fprintf(stderr, "Invalid input. Exiting.\n");
            exit(EXIT_FAILURE);
        }

        switch (choice) {
            case 1:
                if (mutex == 1 && empty > 0)
                    producer();
                else
                    printf("Buffer is full!\n");
                break;

            case 2:
                if (mutex == 1 && full > 0)
                    consumer();
                else
                    printf("Buffer is empty!\n");
                break;

            case 3:
                printf("\nBuffer state (full=%d empty=%d):\n", full, empty);
                if (full == 0) {
                    printf(" [empty]\n");
                } else {
                    int i, idx = out;
                    for (i = 0; i < full; ++i) {
                        printf(" buffer[%d] = %d\n", idx, buffer[idx]);
                        idx = (idx + 1) % BUFFER_SIZE;
                    }
                }
                break;

            case 4:
                printf("Exiting.\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }

    return 0;
}
