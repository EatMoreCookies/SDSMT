		.data



prtfmt:		.asciz	"Enter the number of pennies, nickels, dimes, and quarters for a week %d: "
prtfmt1:	.asciz  "\nOver four weeks you have collected %d pennies, %d nickels, %d dimes and %d quarters.\n"
prtfmt2:	.asciz	"\n\nThis comes to $%d.%d\n"	
prtfmt3:	.asciz	"Your weekly average is $%d.%d\n"
prtfmt4:	.asciz	"Your estimated yearly savings is $%d.%.2d\n"

prtfmt101:	.asciz	"%d\n"
scnfmt:		.asciz  "%d%d%d%d"

		.align 2

pen:		.word	0
nic:		.word	0
dime:		.word	0
quart:		.word	0


		.text

		.global divide10
divide10:	stmfd	    sp!, {lr}
		mov	    r2, r0

		ldr	    r3,=0x28F5C2A
		smull	    r0, r1, r3, r2
		mov	    r3, r2, asr #31
		rsb	    r0, r3, r1

		mov	    r1, #100
		mul	    r1, r1, r0
		sub	    r1, r2, r1

		ldmfd	    sp!, {lr}
		mov	    pc, lr
		
		.global divide4

divide4:	stmfd	    sp!, {lr}
		mov	    r2, r0

		ldr	    r3,=0x40000001
		smull	    r0, r1, r3, r2
		mov	    r3, r2, asr #31
		rsb	    r0, r3, r1

		mov	    r1, #4
		mul	    r1, r1, r0
		sub	    r1, r2, r1
		ldmfd	    sp!, {lr}
		mov	    pc, lr
		
		

		.global main




main:	    	stmfd	    sp!, {r4-r9, lr}  
		sub	    sp, sp, #4		@Quarters
		mov	    r4, #1
		
		@Sums
		mov	    r5, #0
		mov	    r6, #0
		mov	    r7, #0
		mov	    r8, #0

loop:		cmp	    r4, #5
		bge	    exitloop		

		ldr	    r0, =prtfmt
		mov	    r1, r4
		
		bl	    printf
		
		ldr	    r0, =scnfmt
		ldr	    r1, =pen
		ldr	    r2, =nic
		ldr	    r3, =dime
		
		ldr	    r9, =quart
		str	    r9, [sp]

		bl	    scanf
		
		ldr	    r1, =pen
		ldr	    r1, [r1]
		add	    r5, r5, r1

		ldr	    r2, =nic
		ldr	    r2, [r2]
		add	    r6, r6, r2
	    		
		ldr	    r3, =dime
		ldr	    r3, [r3]
		add	    r7, r7, r3
	
		ldr	    r9, =quart
		ldr	    r9, [r9]
		add	    r8, r8, r9
		str	    r8, [sp]
		
		add	    r4, r4, #1
		b	    loop
exitloop:	
		
		ldr	    r0, =prtfmt1
		mov	    r1, r5
		mov	    r2, r6
		mov	    r3, r7
		bl	    printf

		mov	    r0, #0
		add	    r0, r0, r5
	    
		mov	    r1, #5
		mul	    r6, r6, r1
		add	    r0, r0, r6
		
		mov	    r1, #10
		mul	    r7, r7, r1
		add	    r0, r0, r7
		
		mov	    r1, #25
		mul	    r8, r8, r1
		add	    r0, r0, r8
		mov	    r4, r0	    @keep the total
		bl	    divide10
		
		mov	    r2, r0
		ldr	    r0, =prtfmt2
		mov	    r3, r1
		mov	    r1, r2
		mov	    r2, r3
		bl	    printf

		mov	    r0, r4
		bl	    divide4
		mov	    r5, r0	   @r5 holds weekly average	
		bl	    divide10
		mov	    r2, r0
		mov	    r3, r1
		ldr	    r0, =prtfmt3
		mov	    r1, r2
		mov	    r2, r3
		bl	    printf	
	    
		mov	    r0, r5 
		add	    r5, r5, r5, lsl #5	@ x*32 + x = 33x
		add	    r5, r5, r0, lsl#4	@ 33x+16x = 49x
		add	    r5, r5, r0, lsl #1	@2x +49x = 51x
		add	    r0, r5, r0		@x + 51x = 52x --> which is a year
		
		bl	    divide10
		mov	    r2, r0
		mov	    r3, r1
		ldr	    r0, =prtfmt4
		mov	    r1, r2
		mov	    r2, r3
		
		bl	    printf
		
				

		add	    sp, sp, #4
		mov	    r0, #0
		ldmfd	    sp!, {r4-r9, lr}
	    	mov	    pc, lr  
	



