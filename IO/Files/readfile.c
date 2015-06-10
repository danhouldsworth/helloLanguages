#include <stdio.h>
#include <stdlib.h>

int main()
{
   char ch;
   FILE *fp;

   if( (fp = fopen("readfile.c","r")) == NULL ) {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

   printf("The contents are :\n");

   while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);

   fclose(fp);
   return 0;
}
