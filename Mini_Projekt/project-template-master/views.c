#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void menu(){
    display_string(0, "    ");
    display_string(1,"     PLAY");
    display_string(2,"     HIGHSCORE");
    display_string(3, "    ");
    display_update();
}