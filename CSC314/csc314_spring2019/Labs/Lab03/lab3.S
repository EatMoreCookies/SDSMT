	.data
str1:	.asciz "%d"
        .align 2
str2:   .asciz "The sum is %d\n"
        .align 2 
n:      .word  0
m:	.word  0

	.text
	.global main

main:	stmfd sp!, {lr}	

	@scanf("%d\0, &n)

        ldr r0, =str1
	ldr r1, =n
	@ldr r2, =m

        bl	scanf
       
        ldr r0, =str1
        ldr r1, =m
   
        bl	scanf
        
        


        @prinf("You entered the %d\n", n)

        ldr	r0, =str2
	ldr	r1, =n
	ldr     r2, =m
	ldr	r2, [r2]
	ldr	r1, [r1]
        
        add     r1, r2, r1 
	bl	printf 

	ldmfd	sp!,{lr}
	mov	r0, #0
	mov	pc, lr
	.end
