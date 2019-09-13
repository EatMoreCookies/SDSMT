
		.data
msg:		.asciz "negateImage has not been implemented\n"

		.align 2

	
		.text
		.global contrast_image

contrast_image:
		stmfd	sp!, {r4-r10,lr}
		vstmdb	sp!, {d8}

		mov	r4, r0		    @store vals
		mov	r5, r1
		mov	r6, r2
    
	    	ldrb	r2, [r3]	    @get min and max vals
		ldrb	r7, [r3, #1]

		cmp	 r7, r2		    @compare min and max
		moveq	 r0, #1
		vmoveq.f32 s0, r0
		beq	 skipDivide
		

		sub		r1, r2, r7	    @max - min
		vmov.f32	s1, r1
		
		mov		r3, #256
		sub		r3, r3, #1
		vmov.f32	s0, r3

		vdiv.f32	s16, s0, s1

		vmov.f32	s17, r7		    @min val
skipDivide:
		mov		r8, #0

		
loopi:		cmp	r8, r5
		bge	exitLoopi

		ldr	r10, [r4, r8, lsl #2]	    @get right column

		mov	r9, #0

loopj:	    	cmp	r9, r6
		bge	exitLoopj

		ldrb	    r0, [r10, r9]	    @get our grey val

exit:		vmov.f32    s0, r0

		vsub.f32    s0, s0, s17		    @subtract min

		vmul.f32    s0, s0, s16		    @multiply with scale
		
		mov	    r0, #1
		vmov.f32    s1, r0
		mov	    r0, #2
		vmov.f32    s2, r0

		vdiv.f32    s1, s1, s2
	    
		vadd.f32    s0, s0, s2		

		vmov.u32    r0, s0

		bl	    crop

		strb	    r0, [r10, r9]

		add	    r9, r9, #1
		b	    loopj

exitLoopj:

		add	    r8, r8, #1
		b	    loopi
exitLoopi:
	
		mov	    r8, #0

	
		vldmia	sp!, {d8}
		ldmfd	sp!, {r4-r10,lr} 
		mov	pc, lr	
		    		
	


		.global	contrastImage

contrastImage: 
	    
	stmfd	sp!,{r4-r6,lr}
	
	mov	r4, r0
	ldrb	r0, [r4]
	
	cmp	r0, #50		@case 2
	beq	return
	cmp	r0, #52		@case 4
	beq	return

	cmp	r0, #51		@case 3
	beq	colorImage
	cmp	r0, #54		@case 6
	beq	colorImage

	b	default
	
colorImage:
	    

	mov	r0, r4

	bl	grayscaleImage	    @r0 will contain a pointer to a minMax struct 
	mov	r3, r0	

	ldr	r0, [r4,#24]	    @pointer to the gray image
	ldr	r1, [r4,#12]	    @rows
	ldr	r2, [r4,#16]	    @cols

	bl	contrast_image
		
	b	return	


default:		
	ldr	r0,=msg
	bl	printf
	

return:
	ldmfd	sp!,{r4-r6, lr}
	mov	pc,lr


				
		

