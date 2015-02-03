// 3. Done.

int swapChar(char* p, char*q){
    *p=*p^*q;
    *q=*p^*q;
    *p=*p^*q;
    return *p;
}

int main(){
    char origin[]="Hello";
    char copyed[]="world";
    char *a,*b;

    printf("\norigin = <%s> and copyed = <%s>\n",origin,copyed);

    a=origin;
    b=copyed;
    while (swapChar(a++,b++));
    printf("\norigin = <%s> and copyed = <%s>\n",origin,copyed);

    a=origin;
    b=copyed;
    while (*b++=*a++);
    printf("\norigin = <%s> and copyed = <%s>\n",origin,copyed);

}
