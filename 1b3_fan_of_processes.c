#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>2
int main(int argc , char* argv[])
{
    int i=0,n=3;
    for(i=0;i<n;i++)
    {
        if(fork()==0)
        {
            printf("Process P%d --> Parent PID : %d\tChild PID : %d\n",i+1,getppid(),getpid());
            break;
        }
    }
}
