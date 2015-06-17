/*
'GUIdrawDemo.c' - An example demo for my GUIsocket.c project showing off guiDrawLine()
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 GUIdrawDemo.c
Weakness        : Hard coded screen size. Ideally set up at invokation of initGUIsocket(screenSize)
Dependancies    : Just GUIsocket.c !
Memory          : Small amount on the stack.
Elegance?       : Simple. Recursive. Ideally would have used vector math to make the P' interpolation more clear.
*/

#include "GUIsocket.c" // Note : puts socket_fd and client_fd in the global namespace

#define MAX_GEN 19

typedef struct {
    int x;
    int y;
} point;

void dragon(point P1, point P2, int generation);

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app

    for (int generation = MAX_GEN; generation > 0; generation--){
        guiWipe();
        dragon((point){300,500}, (point){1000,500}, generation);
        guiDrawFlush();
        sleep(1);
    }
    closeGUIsocket();
    return 0;
}

void dragon(point P1, point P2, int generation){
    point Pmid = {
        (P1.x + P1.y + P2.x  - P2.y)/2,
        (P2.x + P2.y + P1.y  - P1.x)/2
    };
    if (generation == MAX_GEN) guiDrawLineBuff(P1.x, P1.y, P2.x, P2.y, 0,0,0);
    else {
        dragon(P1, Pmid, generation + 1);
        dragon(P2, Pmid, generation + 1);
    }
}
