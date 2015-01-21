// 3. Done. But is it better than Leibniz...?
// After 10000000001(1e10) samples, PI = 3.1415[835497] (in 2.5mins)

#include <stdio.h>
#include <stdlib.h>
// RAND_MAX = 2^31; On my implementation anyway

double randFloat(){
    // Returns a float 0.0 --> 1.0
    return (double)rand() / (double)RAND_MAX;
}

double sqrFloat(double x) {
    return x * x;
}

int main(void){

    unsigned long long n = 0;
    unsigned long long piSum = 0;

    while (n++ < 1e10) if (sqrFloat(randFloat()) + sqrFloat(randFloat()) < 1.0) piSum++;

    printf("After %llu samples, PI = %.10f\n", n, 4.0 * (double)piSum / (double)n);
    return 0;
}

