 #include <sys/wait.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdio.h>

int main(int argc, char *argv[]) {
    pid_t cpid, w;
    int status;

    printf("\nParent 1/3: about to fork()...\n");

    if ((cpid = fork()) == 0) {            /* Code executed by child */
        printf("Child 1/2 : Our PID is %ld\n", (long) getpid());
        pause(); // Wait for signals
        printf("Child 2/2 : Exiting!\n");
        exit(EXIT_SUCCESS);
    } else {                    /* Code executed by parent */
        printf("Parent 2/3: Waiting on Child %d...\n", cpid);
        do {
            // if (waitpid(cpid, &status, 0) == -1) {
            if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if      (WIFEXITED(status))     printf("Parent : Child Exited. status = %d\n", WEXITSTATUS(status));
            else if (WIFSIGNALED(status))   printf("Parent : Child Killed by signal %d\n", WTERMSIG(status));
            else if (WIFSTOPPED(status))    printf("Parent : Child Stopped by signal %d\n",WSTOPSIG(status));
            else if (WIFCONTINUED(status))  printf("Parent : Child Continued\n");
            else                            printf("Parent : Unknown child signal!\n");

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        printf("Parent 3/3: Exiting!\n");
        exit(EXIT_SUCCESS);
    }
}
