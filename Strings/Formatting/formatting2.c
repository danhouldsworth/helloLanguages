// Done!

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getFourBytesFromThree(unsigned char *src, unsigned char *m, unsigned char *four) {

	// -- Get first 3 chars of string (Padded with 0 where empty)
	unsigned int stringLength = strlen((char *)src);
	unsigned char three[3];
	switch (stringLength) {
	case 1:
		three[0] = src[0];
		three[1] = 0;
		three[2] = 0;
	case 2:
		three[0] = src[0];
		three[1] = src[1];
		three[2] = 0;
	default:
		three[0] = src[0];
		three[1] = src[1];
		three[2] = src[2];
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

	four[0]  = (three[0] & bitMask[0]) >> 2; 		// Amusingly <<>> have higher precidence then & in C than Go
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
	switch (stringLength) {
	case 1:
		four[2] = '=';
		four[3] = '=';
	case 2:
		four[3] = '=';
	}
	// --
}

unsigned char *base64(unsigned char *inputMsg, unsigned char *outputMsgBuf){

	unsigned char mapPtr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // Std encoding OR unsigned char m[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"; // URL encoding
	unsigned char *buf4 = (unsigned char *)malloc(4);

	int i = 0;
	int j = 0;

	while (i < strlen((char *)inputMsg)){
		getFourBytesFromThree((inputMsg+i), mapPtr, buf4);
		outputMsgBuf[j + 0] = buf4[0];
		outputMsgBuf[j + 1] = buf4[1];
		outputMsgBuf[j + 2] = buf4[2];
		outputMsgBuf[j + 3] = buf4[3];
		i += 3;
		j += 4;
	}

	free(buf4);
	return outputMsgBuf;
}


int main() {
	unsigned char msgPtr[] = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";

	unsigned char *outputMsgBuf = (unsigned char *)malloc(strlen((char *)msgPtr));
	printf("\nInput : %s\n\nOutput : %s\n\n", msgPtr, base64(msgPtr, outputMsgBuf));
	free(outputMsgBuf);

	return 0;
}
