#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
// #include<sys/wait.h>

int main()
{
    pid_t id;
    int x,y,fd1[2],fd2[2],len1,len2;
    char s1[20] = "Mariyala";
    char s2[20] = "Siva Kumar";
    len1 = strlen(s1);
    len2 = strlen(s2);
    x = pipe(fd1);
    y = pipe(fd2);

    id = fork();

    if(id<0)
        printf("Error !!!");
    else if(id>0)
    {
        close(fd1[0]);
        write(fd1[1],s1,len1);
        sleep(5);
        printf("Parent Block\n");
        close(fd2[1]);
        read(fd2[0],s2,len2);
        printf("Second String from Parent is : %s\n",s2);
    }
    else
    {
        sleep(1);
        printf("Child Block\n");
        close(fd1[1]);
        read(fd1[0],s1,len1);
        printf("First String from Parent is : %s\n",s1);
        close(fd2[0]);
        write(fd2[1],s2,len2);
    }
    return 0;
}