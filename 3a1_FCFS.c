#include<stdio.h>
struct Process
{
    int id,at,bt,ct,tat,wt,rt,start;
};

int main()
{
    int n;
    printf("Enter the number of Processes : ");
    scanf("%d",&n);
    struct Process p[n];

    for(int i=0;i<n;i++)
    {
        p[i].id = i+1;
        printf("Enter the Arrival Time and Burst Time for P%d : ",p[i].id);
        scanf("%d%d",&p[i].at,&p[i].bt);
    }

    int time = 0;
    float total_wt=0,total_tat=0,total_rt=0;
    for(int i=0;i<n;i++)
    {
        if(time<p[i].at)
            time = p[i].at;

        p[i].start = time;
        p[i].ct = p[i].start + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat = p[i].bt;
        p[i].rt = p[i].start - p[i].at;

        time = p[i].ct;

        total_wt += p[i].wt;
        total_rt += p[i].rt;
        total_tat += p[i].tat;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id, p[i].at, p[i].bt,p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("Average Waiting Time = %.2f\n",total_wt);
    printf("Average Turn Around Time = %.2f\n",total_tat);
    printf("Average Response Time = %.2f\n",total_rt);

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
            printf("\t\t%d|",p[i].at);
            time = p[i].at;
        }
        printf("\t\t%d|",p[i].ct);
        time = p[i].ct;
    }

}