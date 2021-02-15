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

#define TMR2PERIOD ((80000000 / 256) / 10)
#if TMR2PERIOD > 0xffff
#error "Timer period is too big."
#endif 

volatile int *TRIS_E; // declare the pointers volatile and global
volatile int *PORT_E; // DONT!!!!! use the defenitions in pic32 sheet, numerous errors occur

int timeoutcount = 0;

int mytime = 0x0001; // Changed to 0x0001 from 5957 to more easily read I/O binaries

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{

  // 1c
  // Initialize port E, TRISE has adress 0xbf886100, porte has 0xbf886110
  // Set *E to address of TRISE, volatile int pointer
  TRIS_E = (volatile int *)0xbf886100;

  PORT_E = (volatile int *)0xbf886110;

  *PORT_E = 0x0; // Initialize portE to 0, IS this necessary since

  // The TRISx register bits determine whether a PORTx I/O pin is an input or an output
  // Set the 8 least significant bits to zero to set them to be output pins
  // If a data direction bit is ‘1’, the corresponding I/O port pin is an input, 0 is output
  *TRIS_E = *TRIS_E & 0xff00;

  //1e
  // Initialize port D, set bits 11-5 as inputs.
  // DO!!!! Use the definitions in pic32 sheet
  TRISD = TRISD | 0x0fe0;

  PR2 =TMR2PERIOD;
  T2CONSET = 0x70; // for setting bit 5 - 6 to prescale
  TMR2 = 0;

  T2CONSET = 0x0000; // 15th bit set to 1, turns on timer
  
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{

  int switches = getsw();
  int buttons = getbtns();

  /*
  //Button 4
  if(buttons == 4 || buttons == 5 || buttons == 6 || buttons == 7){
    mytime = mytime & 0x0fff;
    mytime = (switches << 12) | mytime;
  }
  //Button 3
  if(buttons == 2 || buttons == 3 || buttons == 6 || buttons == 7){
    mytime = mytime & 0xf0ff;
    mytime = (switches << 8) | mytime;
  }
  //Button 2
  if(buttons == 1 || buttons == 3 || buttons == 5 || buttons == 7){
    mytime = mytime & 0xff0f;
    mytime = (switches << 4) | mytime;
  }
  */

  //Button 4
  if (buttons == 4)
  {
    mytime = mytime & 0x0fff;
    mytime = (switches << 12) | mytime;
  }
  //Button 3
  if (buttons == 2)
  {
    mytime = mytime & 0xf0ff;
    mytime = (switches << 8) | mytime;
  }
  //Button 2
  if (buttons == 1)
  {
    mytime = mytime & 0xff0f;
    mytime = (switches << 4) | mytime;
  }


  if (IFS(0) & 0x100)
  {           
    IFSCLR(0) = 0x100;

    timeoutcount++; 
  }

  if(timeoutcount == 10){
    //delay(1000);
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
    tick(&mytime);
    display_image(96, icon);

    timeoutcount = 0;
  }

  //1d
  //Dereference PORTE-pointer and incriment with 1
  (*PORT_E)++;
}
