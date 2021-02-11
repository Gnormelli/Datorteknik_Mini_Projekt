// #include <pic32mx.h> 
void delay(int ms) /* Wait a number of milliseconds, specified by the parameter value. */
{
    int i;
    while (ms > 0)
    {
        ms = ms - 1;
        /* Executing the following for loop should take 1 ms */
        for (i = 0; i < 4711; i = i + 1) /* The constant 4711 must be easy to change! */
        {
            /* Do nothing. Hej gurra*/
        }
    }
}