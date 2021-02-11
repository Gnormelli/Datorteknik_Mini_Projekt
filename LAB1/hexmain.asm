  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,15	# change this to test different values 

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  # Kommer att ge hexadecimala v�rden.
  hexasc:
	andi	$t0,$a0,0xf		# taking only the last four bits
  
 	ble	$t0,9,number
 	nop	
 		
 	ble	$t0,15,letters
 	nop
 	
 number:
  	addi 	$v0,$t0,0x30	# register $v0 has the seven least significant bits, an ASCII code 
  	jr 	$ra		# 0x30 converts numbers to ASCII
  	nop
  		
 letters:
 	addi 	$v0,$t0,0x37	# register $v0 has the seven least significant bits, 0x37 is for 
 	jr 	$ra		# the letters 
 	nop	
				

	
