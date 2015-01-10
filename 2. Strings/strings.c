// 1. Done (Ye-hah!)
// 2. Done
// 3. Done
// 4. Bonus. Forwards is fine. Backwards and partial give an insight into how unicode is stored and displayed. Am guessing it is 3xbytes

#include <stdio.h>

int main(int argc, char *argv[]){

    // char greeting[] = "Hello, world!";
    char greeting[] = "The quick brown 狐 jumped over the lazy 犬";
    char *ptr = greeting; // pointer to this string
    int index = 0;

    while (*ptr++) { // Note increment operator (++/--) takes precedence over indirect reference operator (*) : equiv *(ptr++)
        index++;
    };

    while (index--) { // Don't forget, this condition still gets expressed even if the while doesn't get executed. ==> index will end up at -1 not 0
        putchar(greeting[index]);
    };

    putchar('\n');
    ptr = greeting;

    while (*ptr) {
        if ((*ptr >= 65) && (*ptr <=90)) putchar(*ptr + 32); // ASCII 65-90 A-Z, 97-122 a-z
        else putchar(*ptr);
        ptr++;
    }

    putchar('\n');
    ptr = greeting;

    while (*ptr) {
        if ((*ptr >= 97) && (*ptr <=122)) putchar(*ptr - 32);
        else putchar(*ptr);
        ptr++;
    }

    putchar('\n');
    ptr = greeting;
    index = 0;

    while (*ptr++) {
        for (int i = 0; i <= index; i++) {
            putchar(greeting[i]);
        }
        putchar('\n');
        index++;
    }
}

// Learnings
// while copy & greeting are pointers to strings, they are fixed...
