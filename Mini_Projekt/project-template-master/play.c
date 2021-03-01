#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 10)
#if TMR2PERIOD > 0xffff
#error "Timer period is too big."
#endif

uint8_t screen[128 * 4] = {0};

volatile int *TRIS_E; // declare the pointers volatile and global
volatile int *PORT_E;

int views = 0; // 0 - title view, 1 - Menu view, 2 - Game view, 3 - Game over view, 4 - Write high score view, 5 - High Score view

int btncounter = 0;