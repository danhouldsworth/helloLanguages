/*
'GUIfunctionDraw.c' - An example putting guiDrawLine() to use to render functions
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 GUIfunctionDraw.c
Weakness        : Have to fudge to avoid singularities....
Dependancies    : <math.h> for sqrt(), sin(), exp() etc. A nice compliment to this project
Memory          : No issue.
Elegance?       : Can't figure out how to return pointers to dynamic functions. Maybe not possible?
*/

#include "GUIsocket.c"
#include <math.h>
#define screenSize 2000
#define XRANGE (15*M_PI)
#define YRANGE (2+2)
#define SINGULARITY_AVOIDANCE_FUDGE 0.0000000001    // Choose << XRANGE / screenSize
#define DELTA_X 0.001                               // Choose <  XRANGE / screenSize

// -- Defines a pointer to any function f(x), that takes and returns a double. Code is hard to read otherwise.
typedef double(* PointerToFuncOfX)(double);
// --

// -- Function prototypes
int mapDoubleToScreenY(double);
double mapScreenXToDouble(int);
int screenY(int, PointerToFuncOfX);
void renderFunctionOfX(PointerToFuncOfX, int, int, int); // Renders any f(x), for -XRANGE<x<XRANGE in colour RGB
// --

// -- Typical Math Functions
double mod(double x) {return sqrt(x*x);}
double fn1(double x) {return sin(x)/x;}
double fn2(double x) {return 1 + x*x/1000;}
double fn3(double x) {return exp(1 / fn2(x*x)) - 2;}
double step(double x){return (mod(x) < 2) ? 1 : 0;}
// --
//
double diff(PointerToFuncOfX f, double x, int order){
    if (order > 0) return ( diff(f, x+DELTA_X, order - 1) - diff(f, x-DELTA_X, order - 1) ) / (2 * DELTA_X);
    else return (*f)(x); // 0th order diff is just f(x)
}
// -- I can't figure out how to return a pointer to a dynamically created function f'(x), so for now we manually define the differentiated functions we want
double diff1_fn1(double x){return diff(fn1, x, 1);} // 1st order diffs wrt x
double diff1_fn2(double x){return diff(fn2, x, 1);}
double diff1_fn3(double x){return diff(fn3, x, 1);}
double diff2_fn1(double x){return diff(fn1, x, 2);} // 2ns order diffs wrt x
double diff2_fn2(double x){return diff(fn2, x, 2);}
double diff2_fn3(double x){return diff(fn3, x, 2);}
double diff3_fn1(double x){return diff(fn1, x, 3);} // 3rd order diffs wrt x
double diff3_fn2(double x){return diff(fn2, x, 3);}
double diff3_fn3(double x){return diff(fn3, x, 3);}
// --

int main(void){
    initGUIsocket();

    guiWipe();

    renderFunctionOfX(fn1,      255,0,  0  );
    renderFunctionOfX(fn2,      0,  255,0  );
    renderFunctionOfX(fn3,      0,  0,  255);
    renderFunctionOfX(diff1_fn1,255,128,128);
    renderFunctionOfX(diff1_fn2,128,255,128);
    renderFunctionOfX(diff1_fn3,128,128,255);
    renderFunctionOfX(diff2_fn1,255,192,192);
    renderFunctionOfX(diff2_fn2,192,255,192);
    renderFunctionOfX(diff2_fn3,192,192,255);
    renderFunctionOfX(diff3_fn1,255,224,224);
    renderFunctionOfX(diff3_fn2,224,255,224);
    renderFunctionOfX(diff3_fn3,224,224,255);
    renderFunctionOfX(step,     0,  0,  0  );
    // renderFunctionOfX(cos,   128,128,128); // Note, we could use any existing function(x) from <math.h> ...!!

    closeGUIsocket();
    return 0;
}

void renderFunctionOfX(PointerToFuncOfX f, int r, int g, int b){
    // For range -XRANGE/2 < x < XRANGE/2, draws line segements f(x) to f(x+1)
    for (int screenX = 0; screenX < screenSize; screenX++){
        guiDrawLineBuff(screenX, screenY(screenX, f), screenX+1, screenY(screenX+1, f), r, g, b);
    }
    guiDrawFlush();
}

double mapScreenXToDouble(int screenX){
    double x = (double)screenX;
    x -= screenSize / 2;            // Centre on x=0
    x /= screenSize / XRANGE;       // Map viewport to -XRANGE/2 < x < XRANGE/2
    x += SINGULARITY_AVOIDANCE_FUDGE;
    return x;
}
int mapDoubleToScreenY(double y){
    y *= screenSize / YRANGE;       // Map viewport to -YRANGE/2 < y < YRANGE/2
    y -= screenSize / 2;            // Centre on y=0
    return -(int)y;                 // Screen is y-axis go top to bottom
}
int screenY(int screenX, PointerToFuncOfX f){
    double x = mapScreenXToDouble(screenX);
    double y = (*f)(x); // y = f(x)
    return mapDoubleToScreenY(y);
}
