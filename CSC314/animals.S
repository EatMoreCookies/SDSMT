	.data
aniaml:	.byte 0
        .align 2
N:	.word  0
scnfmt1:asciz  "%d"
scnfmt2:asciz  "%c"





	.global main
main:	stmfd   sp!, {lr}


	mov 	r5, #0
	mov 	r4, #0

	ldr 	r1, =N
	ldr 	r0, =scnfmt1
	bl 	scanf

loop:
	ldr r0, =scnfmt2
	ldr r1, =animal
	bl  scanf

	ldr	r0, =scnfmt2
	ldr 	r1, =animal

	ldr 	r0, =animal
	ldr     r0, [r0]
	cmp     r0, #'O'
	cmpne   r0, #'Z'
	bne     loop

	lsls     r4, r4, #1
	lsl      r5, r5, #1
	orrcs    r5, r5, #1

	cmp 	r0, #'O'
	orreq   r4, r4, #1

	ldr 	r0, =N
	ldr 	r1, [r0]
	subs	r1, r1, #1
	str	r1, [r0]

	bgt     loop

	ldr 	r0, =ptrfmt 

	mov    r0, #0
	ldmfd  sp!, {r4, r5, lr}
	mov    pc, lr
