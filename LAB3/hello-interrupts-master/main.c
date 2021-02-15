#include <pic32mx.h>

extern void *__use_isr_install;
extern void _make_syscall();
extern void _enable_int_number(int int_no, volatile void *IPCx, int priority, int sub_priority);
extern void _enable_interrupt();

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

int main(void) {
	int i;
	
	delay(10000000);
	ODCE = 0;
	TRISECLR = 0xFF;

	_enable_int_number(7, (void *) IPC(1), 1, 0);
	_enable_interrupt();


	for (i = 0;; i++) {
		PORTE = i & 0xFF;
		delay(1000000);
	}

	return 0;
}
