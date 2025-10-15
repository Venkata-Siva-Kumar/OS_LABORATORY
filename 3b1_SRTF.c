#include <stdio.h>
#include <stdbool.h>

#define MAX 100

struct Process {
    int id, at, bt, rt; 
    int ct, tat, wt, start_time, rp;
    bool started;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT and BT for P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].started = false;
        p[i].rp = -1;
    }

    int completed = 0, time = 0;
    int gcID[MAX], gcST[MAX], gcCT[MAX], gcCount = 0;

    while (completed < n) 
    {
        int idx = -1, minRT = 1e9;
        for (int i = 0; i < n; i++) 
        {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT) 
            {
                minRT = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) 
        {
            time++;
            continue;
        }

        // Response time
        if (!p[idx].started) 
        {
            p[idx].rp = time - p[idx].at;
            p[idx].started = true;
        }

        // Gantt Chart log
        if (gcCount == 0 || gcID[gcCount - 1] != p[idx].id) 
        {
            gcID[gcCount] = p[idx].id;
            gcST[gcCount] = time;
            gcCount++;
        }

        time++;
        p[idx].rt--;

        if (p[idx].rt == 0) 
        {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;

            gcCT[gcCount - 1] = time; // End time of that execution block
        } 
        else 
        {
            gcCT[gcCount - 1] = time;
        }
    }

    // Print Process Table
    float totalWT = 0, totalTAT = 0, totalRT = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) 
    {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        totalRT += p[i].rp;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rp);
    }

    printf("\nAverage WT: %.2f", totalWT / n);
    printf("\nAverage TAT: %.2f", totalTAT / n);
    printf("\nAverage RT: %.2f\n", totalRT / n);

    // -------- Gantt Chart --------
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gcCount; i++) 
    {
        printf("\tP%d\t|", gcID[i]);
    }
    printf("\n");

    printf("%d", gcST[0]);
    for (int i = 0; i < gcCount; i++) 
    {
        printf("\t\t%d", gcCT[i]);
    }
    printf("\n");

    return 0;
}