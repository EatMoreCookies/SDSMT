	.data
msg:	.asciz "smoothImage has not been implemented\n"
    
	.text
	
matrixOps:	    
    
    stmfd   sp!, {r4-r10, lr}	@r0 has pointer to our rows
				@r1 has the number of bytes that we in the cols
				@r2 has the number of the rows that we are on

    
    ldr	    r3, [r0, r2, lsl #2]
    ldrb    r5, [r3, r1]
    mov	    r4, #4
    mul	    r5, r4, r5		@r5 = 4*Pi,j


    sub	    r7, r1, #3 
    ldrb    r4, [r3, r7]	@r4 = Pi,j-1

    add	    r7, r1, #3
    ldrb    r6, [r3, r7]	@r6 = Pi,j+1


    add	    r4, r4, r6

    
    add	    r7, r2, #1
    ldr	    r3, [r0, r7, lsl #2]
    ldrb    r6, [r3, r1]	@r6 = Pi+1, j

    sub	    r7, r2, #1
    ldr	    r3, [r0, r7, lsl #2]
    ldrb    r8, [r3, r1]	@r8 = Pi-1, j

    add	    r4, r4, r6
    add	    r4, r4, r8 
    lsl	    r4, r4, #1	     

    add	    r5, r5, r4		@r5 = 4*Pi,j + 2*(...)

    ldr	    r3, [r0, r7, lsl #2]
    add	    r8, r1, #3
    ldrb    r4, [r3, r8]	@r4 = Pi-1, j + 1

    sub	    r8, r1, #3
    ldrb    r6, [r3, r8]	@r6 = Pi-1, j - 1

    add	    r7, r2, #1
    ldr	    r3, [r0, r7, lsl #2]
    ldrb    r9, [r3, r8]	@r9 = Pi+1,j - 1
    
    add	    r8, r1, #3
    ldrb    r10, [r3, r8]	@r10 = Pi+1, j+1

    add	    r5, r5, r4
    add	    r5, r5, r6
    add	    r5, r5, r9
    add	    r0, r5, r10

    asr	    r0, r0, #4
	    
    ldmfd   sp!, {r4-r10, pc} 

smooth_image_color:
	stmfd	sp!, {r4-r12,lr}
	
	mov	r4, r0			@save our vals
	mov	r5, r1
	mov	r6, r2

	mov	r0, r1
	mov	r1, r2

	bl	allocate_asm_struct	@make new array
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
	
	mov	    r12, r8
	mov	    r2, #3
	mul	    r12, r12, r2	

	mov	    r0, r4
	mov	    r2, r7
	mov	    r1, r12
	bl	    matrixOps
	
	strb	 r0, [r11], #1		@red val

	add	 r1, r12, #1
	mov	 r0, r4
	mov	 r2, r7
	bl	 matrixOps	
	
	strb	r0, [r11], #1 

	add	    r1, r12, #1
	mov	    r0, r4
	mov	    r2, r7
	bl	    matrixOps
	
	strb	r0, [r11], #1

	
	add	r8, r8, #1
	b	loopj

exitLoopj:
    
	add	r7, r7, #1
	b	loopi
exitLoopi:

	mov	r0, r9


	ldmfd	sp!, {r4-r12,pc}



    .global smoothImage
smoothImage:
    stmfd   sp!,{r4-r6,lr}
    
    mov	    r4, r0
    ldrb    r0, [r4]
    
    cmp	r0, #50	    @case 2
    beq	return
    cmp	r0, #52	    @case 4
    beq	return

    cmp	r0, #51	    @case 3
    beq	colorImage
    cmp	r0, #54	    @case 6
    beq	colorImage

    b	default
    
colorImage:
    
    ldr	r1, [r4, #12]	@get rows
    mov	r6, r1

    ldr	r2, [r4, #16]	@get cols

    
    ldr	r0, [r4, #20]	@this gets us the 2D pointer to rgb image
    
    mov	r5, r0
    
    bl	smooth_image_color
    
    str	r0, [r4, #20]
    
    mov	r0, r5
    mov	r1, r6

    bl	free_array

    b	return	

default:	
    ldr	r0,=msg
    bl	printf
    
return:
    ldmfd   sp!,{r4-r6,pc}


