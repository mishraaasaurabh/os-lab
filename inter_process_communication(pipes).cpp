#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipefd[2];  
    char write_msg[BUFFER_SIZE] = "Hello from the producer process!";
    char read_msg[BUFFER_SIZE];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    if (fork() == 0) {

        close(pipefd[1]);  
        read(pipefd[0], read_msg, sizeof(read_msg));
        printf("Consumer received: %s\n", read_msg);
        close(pipefd[0]);
    } else {
        close(pipefd[0]);  
        write(pipefd[1], write_msg, strlen(write_msg) + 1);
        close(pipefd[1]);  
    }

    return 0;
}
