#include <stdio.h>

struct Process {
    int id, at, bt, rbt;
    int ct, tat, wt, rt;
    int qlevel;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input AT and BT
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rbt = p[i].bt;
        p[i].qlevel = 1;   // start in Q1
        p[i].rt = -1;
    }

    int tq1, tq2;
    printf("Enter Time Quantum for Q1: ");
    scanf("%d", &tq1);
    printf("Enter Time Quantum for Q2: ");
    scanf("%d", &tq2);

    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    // Gantt chart arrays
    int gcID[500], gcST[500], gcCT[500], gcCount = 0;

    while (completed < n) {
        int idx = -1, slice = 0, bestQ = 4;

        // Pick highest-priority ready process
        for (int i = 0; i < n; i++) {
            if (p[i].rbt > 0 && p[i].at <= time && p[i].qlevel < bestQ) {
                idx = i;
                bestQ = p[i].qlevel;
            }
        }

        if (idx != -1) {
            if (p[idx].rt == -1) 
                p[idx].rt = time - p[idx].at;  // Response time

            // Allocate CPU slice
            if (p[idx].qlevel == 1) slice = (p[idx].rbt > tq1) ? tq1 : p[idx].rbt;
            else if (p[idx].qlevel == 2) slice = (p[idx].rbt > tq2) ? tq2 : p[idx].rbt;
            else slice = p[idx].rbt;

            // Record Gantt chart
            gcID[gcCount] = p[idx].id;
            gcST[gcCount] = time;
            time += slice;
            p[idx].rbt -= slice;
            gcCT[gcCount] = time;
            gcCount++;

            // If finished
            if (p[idx].rbt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;

                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
                total_rt += p[idx].rt;
            } else {
                // Demote process
                if (p[idx].qlevel < 3) p[idx].qlevel++;
            }
        } else {
            // CPU idle
            gcID[gcCount] = 0;
            gcST[gcCount] = time;
            time++;
            gcCT[gcCount] = time;
            gcCount++;
        }
    }

    // -------- Process Table --------
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage WT  = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage RT  = %.2f\n", total_rt / n);

    // -------- Gantt Chart --------
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gcCount; i++) {
        if (gcID[i] == 0) printf(" Idle |");
        else printf("  P%d  |", gcID[i]);
    }
    printf("\n");

    printf("%d", gcST[0]);
    for (int i = 0; i < gcCount; i++) {
        printf("     %d", gcCT[i]);
    }
    printf("\n");

    return 0;
}