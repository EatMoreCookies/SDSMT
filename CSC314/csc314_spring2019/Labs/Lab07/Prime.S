	    .data
	    
	    .align 2
n:	    .word  
prtfmt1:    .asciz "Please enter a natual number: "
scnfmt1:    .asciz "%d"
prtfmt2:    .asciz "Prime Number: %d\n"
prtfmt3:    .asciz "Total Primes: %d\n"
	    
	    .text

	    .global isPrime

isPrime:    stmfd   sp!, {r7-r8, lr}
	    
	    mov	    r7, r0	@r7 now has x
	    mov	    r8, #2	    	            
	
loopPrime:  cmp	    r8, r7
	    bge	    exitPrime

	    mov	    r0, r7
	    mov	    r1, r8
	    bl	    divide
	    
	    cmp	    r1, #0
	    bne	    continuePrime
	    mov	    r0, #0
	    b	    returnPrime

continuePrime:	    add	r8, r8, #1
		    b	loopPrime
	    

exitPrime:	    mov	    r0, #1

returnPrime:	    ldmfd   sp!, {r7-r8, lr}
		    mov	    pc, lr	

	
	    .global divide

@
@ From ARM Assembly Text Book. Larry Pyeatt
@
divide:		stmfd	    sp!, {lr} @r0 is the dividend and r1 is the divisor
		cmp	    r1, #0
		beq	    exitDivide
		
		mov	    r2, r1
		mov	    r1, r0
		
		mov	    r0, #0
		mov	    r3, #1
		
divideLoop:	cmp	    r2, #0
		blt	    divLoop2

		cmp	    r2, r1
		lslls	    r2, r2, #1
		lslls	    r3, r3, #1
		bls	    divideLoop

divLoop2:	cmp	    r1, r2
		subhs	    r1, r1, r2
		addhs	    r0, r0, r3
		lsr	    r2, r2, #1
		lsrs	    r3, r3, #1
		bcc	    divLoop2


		
exitDivide:	ldmfd	    sp!, {lr}    
		mov	    pc, lr	

	    
	.global main

main:	stmfd	sp!, {r4-r6, lr}
	ldr	r0, =prtfmt1
	bl	printf

	ldr	r0, =scnfmt1
	ldr	r1, =n
	bl	scanf
	ldr	r5, =n
	ldr	r5, [r5]		@r5 has n in it
	
	mov	r4, #2
	mov	r6, #0      

loop:	cmp	r4, r5
	beq	exit	
	
	mov	r0, r4
	bl	isPrime
	
	cmp     r0, #1
	bne	skipPrint
	add	r6, r6, #1
	ldr	r0, =prtfmt2
	mov	r1, r4
	bl	printf	


skipPrint:	add r4, r4, #1
	b	loop		
	
exit:	
	ldr	r0, =prtfmt3
	mov	r1, r6
	bl	printf

	ldmfd   sp!, {r4- r6, lr}
	mov     r0, #0
	mov	pc, lr
	


