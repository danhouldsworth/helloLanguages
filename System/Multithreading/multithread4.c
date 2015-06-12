#include <stdio.h>
#include <unistd.h>

int count(char *owner){
    for (int i = 0; i <= 10; i++) {
        printf("%s counts : %d\n", owner, i);
        sleep(1);
    }
    return 1;
}

int main(void){

    pid_t child_PID;

    if (!fork() && count("Child1")) return 0;
    if (!fork() && count("Child2")) return 0;
    if (!fork() && count("Child3")) return 0;
    if (!fork() && count("Child4")) return 0;

    count("Parent process");

    return 0;
}
