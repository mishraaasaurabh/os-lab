#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100
#define MSG_TYPE 1

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key = ftok("msgfile", 65); 
    int msgid = msgget(key, 0666|IPC_CREAT); 

    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    if (fork() == 0) {

        struct msg_buffer msg;
        msgrcv(msgid, &msg, sizeof(msg), MSG_TYPE, 0);  
        printf("Consumer received: %s\n", msg.msg_text);
    } else {

        struct msg_buffer msg;
        msg.msg_type = MSG_TYPE;
        strcpy(msg.msg_text, "Hello from the producer process!");
        msgsnd(msgid, &msg, sizeof(msg), 0);  
        printf("Producer sent: %s\n", msg.msg_text);
    }

    return 0;
}
