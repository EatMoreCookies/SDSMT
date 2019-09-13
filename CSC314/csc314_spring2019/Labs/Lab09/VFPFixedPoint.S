		.data


message:	.asciz	"This table will create a table for a function in which f(x) = (x^3-x^2-2x) / ((x-2)^4) / 11 + 3. \n\n"
promptLower:	.asciz	"Please enter lower limit of x: "
promptUpper:	.asciz	"Please enter upper limit of x: "
promptNumRows:	.asciz	"Please enter number of rows for the table: "
promptNumBits:	.asciz  "Please enter the number of bits after the decimal points: "
scnfmt:		.asciz	"%lf"
scnfmt1:	.asciz	"%d"
prtnum:		.asciz	"%d\t"
prtfloat:	.asciz  "%f"
prttab:		.asciz  "\t"
prtNL:		.asciz	"\n"

		.align 2

lower:		.word
		.word	  
upper:		.word
		.word	
numRows:	.word
		.word
	     
	    	

		.text
		.global findStepSize
findStepSize:
		stmfd sp!, {lr}		@d0, d1, d2 have upper lower and numRows 


		vsub.f64	d0, d1, d0
		
		vdiv.f64	d0, d0, d2

		ldmfd		sp!, {lr}
		mov		pc, lr


		.global FX

FX:	    stmfd	    sp!, {lr}	    @x in s0	
	    
	    vmul.f64	    d2, d0, d0	    @x^2
	    vmul.f64	    d3, d0, d2	    @x^3
	    vsub.f64	    d2, d3, d2	    @x^3 - x^2

	    mov		    r0, #2
	    vmov.s32	    s2, r0
	    vcvt.f64.s32    d1, s2
	    vmul.f64	    d3, d1, d0	    @2x
	    vsub.f64	    d2, d2, d3	    @d2 has the num

	    vsub.f64	    d1, d0, d1
	    vmul.f64	    d1, d1, d1	    @(x-2)^2
	    vmul.f64	    d1, d1, d1	    @(x-2)^4

	    mov		    r0, #11
	    vmov.s32	    s0, r0
	    vcvt.f64.s32    d0, s0 
	    vdiv.f64	    d1, d1, d0
	    
	    mov		    r0, #3
	    vmov.s32	    s0, r0
	    vcvt.f64.s32    d0, s0
	    
		
	    vadd.f64	    d1, d1, d0

	    vdiv.f64	    d0, d2, d1

	    ldmfd	    sp!, {lr}
	    mov		    pc, lr


	
		.global myPrintf

myPrintf:	stmfd sp!, {lr}
		tst	sp, #4
		vmovne	r1, r2, d0 
		
		vmoveq	r2, r3, d0
		ldr	r0, =prtfloat
		bl	printf

		ldmfd	sp!, {lr}
		mov	pc, lr		    	    
	    





		.global main

main:
	stmfd	sp!, {r4-r5,lr}
	vstmdb	sp!, {d8-d9}	

	ldr	r0, =message;		@print explanation
	bl	printf

	ldr		r0, =promptLower	@promt lower
	bl		printf
	ldr		r0, =scnfmt
	ldr		r1, =lower
	bl		scanf
	
	ldr		r0, =lower
	vldr.f64	d8, [r0]
	vmov.f64	d0, d8
	
	bl		myPrintf

	ldr		r0, =prtNL
	bl		printf

	ldr		r0, =promptUpper
	bl		printf
	ldr		r0, =scnfmt
	ldr		r1, =upper
	bl		scanf

	ldr		r0, =upper
	vldr.f64	d9, [r0]
	vmov.f64	d0, d9
	bl		myPrintf
	
	ldr		r0, =prtNL
	bl		printf
	
	ldr		r0, =promptNumRows
	bl		printf
	ldr		r0, =scnfmt1
	ldr		r1, =numRows
	bl		scanf

	ldr		r0, =numRows
	ldr		r4, [r0]
	
	sub		r4, r4, #1
	vmov.s32	s0, r4
	
	vcvt.f64.s32	d10, s0
		
	vmov.f64	d0, d10
	bl		myPrintf

	ldr		r0, =prtNL
	bl		printf
	
	vmov.f64	d0, d8
	vmov.f64	d1, d9
	vmov.f64	d2, d10

	bl		findStepSize
	vmov.f64	d9, d0
	bl		myPrintf

	ldr		r0, =prtNL
	bl		printf

	mov		r5, #0
	
loop:	cmp		r5, r4
	bgt		exitLoop

	vmov.f64	d0, d8
	bl		myPrintf
	
	ldr		r0, =prttab
	bl		printf	

	vmov.f64	d0, d8
	bl		FX
	
	bl		myPrintf
	
	ldr		r0, =prtNL
	bl		printf

	vadd.f64	d8, d8, d9

	add		r5, r5, #1
	b		loop

exitLoop:

	mov	r0, #0
	vldmia	sp!, {d8-d9}
	ldmfd	sp!, {r4-r5,lr}
	mov	pc, lr
	
	
	
