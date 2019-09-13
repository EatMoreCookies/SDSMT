/* color_to_gray will allocate a new grayimage structure and fill it
   with the grayscale equivalent of the given image.

   The C prototype is:

   grayimage *color_to_gray(rgbimage *image);

*/

	.global	color_to_gray
color_to_gray:
	/* Fill in the code to allocate a new grayimage, then convert
	   each pixel from the given rgbimage from color to grayscale,
	   and store it in the grayimage. */

		    mov	    r4, r0	    @r4 has the pointer to rbg image
		    ldr	    r5, [r4, #4]    @r5 has width
		    ldr	    r6,	[r4, #8]    @r6 has height


		    mov	    r0, r5		    @loading arguments for allocate_grayimage
		    mov	    r1, r6
		    bl	    allocate_grayimage	    @r0 has the pointer to the gray struct
	           
                    mov	    r7, #0		    @counter for outer loop		    
		    
		    ldr	    r1, [r4]		    @r1 and r0 point to the rows
		    ldr	    r2, [r0]	  	    

loopi:		    cmp	    r7, r6
		    bge	    exiti
			
		    ldr	    r4, [r1, r7, lsl #2]
		    ldr	    r10,[r2, r7, lsl #2]
		    
		    ldr	    r11, [r10]
		    ldr	    r3, [r4]    

		
	            mov	    r8, #0
		
loopj:		    
		    cmp	    r8, r5           @counter for inner loop
		    bge	    exitj
		    
    		    ldrb    r4, [r3], #1
		    mov	    r9, #54
		    mul	    r4, r9, r4


		    ldrb    r10, [r3], #1
		    mov	    r9, #184
		    mul	    r10, r10, r9
		    
		    add	    r4, r4, r10

		    ldr	    r10, [r3], #1
		    mov	    r9, #18
		    mul	    r10, r9, r10
		    
		    add	    r4, r4, r10
		    
		    lsr	    r4, r4, #8	    @r2 contains the gray val

		    
		    str	    r4, [r11, r8, lsl #2]
		    add	    r8, r8, #1
		    
		    b	    loopj
		    
exitj:
		    add	    r7, r7, #1
		    b	    loopi
exiti:
		    
		    mov	    pc,lr		@ return
		    
