#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*

** BASIC FUNCTIONING **

    1) ftok()   : Generate a unique key
    2) msgget() : Returns the identifier associated with a message queue (existing or new)
    3) msgsnd() : Sender uses this to push data into the queue
    4) msgrcv() : Receiver uses this to read data from the queue
    5) msgctl() : Used to control a message queue, but here we use it to delete a queue

*/

struct msgbuf{
    long mtype;
    char message[200];
};

int main(){
    struct msgbuf msg;  //Making an instance of the structure
    int msgid;
    
    /*      **GENERATING A KEY**    */

    key_t key;
    if((key = ftok("sender.c", 'b')) == -1){
        perror("Key");
        exit(1);
    }

    /*  ** GENERATING QUEUE IDENTIFER **    */

    if((msgid = msgget(key, 0666 | IPC_CREAT)) == -1){
        perror("msgid");
        exit(1);
    }

    printf("\n The message id is : %d\n", msgid);

    /*

    **SENDING THE MESSAGE**

    To send the message, we use the msgsnd() system call.

    int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)

        msgid : message queue identifier returned by msgget()
        *msgp : pointer to the data to be put on the queue
        msgsz : size in bytes of the data to be sent
        msgflg: some optional flag parameters

    */

    printf("Enter the message to be sent, ^D to quit\n");
    msg.mtype = 1;      //IMPORTANT
    while(gets(msg.message), !feof(stdin)){
        if(msgsnd(msgid, &msg, sizeof(msg), 0) == -1){
            perror("msgsnd");
            exit(1);
        }
    }

    /*

    **DESTROYING THE QUEUE**

    int msgctl(int msgid, int cmd, struct msgid_ds *buf)

        msgid : message queue identifier returned by msgget()
        cmd   : tells msgctl() how to behave, IPC_RMID to remove a queue
        buf   : Can be set to NULL when using IPC_RMID

    */

    if(msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(1);
    }

    exit(0);
}

/*
For more information on msgget(), msgrcv() and msgctl() visit 
the man pages.
*/