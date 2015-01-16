// 2. Done
// Bonus Q. Again, gives an insight into how unicode is stored and displayed. Am guessing it is 3xbytes

/*  Notes :
Although ```char *ptr``` seems standard declaration format, I feel
```char* ptr``` reads more intuitively as 'ptr is of type <pointer to a char>'
*/

#include <stdio.h>

int main(int argc, char *argv[]){

    // char greeting[] = "Hello, world!";
    char greeting[] = "The quick brown 狐 jumped over the lazy 犬";
    char* ptr = greeting;
    int index = 0;

    while (*ptr++) {
        for (int i = 0; i <= index; i++) {
            putchar(greeting[i]);
        }
        putchar('\n');
        index++;
    }
}
