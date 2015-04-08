#include <stdio.h>

int n = 10;
int count = 1;

void solve(int n, int source, int middle, int target){
    if (n == 1){
        printf("Step %d : Move a ring from tower %d to %d\n", count++, source, target);
    } else {
        solve(n-1, source, target, middle);
        solve(1, source, middle, target);
        solve(n-1, middle, source, target);
    }
}

void main(){
    solve(n, 1, 2, 3);
}

