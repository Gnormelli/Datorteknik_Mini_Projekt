#include <stdio.h>

int main()
{

    int n = 3;      // n!
    int i = 1;      // outer loop variable
    int k = n + 1;  // outer loop compare constant
    int result = 1; // result is always 1 or above

    while (i != k)
    {        // as long as i != k we're okay
        i++; // increment i

        int product = 0; // initialize product to 0
        int j = 1;       // initialize inner loop var

        while (j != i)
        {                      // as long as j != i we're okay
            j++;               // increment j
            product += result; // do a1 = a1 + v0
        }

        result = product;
    }

    printf("%d\n", result);

    return 0;
}