#include <stdio.h>

int main()
{
    double sum = 1.0;
    double denominator = 3.0;
    double numerator = 1.0;
    double temp;
    unsigned long long counter = 0;

    while (counter++ < 1e13)
    {
        numerator = -numerator;
        temp = numerator;
        temp /= denominator;
        sum += temp;
        denominator += 2;
    }
    temp = counter;
            printf("%19.0f Iterations, pi estimate = %19.17f\n",temp, 4*sum);

    return (0);
}
