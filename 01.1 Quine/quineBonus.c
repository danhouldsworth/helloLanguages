// Bonus. Done in 341 bytes
// Note : doesn't use superspecial character but instead hard-codes the position of the string at 9-191
// Note : Gives compiler warnings

char d[]="char d[]=_void c(int a){if(a==95)a=10;putchar(a);}_int main(){int i=0,j=0;while(i<9)c(d[i++]);c(34);while(putchar(d[j++])>0);c(34);c(59);while(i<191)c(d[i++]);return 0;}";
void c(int a){if(a==95)a=10;putchar(a);}
int main(){int i=0,j=0;while(i<9)c(d[i++]);c(34);while(putchar(d[j++])>0);c(34);c(59);while(i<191)c(d[i++]);return 0;}
