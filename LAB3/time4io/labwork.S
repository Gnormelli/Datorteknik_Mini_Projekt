  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
  .global hexasc
  .global delay
  .global time2string
  
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  # 
  
  	.text	
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

  
  # old delay:
  #	jr $ra
  #	nop
  
  delay:
  	
  	PUSH $ra
  	
  	move $t3, $a0		# Copy value of $a0 to $t3
  	
  	li $t4, 0		# i=0
  	
  	delayWhileLoop:
  		
  		ble $t3, 0, delayStopLoop
  		nop
  		sub $t3, $t3, 1
  		
  		li $t4, 0
  	
  		delayForLoop:
  		
  			bge $t4, 4711, delayWhileLoop 
  			nop
  			addi $t4, $t4, 1
  			j delayForLoop
  			nop
  		
  		j delayWhileLoop
  		nop
  	
  	delayStopLoop:
  	
  		POP $ra
  		jr $ra
  		nop	
  	
  time2string:
  
 	PUSH	$s0	  	
  	PUSH	$ra
  	
  	move	$s0, $a0
  	
  	PUSH	$a0
  	
  	# First number
  	
  	andi	$t0, $a1, 0xf000		#Extract top nibble
  	srl	$a0, $t0, 12			#>> 12 steps to the right for hexasc, since it handles the 4 Least Significant Bits
  	jal	hexasc				#1111 0000 0000 0000 --> 0000 0000 0000 1111 *not correct bit representation, just for visual representation
  						# 5
  	nop
  	sb	$v0, 0($s0)
  	
  	#Second Number
  	
  	andi	$t0, $a1, 0x0f00		#Extract second top nibble
  	srl 	$a0, $t0, 8			#>> 8 steps to the right for hexasc, since it handles the 4 Least Significant Bits
  	jal	hexasc				# 0000 1111 0000 0000 --> 0000 0000 0000 1111
  						#	9
  	nop
  	sb	$v0, 1($s0)
  	
  	# :
  
  	li	$t0, 0x3a
  	sb	$t0, 2($s0)
  	
  	# Third Number
  	
  	andi	$t0, $a1, 0x00f0		#Extract second bottom nibble
  	srl 	$a0, $t0, 4			#>> 4 steps to the right for hexasc, since it handles the 4 Least Significant Bits
  	jal	hexasc				# 0000 0000 1111 0000 --> 0000 0000 0000 1111
  						#	     5
  	nop
  	sb	$v0, 3($s0)
  	
  	#Fourth Number
  	
  	andi	$t0, $a1, 0x000f		#Extract bottom nibble
  	move	$a0, $t0
  	jal	hexasc				# 0000 0000 0000 1111
  						#		  7	
  	nop
  	sb	$v0, 4($s0)
  	
  	# NULL byte
  	
  	li	$t0, 0x00
  	sb	$t0, 5($s0)
  	
  	POP	$a0
  	POP	$ra
  	POP	$s0
  	
  	jr	$ra
  	nop
  
