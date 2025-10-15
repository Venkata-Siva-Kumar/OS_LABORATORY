#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#define SHMSZ 27

int main()
{
    char c;
    char *shm,*s;
    key_t key = 5678;
    int shmid;
    if((shmid = shmget(key,SHMSZ,IPC_CREAT|0666))<0)
    {
        perror("shmid Error");
        exit(1);
    }
    if((shm = shmat(shmid,NULL,0)) == (char*)-1)
    {
        perror("shmat Error");
        exit(1);
    }
    
    printf("Contents of Shared memory Written by server is : ");
    for(s=shm;*s!='\0';s++)
        putchar(*s);
    putchar('\n');
    *shm = '*';
    //strncpy(shm + 7, "WORLD", 5);

    exit(0);
}