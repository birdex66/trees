#include <stdio.h>
#include <stdlib.h>

int main()
{	
   char buffer[8];
   printf("Triangle height --> ");
   scanf("%s",buffer);

   int i=0,height=atoi(buffer); //,spaces = 1 << height;

   //printf("nodes: %i\n",spaces);
   int base = (height*2)-1;
   int spaces = base/2;

   printf("base: %i\nspaces: %i\n",base,spaces);
/*
   for(int i=0,j=0; j<height; ++i){
      if(i >= base){
         ++j;
         i=0;
         printf("| spaces:%i\n",spaces);
         --spaces;
      }
      printf("%s",( i < spaces || (i >= (base-spaces) && j < height) ) ? " " : "*");
   }
*/
   for(int i=0; i<height; ++i){
      for(int j=0; j<base; ++j){
         printf("%s",( j < spaces || (j >= (base-spaces) && i < height) ) ? " " : "*");
      }
      printf("| spaces:%i\n",spaces--);
   }

   return 0;
}

/*

 *     |
 ***    |
 *****   |
 *******  |

*/
