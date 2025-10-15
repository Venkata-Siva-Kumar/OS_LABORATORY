#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
    int i=0,n=3;
    for(i=0;i<n;i++)
    {
        if(fork()==0)
        {
            printf("Process P%d ---> Parent PID : %d, Child PID : %d\n",i+1,getppid(),getpid());
        }
        else
        {
            wait(NULL);
            break;
        }
    }
    return 0;
}