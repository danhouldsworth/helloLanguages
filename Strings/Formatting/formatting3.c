#include <stdio.h>

/*

See http://en.wikipedia.org/wiki/ANSI_escape_code#Colors

\x1b[...;...;...m

0       : reset all attribs
1       : bold
2       : faint
4       : underline
30-37   : colour

*/

char _colour_none[]  = "\x1b[0m";
char _colour_time[]  = "\x1b[36;2m";
char _colour_warn[]  = "\x1b[31;1;4m";
char _colour_alert[] = "\x1b[31m";
char _colour_comms[] = "\x1b[32m";
char _colour_debug[] = "\x1b[37;2m";

int main(){
    printf("%s12345 %sdebug %swarning %sfinished!\n", _colour_time, _colour_debug, _colour_warn, _colour_none);
    return 0;
}
