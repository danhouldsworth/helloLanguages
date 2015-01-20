// Bonus. Done.

// C is encoding strings as UTF-8 and so storing as an array of 8-bit bytes.
// Where a 3byte Unicode point is represented, it would not make sense to sense to attempt to display is incomplete.

// Great article : http://www.joelonsoftware.com/articles/Unicode.html

#include <stdio.h>

int main(int argc, char *argv[])
{
    /*
    Byte 0 : 1110 xxxx (1st of 3 byte Unicode ie Unicode mapping to U+0800-U+FFFF - bits 13-16 )
    Byte 1 : 10xx xxxx (Follow on Unicode byte - bits 7-12)
    Byte 2 : 10xx xxxx (Follow on Unicode byte - bits 1-6)
    Byte 3 : 0xxx xxxx (1 byte Unicode mapping to U+0000-U+007F aka ASCII)
    Byte 4 : null terminator
    */
    char chinese[] = {
        1 * 128 +\
        1 * 64  +\
        1 * 32  +\
        0 * 16  +\
        0 * 8   +\
        1 * 4   +\
        1 * 2   +\
        1 * 1,   \
                \
        1 * 128 +\
        0 * 64  +\
        0 * 32  +\
        0 * 16  +\
        1 * 8   +\
        0 * 4   +\
        1 * 2   +\
        1 * 1,   \
                \
        1 * 128 +\
        0 * 64  +\
        0 * 32  +\
        1 * 16  +\
        0 * 8   +\
        0 * 4   +\
        0 * 2   +\
        0 * 1,   \
                \
        0 * 128 +\
        0 * 64  +\
        1 * 32  +\
        0 * 16  +\
        0 * 8   +\
        0 * 4   +\
        0 * 2   +\
        1 * 1,   \

        0               // null terminator
    };

    // 狐    72d0 0111 0010 1101 0000
    // ࢢ    2210 0000 1000 1010 0010
    // ࿕    0Fd5 0000 1111 1101 0101
    // ?    07ff 0000 0111 1111 1111

    // char chinese[]= "࿕";
    // char chinese[] = "ࠀ";
    // char chinese[] = "ࢢ";
    // char chinese[] = "ڱ";
    // char chinese[] = "狐";
    // char chinese[] = "犬";
    // char chinese[] = "齟";

    printf("%s\n", chinese);

    char *ptr = chinese;
    while (*ptr) printf("%d\n", *ptr++);
    printf("\n");

    return 0;
}

