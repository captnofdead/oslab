#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
    long mtype;
    char message[200];
};

int main(){
    struct msgbuf msg;  //Making an instance of the structure
    int msgid;

    //Same key as that used in sender.c
    key_t key;
    if((key = ftok("sender.c", 'b')) == -1){
        perror("Key");
        exit(1);
    }

    //Why is there no IPC_CREAT here?
    if((msgid = msgget(key, 0666)) == -1){
        perror("msgid");
        exit(1);
    }

    /*

    **RECEIVING THE MESSAGE**

    To retrieve a message from a message queue, we use the
    msgrcv() system call.

    int msgrcv(int msgid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

        msgid : queue identifier returned by msgget()
        *msgp : a pointer to where we store the received data
        msgsz : size of the data to be received in bytes
        msgtyp: specifies the behaviour of the queue, more below
        msgflg: some optional flag parameters

    The msgtyp argument is related to the mtype we specified earlier.
    Based on this value, the behaviour of the queue is changed.

    1) msgtyp = 0
        Retrieve the next message on the queue, regardless of its mtype.

    2) msgtyp = positive

        Get the next message with an mtype equal to the specified msgtyp.

    3) msgtyp = negative
        Retrieve the first message on the queue whose mtype field is less 
        than or equal to the absolute value of the msgtyp argument.

    So if we just want the standard FIFO behaviour of a queue, we set
    msgtyp to 0.

    */
    while(1){
        //Note that msgtyp = 1 here
        if(msgrcv(msgid, &msg, sizeof(msg), 1, 0) == -1){
            perror("msgrcv");
            exit(1);
        }

        printf("%s\n", msg.message);
    }

    return 0;

    //Why is there no call to msgctl() here?
}