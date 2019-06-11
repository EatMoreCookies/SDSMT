		.data

scnfmt: 	.asciz "%d"
prtfmt: 	.asciz "%d\n"


	.text
@@static int reverse (int x)


reverse: mov 	r1, #0

loop:   lsl 	r1, r1, #1

	ands 	r2, r0, #1
	
        orrne   r1, r1, #1

	lsrs    r0, r0, #1

	bne     loop

	mov     r0, r1

	mov pc, lr

        .global main

main:
        stmfd sp!, {lr}

        sub    sp, sp, #4

	ldr    r0, =scnfmt
	mov    r1, sp
	bl     scanf

	ldr    r0, [sp]

	bl     reverse

	mov    r1, r0
	ldr    r0, =prtfmt
	bl     printf

        

        mov r0, #0
	ldmfd sp!, {lr}
	mov pc, lr
