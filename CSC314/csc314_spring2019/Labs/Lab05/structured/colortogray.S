		.global color_to_gray

color_to_gray:
		stmfd	sp!, {r4-r11, lr}	
		mov	r4, r0		    @pointer to rbg struct
			
		ldr	r5, [r0, #4]	    @width
		ldr	r6, [r0, #8]	    @hidth


		mov	r0, r5
		mov	r1, r6

		bl	allocate_grayimage
		mov	r1, r0
		
	    
		ldr	r4, [r4, #0]	    @in the rows
		ldr	r1, [r1, #0]	    @in the rows

		mov	r2, #0

loopi:		cmp	r2, r6
		bge	exiti

		ldr	r7, [r4, r2, lsl #2]
		ldr	r8, [r1, r2, lsl #2]

		mov	r3, #0

loopj:		cmp	r3, r5
		bge	exitj

		ldrb     r9, [r7], #1
		mov	r10, #54
		mul	r9, r9, r10

		ldrb	r11, [r7], #1
		mov	r10, #184
		mul	r10, r11, r10

		add	r9, r9, r10

		ldrb 	r11, [r7], #1
		mov	r10, #18
		mul	r11, r11, r10
	    
		add	r9, r9, r11		@gray scale value
		
		lsr	r9, r9, #8

		
		strb	r9, [r8, r3] 

		add	r3, r3, #1
		b	loopj
exitj:	

		add	r2, r2, #1
		b	loopi
exiti:	    
		
		ldmfd	sp!, {r4-r11, lr}
		mov	pc, lr




 
		 
