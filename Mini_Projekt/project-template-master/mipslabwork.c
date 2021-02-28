/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

// HEJ HEJ

#define TMR2PERIOD ((80000000 / 256) / 10)
#if TMR2PERIOD > 0xffff
#error "Timer period is too big."
#endif

void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{

}