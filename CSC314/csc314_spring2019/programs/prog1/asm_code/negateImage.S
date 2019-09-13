

		.data
msg:		.asciz "negateImage has not been implemented\n"

	
		.text
		
		.global negate_array_color

negate_array_color:			@Given an pointer to an rgb image in r0
		stmfd	sp!, {r4-r8,lr}


		mov	r4, #0			@i
		mov	r8, #255		@val to subtract
		

negateLoopi:	cmp	r4, r1			@compare r4 with rows    	
		bge	exitNegateLoopi
		
		ldr	r6, [r0, r4, lsl #2]	@to get the right # of rows
		mov	r5, #0			@j		

negateLoopj:	cmp	r5, r2			@cmp r5 with cols
		bge	exitNegateLoopj


		ldrb	r7, [r6]		@r
		sub	r7, r8, r7		@subtract 255 from r
		strb	r7, [r6], #1		@store it back 

		ldrb	r7, [r6]		@g
		sub	r7, r8, r7
		strb	r7, [r6], #1 

		ldrb	r7, [r6]		@b
		sub	r7, r8, r7
		strb	r7, [r6], #1

		add	r5, r5, #1		@increment j
		b	negateLoopj
exitNegateLoopj:
		
		add	r4, r4, #1		@increment i
		b	negateLoopi
exitNegateLoopi:

		ldmfd	sp!, {r4-r8,lr}
		mov	pc, lr







	.global negateImage

negateImage:	    @r0 has the pointer to the netImage
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
	
	ldr	r1, [r4, #12]	@get rows

	ldr	r2, [r4, #16]	@get cols

	
	ldr	r0, [r4, #20]	@this gets us the 2D pointer to rgb image
	mov	r5, r0

	
	bl	negate_array_color
	b	return	


default:		
	ldr	r0,=msg
	bl	printf
	

return:
	mov	r0, r5
	ldmfd	sp!,{r4-r6, lr}
	mov	pc,lr
