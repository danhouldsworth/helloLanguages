// 1. Done (Area = 1.507 with 10000x10000 to 10000dwell in 11m53s)

"use strict"; /* jshint
node : true
*/

var realMax = 1.0,
    realMin = -2.0,
    imagMax = 1.5,
    imagMin = -1.5,
    steps = 10000,
    area = 0,
    maxDwell = 10000;

function isMandy(Cx, Cy) {

    var Zx = Cx,
        Zy = Cy,
        dwell = 0,
        tempX;

    while ((Zx * Zx + Zy * Zy) < 4) {
        if (dwell++ > maxDwell) {return true; }
        tempX = Zx * Zx - Zy * Zy + Cx;
        Zy = 2 * Zx * Zy + Cy;
        Zx = tempX;
    }

    return false;
}

function mapReal(pixelsX) {
    return realMin + (pixelsX / steps) * (realMax - realMin);
}

function mapImag(pixelsY) {
    return imagMin + (pixelsY / steps) * (imagMax - imagMin);
}


for (var i = 0; i <= steps; i++) { // Note : this is scanning in vertical lines rather than the usual horizontal
    for (var j = 0; j <= steps; j++) {
        if (isMandy(mapReal(i), mapImag(j))) {area++; }
    }
}

console.log("Area of mandlebrot set = " + area * (realMax - realMin) * (imagMax - imagMin) / (steps * steps)); // Units : [pixels * pixels] * [real/pixels] * [imag/pixels] == real * imag == area

