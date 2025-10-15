#include <stdio.h>

struct Process 
{
    int id, at, bt, ct, tat, wt, rt, done, start;
};

int main() {
    int n, completed = 0, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }

    // Scheduling
    while (completed < n) {
        int idx = -1, min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++; // No process ready
        } else {
            p[idx].start = time;  // save start time for Gantt Chart
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].start - p[idx].at;

            time = p[idx].ct;
            p[idx].done = 1;
            completed++;
        }
    }

    // Sort by completion time for Gantt chart
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].ct > p[j].ct) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Output Table
    float total_wt = 0, total_tat = 0, total_rt = 0;
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].rt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);

    printf("\nGantt Chart\n\n|");
    time = 0;
    for(int i=0;i<n;i++)
    {
        if(time<p[i].at)
        {
            printf("\tIDLE\t|");
            time = p[i].at;
        }
        printf("\tP%d\t|",p[i].id);
        time = p[i].ct;
    }
    time = 0;
    printf("\n0");
    for(int i=0;i<n;i++)
    {
        if(time<p[i].at)
        {
            printf("\t\t%d",p[i].at);
            time = p[i].at;
        }
        printf("\t\t%d",p[i].ct);
        time = p[i].ct;
    }
}