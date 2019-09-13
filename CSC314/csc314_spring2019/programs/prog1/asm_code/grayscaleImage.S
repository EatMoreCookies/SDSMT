
	.data
msg:	.asciz "grayscaleImage has not been implemented\n"
	
	.text




	.global color_to_gray


color_to_gray: @@ (**image, rows, cols, **grey )
	stmfd	sp!, {r4-r12,lr}    
	sub	sp, sp, #2    	

	mov	r6, r0			    @rgb image pointer
	mov	r7, r3			    @gray image pointer

	mov	r9, r1			    @save cols and rows
	mov	r10, r2	
	

	mov	r1, #255		    @store max opposite vals in new minmax struct
	strb	r1, [sp]
	mov	r1, #0
	strb	r1, [sp, #1]

	mov	r5, #0
	

loopi:	cmp	r5, r9
	bge	exitLoopi

	ldr	r8, [r6, r5, lsl #2]	    @get to rows
	ldr	r11, [r7, r5, lsl #2]	    @get to rows for the grey image
 
	mov	r4, #0

loopj:	cmp	r4, r10
	beq	exitLoopj

	ldrb	r2, [r8], #1		    @red
	mov	r3, #54
	mul	r2, r2, r3
	
	ldrb	r3, [r8], #1		    @green 
	mov	r1, #184
	mul	r3, r1, r3
		
	ldrb	r1, [r8], #1		    @blue
	mov	r12, #18
	mul	r1, r12, r1

	add	r2, r3, r2
	add	r2, r2, r1

	lsr	r0, r2, #8		    @Divde by 256 

	bl	crop
	
	ldr	r1, [sp]
	ldr	r2, [sp, #1]

	cmp	r0, r1
	strltb	r0, [sp]
	b	continue

	cmp	    r0, r2
	ble	    continue
	strb    r0, [sp, #1]
continue:
	    		
	strb	r0, [r11, r4]		    @store the cropped val

	add	r4, r4, #1

	b	loopj
exitLoopj:
	
	add	r5, r5, #1
	b	loopi

exitLoopi:			
	
	mov	r0, #2
	bl	malloc
	
	ldrb	r1, [sp]
	ldrb	r2, [sp, #1]

	strb	r1, [r0]
	strb	r2, [r0, #1]	

	add	sp, sp, #2
	ldmfd	sp!, {r4-r12, lr } 
	mov	pc, lr
    




	.global grayscaleImage
	
grayscaleImage:

	stmfd	sp!,{r4-r8,lr}
	
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
	sub	r0, r0, #1
	mov	r7, r0
	
	strb	r7, [r4]	

	ldr	r0, [r4, #12]	@get rows

	ldr	r1, [r4, #16]	@get cols

	mov	r5, r0
	mov	r6, r1
	
	bl	allocate_pixel_array		@when we come back r0 has pointer to newly created greyimage

	str	r0, [r4, #24]			@store our new grey image
    
	mov	r3, r0				@this is our pointer to the new gray structure
	
	ldr	r0, [r4, #20]			@this gets us the 2D pointer to rgb image
		
	mov	r1, r5		
	mov	r2, r6				@rows and cols

	
	bl	color_to_gray
	b	return	
		

default:		
	ldr	r0,=msg
	bl	printf
	


return:
	
	ldmfd	sp!,{r4-r8,lr}
	mov	pc,lr
