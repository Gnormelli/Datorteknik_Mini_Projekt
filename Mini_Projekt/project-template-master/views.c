#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdbool.h>

char highscore1[12] = {8, 8, 8, 8, 8, 8, 49, 46, 8, 48, 48, 0};
char highscore2[12] = {8, 8, 8, 8, 8, 8, 50, 46, 8, 48, 48, 0};
char highscore3[12] = {8, 8, 8, 8, 8, 8, 51, 46, 8, 48, 48, 0};

char letter1[12] = {8, 8, 8, 8, 8, 8, 49, 46, 8, 48, 48, 0};
char letter2[12] = {8, 8, 8, 8, 8, 8, 50, 46, 8, 48, 48, 0};
char letter3[12] = {8, 8, 8, 8, 8, 8, 51, 46, 8, 48, 48, 0};

int firsths = 0;
int secondhs = 0;
int thirdhs = 0;

void titleview()
{
    display_string(2, "TETRIS");
    display_update();
}

void menu()
{

    display_string(0, "    ");
    display_string(1, "  PLAY - BTN2");
    display_string(2, "  HIGHSCORE - BTN3");
    display_string(3, "    ");
    display_update();
}
void write_highscore()
{
    bool write = true;
    int press = 0;


    while (write)
    {
        display_string(0, "  Enter your initials ");
        if (getsw())
        { 
            int btn = getbtns(); 
            //Activate first letter
            if (getsw() & 0x4) // switch 100
            {
                
                if (getbtns())
                press++;
            }

            //Activate second letter
            if (getsw() & 0x2) // switch 010
            {
                
            }

            //Activate third letter
            if (getsw() & 0x1) // switch 001
            {
                
            }
        }
    }

    display_string(1, letter1 + " " + letter2 + " " + letter3);
    display_update();
}

void gameover(int gamescore)
{
    if (gamescore > firsths)
    {
        thirdhs = secondhs;
        secondhs = firsths;
        firsths = gamescore;
    }
    else if (gamescore > secondhs)
    {
        thirdhs = secondhs;
        secondhs = gamescore;
    }
    else if (gamescore > thirdhs)
    {
        thirdhs = gamescore;
    }
    highscore1[9] = firsths / 10 + 48;
    highscore1[10] = firsths % 10 + 48;
    highscore2[9] = secondhs / 10 + 48;
    highscore2[10] = secondhs % 10 + 48;
    highscore3[9] = thirdhs / 10 + 48;
    highscore3[10] = thirdhs % 10 + 48;

    display_string(0, "    GAME OVER");
    display_string(1, "     score:");
    display_string(3, "");
    display_string(2, gamescore);
    display_update();
    delay(2000);
}

void highscore()
{
    display_string(0, "  Highscore ");

    display_string(1, "1: " + letter1 + " " + highscore1);
    display_string(2, "2: " + letter2 + " " + highscore2);
    display_string(3, "3: " + letter2 + " " + highscore2);
    display_update();
}
