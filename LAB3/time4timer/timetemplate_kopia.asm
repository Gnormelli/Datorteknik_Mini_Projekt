  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  
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
  	
  	PUSH ($ra)	# inga jump and links därför behövs det inte push/pop. Eftersom det inte sparas några register 
  	
  	move $t3, $a0		# Copy value of $a0 to $t3
  	
  	li $t4, 0		# i=0
  	
  	delayWhileLoop:
  		
  		ble $t3, 0, delayStopLoop
  		nop
  		sub $t3, $t3, 1
		
		li $t4, 0  	
  		delayForLoop:
  		
  			bge $t4,60000, delayWhileLoop 
  			nop
  			addi $t4, $t4, 1
  			j delayForLoop
  			nop
  		
  		j delayWhileLoop
  		nop
  	
  	delayStopLoop:
  	
  		POP ($ra)
  		jr $ra
  		nop	
  	
  time2string:
  
 	PUSH	($s0)		
 	PUSH	($s1)	  	
  	PUSH	($ra)
  	
  	move	$s0, $a0	# Possibly erase
  	move 	$s1, $a1
  	
  	#First number
  	
  	andi	$t0, $s1, 0xf000		#Extract top nibble
  	srl	$a0, $t0, 12			#>> 12 steps to the right for hexasc, since it handles the 4 Least Significant Bits
  	jal	hexasc				#1111 0000 0000 0000 --> 0000 0000 0000 1111 *not correct bit representation, just for visual representation
  						# 5
  	nop
  	sb	$v0, 0($s0)
  	
  	#Second Number
  	
  	andi	$t0, $s1, 0x0f00		#Extract second top nibble
  	srl 	$a0, $t0, 8			#>> 8 steps to the right for hexasc, since it handles the 4 Least Significant Bits
  	jal	hexasc				# 0000 1111 0000 0000 --> 0000 0000 0000 1111
  						#	9
  	nop
  	sb	$v0, 1($s0)
  	
  	# :
  
  	li	$t0, 0x3a
  	sb	$t0, 2($s0)
  	
  	#Third Number
  	
  	andi	$t0, $s1, 0x00f0		#Extract second bottom nibble
  	srl 	$a0, $t0, 4			#>> 4 steps to the right for hexasc, since it handles the 4 Least Significant Bits
  	jal	hexasc				# 0000 0000 1111 0000 --> 0000 0000 0000 1111
  						#	     5
  	nop
  	sb	$v0, 3($s0)
  	
  	#Fourth Number
  	
  	andi	$t0, $s1, 0x000f		#Extract bottom nibble
  	move	$a0, $t0
  	jal	hexasc				# 0000 0000 0000 1111
  						#		  7	
  	nop
  	sb	$v0, 4($s0)
  	
  	# X
  	andi	$t0,$s1,0xff
  	beq	$t0,0,X
  	nop  
  	
  	# NULL byte
  	
  	li	$t0, 0x00
  	sb	$t0, 5($s0)
  	
 stop:
 
  	POP	($ra)
  	POP	($s1)
  	POP	($s0)
  	
  	jr	$ra
  	nop
  	
X: 
 	li $t1, 0x58
  	sb $t1, 5($s0)
  	
  	li $t1, 0x00
  	sb $t1, 6($s0)

  	j stop
	nop
