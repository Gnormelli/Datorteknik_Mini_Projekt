#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


void menu()
{
    // Improve with a delay
    
    /*
    int btn = 0;
    int btn = getbtns();

    
    if (btn & 0x4) 
    {
        display_string(0, "    ");
        display_string(1, "PLAY-BTN2");
        display_string(2, "HIGHSCORE-BTN3");
        display_string(3, "    ");
        display_update();
    }
    if (btn & 0x2)
    */
    display_string(0, "    ");
    display_string(1, "  PLAY - BTN2");
    display_string(2, "  HIGHSCORE - BTN3");
    display_string(3, "    ");
    display_update();

    /* int btn = getbtns();

    if (btn & 0x4){
        highscore();
    }
    if (btn & 0x1)
    {
        play();
    }
    */

}
void write_highscore(){
    display_string(0, "  Enter your initials ");
    display_string(1, "");
    display_string(2, "");
    display_string(3, "");
    display_update();
    display_update();
}

void highscore()
{
    // int btn = getbtns();

    display_string(0, "  Highscore ");
    display_string(1, "1:     ");
    display_string(2, "2:     ");
    display_string(3, "3:   ");
    display_update();
    display_update();
    /* if (btn & 0x1){
        menu();
    }
    */ // To be added back if Views does not work.
    
}
