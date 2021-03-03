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

uint8_t screen[128 * 4] = {0};
uint8_t screen2[128 * 4] = {0};
int y = 360;
int n = 15;

int shape = 0; // 0 = Cube, 1 = L-shape , 2 = Z - shape , 3 = Rectangle, 4 = T - shape

int block[8] = {0xf, 0, 0, 0, 0, 0, 0, 0};
int blockTwo[8] = {0};

int gamespeed = 100;

int randomizer = 0;

int i;

char scorescreen[10] = {32, 32, 32, 32, 32, 32, 32, 48, 48, 0};
int score = 0;

<<<<<<< HEAD


void play(){
    
    setup();
    
    int gaming = 1;
    while(gaming == 1)
    {
        countdown();
        movedown();    
    }
   

}

/* Lab-specific initialization goes here */
void setup(void)
{
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
  screen[118] = 255; // 1111 1111
  screen[246] = 255;
  screen[374] = 255;
  screen[502] = 255;

  screen[pos] = 15; // 0000 1111
  screen[pos + 1] = 15;
  screen[pos + 2] = 15;
  screen[pos + 3] = 15;

  return;
=======
int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;

/* Lab-specific initialization goes here */
void createblock(void)
{
  for (i = 0; i < 4; i++)
  {
    screen[y + i] += block[0];      // creates block part A
    screen[y + 4 + i] += block[1];  //  creates block part B
    screen[y + 8 + i] += block[2];  // creates block part C
    screen[y + 12 + i] += block[3]; // creates block part J
    screen[y + 128 + i] += block[4];       // creates block part D
    screen[y + 128 + 4 + i] += block[5];    // creates block part E
    screen[y + 128 + 8 + i] += block [6];   // creates block part F
    screen[y + 256 + i] += block[7];        // creates block part G
    //screen[y + 256 + 4 + i] += block[8];    // creates block part H
    //screen[y + 256 + 8 + i] += block[9];    // creates block part I
    
  }
}
void clearblock(void)
{
  //Removes previous block iteration
  for (i = 0; i < 4; i++)
  {
    screen[y + i] -= block[0];      // clears block part A
    screen[y + 4 + i] -= block[1];  // clears block part B
    screen[y + 8 + i] -= block[2];  // clears block part C
    screen[y + 12 + i] -= block[3]; // clears block part J
    screen[y + 128 + i] -= block[4];    // clears block part D
    screen[y + 128 + 4 + i] -= block[5]; // clears block part E
    screen[y + 128 + 8 + i] -= block[6]; // clears block part F
    screen[y + 256 + i] -= block[7];     // clears block part G
    //screen[y + 256 + 4 + i] -= block[8]; // clears block part H
    //screen[y + 256 + 8 + i] -= block[9]; // clears block part I
    
  }
}

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
  PR3 = 50000;     //Arbitrary number, need the remainders of this
  T3CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  // Bottom line
  for (i = 0; i < 4; i++)
  {
    screen[0 + (128 * i)] = 0xff;
  }

  //Top line
  for (i = 0; i < 4; i++)
  {
    screen[118 + (128 * i)] = 0xff;
  }

  // First block
  for (i = 0; i < 4; i++)
  {
    block[1] = 0xf;
    block[2] = 0xf;
    block[3] = 0xf;
    createblock(); // ********change to 255 for big block later***************
  }

  return;
}

void user_isr(void)
{
  return;
}

void newshape(void) // generates a new block at the top of the gamescreen
{
  shape = 1; // 0 = Cube, 1 = L-shape , 2 = Z - shape , 3 = Rectangle, 4 = T - shape
  y = 360;
  for(i = 0; i < 8; i++)
  {
    block[i] = 0;
  }
  if (shape == 0) //Cube
  {
    block[0] = 0xff;
    block[1] = 0xff;
  }
  
  if(shape == 1)  // L-shape
  {
    block[0] = 0xff;
    block[1] = 0xf;
    block[2] = 0xf;
    //block[6] = 0xf;
  }
  /*
  if(shape == 2)   // Z - Shape
  {
    block[1] = 0xf;
    block[2] = 0xf;
    block[4] = 0xf;
    block[5] = 0xf;
  }
  if(shape == 3)    // Rectangle
  {
    block[0] = 0xf;
    block[1] = 0xf;
    block[2] = 0xf;
    block[3] = 0xf;
  }
  if(shape == 4)    // T- shape
  {
    block[0] = 0xf;
    block[4] = 0xf;
    block[5] = 0xf;
    block[7] = 0xf;
  }
  */
  createblock();
  
>>>>>>> master
}

void movedown(void) // move down logic, every tick will make the block fall
{
  if ((screen[y - 1] & block[0]) || (screen[y - 1 + 128] & block[2]) ||
      ((screen[y + 3] & ~block[0]) & block[1]) || ((screen[y + 3 + 128] & ~block[2]) & block[3]))
  {

    if (y % 128 > 107)
    {
      display_string(0, "    GAME OVER");
      display_string(1, "     score:");
      display_string(3, "");
      scorescreen[8] = score % 10 + 48;
      scorescreen[7] = score / 10 + 48;
      display_string(2, scorescreen);
      display_update();
      delay(2000);
    }
    newshape();
  }
  else
  {
    clearblock();

    y--;

<<<<<<< HEAD
        if (pos % 128 > 111)
        {
            gameover(scorescreen, score);
        }
=======
    createblock();
  }
}

void countdown(void) // Countdown for the game
{ // (screen is oriented upside down)

  screen[320] = 31; // 1 1111            1 1111            1
  screen[321] = 16; // 1                      1            1
  screen[322] = 16; // 1                      1            1
  screen[323] = 31; // 1 1111    ----->  1 1111   ---->    1
  screen[324] = 16; // 1                 1                 1
  screen[325] = 16; // 1                 1                 1
  screen[326] = 31; // 1 1111            1 1111            1

  display_image(0, screen); // shows 3
  delay(1000);
  screen[321] = 1;
  screen[322] = 1;
  display_image(0, screen); // changes 3 -> 2
  delay(1000);
  for (i = 0; i < 7; i++)
    screen[320 + i] = 1;
  display_image(0, screen); // changes 2 -> 1
  delay(1000);
  for (i = 0; i < 7; i++)
    screen[320 + i] = 0; // Clears the screen
}
>>>>>>> master

void labwork(void)
{
  int btn = getbtns();
  int sw = getsw();
  if (views == 0)
  {
    display_string(2, "TETRIS");
    display_update();
    delay(3000);
    menu();
    views = 1;
  }

  if (btn != 0 && btncounter == 0)
  {
    btncounter == 1;
    if (views == 1)
    {
      if (sw & 0x4) // Start to play the game, WIP, needs F port, mapped to BTN3 for now
      {
        views = 2;
        countdown();
        return;
      }
      if (sw & 0x2) //  Highscore
      {
        views = 5;
        highscore();
        return;
      }
    }
    if (views == 5)
    {
      if (sw & 0x2)
      {
        views = 1;
        menu();
        return;
      }
    }
  }
  display_image(0, screen);
  if (IFS(0))
  {
    IFS(0) = 0;
    movedown();
  }
}

void moveright(void) // move right logic, if BTN1 is pressed, the block will move right
{
}

void moveleft(void) // move left logic, if BTN2 is pressed, the block will move left
{
}

void rotate(void) // rotation logic, if BTN3 is pressed, the block will rotate
{
}

void cleaner(void) // Removes the "leftovers" from the blocks previous position after a movement is performed
{
}

void rowcomplete(void) // Checks if a row is complete. If its true, the player will be awarded 1 point and the gamespeed will increase
{
}



