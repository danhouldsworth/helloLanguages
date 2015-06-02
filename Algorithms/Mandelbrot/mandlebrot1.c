// 1. Done. Area = 1.507 with 10000x10000 to 10000dwell in 5m41s using -O3.  :-)

#include <stdio.h>

int isMandy(double cx, double cy, unsigned int maxDwell){

    double tempX;       // 64-bit, and interestingly almost no slower than 32-bit float (must be 64bitFPU)
    double zx = cx;
    double zy = cy;
    unsigned int dwell = 0;

    while ((zx * zx + zy * zy) <= 4.0){
        if (dwell++ >= maxDwell) return 1;
        tempX = zx * zx - zy * zy + cx;
        zy = 2 * zx * zy + cy;
        zx = tempX;
    }

    return 0;
}

int main(){

    unsigned int area = 0; // 4 bytes on 64-bit OS X

    double argandMin = -2.0;
    double argandMax = 2.0;
    double argandSize = argandMax - argandMin;
    double zx = argandMin;
    double zy = argandMin;
    unsigned int steps = 1000;
    unsigned int maxDwell = 10000;
    double stepSize = argandSize / (double)steps;

    printf("About to calculate %dx%d image to depth of %d...\n", steps, steps, maxDwell);

    while (zy < argandMax){
        zy += stepSize;
        zx = argandMin;
        while (zx < argandMax){
            zx += stepSize;
            area += isMandy(zx, zy, maxDwell);
        }
    }

    printf("Total area = %d\n", area);
    printf("Coverage = %3.3f\n", argandSize * argandSize * (double)area / (double)(steps * steps));

    return 0;
}

