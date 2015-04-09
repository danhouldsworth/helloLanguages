// 1 - tbc

#include <stdio.h>
#include <stdlib.h>

char* toUpper(char* stringStart){
    char* ptr = stringStart;
    do {
        if ((*ptr >= 97) && (*ptr <=122)) *ptr -= 32;
    } while (*ptr++);
    return stringStart;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        printf("CLI in C : Name = %s, and age converted into months = %d\n", toUpper(argv[1]), 12 * atoi(argv[2]));
    }
    return 0;
}
