#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

#define TMR2PERIOD (80000000 / 256)

uint8_t screen[128 * 4] = {0};
uint8_t screen2[128 * 4] = {0};
int pos = 220;
int n = 15;

int blocktype = 0;

int block[4] = {15, 0, 0, 0};
int blockTwo[4] = {0, 0, 0, 0};

int gamespeed = 10;

int randomizer = 0;

int i;

char *scorescreen[10] = {1, 1, 1, 1, 1, 1, 1, 48, 48, 0};
int score = 0;



void play(){

    setup();
    int gaming = 1;
    while(gaming == 1){
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
}

void movedown(void) // move down logic, every tick will make the block fall
{
    if ((screen[pos - 1] & block[0]) || (screen[pos - 1 + 128] & block[2]) ||
        ((screen[pos + 3] & ~block[0]) & block[1]) || ((screen[pos + 3 + 128] & ~block[2]) & block[3]))
    {

        if (pos % 128 > 111)
        {
            gameover(scorescreen, score);
        }

    }
    else
    {
        // clear block
        for (i = 0; i < 4; i++)
        {
            screen[pos + i] -= block[0];
            screen[pos + 4 + i] -= block[1];
            screen[pos + 128 + i] -= block[2];
            screen[pos + 128 + 4 + i] -= block[3];
        }
        // add block
        pos--;
        for (i = 0; i < 4; i++)
        {
            screen[pos + i] += block[0];
            screen[pos + 4 + i] += block[1];
            screen[pos + 128 + i] += block[2];
            screen[pos + 128 + 4 + i] += block[3];
        }
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

void newblock(void) // generates a new block at the top of the gamescreen
{
}

void rowcomplete(void) // Checks if a row is complete. If its true, the player will be awarded 1 point and the gamespeed will increase
{
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