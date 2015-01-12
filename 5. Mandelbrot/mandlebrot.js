// 1. Done

var realMax = 1.0,
    realMin = -2.0,
    imagMax = 1.5,
    imagMin = -1.5,
    steps = 10000,
    area = 0,
    maxDwell = 1000;

for (var i = 0; i <= steps; i++){
    for (var j = 0; j <= steps; j++){
        if ( isMandy(mapReal(i), mapImag(j) ) ) area++;
    }
}

console.log("Area of mandlebrot set = " + area * (realMax - realMin) * (imagMax - imagMin) / (steps * steps) ); // Units : [pixels * pixels] * [real/pixels] * [imag/pixels] == real * imag == area

function isMandy(Cx, Cy){

    var Zx = Cx,
        Zy = Cy,
        dwell = 0,
        temp_X;

    while( (Zx*Zx + Zy*Zy) < 4 ){
        if (dwell++ > maxDwell) return true;
        temp_X = Zx * Zx - Zy * Zy + Cx;
        Zy = 2 * Zx * Zy + Cy;
        Zx = temp_X;
    }

    return false;

}

function mapReal(pixelsX){
    return realMin + (pixelsX / steps) * (realMax - realMin);
}

function mapImag(pixelsY){
    return imagMin + (pixelsY / steps) * (imagMax - imagMin);
}
