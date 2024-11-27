#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65); 
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT); 

    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    char *data = (char *) shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat failed");
        return 1;
    }

    printf("Enter some text: ");
    fgets(data, SHM_SIZE, stdin);  
    printf("Data written to shared memory: %s", data);

    if (shmdt(data) == -1) {
        perror("shmdt failed");
    }

    return 0;
}
