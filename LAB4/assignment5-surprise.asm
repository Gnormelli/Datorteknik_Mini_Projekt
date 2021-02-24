addi $a0, $0, 8		# n = 0, 3, 8
addi $v0, $0, 1		# return value, given 1 since the lowest factorial is !0 = 1
addi $v1, $a0, 1 	# k = n + 1
addi $a2, $0, 1		# i = 1, given 1 since the lowest factorial is !0 = 1

loop:
	beq $a2, $v1, done	# if i != k the loop will continue
	add $0, $0, $0		#NOP
	
	mul $v0, $v0, $a2	
	
	addi $a2, $a2, 1
	beq $0, $0, loop
	add $0, $0, $0
done:
	beq $0, $0, done		# "stop"
	add $0, $0, $0
