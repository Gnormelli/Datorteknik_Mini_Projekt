/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_primes(int n)
{
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  int i = 1;
  for (i; i <= n; i++)
  {
    if (is_prime(i) == 1)
    {
      print_number(i);
    }
  }
}

int c = 0; // Global variabel
void print_number(int number)
{
  printf("%10d ", number);
  c++;
  if (c == COLUMNS)
  {
    printf("\n");
    c = 0;
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
 /* 
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
  */
  print_primes(105); // Fungerar som det ska. 
}

int is_prime(int n)
{
  int prime;
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
