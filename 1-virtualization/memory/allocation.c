#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   char *txt;
   
   // Add your code below this line

   txt = (char *) malloc(6);
   strcpy(txt, "Hello");
   printf("String: %s,  Address: %u\n", txt, txt);

   txt = (char *) realloc(txt, 25);
   strcat(txt, " World");
   printf("String: %s,  Address: %u\n", txt, txt);

   free(txt);
   printf("String: %s,  Address: %u\n", txt, txt);
   
   // Add your code above this line

    return 0;
}