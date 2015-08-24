/*
'complexAnalysis.c' - I realised this might be useful for experimenting with complex functions
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 complexAnalysis.c
Weakness        : Colour scheme confused poles / singularities unless make first band large.
Dependancies    : <complex.h> and sqrt() from <math.h>,
Memory          :
Elegance?       : Yes, using 'native' complex algebra makes for intuitive calculations
                : Nice exploration of poles / singularities
                : Nice method of banding saturation and value
*/

#include "GUIsocket.c" // Note : puts socket_fd and client_fd in the global namespace
#include <math.h>
#include <complex.h>
#define imgSize 2000

void chooseHSV( double complex z, double HSVcolor[3] ){
    double modulus      = cabs(z);
    double bandStart    = 0;
    double bandEnd      = 1;
    while (modulus > bandEnd){ // Chose first band that modulus sits in
        bandStart = bandEnd;
        bandEnd = bandEnd * 2.7183;
    }
    double k = (modulus - bandStart) / (bandEnd - bandStart);   // Proportion through band
    k = (k < 0.5) ? (2 * k) : (1 - 2*(k-0.5));                  // Take Saturation as rise and fall /\/\/\/\/\/\ and not saw tooth  /|/|/|/|
    double sat = k;         // 0->1->0
    double val = 1 - k;     // 1->0->1 ie 1/2 out of phase

    HSVcolor[0] = 0.5 + carg(z) / (2 * 3.14159265359);      // Hue [0:1]
    HSVcolor[1] = 1 - sat*sat*sat*sat*sat*sat*sat;          // Saturation           (Smoother topped hills / steeper vallies)
    HSVcolor[2] = 1 - val*val*val*val*val*val*val;          // Value (brightness)   (Smoother topped hills / steeper vallies)
}

void mapHSVtoRGB( double HSVcolor[3], unsigned char RGBcolor[3] ) {
        double Red, Green, Blue;
        double hue = HSVcolor[0];
        double sat = HSVcolor[1];
        double bright = HSVcolor[2];

        int     primaryCol  = floor(hue*6);         // [0,1,2,3,4,5]
        double  fractional  = (hue*6 - primaryCol); // [0:1]
        double  greyness    = bright*(1 - sat);
        double  prevPrimary = bright*(1 - sat*fractional);
        double  nextPrimary = bright*(1 - sat*(1 - fractional));
        switch(primaryCol){
                case 0: Red=bright;         Green=nextPrimary;  Blue=greyness;    break; // Red
                case 1: Red=prevPrimary;    Green=bright;       Blue=greyness;    break; // Yellow
                case 2: Red=greyness;       Green=bright;       Blue=nextPrimary; break; // Green
                case 3: Red=greyness;       Green=prevPrimary;  Blue=bright;      break; // Cyan
                case 4: Red=nextPrimary;    Green=greyness;     Blue=bright;      break; // Blue
                case 5: Red=bright;         Green=greyness;     Blue=prevPrimary; break; // Purple
        }
        RGBcolor[0] = (int)(255*Red);
        RGBcolor[1] = (int)(255*Green);
        RGBcolor[2] = (int)(255*Blue);
}

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app
    guiWipe();

    unsigned char *imageDataRGBA = (unsigned char *)malloc(4*imgSize*imgSize + 11); // It's convenient to include space for the 11-byte frame header, so this becomes the entire TCP payload
    unsigned char *ptr = imageDataRGBA + 11;

    double complex z, f;
    unsigned char RGBcolor[3];
    double HSVcolor[3];

    for (int j = 0; j < imgSize; j++){
        for (int i = 0; i < imgSize; i++) {

            // Map to screen to [-5:5]x[-5:5]
            z = (i - (double)imgSize/2)/100 + I*((double)imgSize/2 - j)/100;

            f = (z - 1) * (z + 1) * (z - 3 - I) * (z - 6 - I) / ( (z + 2 + I) * (z - 3) );
            chooseHSV( f, HSVcolor );
            mapHSVtoRGB(HSVcolor,RGBcolor);

            *ptr++ = (unsigned char)(RGBcolor[0]);
            *ptr++ = (unsigned char)(RGBcolor[1]);
            *ptr++ = (unsigned char)(RGBcolor[2]);
            *ptr++ = (unsigned char)(255);
        }
    }

    guiPasteImage(0, 0, imgSize, imgSize, imageDataRGBA);
    closeGUIsocket();
    return 0;
}
