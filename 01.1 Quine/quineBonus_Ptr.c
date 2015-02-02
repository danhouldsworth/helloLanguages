// Bonus. Increased to 364 bytes, but uses pointers rather than hard coding string size

char d[]="char d[]=@_char *e=d,*f=d;_int c(int a){if(a==95)a=10;if(a==64)a=0;return putchar(a);}_void g(){while(c(*e++));}_int main(){g();c(34);while(putchar(*f++));c(34);c(59);g();return 0;}";
char *e=d,*f=d;
int c(int a){if(a==95)a=10;if(a==64)a=0;return putchar(a);}
void g(){while(c(*e++));}
int main(){g();c(34);while(putchar(*f++));c(34);c(59);g();return 0;}
