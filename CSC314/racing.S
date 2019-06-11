	.data

scnfmt:		.asciz "%d%d"
prtfmt:		.asciz "%d\n"
	


 	.text
quad:
	cmp    	r0, #0
        blt    	else

	cmp 	r1, #0
	movgt 	r0, #1

	movle   r0, #4

        b     	return
else:
        cmp 	r1, #0

	movgt   r0, #2

	movle   r0, #3



return:
	mov pc, lr


	.global main

	
main:	stmd 	sp!, {lr}
	sub 	sp, sp, #8

	

	ldr    	r0, =scnfmt
	add    	r1, sp, #4
	mov 	r2, sp
	bl	scanf

	ldr     r0, [sp, #4]
	ldr     r1, [sp]

	bl 	quad

	mov     r1, r0
	ldr     r0, =ptrfmt
	bl 	printf


	

	mov     r0, #0
	add     sp, sp, #8
	ldmfd   sp!, {lr}
	mov 	pc, lr
