#include <stdio.h>

//Function declarations

void adder(const int *x,const int *y,int *z);

int foo(int a);

int main()

{
    int result;
    result=foo(7);

    printf("Result = %d",result);

    return 0;
}

void adder(const int *x,const int *y,int *z)

{
    *z=(*x)+(*y);
}

int foo(int a)
{
    int result;
    const int k=10;

    adder(&a,&k,&result);

    return result;
}