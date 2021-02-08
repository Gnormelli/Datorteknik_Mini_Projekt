
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define COLUMNS 6
int counter = 0;


void print_number(int n)
{

  if(counter == COLUMNS)
  {
    printf("\n");
    counter = 0;
  }

  printf("%10d ", n);
  counter++;

}
void print_sieves(int n){
	
    int a[n + 1];

    // Filling Array, will be changed later in code
    for(int i = 0; i < n; i++){
        a[i] = 1;
    }


    //Sieves of Erasthones algorithm
    for(int i = 2 ; i < sqrt(n); i++){                     // For every i below the root of n
        if( a[i] == 1){                                     // if the array is true
            for(int j = i * i; j <= n; j = j + i){          // for j = i^2, j = i^2 + i, i^2  not exceeding n, set to false
                a[j] = 0;
            }
        }
    }
    for(int i = 2; i <= n; i++){                            // if i is primes(a[i]) = true), it wil print all primes up to n
        if(a[i] == 1){
            print_number(i);
        }
    }
}
// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
