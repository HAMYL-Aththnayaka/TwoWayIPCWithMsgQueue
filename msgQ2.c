#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#define MAX 100
#define MSGKEY 114

struct msg_buffer {
    long mtype;
    char text[MAX];
};

int main() {
    int f;
    int msqid = msgget(MSGKEY, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msg_buffer msg;

    f = fork();
    if (f == 0) {
        // Child process: send two messages with type 1 and 2
        msg.mtype = 1;
        printf("\nPlease Enter the First Name: ");
        if (fgets(msg.text, MAX, stdin) == NULL) {
            fprintf(stderr, "fgets failed in child\n");
            exit(EXIT_FAILURE);
        }
        // Remove newline from fgets
        
        if (msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed (first message)");
            exit(EXIT_FAILURE);
        }
        printf("\nThe First Message Is Sent\n");

        msg.mtype = 2;
        printf("\nPlease Enter the Second Name: ");
        if (fgets(msg.text, MAX, stdin) == NULL) {
            fprintf(stderr, "fgets failed in child\n");
            exit(EXIT_FAILURE);
        }
       

        if (msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed (second message)");
            exit(EXIT_FAILURE);
        }
        printf("\nThe Second Message Is Sent\n");
        exit(EXIT_SUCCESS);
    } else if (f > 0) {
        // Parent process: receive two messages with type 1 and 2
        wait(NULL);

        if (msgrcv(msqid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("msgrcv failed (first message)");
            exit(EXIT_FAILURE);
        }
        printf("\nThe First Message Is: %s\n", msg.text);

        if (msgrcv(msqid, &msg, sizeof(msg.text), 2, 0) == -1) {
            perror("msgrcv failed (second message)");
            exit(EXIT_FAILURE);
        }
        printf("\nThe Second Message Is: %s\n", msg.text);

        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl failed");
            exit(EXIT_FAILURE);
        }
        printf("\nMessage Queue removed successfully\n");
    } else {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
