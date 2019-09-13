	.data

prtfmt1:	.asciz "Enter text (ctrl - D to end): "
		.align 2
prtfmt2:	.asciz "%s\n"
		.align 2
prtfmt3:	.asciz "\nThe checksum is %08X\n"
		.align 2
prtfmt4:	.asciz "%08X\n" 
		.align 2



	.text

checksum:   
	    
	    mov	    r1, #0	@incrementer i
	    mov	    r2, #0  @sum
loop1:						
	    ldrb    r3, [r0, r1]
	    cmp	    r3, #0
	    beq	    exit1
	    
	    add	    r2, r3, r2

	    add	    r1, r1, #1
	    b	    loop1
exit1:
	    mov	    r0, r2
	    mov	    pc, lr


	    .global main

main:	    stmfd  sp!, {lr}

	    sub	   sp, sp, #4096    @buffer

	    
	    ldr r0, =prtfmt1
	    bl	    printf

	    mov	    r4, #0	@incrementer i	    

loop:	    
	    bl 	    getchar
	    
	    strb    r0, [sp, r4]

	    
	    cmp	    r0, #-1
	    beq	    exit


	    add	    r4, r4, #1
	    mov	    r1, #4096
	    sub	    r1, r1, #1

	    cmp	    r4, r1
	    bge	    exit
	    b	    loop


exit:	    
	    mov	    r0,	#0
	    strb    r0, [sp, r4]	    

	    ldr	    r0, =prtfmt2
	    mov	    r1, sp
	    
	    bl	    printf	    @print out original string	
    

	    mov	    r0, sp
	    bl	    checksum
	    mov	    r1, r0
	    ldr	    r0, =prtfmt3
	    bl	    printf

	    mov	    r0, sp
	    bl	    checksum		
	    mov	    r1, r0
	    ldr	    r0, =prtfmt3			
	    bl	    printf
	    
	    

	    add	    sp, sp,#4096
	    mov	    r0, #0
	    ldmfd   sp!, {lr}
	    mov	    pc, lr
	        

	    

	    
	    
	    
	
	    
	    
