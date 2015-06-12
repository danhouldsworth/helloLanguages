#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){

    pid_t child_PID = fork(); // Equivalent to `./a.out &` but it doesn't write the background process to stdout

    if (child_PID == 0) {
        for (int i = 0; i <= 10; i++) {
            printf("Child : count %d\n", i);
            if (i == 5) sleep(2);
        }
        printf("Child : closing...\n");
        return 0; // A child ending will not return to the command line (as was not the foreground task)...
    }
    else {
        for (int i = 0; i <= 10; i++) {
            printf("Parent : count %d\n", i);
            // if (i == 5) sleep(2);
        }
    }

    printf("Parent : closing...\n");
    return 0; // ...but the parent will exit to command line leaving the children running in the background.
}




