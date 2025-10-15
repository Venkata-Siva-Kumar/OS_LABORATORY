// Readers & Writers using Semaphore
#include <stdio.h>
#include <stdlib.h>

int readcount = 0;   // number of readers currently reading
int writecount = 0;  // number of writers currently writing (0 or 1)
int shared_data = 0; // shared resource

// semaphores (simulated using integers)
int mutex = 1; // for readcount
int wrt = 1;   // for writer access

// semaphore wait (P) operation
void wait(int *S) {
    (*S)--;
    while (*S < 0) {
        // busy wait
    }
}

// semaphore signal (V) operation
void signal(int *S) {
    (*S)++;
}

void reader() {
    wait(&mutex);
    readcount++;
    if (readcount == 1)
        wait(&wrt); // first reader locks the writer
    signal(&mutex);

    // critical section
    printf("Reader is READING. Shared data = %d\n", shared_data);

    wait(&mutex);
    readcount--;
    if (readcount == 0)
        signal(&wrt); // last reader unlocks writer
    signal(&mutex);
}

void writer() {
    wait(&wrt); // only one writer at a time
    shared_data++;
    printf("Writer is WRITING. Updated shared data = %d\n", shared_data);
    signal(&wrt);
}

int main() {
    int choice;
    printf("Readers-Writers Problem (Simple Simulation)\n");
    printf("-------------------------------------------\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Reader\n");
        printf("2. Writer\n");
        printf("3. Show Shared Data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                reader();
                break;

            case 2:
                writer();
                break;

            case 3:
                printf("Current Shared Data = %d\n", shared_data);
                break;

            case 4:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
