#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */c
#include "mipslab.h" /* Declatations for these labs */

#define TMR2PERIOD (80000000 / 256)

uint8_t screen[128 * 4] = {0};
uint8_t screentemp[128 * 4] = {0};
int y = 233;

int block[4] = {0xf, 0, 0, 0};
int blocktemp[4] = {0};
int shape = 0; // 0 = Cube, 1 = L-shape , 2 = Z - shape , 3 = Rectangle, 4 = T - shape
int check = 0;

int btncounter = 0;

int gamespeed = 30;

int views = -1; // -1 - title, 0 - startscreen, 1 - running, 2 - game over, 3 - highscore
int i;

/* Interrupt Service Routine */
void user_isr(void)
{
  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{

  TRISD = TRISD | 0x0fe0;

  TRISF = TRISF | 0x1; // btn 4

  TMR2 = 0;
  PR2 = TMR2PERIOD / gamespeed;
  T2CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  // random nr
  TMR3 = 0;
  PR3 = 54321;     //Arbitrary number, need the remainders of this for random shapes in newshapes function
  T3CON = 0x08070; // Turn on 15 bit for timer, bit 4-6 for prescale

  // Bottom line for "floor"
  for (i = 0; i < 4; i++)
  {
    screen[0 + (128 * i)] = 0xff;
  }

  //Top line to cut off for preview screen
  for (i = 0; i < 4; i++)
  {
    screen[120 + (128 * i)] = 0xff;
  }

  display_string(2, "     TETRIS");
  display_update();
  delay(2000);

  newshape();

  return;
}

void labwork(void)
{
  int btn = getbtns();
  if (btn != 0 && btncounter == 0)
  {
    btncounter = 1;

    if (views == -1)
    {
      views = 0;
      display_string(0, " LETS");
      display_string(1, "  GO");
      display_string(2, "  ");
      display_string(3, "  ");
      display_update();
      return;
    }

    /* if (views == 0)
    {
      countdown();
      views = 1;
      return;
    }*/

    if ((btn & 0x01) == 1)
      rotate();

    if ((btn & 0x02) == 2 && (y < 384 || check == 0)) //BTN2
      moveright();

    if ((btn & 0x08) == 8 && (y > 127 || check == 1)) //BTN4
      moveleft();
  }
  else if (btn == 0)
    btncounter = 0;

  display_image(0, screen); // update image on screen

  if (IFS(0))
  {
    IFS(0) = 0;
    movedown();
  }
}

void createblock(void) // Self explanatory
{
  for (i = 0; i < 4; i++)
  {
    screen[y + i] += block[0];     // creates block part A
    screen[y + 4 + i] += block[1]; //  creates block part B
    /*screen[y + 8 + i] += block[2];       // creates block part C
    screen[y + 12 + i] += block[3];      // creates block part J*/
    screen[y + 128 + i] += block[2];     // creates block part D
    screen[y + 128 + 4 + i] += block[3]; // creates block part E
    /*screen[y + 128 + 8 + i] += block[6]; // creates block part F
    screen[y + 256 + i] += block[7];     // creates block part G*/
  }
}

void clearblock(void) // Self expalatory
{
  //Removes previous block iteration
  for (i = 0; i < 4; i++)
  {
    screen[y + i] -= block[0];     // clears block part A
    screen[y + 4 + i] -= block[1]; // clears block part B
    /*screen[y + 8 + i] -= block[2];       // clears block part C
    screen[y + 12 + i] -= block[3];      // clears block part J*/
    screen[y + 128 + i] -= block[2];     // clears block part D
    screen[y + 128 + 4 + i] -= block[3]; // clears block part E
    /* screen[y + 128 + 8 + i] -= block[6]; // clears block part F
    screen[y + 256 + i] -= block[7];     // clears block part G*/
  }
}

void movedown(void) // move down logic, every tick will make the block fall
{
  if ((screen[y - 1] & block[0]) || (screen[y - 1 + 128] & block[2]) ||
      ((screen[y + 3] & ~block[0]) & block[1]) || ((screen[y + 3 + 128] & ~block[2]) & block[3]))
  {
    if (y % 128 > 97)
    {
      views = 2;
      display_string(0, "    GAME OVER");
      display_string(1, "     ");
      display_string(3, "");
      display_update();
      delay(3000);
    }
    rowcomplete();
    newshape();
  }
  else
  {
    clearblock();

    y--;

    createblock();
  }
}

void rowcomplete(void) // Checks if a row is complete. If its true, the player will be awarded 1 point and the gamespeed will increase
{
  int k = 0;
  int j = 0;
  for (i = 0; i < 4; i++)
  {
    if (screen[(y % 128) + (128 * i)] != 255)
    {
      return;
    }
  }

  //clears blocks if one row is full
  for (i = 0; i < 4; i++)
  {
    for (k = 0; k < 4; k++)
    {
      screen[((y + i) % 128) + (128 * k)] = 0;
    }
  }

  for (i = y % 128; i < 124; i++)
  {
    for (k = 0; k < 4; k++)
    {
      screentemp[i + (128 * k)] = screen[i + 4 + (128 * k)];
    }
  }

  for (i = y % 128; i < 124; i++)
  {
    for (k = 0; k < 4; k++)
    {
      screen[i + (128 * k)] = screentemp[i + (128 * k)];
    }
  }

}

void newshape(void) // generates a new block at the top of the gamescreen
{
  shape = TMR3 % 3; // value between [0-2]
  y = 233;
  check = 0;

  for (i = 0; i < 4; i++)
  {
    block[i] = 0;
  }
  block[0] = 0xff;

  if (shape == 1)
  {
    block[1] = 0xff;
  }
  if (shape == 2)
  {
    block[1] = 0xf;
  }
  createblock();
}

void moveright(void) // move right logic, if BTN1 is pressed, the block will move right
{
  if (y >= 384) // && (shape && !(block[0] == 15 && block[1] == 15))
    return;

  for (i = 0; i < 4; i++)
    blocktemp[i] = 0;

  if (check == 0)
  {
    blocktemp[0] = ((block[0] & 0xf) << 4);
    blocktemp[1] = ((block[1] & 0xf) << 4);
    blocktemp[2] = ((block[0] & 0xf0) >> 4); // Keeps the block intact in movemnent, or else parts of the blocks will dissapear
    blocktemp[3] = ((block[1] & 0xf0) >> 4);
  }
  else
  {
    blocktemp[2] = (block[0] >> 4) | (block[2] << 4);
    blocktemp[3] = (block[1] >> 4) | (block[3] << 4);
  }

  cleaner();

  if (check == 0)
    for (i = 0; i < 4; i++)
      block[i] = blocktemp[i];
  else
  {
    block[0] = blocktemp[2];
    block[1] = blocktemp[3];
    block[2] = 0;
    block[3] = 0;
  }

  if (check == 0)
  {
    createblock();
    check = 1;
  }
  else
  {
    check = 0;
    y += 128;
    createblock();
  }
}

void moveleft(void) // move left logic, if BTN2 is pressed, the block will move left
{
  if (y < 128 && (check == 0))
    return;

  for (i = 0; i < 4; i++)
    blocktemp[i] = 0;

  if (check == 0)
  {
    blocktemp[0] = ((block[0] & 0xf) << 4);
    blocktemp[1] = ((block[1] & 0xf) << 4);
    blocktemp[2] = ((block[0] & 0xf0) >> 4) | (block[2] << 4);
    blocktemp[3] = ((block[1] & 0xf0) >> 4) | (block[3] << 4);
  }
  else
  {
    blocktemp[0] = (block[0] >> 4) | (block[2] << 4);
    blocktemp[1] = (block[1] >> 4) | (block[3] << 4);
  }

  cleaner();

  if (check == 0)
    for (i = 0; i < 4; i++)
      block[i] = blocktemp[i];
  else
  {
    block[0] = blocktemp[0];
    block[1] = blocktemp[1];
    block[2] = 0;
    block[3] = 0;
  }

  if (check == 0)
  {
    y -= 128;
    createblock();
    check = 1;
  }
  else
  {
    check = 0;
    createblock();
  }
}

void rotate(void) // rotation logic, if BTN3 is pressed, the block will rotate
{
  for (i = 0; i < 4; i++)
  {
    blocktemp[i] = 0;
  }

  if (check == 0)
  {
    blocktemp[0] = ((block[0] & 0xf0) >> 4) | (block[1] & 0xf0);
    blocktemp[1] = ((block[1] & 0xf) << 4) | (block[0] & 0xf);
  }
  else
  {
    blocktemp[0] = block[2] << 4;
    blocktemp[1] = block[0];
    blocktemp[2] = block[3];
    blocktemp[3] = block[1] >> 4;
  }

  cleaner();

  for (i = 0; i < 4; i++)
    block[i] = blocktemp[i];

  createblock();
}

int cleaner(void) // Removes the "leftovers" from the blocks previous position after a movement is performed
{
  clearblock();

  for (i = 0; i < 4; i++)
  {
    if ((screen[y + i] & blocktemp[0]) || (screen[y + 4 + i] & blocktemp[1]) ||
        (screen[y + 128 + i] & blocktemp[2]) || (screen[y + 128 + 4 + i] & blocktemp[3]))
    {
      createblock();
      return 1;
    }
  }
  return 0;
}

void countdown(void) // Countdown for the game
{                    // (screen is oriented upside down)

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