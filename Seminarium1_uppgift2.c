#include <stdio.h>
/* A “Hello World!” program. */
int main()
{
 int x = 0x14;
 int y = 0xFFFFFFCA;
 int z = 0xFFFFFF80;
 
 printf("%d \n",z);
 printf("%d \n",y);

 y<<5; 
 z = z<<8;
 printf("%d \n",z);
  
 printf("%d",x);

}