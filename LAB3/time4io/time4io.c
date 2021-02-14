#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/*
 * Returns data from SWx
 * switches are bits 11-8
 * slr >> 8 steps to teturn 4 LSB
 */
int getsw(void)  // called as "getsw();"
{ 

    return (PORTD >> 8) & 0x000F;
}

/*
 * Returns data from BTNx
 * buttons are bits 7-5
 * slr >> 5 steps
 */
int getbtns(void) // called as "getbtns();"
{
    return (PORTD >> 5) & 0x0007;
}