// Deadlock Banker’s Algorithm:
/* bankers.c
   Simple Banker's Algorithm implementation (deadlock avoidance)
   Compile: gcc bankers.c -o bankers
   Run: ./bankers
*/
#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10 /* max processes */
#define MAX_R 10 /* max resource types */



int P, R; /* actual numbers */

/* helper: print array */
void print_array(const char *label, int arr[], int n) {
    printf("%s: ", label);
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Safety algorithm: returns true if state is safe and fills safe_seq[] */
bool is_safe(int available[], int max[][MAX_R], int alloc[][MAX_R], int safe_seq[]) {
    bool finish[MAX_P] = {0};
    int work[MAX_R];

    for (int j = 0; j < R; ++j)
        work[j] = available[j];

    int need[MAX_P][MAX_R];
    for (int i = 0; i < P; ++i)
        for (int j = 0; j < R; ++j)
            need[i][j] = max[i][j] - alloc[i][j];

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; ++i) {
            if (!finish[i]) {
                bool can = true;
                for (int j = 0; j < R; ++j)
                    if (need[i][j] > work[j]) {
                        can = false;
                        break;
                    }

                if (can) {
                    /* pretend to run i -> release its resources */
                    for (int j = 0; j < R; ++j)
                        work[j] += alloc[i][j];
                    safe_seq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            break; /* no process can be satisfied now */
    }

    if (count == P)
        return true;
    return false;
}


int main(void) {
    int max[MAX_P][MAX_R], alloc[MAX_P][MAX_R], avail[MAX_R];
    int safe_seq[MAX_P];

    printf("Enter number of processes (P, <= %d): ", MAX_P);
    if (scanf("%d", &P) != 1 || P <= 0 || P > MAX_P) {
        printf("Invalid P\n");
        return 1;
    }

    printf("Enter number of resource types (R, <= %d): ", MAX_R);
    if (scanf("%d", &R) != 1 || R <= 0 || R > MAX_R) {
        printf("Invalid R\n");
        return 1;
    }

    printf("\nEnter Allocation matrix (P x R). Row i = allocation for process i\n");
    for (int i = 0; i < P; ++i)
        for (int j = 0; j < R; ++j)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max matrix (P x R). Row i = maximum demand for process i\n");
    for (int i = 0; i < P; ++i)
        for (int j = 0; j < R; ++j)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available vector (R):\n");
    for (int j = 0; j < R; ++j)
        scanf("%d", &avail[j]);

    /* show Need matrix (for clarity) */
    printf("\nNeed matrix (Max - Allocation):\n");
    for (int i = 0; i < P; ++i) {
        printf("P%d: ", i);
        for (int j = 0; j < R; ++j)
            printf("%d ", max[i][j] - alloc[i][j]);
        printf("\n");
    }

    /* Check safety of current state */
    if (is_safe(avail, max, alloc, safe_seq)) {
        printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
        for (int i = 0; i < P; ++i) {
            printf("P%d", safe_seq[i]);
            if (i < P - 1)
                printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state (possible deadlock).\n");
    }

    /* Optional: handle a single resource request */
    int req_proc;
    printf("\nDo you want to simulate a resource request? (enter process number 0..%d or -1 to skip): ", P - 1);


    if (scanf("%d", &req_proc) != 1)
        return 0;

    if (req_proc >= 0 && req_proc < P) {
        int request[MAX_R];
        printf("Enter request vector of length %d for P%d:\n", R, req_proc);
        for (int j = 0; j < R; ++j)
            scanf("%d", &request[j]);

        /* compute need */
        int need_proc[MAX_R];
        for (int j = 0; j < R; ++j)
            need_proc[j] = max[req_proc][j] - alloc[req_proc][j];

        /* check request <= need */
        bool ok = true;
        for (int j = 0; j < R; ++j)
            if (request[j] > need_proc[j]) {
                ok = false;
                break;
            }

        if (!ok) {
            printf("Error: Request exceeds process's declared maximum need. Request DENIED.\n");
            return 0;
        }

        /* check request <= available */
        for (int j = 0; j < R; ++j)
            if (request[j] > avail[j]) {
                ok = false;
                break;
            }

        if (!ok) {
            printf("Resources not available now. Request must wait.\n");
            return 0;
        }

        /* Pretend to allocate and test safety */
        for (int j = 0; j < R; ++j) {
            avail[j] -= request[j];
            alloc[req_proc][j] += request[j];
            /* need would reduce implicitly as max-alloc */
        }

        if (is_safe(avail, max, alloc, safe_seq)) {
            printf("Request can be GRANTED safely.\nSafe sequence after granting: ");
            for (int i = 0; i < P; ++i) {
                printf("P%d", safe_seq[i]);
                if (i < P - 1)
                    printf(" -> ");
            }
            printf("\n");
        } else {
            printf("Granting request would lead to unsafe state. Request DENIED.\n");

            /* rollback */

            for (int j = 0; j < R; ++j) {
                avail[j] += request[j];
                alloc[req_proc][j] -= request[j];
            }
        }
    } else {
        printf("Skipping request simulation.\n");
    }

    return 0;
}
