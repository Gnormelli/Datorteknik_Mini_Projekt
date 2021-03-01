<<<<<<< HEAD
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void menu(void){
    display_string(0, "    ");
    display_string(1,"     PLAY");
    display_string(2,"     HIGHSCORE");
    display_string(3, "    ");
    display_update();
    int btn = getbtns();

    display_string(0, "  Highscore ");
    display_string(1, "    ");
    display_string(2, "     ");
    display_string(3, "    ");
    display_update();
    display_update();
    if (btn){
        menu();
    }
}
>>>>>>> master
