// 1. Done.
// Note: This approach is generically scalable accept for making '@','_' and ':' special commands.

#include <stdio.h>

#define COLON 58
#define UNDERSCORE 95
#define TAB 9
#define NEWLINE 10

#define DOUBLEQUOTE 34
#define SEMICOLON 59
#define STRINGTERMINATOR 0

#define SUPERSPECIAL 64

char programString[]="_#include <stdio.h>__#define COLON 58_#define UNDERSCORE 95_#define TAB 9_#define NEWLINE 10__#define DOUBLEQUOTE 34_#define SEMICOLON 59__#define SUPERSPECIAL 64__char programString[]=@__void parseForColonOrNewLine(int a){_:if(a == COLON) a = TAB;_:if(a == UNDERSCORE) a = NEWLINE;_:putchar(a);_}__int main(){_:int i = 0, j = 0;_:char symbol;_:while ((symbol = programString[i++]) != SUPERSPECIAL) parseForColonOrNewLine(symbol);_:putchar(DOUBLEQUOTE);_:while ((symbol = programString[j++]) != STRINGTERMINATOR) putchar(symbol);_:putchar(DOUBLEQUOTE);_:putchar(SEMICOLON);_:while ((symbol = programString[++i]) != STRINGTERMINATOR) parseForColonOrNewLine(symbol);_:return 0;_}__";

void parseForColonOrNewLine(char c){
    if(c == COLON) c = TAB;
    if(c == UNDERSCORE) c = NEWLINE;
    putchar(c);
}

int main(){
    int i = 0, j = 0;
    char symbol;
    while ((symbol = programString[i++]) != SUPERSPECIAL) parseForColonOrNewLine(symbol);
    putchar(DOUBLEQUOTE);
    while ((symbol = programString[j++]) != STRINGTERMINATOR) putchar(symbol);
    putchar(DOUBLEQUOTE);
    putchar(SEMICOLON);
    while ((symbol = programString[i++]) != STRINGTERMINATOR) parseForColonOrNewLine(symbol);
    return 0;
}
