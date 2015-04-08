// 2. Done
// Bonus. When compiling with -Ofast it nails javascript!! (n=7 in 0.5s, n=8 in 4.8s), [even -O3 does n=8 in 21.6s]

#include <stdio.h>
#include <math.h>

double pi(int dp);
double truncate(double x, int dp);
double leibnizTerm(unsigned long int n);

const int n = 9; // Tells the compiler that I have no intention of modifying but does not mean

int main(int argc, char *argv[]){
    printf("PI correct to %d dps = %12.11g\n", n, pi(n) );
}

double pi(int dp){
    double lastSum;
    double sum = 0;

    for (unsigned long long int n = 0; ; ) { // Note : Dont want to overflow before c.5bn terms for 10dps
        lastSum = truncate(sum, dp);
        sum += 4.0 * leibnizTerm(n++);
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
