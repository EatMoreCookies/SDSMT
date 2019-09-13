            .data
msg:
            .ascii "Hello World!\n"
len         = . - msg

            .text
.global     main
            @just testing the comments

main:    
  
    stmfd sp!,{lr}


    ldr r0, =msg
    
    bl printf

    mov r0, #0
    ldmfd sp!, {lr}
    mov pc, lr
