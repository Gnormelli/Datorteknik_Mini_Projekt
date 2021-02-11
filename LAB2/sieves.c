#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6


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

void print_sieves(int n)
{
    bool numbers[n];
    for (int i = 0; i < n; i++)
    {
        numbers[i] = true;
    }
    for (int i = 2; i < sqrt(n); i++)
    {
        if(numbers[i] == 1)
            for (int j = (i * i); j < n; j+=i)  
            {
                numbers[j] = false;
            }
    }
    for (int i = 2; i < n; i++)
    {
        if (numbers[i] == true)
        {
            print_number(i);
        }
    }
}
// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{   
    
    // Calculate the time taken by fun() 
    clock_t t; 
    t = clock(); 
    print_sieves(80000); 
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  
    printf("fun() took %f seconds to execute \n", time_taken); 
    return 0; 
    /*
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");
    return 0;
    */
   //print_sieves(105); // Fungerar som det ska.*/
}