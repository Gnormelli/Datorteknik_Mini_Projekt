#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

#define TMR2PERIOD (80000000 / 10 / 256)

volatile int *TRIS_E; // declare the pointers volatile and global
volatile int *PORT_E; // DONT!!!!! use the defenitions in pic32 sheet, numerous errors occur

int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;

void user_isr(void)
{
  return;
}

void labinit(void)
{

  // Initialize port E, TRISE has adress 0xbf886100, porte has 0xbf886110
  // Set *E to address of TRISE, volatile int pointer
  TRIS_E = (volatile int *)0xbf886100;
  PORT_E = (volatile int *)0xbf886110;

  *PORT_E = 0x0;
  *TRIS_E = *TRIS_E & 0xff00;

  TRISD = TRISD | 0x0ff0;

  TRISF = TRISF | 0x1;

  IFS(0) = 0;

  TMR2 = 0;
  PR2 = TMR2PERIOD;
  T2CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  // Will help with generating random blocks
  TMR3 = 0;
  PR3 = 50000;     //Arbitrary number, need the remainders of this
  T3CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  titleview();
  delay(2000);
  views = 1;

  return;
}

void labwork(void)
{
  if (views == 1)
  {
    menu();
    views = 0;
    return;
  }

  if (views == 0)
  {
    if (getbtns() & 0x4) // Start to play the game, WIP, needs F port, mapped to BTN3 for now
    {
      views = 2;
      gameboard();
      while (views == 2)
      {
        play();
      }
      return;
    }
    else if (getbtns() & 0x2) //  Highscore
    {
      highscore();
      views = 5;
      PORTDCLR = 0x0007;
      return;
    }
  }
  else if (views == 5)
  { 
    if (getbtns() & 0x2)
    {
      views = 1;
      PORTDCLR = 0x0007;
      return;
    }
  }
}