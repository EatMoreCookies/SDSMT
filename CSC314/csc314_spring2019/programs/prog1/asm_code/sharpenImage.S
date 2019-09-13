		.data
msg:		.asciz "negateImage has not been implemented\n"

	
		.text	


matrixOps:
	stmfd	sp!, {r4-r9, lr}    @r0 has a pointer to a rgb image
				    @r1 is the number of bytes that we are in
				    @r2 is the number of rows

	ldr    r3, [r0, r2, lsl #2] @get to the right row
	ldrb   r4, [r3, r1]	    @number of bytes we are into the array

	mov	r5, #5 

	mul	r6, r5, r4	    @r6=5*Pi,j
	
	
	sub	r7, r1, #3
	ldrb	r4,[r3, r7]	    @Pi,j-1

	
	add	r7, r1, #3	    
	ldrb	r5, [r3, r7]	    @Pi,j+1

	
	add	r7, r2, #1
	ldr	r8, [r0, r7, lsl #2]
	ldrb	r8, [r8, r1]	    @Pi+1, j

	
	sub	r7, r2, #1
	ldr	r9, [r0, r7, lsl #2]
	ldrb	r9, [r9, r1]	    @Pi-1, j 


	add	r9, r9, r8
	add	r9, r9, r5
	add	r9, r9, r4

	sub	r0, r6, r9



	ldmfd	sp!, {r4-r9, pc}
	


sharpen_array_color:
	stmfd	sp!, {r4-r12,lr}

	
	mov	r4, r0			@save our vals
	mov	r5, r1
	mov	r6, r2

	mov	r0, r1
	mov	r1, r2

	bl	allocate_asm_struct	@make new arry
	mov	r9, r0			@pointer to our new struct	

	sub	r5, r5, #1	
	sub	r6, r6, #1
  

	mov	r7, #1
loopi:	cmp	r7, r5
	beq	exitLoopi

	ldr	r11, [r9, r7, lsl #2]	@pointer to our new array

	mov	r8, #1

loopj:  cmp	r8, r6
	bge	exitLoopj
	
	mov	r12, r8
    
	mov	r2, #3
	mul     r12, r12, r2
	
	mov	r1, r12 		@how many bytes we are in	
	mov	r0, r4
	mov	r2, r7
	bl	matrixOps
	
	
	strb	r0, [r11], #1		@red val

	add	r1, r12, #1
	mov	r0, r4
	mov	r2, r7
	bl	matrixOps
    
	
	strb	r0, [r11], #1 
	
	add	r1, r12, #1
	mov	r0, r4
	mov	r2, r7
	bl	matrixOps

	
	strb	r0, [r11], #1

	
	add	r8, r8, #1
	b	loopj

exitLoopj:
    
	add	r7, r7, #1
	b	loopi
exitLoopi:

	mov	r0, r9
	mov	r1, r5
	mov	r2, r6
	bl	fixSharpenBorders	


	ldmfd	sp!, {r4-r12,pc}

	.global sharpenImage

sharpenImage:	    @r0 has the pointer to the netImage
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
	mov	r5, r1

	ldr	r2, [r4, #16]	@get cols

	
	ldr	r0, [r4, #20]	@this gets us the 2D pointer to rgb image
	mov	r6, r0

	
	bl	sharpen_array_color

	str	r0, [r4, #20]	@store new array

	mov	r0, r6
	mov	r1, r5
	bl	free_array
	
	
	b	return	


default:		
	ldr	r0,=msg
	bl	printf
	

return:
	ldmfd	sp!,{r4-r6, lr}
	mov	pc,lr
