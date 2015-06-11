/*
'mandy.c' - An example demo for my GUIsocket.c project
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 mandy.c
Weakness        : Hard coded screen size. Ideally set up at invokation of initGUIsocket(screenSize)
                : Currently only using single CPU core - although still faster than Go when using all 8
                  ToDo : use fork() to split task across cores, but watch for race conditions for socket()

Dependancies    : Just the GUIsocket.c
Memory          : Early version blew up the OS, this version uses no malloc()s and only has Z0 and Zn on the stack.
Elegance?       : Certainly the shortest isMandy() algorithm I've ever written.
                : No optimisations of Mandy set (other than connected contours) as is supposed to be demo of GUIsocket rather than a mandy calculator
*/

#include "GUIsocket.c" // Note : puts socket_fd and client_fd in the global namespace

#define screenSize 2048 // (2048==1<<11)
#define maxDwell 65536  // (8192==1<<13, 32768==1<<15, 65536==1<<16)

typedef struct {
    double x;
    double y;
} complex128;

// -- Function declarations
double ratio(int a, int b);
int isMandy(complex128 c);
complex128 mapToArgand(int x, int y);
complex128 *complexAdd(complex128 *a, complex128 *b);
complex128 *complexSq(complex128 *z);
double complexModSq(complex128 *z);
void mandy(int left, int right, int top, int bottom);
// --

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app

    guiWipe();
    int counter = 0;
    for (unsigned int rectSize = screenSize; rectSize > 2; rectSize /= 2 ){
        for (unsigned int x = 0; (x + rectSize) <= screenSize; x += rectSize){
            for (unsigned int y = 0; (y + rectSize) <= screenSize; y += rectSize, counter++){
                guiFillRectBuff(x,y,rectSize,rectSize,x>>3,y>>3,255-(rectSize>>3),255);
            }
        }
    }
    printf("Finished painting %d rectangles!\n", counter);

    printf("Commencing mandlebrot set %dx%d to MaxDwell=%d...\n", screenSize,screenSize,maxDwell);
    mandy(0, screenSize-1, 0, screenSize-1);

    printf("Done! Flushing GUIsocket buffers and closing.\n");
    closeGUIsocket();
    return 0;
}

void mandy(int left, int right, int top, int bottom) {
    int deltaX = 1;     // 1 == Left to right
    int deltaY = 0;     // 1 == Top to bottom
    int colourBlock = 1;// 1 == TRUE

    // -- This wastes a pixel calc, but gets the opening colour
    complex128 z0 = mapToArgand(left, top);
    int firstColour = isMandy(z0);
    // --

    // -- Work around the 4 edges of the square
    for (int dwell, i = left, j = top, edge = 0; edge < 4; i += deltaX, j += deltaY) {

        // -- Set Z0 aka C, and iterate to get & plot dwell
        z0 = mapToArgand(i,j);
        dwell = isMandy(z0);
        guiPlotBuff(i, j, (unsigned char)(dwell%64), (unsigned char)(dwell%16), (unsigned char)(dwell%2), 255-(unsigned char)(dwell%256));
        // --

        // -- If not going to be a solic block, flag it and look to divide recursively
        if (colourBlock && dwell != firstColour) {
            colourBlock = 0;
            // -- Can we fit at least 2x2 pixel box in the inner box
            if ( (bottom-top)>3 && (right-left)>3 ) {
                int midleft = left + (right-left)/2;
                int midtop = top + (bottom-top)/2;
                mandy(left+1, midleft, top+1, midtop);         // TL
                mandy(left+1, midleft, midtop+1, bottom-1);    // BL
                mandy(1+midleft, right-1, midtop+1, bottom-1); // BR
                mandy(1+midleft, right-1, top+1, midtop);      // TR
            }
        }
        // --

        // -- Check if reached the end of current edge
        if (deltaX > 0 && i == right) {
            edge++;
            deltaX--;
            deltaY++;
        } else if (deltaY > 0 && j == bottom) {
            edge++;
            deltaX--;
            deltaY--;
        } else if (deltaX < 0 && i == left) {
            edge++;
            deltaX++;
            deltaY--;
        } else if (deltaY < 0 && j == top) {
            edge++;
            deltaX++;
            deltaY++;
        }
        // --
    }
    // -- Fill the inner rectangle if the perimeter all same colour
    if (colourBlock) guiFillRectBuff(left+1, top+1, right-left-1, bottom-top-1, (unsigned char)(firstColour%64), (unsigned char)(firstColour%16), (unsigned char)(firstColour%2), 255-(unsigned char)(firstColour%256));
    // --
}


/*
    Take a complex Z and return how many dwells before escaped set
*/
int isMandy(complex128 c) {
    int dwell = 0;
    for (complex128 z = c; complexModSq(&z) < 4; z = *complexAdd(complexSq(&z), &c)) if (dwell++ >= maxDwell) break;
    return dwell;
}

/*
    Take (int) screen pixel positions, and map to (double) complex z + iy in the mandy argand plane.
*/
complex128 mapToArgand(int x, int y) {
    // This could still be called ~millions, so could make more efficient. Although -O3 should handle this.
    complex128 z0;
    complex128 mandyMIN = {-2,-1.5};
    complex128 mandyMAX = {1,1.5};
    z0.x = mandyMIN.x + ratio(x, screenSize) * (mandyMAX.x - mandyMIN.x);
    z0.y = mandyMIN.y + ratio(y, screenSize) * (mandyMAX.y - mandyMIN.y);
    return z0;
}


/* These complex128 operations will be used BILLIONS of times, so be careful about memory usage/leakage */
/*
    a += b
*/
complex128 *complexAdd(complex128 *a, complex128 *b){
    a->x = a->x + b->x;
    a->y = a->y + b->y;
    return a;
}

/*
    z *= z
*/
complex128 *complexSq(complex128 *z){
    double temp = z->x * z->x - z->y * z->y;
    z->y = 2 * z->y * z->x;
    z->x = temp;
    return z;
}

/*
    return |z|^2
*/
double complexModSq(complex128 *z){
    return z->x * z->x + z->y * z->y;
}

/*
    A reminder to self to cast, as I tend to forget a/b === 0 for ints where a<b
*/
double ratio(int a, int b) {
    return (double)a / (double)b;
}
