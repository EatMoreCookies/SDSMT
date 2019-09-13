		.global _ZN5queue5enqueEi

_ZN5queue5enqueEi:
			stmfd	sp!, {r4, r5, lr}
			
			mov	r4, r0		
			mov	r5, r1	

			bl	_ZN5queue6isfullEv	@call isfull function
			cmp	r0, #0
			beq	continue
			mov	r0, #0
			b	return
continue:

			ldr	r1, [r4, #212]		@this gets us to the end index
			mov	r3, #4
			mul	r3, r1, r3		@multiply by 4 to get num bytes tp store
			str	r5, [r4, r3]		@store new item at this index
		

			add	r1, r1, #1
			cmp	r1, #52
		    
			
			movge	r1, #0
			str	r1, [r4, #212]

			ldr	r2, [r4, #216]		@get the number of items
			add	r2, r2, #1
			str	r2, [r4, #216]
    
			mov	r0, #1

return:			ldmfd	sp!, { r4, r5, lr}
			mov	pc, lr

			
			
		
		    
		.global	_ZN5queue5dequeERi 	

_ZN5queue5dequeERi:	    stmfd   sp!, {r4, r5,lr}
			    mov	    r4, r0
			    mov	    r5, r1
			    
			    bl	    _ZN5queue7isemptyEv
			    cmp	    r0, #0
			    beq	    continue2
			    mov	    r0, #0
			    b	    return1

continue2:		    
			    ldr	    r0, [r4, #208]	    @front index
			    mov	    r1, #4
			    mul	    r1, r1, r0
		
			    ldr	    r2,	[r4, r1]	    @r2 has the item
			    str	    r2, [r5, #0]			   
 
			    add	    r0, r0, #1
			    cmp	    r0, #52
			    movge   r0, #0
			    str	    r0, [r4, #208]
			    	    		    
			    ldr	    r0, [r4, #216]
			    sub	    r0, r0, #1
			    str	    r0, [r4, #216]

			    mov	    r0, r2
return1:		    
			    ldmfd   sp!, {r4, r5, lr}
			    mov	    pc, lr
	    
