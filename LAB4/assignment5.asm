addi $a0, $0, 8		# n = 0, 3, 8
addi $v0, $0, 1		# return value, given 1 since the lowest factorial is !0 = 1
addi $v1, $a0, 1 	# k = n + 1
addi $a2, $0, 1		# i = 1, given 1 since the lowest factorial is !0 = 1

loop:
	beq $a2, $v1, done	# if i != k the loop will continue
	add $0, $0, $0		#NOP
	addi $a2, $a2, 1	# i++
	
	addi $a1, $0, 0		# product = 0
	addi $a3, $0, 1		# j = 1
	
	inner_loop:
	beq $a3, $a2, inner_done	# if i != j, the inner loop will continue
	add $0, $0, $0			#NOP
	addi $a3, $a3, 1		# j++
	add $a1, $a1, $v0		# Product = product + return
	beq $0, $0, inner_loop		# Jumps back to inner_loop
	add $0, $0, $0			#NOP
	
	inner_done:
	addi $v0, $a1, 0		# Give return the value of the product
	beq $0, $0, loop		# Jump back to while_loop
	add $0, $0, $0			#NOP
	

done:
	beq $0, $0, done		# "stop"
	add $0, $0, $0			#NOP
