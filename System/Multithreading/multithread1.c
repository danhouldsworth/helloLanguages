#include <stdio.h>
#include <unistd.h>

void count(char *owner){
    for (int i = 0; i <= 10; i++) {
        printf("%s counts : %d\n", owner, i);
    }
}

int main(void){

    pid_t child_PID = fork();

    if (child_PID == 0) {
        count("Child process");
    }
    else {
        printf("Our Child process is %d\n", child_PID);
        count("Parent process");
    }

    return 0;
}
