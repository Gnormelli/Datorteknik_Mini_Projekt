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
  # Kommer att ge hexadecimala värden.
  hexasc:
  	andi $t0,$a0,0xf		# Tar bitwise AND $a0 och zeroext 0xf till hela 32 bitar. 
  
 	ble $t0,9,siffra		# Branch if less or equal 0-9 ger en siffra 
 	nop				# no operation dvs end		
 	
 	bokstav:
 		addi $v0,$t0,0x37	
 		jr $ra	
 	
 	siffra:
  		addi $v0,$t0,0x30	 
  		jr $ra			
				

	
