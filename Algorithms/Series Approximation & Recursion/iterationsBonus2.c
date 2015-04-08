
#include <stdio.h>


#define n 100                                // required number of decimal places
#define len   (int) 10 * n / 3
int q, x, nines, predigit, first_zero, first_three;
long int a[len];

int main()
{
first_zero = 0;                                 // trap for pretty formatting
first_three = 3;
printf("\nPi (to %d decimal places) = \n",n);
for (int j = 0; j < len; ++j) a[j] = 2;         // Start with 2s
nines = 0; predigit = 0;                        // First predigit is a 0
for (int j = 0; j < n; ++j)
{
    q = 0;
    for (int i = len; i >=1; --i)               // Work backwards
    {
        x = 10 * a[i-1] + q*i;
        a[i-1] = x % (2*i-1);
        q = (int) x / (2*i-1);
    }
    a[0] = q % 10; q = (int)q / 10;
    if (q == 9 ) nines = nines + 1;
    else if (q == 10)
        {
            printf("%.1d", predigit+1);
            for (int k = 1; k <= nines; ++k) printf("%.1d",0);  //zeros
            predigit =0 ; nines = 0;
        }
    else
        {
        if(predigit == first_zero) first_zero = -1;             // swallow first zero
                                                                // and place dp after first “3"
        else  if (predigit == first_three) {first_three = -1; printf("%.1d.", predigit);}
        else  printf("%.1d", predigit);

        predigit = q;
        if (nines !=0)
        {
        for (int k = 1; k <= nines; ++k) printf("%.1d", 9);
        nines = 0;
        }

        }
}
printf("%.1d\n",predigit );
return 0;
}
