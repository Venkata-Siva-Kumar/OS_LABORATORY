#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#define MAX 100
struct message
{
    long msg_type;
    char msg_text[100];
}message;

int main()
{
    key_t key;
    int msgid;
    key = ftok("Program File",65);
    msgid = msgget(key,0666|IPC_CREAT);
    msgrcv(msgid,&message,sizeof(message),1,0);
    printf("Data received is : %s\n",message.msg_text);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}

