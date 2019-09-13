		
		.global color_to_gray

color_to_gray:
		stmfd	sp!, {r4-r12, lr}	
		mov	r4, r0		    @pointer to rbg struct
			
		ldr	r5, [r0, #4]	    @width
		ldr	r6, [r0, #8]	    @hidth


		mov	r0, r5
		mov	r1, r6

		bl	allocate_grayimage
		mov	r1, r0
		mov	r12, r0
		
	    
		ldr	r4, [r4, #0]	    @in the rows
		ldr	r1, [r1, #0]	    @in the rows

		
		mov		r0, #54	    @Store the constants to mul
		vmov.u16    	d3[0], r0

		mov		r0, #184
		vmov.u16	d3[1], r0

		mov		r0, #18
		vmov.u16	d3[2], r0



		mov	    r2, #0

loopi:		cmp	    r2, r6
		bge	    exiti

		ldr	    r7, [r4, r2, lsl #2]
		ldr	    r8, [r1, r2, lsl #2]

		mov	    r3, #0

loopj:		cmp		r3, r5
		bge		exitj

		vld3.8		{d0, d1, d2}, [r7]!
		
		vmovl.u8	q2, d0
		
		vmovl.u8	q3, d1
		
		vmovl.u8	q4, d2
		
		vmul.u16	q2, q2, d3[0]
		vmul.u16	q3, q3, d3[1]
		vmul.u16	q4, q4, d3[2]

		vadd.u16	q2, q2, q3
		vadd.u16	q2, q2, q4
	    
		vshrn.u16 	d0, q2, #8


		vst1.8		d0, [r8]!

			    
		add	    	r3, r3, #8
		b		loopj
exitj:	

		add	    r2, r2, #1
		b	    loopi
exiti:	    
		mov	    r0, r12
		ldmfd	    sp!, {r4-r12, lr}
		mov	    pc, lr




 
		 
