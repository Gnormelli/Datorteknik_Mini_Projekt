  # analyze.asm
  # This file written 2015 by F Lundevall
  # Copyright abandoned - this file is in the public domain.

	.text
main:
	li	$s0,0x30
loop:
	move	$a0,$s0		# copy from s0 to a0
	
	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window

	addi	$s0,$s0,3	# Bitwise adderar v�rdet i $s0 med 3.
	
	li	$t0,0x5d	# Laddar $t0 med 93 f�r att rad 18 ska vara olika.
				# F�r att ska fungera m�ste 0x5b �ndras till 0x5d.
	bne	$s0,$t0,loop
	nop			# delay slot filler (just in case)

stop:	j	stop		# loop forever here
	nop			# delay slot filler (just in case)

