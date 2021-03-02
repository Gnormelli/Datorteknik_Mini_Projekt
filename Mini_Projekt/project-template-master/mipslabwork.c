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

int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;

void user_isr(void)
{
  return;
}


void labwork(void)
{
  int btn = getbtns();
  if(views==0){
    display_string(2, "TETRIS");
    display_update();
    delay(3000);
    menu();
    views = 1; 
  }

  if(btn!=0 && btncounter == 0) 
  {
    btncounter == 1;
    if(views==1){
      if(btn & 0x4) // Start to play the game, WIP, needs F port, mapped to BTN3 for now
      {
        views = 2;
        countdown();
        movedown();
        return;
      }
      if(btn & 0x2) //  Highscore
      {
        views = 5;
        highscore();
        return;
      }
    }
    if(views == 5){
      if(btn & 0x2){
        views = 1;
        menu();
        return;
      }
    }
  }
}