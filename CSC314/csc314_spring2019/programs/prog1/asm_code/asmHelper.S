


		.global allocate_asm_struct
allocate_asm_struct:	
		    stmfd   sp!, {r4-r7, lr}

		    mov	    r7, r0
		    mov	    r4, r0
		    mov	    r5, r1

		    lsl	    r0, r0, #2
		    bl	    malloc		@gets us a pointer to our rows

		    mov	    r6, r0		@pointer to our rows
		    
		    mov	    r2, #3		@size of struct
		    mul	    r5, r5, r2
		    
					    	
		    mov	    r7, #0

do:		    cmp	    r7, r4
		    bge	    exitLoop		    	
		    
		    mov	    r0, r5
	    
		    bl	    malloc

		    str	    r0, [r6, r7, lsl #2] @store column pointer into    

		    add	    r7, r7, #1
		    b	    do
exitLoop:	
		    mov	    r0, r6
		    ldmfd   sp!, {r4-r7, pc}		    
		
