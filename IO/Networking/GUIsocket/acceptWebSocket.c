/*
'acceptWebSocket.c' - A homemade library for creating a WebSocket-Secure-Handshake key.
Usage           : The primary function createAcceptKeyStr accepts a client handshake key, then
i) concatenates it with the magic key
ii) generates a 20-byte SHA1 hash
iii) base64 encodes this (being clever about the potential for the bytes to be 0)

Weakness        : It trusts you to pass it a pointer to string buffer that can take 28bytes plus a terminating '\0'
Dependancies    : The openssl/sha1 algorithm looked doable but I'd run out of energy to hand craft it...! See note on deprecation.
Memory          : (I believe) I am only creating modest amount of vars temporarily on the stack. For our one time use case, this seems fine.
Elegance        : The main base64 algorithm shows my bitmask, and padding techniques, and although (slightly) superflous it is ready to
be extended as a more generic base64 encoder. This may of course be needed if the W3C spec changed the key lengths.
*/

#include <openssl/sha.h>// OS X has deprecated this so need to compile with -Wno-deprecated-declarations -lcrypto

// -- Function declarations
unsigned char *createAcceptKeyStr(unsigned char *base64string, unsigned char *clientKey);
void getFourBytesFromThree(unsigned char *src, int length, unsigned char *four);
unsigned char *base64(unsigned char *inputMsg, int length, unsigned char *outputMsgBuf);
// --

unsigned char *createAcceptKeyStr(unsigned char *base64string, unsigned char *clientKey){
        unsigned char magicKey[24+36];
        unsigned char hash[20];

        memcpy(magicKey, clientKey, 24);
        memcpy(magicKey+24, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11",   36);
        SHA1(magicKey,  60, hash);
        base64(hash,    20, base64string);
        base64string[28] = '\0';

        return base64string;
}

/*
 Read 3x 8-bit bytes and convert into 4x 6-bit bytes
*/
void getFourBytesFromThree(unsigned char *src, int length, unsigned char *four) {

        // Std encoding map for the 6-bit bytes
        unsigned char m[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        // -- Get first 3 chars of string (Padded with 0 where empty)
        unsigned char three[3];
        switch (length) {
        case 1:
                three[0] = src[0];
                three[1] = 0;
                three[2] = 0;
                break;
        case 2:
                three[0] = src[0];
                three[1] = src[1];
                three[2] = 0;
                break;
        default:
                three[0] = src[0];
                three[1] = src[1];
                three[2] = src[2];
                break;
        }
        // --

        // -- Create bitmask to convert 3xOctets to 4xSextets
        unsigned char bitMask[] = {
                0b11111100,
                0b00000011,
                0b11110000,
                0b00001111,
                0b11000000,
                0b00111111
        };

        four[0]  = (three[0] & bitMask[0]) >> 2;                // Amusingly <<>> have higher precidence then & in C than Go
        four[1]  = (three[0] & bitMask[1]) << 4;
        four[1] += (three[1] & bitMask[2]) >> 4;
        four[2]  = (three[1] & bitMask[3]) << 2;
        four[2] += (three[2] & bitMask[4]) >> 6;
        four[3]  = (three[2] & bitMask[5]);
        // --

        // -- Encode into base64 using 4 Sextets as indices
        four[0] = m[four[0]];
        four[1] = m[four[1]];
        four[2] = m[four[2]];
        four[3] = m[four[3]];
        // --

        // -- Pad out if shorter than 3 bytes to this block
        switch (length) {
        case 1:
                four[2] = '=';
                four[3] = '=';
                break;
        case 2:
                four[3] = '=';
                break;
        }
        // --
}

unsigned char *base64(unsigned char *inputMsg, int length, unsigned char *outputMsgBuf){

        unsigned char buf4[4];
        unsigned char *outPtr = outputMsgBuf;

        for (int i = 0; i < length; i += 3){
                getFourBytesFromThree(inputMsg + i, (3 < length - i) ? 3 : (length - i) , buf4);
                *outPtr++ = buf4[0];
                *outPtr++ = buf4[1];
                *outPtr++ = buf4[2];
                *outPtr++ = buf4[3];
        }
        return outputMsgBuf;
}
