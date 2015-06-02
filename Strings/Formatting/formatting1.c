#include <stdio.h>

void str_replace(char *string, char findChar, char replaceChar){
    char *ptr = string;
    while (*ptr++) if (*(ptr-1) == findChar) *(ptr-1) = replaceChar;
}

int pow10(int power){
    int result = 1;
    for (int i = 0; i < power; i++) result *= 10;
    return result;
}

int intToBinary(unsigned char octet){
    int result = 0;
    for (int i = 0; i < 8; i++) result += pow10(i) * (octet & (1 << i)) >> i;
    return result;
}

int main() {
    unsigned char i = 0;
    char str[100];
    do {
        sprintf(str, "%3d\t%2x\t%8d\n",i,i,intToBinary(i));
        str_replace(str, ' ', '0');
        printf("%s", str);
    } while (i++ < 255);
    return 0;
}

