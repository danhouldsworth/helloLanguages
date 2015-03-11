#include <stdio.h>
#include <stdlib.h>
// RAND_MAX = 2^31; On my implementation anyway

int birthday(){
    return rand() % 366; // This is acceptably even distribution as 366 << RAND_MAX
}

int main(){

    int birthdays[366];
    unsigned long birthdayClash = 0;
    unsigned long sampleCount = 0;
    unsigned long sampleSize = 1000000;

    printf("Birthday party : running %ld simulations per party...\n", sampleSize);

    for (int partySize = 15; partySize < 25; partySize++){

        sampleCount = 0;
        birthdayClash = 0;

        while(sampleCount++ < sampleSize){
            for (int day = 0; day < 366; day++) birthdays[day] = 0;
            for (int person = 1; person < partySize; person++) birthdays[birthday()]++;
            for (int day = 0; day < 366; day++) if (birthdays[day] > 1) birthdayClash++;
        }

        printf("PartySize of %d has probabiltiy of %4.1f%%\n", partySize, 100.0 * (double)birthdayClash/(double)sampleSize );
    }

    return 0;
}
