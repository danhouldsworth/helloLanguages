// Bonus. Done
// With n=100bn (1e11) it solves PI to 10 dps in 6min30sec (compiled with -Ofast on 17"MBP)

#include <stdio.h>

int main() {
    double sum = 1.0;
    double denominator = 3.0;
    double numerator = 1.0;
    unsigned long long n = 0;

    while (n++ < 1e11) {
        numerator = -numerator;
        sum += numerator / denominator;
        denominator += 2;
    }

    printf("After %lld iterations, PI estimate to 10dps = %.10f\n", n, 4 * sum);

    return (0);
}
