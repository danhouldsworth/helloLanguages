#include <stdio.h>

#define Source 1
#define Middle 2
#define Target 3

int n = 10;
int count = 1;

void solve(int n, int src, int mdl, int tgt){
    if (n == 1){
        printf("Step %d : Move a ring from tower %d to %d\n", count++, src, tgt);
    } else {
        solve(n-1, src, tgt, mdl);
        solve(1, src, mdl, tgt);
        solve(n-1, mdl, src, tgt);
    }
}

void main(){
    solve(n, Source, Middle, Target);
}

