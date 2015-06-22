/*
'GUIdrawDemo.c' - An example demo for my GUIsocket.c project showing off guiDrawLine()
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 GUIdrawDemo.c
Weakness        : Hard coded screen size. Ideally set up at invokation of initGUIsocket(screenSize)
Dependancies    : Just GUIsocket.c !
Memory          : Small amount on the stack.
Elegance?       : Simple. Recursive. Ideally would have used vector math to make the P' interpolation more clear.
*/

#include "GUIsocket.c"
#include <math.h>
#define screenSize 2000
#define XRANGE 30
#define YRANGE 2

// -- Defines a pointer to any function f(x), that takes and returns a double. Code is hard to read otherwise.
typedef double(* PointerToFuncOfX)(double);
// --

// -- Function prototypes
int mapDoubleToScreenY(double);
double mapScreenXToDouble(int);
int screenY(int, PointerToFuncOfX);
void renderFunc(PointerToFuncOfX, int, int, int); // Renders any f(x), for -XRANGE<x<XRANGE in colour RGB
// --

// -- Typical Math Functions
double mod(double x) {return sqrt(x*x);}
double fn1(double x) {return sin(x)/x;}
double fn2(double x) {return 1 + x*x/1000;}
double fn3(double x) {return exp(1 / fn2(x)) - 2;}
double step(double x){return (mod(x) < 2) ? 1 : 0;}
// --

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app

    guiWipe();

    renderFunc(fn1,              255,0,  0  );
    renderFunc(fn2,              0,  255,0  );
    renderFunc(fn3,              0,  0,  255);
    renderFunc(step,             0,  0,  0);
    renderFunc(cos,              128,128,128); // Note, we can use any existing function(x)...!

    closeGUIsocket();
    return 0;
}

void renderFunc(PointerToFuncOfX f, int r, int g, int b){
    // For range -XRANGE < x < XRANGE, draws line segements f(x) to f(x+1)
    for (int screenX = 0; screenX < screenSize; screenX++){
        guiDrawLineBuff(screenX, screenY(screenX, f), screenX+1, screenY(screenX+1, f), r, g, b);
    }
    guiDrawFlush();
}

double mapScreenXToDouble(int screenX){
    double x = (double)screenX;
    int unit = screenSize / 2;
    x -= unit;              // Centre on x=0
    x /= unit / XRANGE;     // Map viewport to -XRANGE < x < XRANGE
    x += 0.0000000000001;   // Fudge to avoid singularities around x = 0
    return x;
}
int mapDoubleToScreenY(double y){
    int unit = screenSize / 2;
    y *= unit / YRANGE;     // Map viewport to -YRANGE < y < YRANGE
    y -= unit;              // Centre on y=0
    int screenY = (int)y;
    return -screenY;        // Screen is y-axis go top to bottom
}
int screenY(int screenX, PointerToFuncOfX f){
    double x = mapScreenXToDouble(screenX);
    double y = (*f)(x); // y = f(x)
    return mapDoubleToScreenY(y);
}
