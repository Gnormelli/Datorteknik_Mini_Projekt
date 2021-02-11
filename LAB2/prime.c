/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>

int is_prime(int n)
{
  int prime = 0;
  int i;
  if (n == 2)
  {
    return prime = 1;
  }
  for (i = 2; i < n; i++)
  {
    if (n % i == 0)
    {
      prime = 0;
      break;
    }
    else
    {
      prime = 1;
    }
  }
  return prime;
}

int main(void)
{
  printf("%d\n", is_prime(1));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(2)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
