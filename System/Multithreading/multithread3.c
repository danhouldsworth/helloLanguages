#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){

    int status = 0;
    pid_t child_PID = fork();

    if (child_PID == 0) {
        for (int i = 0; i <= 10; i++) {
            printf("Child : count %d\n", i);
            if (i >= 8) sleep(1);
        }
        printf("Child : Exiting!\n");
        exit(255);
    }
    else for (int i = 0; i <= 10; i++) printf("Parent : count %d\n", i);

    printf("Parent : waiting for child %d to close...\n", child_PID);
    waitpid(child_PID, &status, 0); // BLOCKING
    printf("Parent : ...done! ");

    if (WIFEXITED(status))          printf("Child ended by its own exit code : %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))   printf("Child ended because of an uncaught signal\n");

    return 0;
}

