// Bonus. Done in 366 bytes (if you don't mind a compiler warning) :-)
char d[]="char d[]=_void c(int a){_if(a==95)a=10;_putchar(a);_}_int main(){_int i=0,j=0;_while(i<9)c(d[i++]);_c(34);_while(putchar(d[j++])>0);_c(34);_c(59);_while(i<191)c(d[i++]);_return 0;_}_";
void c(int a){
if(a==95)a=10;
putchar(a);
}
int main(){
int i=0,j=0;
while(i<9)c(d[i++]);
c(34);
while(putchar(d[j++])>0);
c(34);
c(59);
while(i<191)c(d[i++]);
return 0;
}
