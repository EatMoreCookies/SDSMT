	.data

prtfmt1:	.asciz "Enter text (ctrl - D to end): "
		.align 2
prtfmt2:	.asciz "%s\n"
		.align 2
prtfmt3:	.asciz "\nThe checksum is %08X\n"
		.align 2
prtfmt4:	.asciz "%08X\n" 
		.align 2

buffer:	.skip  4096
i:	.word  0
sum:	.word  0 

	.text

checksum:    
    
	mov	r2, r0
    
	ldr r0, =sum
	ldr r0, [r0]   @r0 holds sum

	ldr r1, =i
	ldr r1, [r1]	    @r1 holds i 
    

loop:	ldrb	r3, [r2, r1]    @r3 is intermediate register
	
	cmp	r3, #0
        beq	return    

	add r0, r0, r3

	add r1, r1, #1

	b	  loop	


return:	    
	ldr r1, =sum

	str r0, [r1]

	mov pc, lr
	  
	    
    
	

	.global main

main:	stmfd	sp!, {lr}

	ldr	r0, =prtfmt1
	bl	printf
    
	mov	r4, #0
loop1:
	bl	getchar
	
	ldr	r2, =buffer	

	strb	r0, [r2, r4] 
	
		
	cmp     r0, #-1
	beq	exit
    		 	
	
	add	r4, r4, #1
	mov	r1, #4096
	sub	r1, #1
	

	cmp     r4, r1
	bge	exit
	bl	loop1
exit:
	mov	r0, #0
	strb	r0, [r2, r4]	

	ldr	r0, =prtfmt2
	mov	r1, r2  @r1 has buffer in it now

	bl	printf

	ldr	r0, =buffer
	bl	checksum
	mov	r1, r0
	ldr	r0, =prtfmt3
	bl	printf

	

	ldr	r0, =buffer 
	bl	checksum
	mov	r1, r0
	ldr	r0, =prtfmt3
	bl	printf


	mov	r0, #0
	ldmfd	sp!, {lr}
	mov	pc, lr
