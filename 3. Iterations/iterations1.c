// 1. Done

#include <stdio.h>

int fact(int x);    // Function prototypes. No body, just a declaration of the functions interface. [Interestingly, like go they can't be defined locally within another function.]
int fib(int x);

int main(int argc, char *argv[]){
    for (int n = 0; n <= 8; n++){
        printf("%d!\t= %d,  \t%dth Fibonacci = %d\n", n, fact(n), n, fib(n) );
    }
}

int fact(int x){
    if (x == 0 || x == 1) return x;
    return x * fact(x-1);
}

int fib(int x){
    if (x == 0 || x == 1) return x;
    return fib(x-1) + fib(x-2);
}
