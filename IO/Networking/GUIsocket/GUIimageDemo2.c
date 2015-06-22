/*
'GUIimageDemo.c' - An example demo for my GUIsocket.c project showing off GUIpasteImage
Usage           : gcc -Wno-deprecated-declarations -lcrypto -O3 GUIimageDemo.c
Weakness        : Hard coded screen size. Ideally set up at invokation of initGUIsocket(screenSize)
Dependancies    : sqrt() from <math.h>
Memory          : I needed to re-use the buffer, to avoid a stack overflow. Suppose I could have used malloc() and reduced the code size.
Elegance?       : No. But very simple to read.
*/

#include "GUIsocket.c" // Note : puts socket_fd and client_fd in the global namespace
#include <math.h>
#define imgSize 2000

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app
    guiWipe();

    unsigned char *imageDataRGBA = (unsigned char *)malloc(4*imgSize*imgSize + 11); // It's convenient to include space for the 11-byte frame header, so this becomes the entire TCP payload
    unsigned char *ptr;
    double radius,dx,dy;
    ptr = imageDataRGBA + 11;
    for (double c = 24; c < 26; c+=0.2){
        for (int i = 0; i < imgSize; i++){
            for (int j = 0; j < imgSize; j++) {
                dx = i - imgSize/2 ; dy = j - imgSize/2 ;
                radius = sqrt(dx*dx + dy*dy);
                *ptr++ = (unsigned char)(127+127*sin(radius/24));
                *ptr++ = (unsigned char)(127+127*sin(radius/25));
                *ptr++ = (unsigned char)(127+127*sin(radius/26));
                *ptr++ = (unsigned char)(127+127*sin(radius/c));
            }
        }
        ptr = imageDataRGBA + 11;
        guiPasteImage(0, 0, imgSize, imgSize, imageDataRGBA);
        sleep(1);
    }
    closeGUIsocket();
    return 0;
}
