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
    bool *size;
    size = malloc(sizeof(bool)*n); // Change to boolean

    for (int i = 0; i < n; i++) // Change 
    {
        size[i] = 1; // True and 1  
    }
    for (int i = 2; i < sqrt(n); i++)
    {
        if(size[i]== 1){
            for (int j = (i * i); j < n; j+=i)
            {
                size[j] = 0;
            }
        }
    }
    for (int i = 2; i < n; i++)
    {
        if (size[i] == 1)
        {
            print_number(i);
        }
    }
    free(size);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
    // Calculate the time taken by fun() 
    clock_t t; 
    t = clock(); 
    print_sieves(100000); 
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
    //print_sieves(80000); // Fungerar som det ska.
}