// 1. Done (Ye-hah!)


#include <stdio.h>

int main(int argc, char *argv[]){

    char greeting[] = "Hello, world!";
    char copy[0]; // Or could do copy[] = ''

    char *i = greeting; // pointers to the strings

    int greetIndex = 0;
    int copyIndex = 0;

    while (*i++) { // While the memory content pointed to by the pointer i is non-zero, count the greeting length
        greetIndex++;
    };

    while (greetIndex--) {
        copy[copyIndex++] = greeting[greetIndex];
    };

    copy[copyIndex] = 0; // Terminate the new string

    puts(copy);
}

// Learnings
// while copy & greeting are pointers to strings, they are fixed...
