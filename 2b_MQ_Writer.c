#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/wait.h>
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
    key = ftok("progfile",65);
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1;
    printf("Write data : ");
    fgets(message.msg_text,MAX,stdin);
    msgsnd(msgid,&message,sizeof(message),0);
    printf("Message send is : %s\n",message.msg_text);
    return 0;
}