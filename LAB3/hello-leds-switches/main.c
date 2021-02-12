#include <pic32mx.h>

int main(void)
{
	volatile int *push_buttons = (volatile int *)0x8000abc0;
	volatile int *LED = (volatile int *)0x80007bc0;
	while (1)
	{
		if ((*push_buttons) & 8)
			*LED = 0x3f;
		else
			*LED = 0x0;
	}
}