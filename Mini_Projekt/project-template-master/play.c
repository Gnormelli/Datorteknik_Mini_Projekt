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

char scorescreen[10] = {1, 1, 1, 1, 1, 1, 1, 48, 48, 0};
int score = 0;



void play(){

    countdown();
    movedown();    

   

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