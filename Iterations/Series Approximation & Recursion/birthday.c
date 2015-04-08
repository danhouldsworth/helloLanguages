#include <stdio.h>
#include <stdlib.h>
// RAND_MAX = 2^31; On my implementation anyway

#define false 0
#define true  1

int birthday(){
    return 1 + rand() % 365; // This is acceptably even distribution between 1-365 as 366 << RAND_MAX
}

int main(){

    int birthdays[366]; // I will be ignoring [0] and using 1-365 without need for re indexing
    int clashFlag = false;
    unsigned long birthdayClashes = 0;
    unsigned long sampleCount = 0;
    unsigned long sampleSize = 1000000;

    printf("Birthday party : running %ld simulations per party...\n", sampleSize);

    for (int partySize = 15; partySize < 25; partySize++){

        sampleCount = 0;
        birthdayClashes = 0;

        while(sampleCount++ < sampleSize){
            clashFlag = false;
            for (int day = 1; day <= 365; day++) birthdays[day] = 0;                     // Wipe the bithday tallies
            for (int person = 1; person <= partySize; person++) birthdays[birthday()]++; // Log the partygoers birthdays
            for (int day = 1; day <= 365; day++) if (birthdays[day] > 1) clashFlag = true; // Check for days with clashes
            if (clashFlag == true) birthdayClashes++;                                     // Increment the clash tally if this sample has clashed
        }

        printf("PartySize of %d has probabiltiy of %4.1f%%\n", partySize, 100.0 * (double)birthdayClashes/(double)sampleSize );
    }

    return 0;
}
