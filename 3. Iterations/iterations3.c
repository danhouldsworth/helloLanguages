// 3. Done. But is it better than Leibniz...?
// After n=10bn [1e10] samples, PI = 3.1415[835497] (in 2.5mins with -Ofast)
// After n=100bn[1e11] samples, PI = 3.1415[868431] (in 26 mins with -Ofast)
// After n=10bn [1e10] samples, PI = 3.14159[72668] (in 2m45s with -Ofast) **
// After n=100bn[1e11] samples, PI = 3.14159[74965] (in 27mins with -Ofast) **

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
// RAND_MAX = 2^31; On my implementation anyway

struct timeval t1;

double randFloat(){
    // Returns a float 0.0 --> 1.0 with 2^31 possible values increments
    return (double)rand() / (double)RAND_MAX;
}

double sqrFloat(double x) {
    return x * x;
}

void reseed(){
        gettimeofday(&t1, NULL);
        srand(t1.tv_usec * t1.tv_sec);
}

int main(void){

    unsigned long long n = 0;
    unsigned long long sequence = 0;
    unsigned long long piSum = 0;

    while (n < 1e11){
        sequence = 0;
        while (sequence++ < 1<<31) if (sqrFloat(randFloat()) + sqrFloat(randFloat()) <= 1.0) {
            piSum++;
            n++;
        }
        reseed();
    }

    printf("After %llu samples, PI = %.10f\n", n, 4.0 * (double)piSum / (double)n);
    return 0;
}

// ** while (n++ < 1e11) if (sqrFloat(randFloat() - 1.0) + sqrFloat(randFloat() - 1.0 ) <= 1.0) piSum++;
