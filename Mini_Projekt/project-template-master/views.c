#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdbool.h>
                    // 0,      1,2,       3,    4,      5,      6,     7,       8,       9,     10,   11
                    //{number,:,blank,letter1,letter2,letter3,blank,hsnumber1,hsnumber2,blank,blank, null}
char highscore1[12] = {49, 46, 8, 71, 85, 78, 8, 49, 51, 8, 8, 0};
char highscore2[12] = {50, 46, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0};
char highscore3[12] = {51, 46, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0};

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
    display_string(1, "PLAY - BTN4");
    display_string(2, "HIGHSCORE - BTN3");
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

    // display_string(1,);
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
    highscore1[7] = firsths / 10 + 48;
    highscore1[8] = firsths % 10 + 48;
    highscore2[7] = secondhs / 10 + 48;
    highscore2[8] = secondhs % 10 + 48;
    highscore3[7] = thirdhs / 10 + 48;
    highscore3[8] = thirdhs % 10 + 48;

    display_string(0, "    GAME OVER");
    display_string(1, "     score:");
    display_string(3, "");
    display_string(2, gamescore);
    display_update();
    delay(2000);
}

void highscore()
{
    display_string(0, "Highscore    BTN1");

    display_string(1, highscore1);
    display_string(2, highscore2);
    display_string(3, highscore2);
    display_update();
}
