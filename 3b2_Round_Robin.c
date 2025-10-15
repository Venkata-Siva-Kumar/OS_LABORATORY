#include<stdio.h>
#include<stdbool.h>
#define MAX 100
struct Process {
    int id,at,bt,ct,tat,wt,rp,rt;
    bool started;
};

int main()
{
    int n,time=0,tq;
    printf("Enter the no.of Processes : ");
    scanf("%d",&n);

    struct Process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].id = i+1;
        printf("Enter the Arrival Time and Burst Time for P%d: ",p[i].id);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].rt = p[i].bt;
        p[i].started = false;
        p[i].rp = -1;
    }

    printf("Enter the time quantum : ");
    scanf("%d",&tq);

    int completed = 0,queue[MAX],front=0,rear=0;
    bool inQueue[n];
    int gcID[MAX],gcST[MAX],gcCT[MAX],gcCount=0;
    for(int i=0;i<n;i++)
    {
        inQueue[i] = false;
    }

    for(int i=0;i<n;i++)
    {
        if(p[i].at==0)
        {
            queue[rear++] = i;
            inQueue[i] = true;
        }
    }

    while(completed<n)
    {
        if(front==rear)
        {
            time++;
            for(int i=0;i<n;i++)
            {
                if(!inQueue[i] && p[i].at<=time && p[i].rt>0)
                {
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++];
        gcID[gcCount] = p[idx].id;
        gcST[gcCount] = time;

        if(!p[idx].started)
        {
            p[idx].rp = time-p[idx].at;
            p[idx].started = true;
        }

        int exec = (p[idx].rt>tq) ? tq: p[idx].rt;
        time += exec;
        p[idx].rt -=exec;
        gcCT[gcCount++] = time;
        
        for(int i=0;i<n;i++)
        {
            if(!inQueue[i] && p[i].at<=time && p[i].rt>0)
            {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }

        if(p[idx].rt>0)
        {
            queue[rear++] = idx;
        }
        else
        {
            p[idx].ct = time;
            completed++;
        }
    }

    float total_wt = 0,total_tat = 0,total_rp = 0;
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat-p[i].bt;
        total_tat += p[i].tat;
        total_rp += p[i].rp;
        total_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rp);
    }

    printf("\nAverage Wait Time: %.2f", total_wt / n);
    printf("\nAverage Turn Around Time: %.2f", total_tat / n);
    printf("\nAverage Response Time : %.2f\n", total_rp / n);
    printf("Gantt chart\n|");
    printf("\nGantt Chart\n\n|");
    time = 0;
    for(int i=0;i<gcCount;i++)
    {
        if(time<gcST[i])
        {
            printf("\tIDLE\t|");
            time = gcST[i];
        }
        printf("\tP%d\t|",gcID[i]);
        time = gcCT[i];
    }
    time = 0;
    printf("\n0");
    for(int i=0;i<gcCount;i++)
    {
        if(time<gcST[i])
        {
            printf("\t\t%d",gcST[i]);
            time = gcST[i];
        }
        printf("\t\t%d",gcCT[i]);
        time = gcCT[i];
    }
    printf("\n");
    return 0;
}