
	.data
msg:	.asciz "brightenImage has not been implemented\n"
	
		.text
		
		.global brighten_array_color

brighten_array_color:				@Given an pointer to an rgb image in r0 
		stmfd	sp!, {r4-r11,lr}



		mov	r4, #0			@i			
		
		mov	r9, r1			@get rows and cols into permanent registers
		mov	r10, r2
		mov	r8, r3			@val to add
		mov	r11, r0			
		

BrightenLoopi:	cmp	r4, r9			@compare r4 with rows    	
		bge	exitBrightenLoopi
		
		ldr	r6, [r11, r4, lsl #2]	@to get the right # of rows
		mov	r5, #0

BrightenLoopj:	cmp	r5, r10			@cmp r5 with cols
		bge	exitBrightenLoopj


		ldrb	r7, [r6]		@r

		add	r0, r8, r7		@add 255 from r
		bl 	crop			@Make sure the val is between 255 and 0
		strb	r0, [r6], #1		@store it back 

		ldrb	r7, [r6]		@g
		add	r0, r8, r7
		bl	crop			@Make sure its between 255 and 0
		strb	r0, [r6], #1 

		ldrb	r7, [r6]		@b
		add	r0, r8, r7
		bl	crop			@Make sure its between 255 and 0
		strb	r7, [r6], #1

		add	r5, r5, #1		@increment j
		b	BrightenLoopj
exitBrightenLoopj:
		
		add	r4, r4, #1		@increment i
		b	BrightenLoopi
exitBrightenLoopi:

		ldmfd	sp!, {r4-r11,lr}
		mov	pc, lr




	.global brightenImage

brightenImage:	    @r0 has the pointer to the netImage
	stmfd	sp!,{r4-r6,lr}
	
	mov	r4, r0
	mov	r0, r1
//	bl	atoi

	mov	r3, r0	

	ldrb	r0, [r4]
	
		         	@we will need this val later
	
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

	
	bl	brighten_array_color
	b	return	

default:		
	ldr	r0,=msg
	bl	printf
	

return:
	mov	r5, r0
	ldmfd	sp!,{r4-r6, lr}
	mov	pc,lr
    
