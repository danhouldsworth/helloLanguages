// 1. Done (Ye-hah!)

/*
Learnings : Although ```greeting``` & ```ptr``` are both pointers to the same string, ```greeting``` is fixed.
*/

#include <stdio.h>

int main(int argc, char *argv[]){

    char greeting[] = "Hello, world!";
    // char greeting[] = "The quick brown 狐 jumped over the lazy 犬";
    char* ptr = greeting;
    int index = 0;

    while (*ptr++) { // Note increment operator (++/--) takes precedence over indirect reference operator (*) : equiv *(ptr++)
        index++;
    };
    while (index--) { // Don't forget, this expression still gets evaluated even if the while block doesn't get executed. ==> index will end up at -1 not 0
        putchar(greeting[index]);
    };
    putchar('\n');

    ptr = greeting;
    do { // Do while loop at least once
        if ((*ptr >= 65) && (*ptr <=90)) putchar(*ptr + 32); // ASCII 65-90 A-Z, 97-122 a-z
        else putchar(*ptr);
    } while (*ptr++);
    putchar('\n');

    ptr = greeting;
    do {
        if ((*ptr >= 97) && (*ptr <=122)) putchar(*ptr - 32);
        else putchar(*ptr);
    } while (*ptr++);
    putchar('\n');
}
