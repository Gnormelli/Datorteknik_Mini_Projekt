#include <pic32mx.h>

int main(void)
{
	int switches;
	TRISD = 0xFF00; // set RD[7:0] to output,
	// RD[11:8] to input
	while (1)
	{
		switches = (PORTD >> 8) & 0xF; // Read and mask switches from
		// RD[11:8]
		PORTD = switches; // display on the LEDs
	}
}