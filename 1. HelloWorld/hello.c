// 1. Done
// Bonus. Done

#include <stdio.h>                  // <libraries> looked within compilation include path vs "libraries" absolute path

int main(int argc, char *argv[])    // main() is expected to return an int, and (I think) takes args as number, and pointer to array of chars. Need to check if this is command line args...
{
    char greeting1[] = "Hello";
    char greeting2[] = {44, 32, 0}; // chars are unsigned ints !!
    char greeting3[] = {'w','o','r','l','d','!','\0'}; // strings are terminated by 'null' (the 0 byte)
    printf("%s%s%s\n", greeting1, greeting2, greeting3);
    return 0;
}

// Learning : Although C can be a pain with strings, I do love the way to forces you to think about the memory representation from the outset


