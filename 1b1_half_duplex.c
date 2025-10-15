#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
// #include<sys/wait.h>

int main()
{
    pid_t id;
    int x,fd[2],len;
    char s[20] = "Siva Kumar";
    len = strlen(s);
    x = pipe(fd);
    id = fork();

    if(id<0)
        exit(1);
    else if(id>0)
    {
        printf("Parent is writing the data : \n");
        write(fd[1],s,len);
    }
    else
    {
        printf("Message Received from parent is : %s",s);
        read(fd[0],s,len);
    }
    return 0;
}