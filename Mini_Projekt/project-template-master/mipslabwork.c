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

#define TMR2PERIOD (80000000 / 256)

volatile int *TRIS_E; // declare the pointers volatile and global
volatile int *PORT_E; // DONT!!!!! use the defenitions in pic32 sheet, numerous errors occur

uint8_t screen[128 * 4] = {0};
uint8_t screen2[128 * 4] = {0};
int pos = 240;
int n = 15;

int blocktype = 0;

int block[4] = {15, 0, 0, 0};
int blockTwo[4] = {0, 0, 0, 0};

int gamespeed = 10;

int randomizer = 0;

int i;

/* Lab-specific initialization goes here */
void labinit(void)
{

  // Initialize port E, TRISE has adress 0xbf886100, porte has 0xbf886110
  // Set *E to address of TRISE, volatile int pointer
  TRIS_E = (volatile int *)0xbf886100;
  PORT_E = (volatile int *)0xbf886110;

  *PORT_E = 0x0;
  *TRIS_E = *TRIS_E & 0xff00;

  TRISD = TRISD | 0x0fe0;

  TRISF = TRISF | 0x1;

  IFS(0) = 0;

  TMR2 = 0;
  PR2 = TMR2PERIOD;
  T2CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  // Will help with generating random blocks
  TMR3 = 0;
  PR3 = 50000;
  T3CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  int pos = 240;
  // Bottom line
  screen[0] = 255;
  screen[128] = 255;
  screen[256] = 255;
  screen[384] = 255;

  //Top line
  screen[110] = 255;
  screen[238] = 255;
  screen[366] = 255;
  screen[494] = 255;

  screen[pos] = 15;
  screen[pos + 1] = 15;
  screen[pos + 2] = 15;
  screen[pos + 3] = 15;

  return;
}

int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;

void user_isr(void)
{
  return;
}

void labwork(void)
{
  int btn = getbtns();
  if (views == 0)
  {
    display_string(2, "TETRIS");
    display_update();
    delay(3000);
    //menu();
    views = 1;
  }

  if (btn & 0x4)
  {
    countdown();
  }
}

void countdown(void)
{ // (screen is oriented upside down)

  screen[320] = 31; // 1 1111            1 1111            1
  screen[321] = 16; // 1                      1            1
  screen[322] = 16; // 1                      1            1
  screen[323] = 31; // 1 1111    ----->  1 1111   ---->    1
  screen[324] = 16; // 1                 1                 1
  screen[325] = 16; // 1                 1                 1
  screen[326] = 31; // 1 1111            1 1111            1

  display_image(0, screen); // shows 3
  delay(50000);
  screen[321] = 1;
  screen[322] = 1;
  display_image(0, screen); // changes 3 -> 2
  delay(50000);
  for (i = 0; i < 7; i++)
    screen[320 + i] = 16;
  display_image(0, screen); // changes 2 -> 1
  delay(50000);
  for (i = 0; i < 7; i++)
    screen[320 + i] = 0; // Clears the screen
}