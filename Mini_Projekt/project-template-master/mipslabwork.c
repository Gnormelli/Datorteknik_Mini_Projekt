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

uint8_t screen[128*4] = {0};

 
volatile int *TRIS_E; // declare the pointers volatile and global
volatile int *PORT_E;

int gameviews = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view  
   
int btncounter = 0;

void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  
  PORT_E = (volatile int *)0xbf886110; 
  *PORT_E = 0x0; 
  

  TRISD = TRISD | 0x0fe0;

  display_string(2,"TETRIS");
  display_update();

  return;
}

void labwork(void)
{

  menu();
  int btn = getbtns();

  if(btn) 
  {
    btncounter == 1;

    if(btn) //
    {
      gameviews = 1;
      display_string(0, "    ");
      display_string(1,"     PLAY");
      display_string(2,"     HIGHSCORE");
      display_string(3, "    ");
      display_update();
      return;
    }
    if(btn & 0x4) // Start to play the game, WIP, needs F port, mapped to BTN3 for now
    {
      gameviews = 2;
      play();
      return;
    }
    if(btn & 0x2) //  Highscore
    {
      gameviews = 2;
      highscore();
      return;
    }
  }
}

void play()
{
  display_string(0,"");
  display_string(1, "");
  display_update();
}

void highscore()
{

}