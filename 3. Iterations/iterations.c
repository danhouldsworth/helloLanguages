// 1. Done
// 2. Done
// 3. Done
// Bonus. Done. but embarrasingly its slightly slower than javascript..! (n=7 in 3.2s, n=8 in 46s)

#include <stdio.h>
#include <math.h>

int fact(int x);    // I think these are called prototypes. Either way, need to define functions before they are called
int fib(int x);     // Interestingly, like go they can't be defined locally within another function.
double pi(int dp);
double truncate(double x, int dp);
double leibnizTerm(unsigned long int n);

int main(int argc, char *argv[]){
    for (int n = 0; n <= 8; n++){
        printf("%d!\t= %d,  \t%dth Fibonacci = %d,  \tPI(correct to %d dps)\t= %12.11g\n", n, fact(n), n, fib(n), n, pi(n) );
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

double pi(int dp){

    double lastSum;
    double sum = 0;

    for (unsigned long int n = 0; ; n++) { // Note : this will overflow at 2^32 ie before the estimated 5bn terms for 10 dps
        lastSum = truncate(sum, dp);
        sum += 4.0 * leibnizTerm(n);
        if (truncate(sum, dp) == lastSum) return lastSum;
    }
}

double leibnizTerm(unsigned long int n){
    int divisor = n + n + 1;
    double term = 1.0 / (double)divisor;
    if (n % 2) return -term;
    else return term;
}

double truncate(double x, int dp){
    int count = dp;
    while (count--){
        x *= 10.0;
    }

    x = trunc(x);

    count = dp;
    while (count--){
        x = x / 10.0;
    }

    return x;
}


