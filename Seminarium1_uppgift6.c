#include "stdio.h"

int main() {
  double in[] = {11.0, 20.0, 100.0}; 
  double out[3];

  square_reverse(in, out, 3);

  printf("pos 0 = %.1f\npos 1 = %.1f\npos 2 = %.1f\n", out[0], out[1], out[2]);
  
  return 0;
}

void square_reverse(const double *x, double *y, const int len){
  int i = 0;
  while(i <= len){
    *(y+len-i-1) = *(x+i) * *(x+i);
    i++;
  }
}