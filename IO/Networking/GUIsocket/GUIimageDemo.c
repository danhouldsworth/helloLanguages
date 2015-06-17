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
#define imgSize 1000

int main(void){
    initGUIsocket(); // This only returns if we get a valid WebSocket handshake after serving the app
    guiWipe();

    unsigned char imageDataRGBA[4*imgSize*imgSize + 11]; // It's convenient to include space for the 11-byte frame header, so this becomes the entire TCP payload
    unsigned char *ptr;
    ptr = &imageDataRGBA[11];
    for (int i = 0; i < imgSize; i++){
      for (int j = 0; j < imgSize; j++) {
        *ptr++ = (unsigned char)((i%100)*25+25);
        *ptr++ = (unsigned char)((j%100)*25+25);
        *ptr++ = (unsigned char)(i*j*(i%100)*(j%100)+i*j);
        *ptr++ = (unsigned char)(255-(i%100)*(j%100)*3);
      }
    }
    guiPasteImage(0,    0,      imgSize, imgSize, imageDataRGBA);
    ptr = &imageDataRGBA[11];
    for (int i = 0; i < imgSize; i++){
      for (int j = 0; j < imgSize; j++) {
        *ptr++ = (unsigned char)((i/100)*25+25);
        *ptr++ = (unsigned char)((j/100)*25+25);
        *ptr++ = (unsigned char)(i*j*(i/100)*(j/100)+(i)*(j));
        *ptr++ = (unsigned char)(255-(i/100)*(j/100)*3);
      }
    }
    ptr = &imageDataRGBA[11];
    guiPasteImage(1000, 0,      imgSize, imgSize, imageDataRGBA);
    for (int i = 0, count = 0; i < imgSize; i++){
      for (int j = 0; j < imgSize; j++) {
        *ptr++ = (unsigned char)(count++);
        *ptr++ = (unsigned char)(count);
        *ptr++ = (unsigned char)(count);
        *ptr++ = (unsigned char)(count);
      }
    }
    ptr = &imageDataRGBA[11];
    guiPasteImage(0, 1000,   imgSize, imgSize, imageDataRGBA);
    for (int i = 0; i < imgSize; i++){
      for (int j = 0; j < imgSize; j++) {
        *ptr++ = (unsigned char)sqrt(i*i+j*j);
        *ptr++ = (unsigned char)sqrt((imgSize-i)*(imgSize-i)+j*j);
        *ptr++ = (unsigned char)sqrt(i*i+(imgSize-j)*(imgSize-j));
        *ptr++ = (unsigned char)sqrt((imgSize-i)*(imgSize-i)+(imgSize-j)*(imgSize-j));
      }
    }
    guiPasteImage(1000, 1000,   imgSize, imgSize, imageDataRGBA);
    closeGUIsocket();
    return 0;
}
