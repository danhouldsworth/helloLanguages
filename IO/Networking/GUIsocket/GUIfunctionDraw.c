/*
'GUIfunctionDraw.c' - An example putting guiDrawLine() to use to render functions
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 GUIfunctionDraw.c
Weakness        : Have to fudge to avoid singularities. Cannot differentiate dicontinuities.
Dependancies    : <math.h> for sqrt(), sin(), exp() etc. A nice compliment to this project
Memory          : No issue.
Elegance?       : Kind of - if the differentials are of interest. Easy to switch off if not.
                : Pretty cool the way we can chart existing functions just by function pointer name.
*/

#include "GUIsocket.c"
#include <math.h>
#define screenSize 2000

#define AXIS_MARK_SIZE (screenSize/100)
#define X_UNIT (double)(0.5 * M_PI)
#define Y_UNIT (double)(0.5)
#define XRANGE (double)20                           // Multiples of X_UNIT
#define YRANGE (double)6
#define SINGULARITY_AVOIDANCE_FUDGE 0.0000000001    // Choose << XRANGE / screenSize
#define DELTA_X 0.001                               // Choose <  XRANGE / screenSize
#define RED         255,0,0
#define GREEN       0,255,0
#define BLUE        0,0,255
#define BLACK       0,0,0
#define LIGHTGREY   200,200,200

// -- Defines a pointer to any function f(x), that takes and returns a double. Code is hard to read otherwise.
typedef double(* PointerToFuncOfX)(double);
// --

// -- Function prototypes
int mapDoubleToScreenX(double);
int mapDoubleToScreenY(double);
double mapScreenXToDouble(int);
int screenY(int, PointerToFuncOfX);
void renderFunctionOfX(PointerToFuncOfX, int, int, int); // Renders any f(x), for -XRANGE<x<XRANGE in colour RGB
void drawAxis();
// --

// -- Examples for f(x)
double mod(double x) {return sqrt(x*x);}
double quadratic(double x) {return 1 + x*x/1000;}
double stepFn(double x){return (mod(x) < 2) ? 1 : 0;}
double fn1(double x) {return sin(x)/x;}
double fn2(double x) {return 1 / exp(1 / quadratic(10*x));}
// --
// -- Define the Nth differential of f(x)
double diff(PointerToFuncOfX f, double x, int order){
    if (order > 0) return ( diff(f, x+DELTA_X, order - 1) - diff(f, x-DELTA_X, order - 1) ) / (2 * DELTA_X);
    else return (*f)(x); // 0th order diff is just f(x)
}
// --

int main(void){
    initGUIsocket();
    guiWipe();
    drawAxis();
    //                fn(x),    RGBmacro
    renderFunctionOfX(cos,      LIGHTGREY);// We can use any existing function(x) from <math.h> ...!!
    renderFunctionOfX(stepFn,   RED     );
    renderFunctionOfX(fn1,      GREEN   ); // Or our own defined functions
    renderFunctionOfX(fn2,      BLUE    );

    closeGUIsocket();
    return 0;
}

void renderFunctionOfX(PointerToFuncOfX f, int r, int g, int b){
    for (int order = 0; order < 4; order++) {                   // f(x), f(x)', f(x)'', f(x)'''
        // For range -XRANGE/2 < x < XRANGE/2, draws line segements f(x) to f(x+1)
        for (int screenX = 0; screenX < screenSize; screenX++) guiDrawLine(screenX, mapDoubleToScreenY(diff(f, mapScreenXToDouble(screenX), order)), screenX+1, mapDoubleToScreenY(diff(f, mapScreenXToDouble(screenX+1), order)), r, g, b);
        r += (255-r)/2; // Fade each successive differential
        g += (255-g)/2;
        b += (255-b)/2;
    }
}
double mapScreenXToDouble(int screenX){
    double x = (double)screenX;
    x -= screenSize / 2;                // Centre on x=0
    x /= screenSize / (XRANGE * X_UNIT);// Map viewport to -XRANGE/2 < x < XRANGE/2
    x += SINGULARITY_AVOIDANCE_FUDGE;
    return x;
}
int mapDoubleToScreenY(double y){
    y *= screenSize / (YRANGE * Y_UNIT);// Map viewport to -YRANGE/2 < y < YRANGE/2
    y -= screenSize / 2;                // Centre on y=0
    return -(int)y;                     // Screen is y-axis go top to bottom
}
int mapDoubleToScreenX(double x){
    x *= screenSize / (XRANGE * X_UNIT);
    x += screenSize / 2;
    return (int)x;
}
void drawAxis(){
    guiDrawLine(mapDoubleToScreenX(-XRANGE*X_UNIT/2), mapDoubleToScreenY(0), mapDoubleToScreenX(XRANGE*X_UNIT/2), mapDoubleToScreenY(0), BLACK);
    guiDrawLine(mapDoubleToScreenX(0), mapDoubleToScreenY(-0.5*YRANGE*Y_UNIT), mapDoubleToScreenX(0), mapDoubleToScreenY(0.5*YRANGE*Y_UNIT), BLACK);
    for(double x = -0.5*XRANGE*X_UNIT; x < 0.5*XRANGE*X_UNIT; x += X_UNIT) guiDrawLine(mapDoubleToScreenX(x), screenSize/2 - AXIS_MARK_SIZE, mapDoubleToScreenX(x), screenSize/2 + AXIS_MARK_SIZE, BLACK);
    for(double y = -0.5*YRANGE*Y_UNIT; y < 0.5*YRANGE*Y_UNIT; y += Y_UNIT) guiDrawLine(screenSize/2 - AXIS_MARK_SIZE, mapDoubleToScreenY(y), screenSize/2 + AXIS_MARK_SIZE, mapDoubleToScreenY(y), BLACK);
}
