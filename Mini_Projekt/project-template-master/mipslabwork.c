#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

#define TMR2PERIOD (80000000 / 256)

volatile int *TRIS_E; // declare the pointers volatile and global
volatile int *PORT_E; // DONT!!!!! use the defenitions in pic32 sheet, numerous errors occur

int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;

int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;

void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
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

  titleview();
	delay(3000);
	views = 1;

  return;
}

void labwork(void)
{
  //if (swt != 0 && btncounter == 0) //
  //{
  //if (views == 1)
  //{
  int swt = getsw();
  if (views == 1)
  {
    menu();
    views = 0;
    return;
  }
  if (swt & 0x4) // Start to play the game, WIP, needs F port, mapped to BTN3 for now
  {
    views = 2;
    while (views == 2)
    {
      play(); /* Do lab-specific things again and again */
    }
    PORTDCLR = 0x4;
    return;
  }
  if (swt & 0x2) //  Highscore
  {
    views = 5;
    highscore();
    PORTDCLR = 0x2;
    return;
  }
  //}
  if (views == 5)
  {
    if (swt & 0x2) // Back to menu
    {
      views = 1;
      PORTDCLR = 0x2;
      return;
    }
  }
  //}
}