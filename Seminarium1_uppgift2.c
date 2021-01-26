#include <stdio.h>
/* A “Hello World!” program. */
int main()
{
 int x = 0x14;             // 0001 0100
 int y = 0xFFFFFCA;        // 1111 1111 1111 1111 1111 1111 1100 1010
 int z = 0xFFFFF80;        // 1111 1111 1111 1111 1111 1111 1000 0000  

z= ((x & 0x3E00)>>13)|((y & 0x7)<<5)|z;  

 printf("%d \n",y);  
 printf("%d \n",x);
 printf("%d \n",z);
}