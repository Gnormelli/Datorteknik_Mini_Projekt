#include <pic32mx.h>

.macro movi reg, val
	lui \reg, %hi(\val)
	ori \reg, \reg, %lo(\val)
.endm



.align 4
.global _isr_test
_isr_test:
	lw $k0, _isr_test
	jr $k0
	nop
	eret
	nop

.global _enable_interrupt
_enable_interrupt:
	mfc0 $t0, $12, 0
	ori $t0, $t0, 1
	mtc0 $t0, $12, 0
	jr $ra
	nop


## Arg0: interrupt number, Arg1: IPCx, x = interrupt number / 4, Arg2: Priority, Arg3: Subpriority
.global _enable_int_number
_enable_int_number:
	## Test if interrupt is >= 32
	srl $t0, $a0, 5
	andi $t1, $a0, 0x1F
	beq $t0, $0, Lintbank_0
	nop

	## Mask out the lower 5 bits and place in $t1
	movi $t2, IEC(1)
	movi $t5, IFSCLR(1)
	j Lintsetbank
	nop
Lintbank_0:
	movi $t5, IFSCLR(0)
	movi $t2, IEC(0)

Lintsetbank:
	## Set bit in Interrupt Enable (IECx) for provided interrupt
	## Bit is 1 << (int & 0x1F)
	addi $t3, $0, 1
	sllv $t3, $t3, $t1
	lw $t4, ($t2)
	or $t4, $t4, $t3
	sw $t4, ($t2)

	## Clear interrupt bit in case it's set
	lw $t4, ($t5)
	or $t4, $t4, $t3
	sw $t4, ($t5)

	## Write interrupt priority
	andi $a0, $a0, 0x3
	addi $t0, $0, 8
	multu $a0, $t0
	mflo $t0
	sll $a2, $a2, 2
	or $t1, $a2, $a3
	sllv $t1, $t1, $t0
	addi $t2, $0, 0x1F
	sllv $t2, $t2, $t0
	nor $t2, $t2, $t2
	lw $t0, ($a1)
	and $t0, $t0, $t2
	or $t0, $t1, $t0
	sw $t0, ($a1)

	jr $ra
	nop

