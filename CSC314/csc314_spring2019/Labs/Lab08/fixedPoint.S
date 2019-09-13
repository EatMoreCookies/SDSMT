		.data



message:	.asciz	"This table will create a table for a function in which f(x) = (x^3-x^2-2x) / ((x-2)^4) / 11 + 3. \n\n"
promptLower:	.asciz	"Please enter lower limit of x: "
promptUpper:	.asciz	"Please enter upper limit of x: "
promptNumRows:	.asciz	"Please enter number of rows for the table: "
promptNumBits:	.asciz  "Please enter the number of bits after the decimal points: "
scnfmt:		.asciz	"%s"
scnfmt1:	.asciz	"%d"
lower:		.asciz  "%s"	
upper:		.asciz	"%s"
numRows:	.asciz  "%s"
prtnum:		.asciz	"%d\t"
prtfun:		.asciz  "%d\n"
num1:		.asciz	"1"
num3:		.asciz  "3"
prtfmt:		.asciz  "\t"
prtfmt1:	.asciz	"\n"
num2:		.asciz  "2"
num11:		.asciz	"11"

		.align 2
numBits:	.word	

		.text

	
@@@ -----------------------------------------------------------------
    @@ udiv64 takes a 64 bit unsigned dividend in r1:r0
    @@ and divides it by a 64 bit unsigned divisor in r3:r2
        @@ Returns a 64-bit result in r1:r0 and
    @@ 64-bit modulus in r3:r2
    .global udiv64
udiv64:
    @@ check for divisor of zero
    cmp	r2,#0
    cmpeq   r3,#0
    beq	quitudiv64
    stmfd   sp!,{r4-r6}
    mov	r4,r2	    @ move divisor to r5:r4
    mov	r5,r3
    mov	r2,r0	    @ move dividend to r3:r2
    mov	r3,r1
        mov     r0,#0           @ clear r1:r0 to accumulate result
        mov     r1,#0
        mov     r6,#0           @ set counter to zero
divstrt64:
    @@ shift divisor left until its msb is set, or
    @@   until divisor>=dividend
    @@ WHILE (( divisor > 0) && (divisor < dividend))
    cmp	r5,#0	    @ is msb of divisor set?
    blt	divloop64   @ end loop if msb of divisor is set
    cmp     r5,r3           @ compare high words
    cmpeq   r4,r2	@ if they are equal, compare low words
    bhs	divloop64   @ end loop if divisor >= dividend (unsigned!)
    lsl	r5,r5,#1    @   shift divisor left(high 32 bits)
    lsls    r4,r4,#1	@   shift divisor left(low 32 bits)
    orrcs   r5,r5,#1	@   shift divisor left(carry low to high)
        add r6,r6,#1	@   increment count
        b	divstrt64   @ end WHILE

divloop64:
    lsl	r1,r1,#1    @ shift quotient left (high 32 bits)
    lsls    r0,r0,#1	@ shift quotient left (low 32 bits)
    orrcs   r1,r1,#1	@ shift quotient left (carry from low to high)
    
    cmp     r5,r3           @ compare divisor to dividend
    cmpeq   r4,r2	@ if they are equal, compare low words
    bhi	NoSub	    @ IF (divisor<=dividend) Unsigned!
    subs    r2,r2,r4	@   subtract divisor from dividend
    sbc	r3,r3,r5    
    orr	r0,r0,#1    @   set lsb of quotient
    
NoSub:	lsr r4,r4,#1	@ shift divisor right (low 32 bits)
    lsrs    r5,r5,#1	@ shift divisor right (high 32 bits)
    orrcs   r4,r4,#(1<<31)  @ shift divisor right (carry from high to low)
    subs    r6,#1	@ decrement count
    bge	divloop64   @ continue until count is negative

        ldmfd	sp!,{r4-r6}
quitudiv64: 
        mov     pc,lr




	
@@@ -----------------------------------------------------------------
    @@ sdiv64 takes a 64 bit signed dividend in r1:r0
    @@ and divides it by a 64 bit signed divisor in r3:r2
        @@ Returns a 64-bit result in r1:r0 and
    @@ 64-bit modulus in r3:r2
    .global sdiv64
sdiv64:
    stmfd   sp!,{r4,lr}
    mov	r4,#0	    @ r4 will hold the sign of the result

    @@ Complement dividend if it is negative
    cmp	r1,#0
    bge	NotNeg1
    mvn	r0,r0	    @ complement if negative
    mvn	r1,r1
    adds    r0,r0,#1	@ add one to get two's complement
    adc	r1,r1,#0
    eor	r4,r4,#1    @ keep track of sign

NotNeg1:    
    @@ Complement divisor if it is negative
    cmp	r3,#0
    bge	NotNeg2
    mvn	r2,r2	    @ complement if negative
    mvn	r3,r3
    adds    r2,r2,#1	@ add one to get two's complement
    adc	r3,r3,#0
    eor	r4,r4,#1    @ keep track of sign
    
NotNeg2:
    bl	udiv64	    @ do unsigned division

    @@ Complement result if sign bit is set
    cmp	r4,#0
    beq	NoComplement
    mvn	r0,r0	    @ complement if negative
    mvn	r1,r1
    adds    r0,r0,#1	@ add one to get 2's complement
    adc	r1,r1,#0
    
NoComplement:	
        ldmfd	sp!,{r4,pc} 
	    





		.global Divide

Divide:		@ r0 = num, r1 = dem	S(15,16)
		stmfd sp!, {lr}

		
		mov	r2, r1

		asr	r1, r0, #16	@r1:r0 => num
		lsl	r0, r0, #16

		cmp 	r2, #0 
		movge	r3, #0
		movlt	r3, #-1		@r3:r2
		
		bl	sdiv64		@result = r1:r0	

		ldmfd sp!, {pc}			
	    
			
		.global FX
FX:	    @x comes in r0		S(15, 16)
	    stmfd	sp!, {r4,r9-r11, lr}	    

	    mov		r4, r0			@save x for future use
	    
	    smull	r0, r1, r0, r0		@S(31,32)   
	    lsr		r0, r0, #16
	    orr		r0, r1, lsl #16		@S(15,16)
	    
	    mov		r11, r0			@r11 => x^2

	    smull	r1, r2, r4, r11		@to get x^3 S(31, 32)
	    lsr		r1, r1, #16
	    orr		r1, r2, lsl #16		@to get S(15, 16)

	    mov		r10, r1			@r10 => x^3
    
	    mov		r9, #2
	    lsl		r9, r9, #16


	    smull	r0, r1, r9, r4		@2x
	    lsr		r0, r0, #16
	    orr		r0, r1, lsl #16 

	    sub		r1, r10, r11
	    sub		r11, r1, r0		@x^3-x^2-2x => Numerator    r11 holds numerator

	    
	    sub		r9, r4, r9		@x-2
	    
	    smull	r1, r2, r9, r9		@S(31, 32) x^2
	    lsr		r1, r1, #16
	    orr		r1, r2, lsl #16		@S(15, 16) x^2

	    mov		r9, r1

	    smull	r1, r2, r9, r9		@S(31, 32) x^4
	    lsr		r1, r1, #16
	    orr		r1, r2, lsl #16

	    mov		r9, r1			@S(15, 16) x^4	    r9 => x^4
	    
	    ldr		r0, =num11		@get 11 in S(15, 16)
	    mov		r1, #16
	    bl		strtoSfixed

	    mov		r1, r0
	    mov		r0, r9			
	    bl		Divide			@Divide 
	    mov		r10, r0			@r10 has (x-2)^4/11 => denominator
	    
	    ldr		r0, =num3		@get 3 in S(15,16)
	    mov		r1, #16
	    bl		strtoSfixed
	    
	    add		r1, r10, r0

	    mov		r0, r11

	    bl		Divide
		    

	    ldmfd	sp!, {r4,r9-r11,lr}
	    mov		pc, lr


	    .global main

main:	    stmfd   sp!, {r4-r8,lr}
	    
	    @Summary
	    ldr	    r0, =message
	    bl	    printf

					@get lower limit
	    ldr	    r0, =promptLower
	    bl	    printf
	    ldr	    r0, =scnfmt
	    ldr	    r1, =lower
	    bl	    scanf
	    ldr	    r0, =lower
	    mov	    r1, #16 
	    bl	    strtoSfixed
	    mov	    r4, r0
	    
	    ldr	    r0, =prtfmt1
	    bl	    printf

					@Get upper limit
	    ldr	    r0, =promptUpper
	    bl	    printf
	    ldr	    r0, =scnfmt
	    ldr	    r1, =upper
	    bl	    scanf
	    ldr	    r0, =upper
	    mov	    r1, #16
	    bl	    strtoSfixed
	    mov	    r5, r0
	
	    ldr	    r0, =prtfmt1
	    bl	    printf

	    ldr	    r0, =promptNumBits
	    bl	    printf
	    ldr	    r0, =scnfmt1
	    ldr	    r1, =numBits
	    bl	    scanf
	    ldr	    r7, =numBits
	    ldr	    r7, [r7]

	    ldr	    r0, =prtfmt1
	    bl	    printf


					@Get number of rows
	    ldr	    r0, =promptNumRows
	    bl	    printf
	    ldr	    r0, =scnfmt
	    ldr	    r1,	=numRows
	    bl	    scanf
	    ldr	    r0, =numRows
	    mov	    r1, #16
	    bl	    strtoSfixed
	    mov	    r6, r0

	    ldr	    r0, =prtfmt1
	    bl	    printf

	    

	    ldr	    r0, =num1
	    mov	    r1, #16
	    bl	    strtoSfixed
	    

	    sub	    r1, r6, r0	    @rows = dem
	    sub	    r0, r5, r4	    @num
	    
	    bl	    Divide	    
	    mov	    r6, r0
	
	    ldr	    r0, =prtfmt1
	    bl	    printf




mainLoop:   cmp	    r4, r5
	    bgt	    exitMainLoop
	    

	    mov	    r0, r4
	    mov	    r1, #16
	    mov	    r2, r7
	    bl	    printS
	    
	    ldr	    r0, =prtfmt
	    bl	    printf 

	    mov	    r0, r4
	    bl	    FX

	    mov	    r1, #16
	    mov	    r2, r7
	    bl	    printS

	    ldr	    r0, =prtfmt1
	    bl	    printf
	    
	    add	    r4, r4, r6
	    b	    mainLoop

exitMainLoop:



	    mov	    r0, #0
	    ldmfd   sp!, {r4-r8, lr}
	    mov	    pc, lr
