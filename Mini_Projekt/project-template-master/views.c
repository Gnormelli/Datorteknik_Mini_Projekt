#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdbool.h>
                    // 0,     1, 2,       3,    4,      5,      6,     7,       8,       9,     10,   11
                    //{number,:,blank,letter1,letter2,letter3,blank,hsnumber1,hsnumber2,blank,blank, null}
char highscore1[12] = {49, 46, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0};
char highscore2[12] = {50, 46, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0};   //index 3 and 4
char highscore3[12] = {51, 46, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0};

int firsths = 0;
int secondhs = 0;
int thirdhs = 0;

char scoreboard[9] = {8,8,8,8,8,8,48,48,0};

void titleview()
{   
    display_string(0,"          ");
    display_string(1, "     TETRIS");
    display_string(2,"          ");
    display_string(3,"          ");
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
    int score = gamescore;

    if (score > firsths)
    {
        thirdhs = secondhs;
        secondhs = firsths;
        firsths = score;
    }
    else if (score > secondhs)
    {
        thirdhs = secondhs;
        secondhs = score;
    }
    else if (score > thirdhs)
    {
        thirdhs = score;
    }
    highscore1[3] = firsths / 10 + 48;
    highscore1[4] = firsths % 10 + 48;
    highscore2[3] = secondhs / 10 + 48;
    highscore2[4] = secondhs % 10 + 48;
    highscore3[3] = thirdhs / 10 + 48;
    highscore3[4] = thirdhs % 10 + 48;

    scoreboard[6] = score /10 + 48;
    scoreboard[7] = score % 10 + 48;

    display_string(0, "    GAME OVER");
    display_string(1, "     score:");
    display_string(3, "");
    display_string(2, scoreboard);
    display_update();

    score = 0;

    delay(3000);
    highscore();
    delay(3000);
    main();
}

void highscore()
{
    display_string(0, "Highscore    BTN1");

    display_string(1, highscore1);
    display_string(2, highscore2);
    display_string(3, highscore3);
    display_update();
}
