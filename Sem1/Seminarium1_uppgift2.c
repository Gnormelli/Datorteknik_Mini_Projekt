#include <stdio.h>
/* A “Hello World!” program. */
int main()
{
 int x = 0xABCDEAB;        // 0001 0100
 int y = 0xFFFFFCA;        // 1111 1111 1111 1111 1111 1111 1100 1010
 int z = 0xFFFFF80;        // 1111 1111 1111 1111 1111 1111 1000 0000  
 
 z = ((x & 0x3E00)>>13) | ((y & 0x7)<<5) | z;

 // x & 0x3E00 = 0000 0000 0000 0000 0000 0000 0000 0000
 // y & 0x7    =    
 
 printf("%d \n",x);
 printf("%d \n",y);  
 printf("%d \n",z);
}