/*
'mandy.c' - An example demo for my GUIsocket.c project
Usage           :
Weakness        :
                : Create queue
                  Create fork to correctly split up
                : Test against goGUIsocket
Dependancies    :
Memory          :
Elegance        :
*/

#include "GUIsocket.c" // Note : puts socket_fd and client_fd in the global namespace

#define screenSize 512
#define maxDwell 100

typedef struct {
    double x;
    double y;
} complex128;

// -- Function declarations
double ratio(int a, int b);
int isMandy(complex128 c);
complex128 mapToArgand(int x, int y);
void mandy(int left, int right, int top, int bottom);
// --

complex128 *complexAdd(complex128 *a, complex128 *b){ // a += b
    a->x = a->x + b->x;
    a->y = a->y + b->y;
    return a;
}
complex128 *complexSq(complex128 *z){     // z *= z
    double temp = z->x * z->x - z->y * z->y;
    z->y = 2 * z->y * z->x;
    z->x = temp;
    return z;
}
double complexModSq(complex128 *z){ // |z|^2
    return z->x * z->x + z->y * z->y;
}


// struct complex128

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app

    guiWipe();
    for (unsigned int rectSize = screenSize; rectSize > 2; rectSize /= 2 ){
        for (unsigned int x = 0, counter = 0; (x + rectSize) <= screenSize; x += rectSize, counter++){
            for (unsigned int y = 0, counter = 0; (y + rectSize) <= screenSize; y += rectSize, counter++){
                guiFillRect(x,y,rectSize,rectSize,x>>1,y>>1,counter%255,255-(rectSize>>1));
            }
        }
    }
    mandy(0, screenSize-1, 0, screenSize-1);

    closeGUIsocket();
    return 0;
}
void mandy(int left, int right, int top, int bottom) {
    int deltaX = 1;
    int deltaY = 0;
    int colourBlock = 1;
    int area = 0;
    complex128 z0 = mapToArgand(left, top);
    int firstColour = isMandy(z0); // This wastes a pixel calc

    while (area < screenSize * screenSize) {
        for (int dwell, i = left, j = top, edge = 0; edge < 4; i += deltaX, j += deltaY) {
            z0 = mapToArgand(i,j);
            dwell = isMandy(z0);
            if (colourBlock && dwell != firstColour) {
                colourBlock = 0;
                // Initiate recurcise split immediately in case of idle CPUs
                if ( (bottom-top)>50 && (right-left)>50 ) {
                    // Ie we can fit at least 2x2 pixel box in the inner box
                    int midleft = left + (right-left)/2;
                    int midtop = top + (bottom-top)/2;
                    // mandy(left+1, midleft, top+1, midtop);         // TL
                    // mandy(left+1, midleft, midtop+1, bottom-1);    // BL
                    // mandy(1+midleft, right-1, midtop+1, bottom-1); // BR
                    // mandy(1+midleft, right-1, top+1, midtop);      // TR
                }

            }
            guiPlot(i, j, (unsigned char)(dwell%64), (unsigned char)(dwell%16), (unsigned char)(dwell%2), 255-(unsigned char)(dwell%256));
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
        }
        if (colourBlock) {
            guiFillRect(left+1, top+1, right-left-1, bottom-top-1, (unsigned char)(firstColour%64), (unsigned char)(firstColour%16), (unsigned char)(firstColour%2), 255-(unsigned char)(firstColour%256));
            area += (right - left - 1) * (bottom - top - 1);
        } else {
            area += 2 * (right - left + bottom - top);
        }
        left++; right--; top++; bottom--;
    }
}


/*
    Take a complex Z and return how many dwells before escaped set
*/
int isMandy(complex128 c) {
    int dwell = 0;
    for (complex128 z = c; complexModSq(&z) < 4; z = *complexAdd(complexSq(&z), &c)) {
        if (dwell++ >= maxDwell) break;
    }
    return dwell;
}

/*
    Take (int) screen pixel positions, and map to (double) complex z + iy in the mandy argand plane.
*/
complex128 mapToArgand(int x, int y) {
    complex128 z0;
    complex128 mandyMIN = {-2,-1.5};
    complex128 mandyMAX = {1,1.5};
    z0.x = mandyMIN.x + ratio(x, screenSize) * (mandyMAX.x - mandyMIN.x);
    z0.y = mandyMIN.y + ratio(y, screenSize) * (mandyMAX.y - mandyMIN.y);
    return z0;
}

double ratio(int a, int b) {
    return (double)a / (double)b;
}