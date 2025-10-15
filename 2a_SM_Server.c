#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
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
    s = shm;
    for(c = 'a';c<='z';c++)
        *s++ = c;
    *s = '\0';

    // printf("Enter a string: ");
    // fgets(shm, SHMSZ, stdin);
    
    printf("Shared memory altered by client is : ");
    while(*shm!='*')
        sleep(1);
    printf("%s",shm);
    exit(0);
}