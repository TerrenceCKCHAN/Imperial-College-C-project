
// Data Section
.balign 4
var1:
    .word 3

.balign 4
var2:
    .word 4
// Code Section
.text
.balign 4

.global main

main:
    ldr r1, addr_of_var1 // r1 <- &var1
    ldr r1, [r1]         // r1 <- *r1
    ldr r2, addr_of_var2 // r1 <- &var2
    ldr r2, [r2]         // r2 <- *r2
    add r0, r1, r2

    // Delay LED switching
    for_loop_x:
        mov r1, #0

    next_x:
        cmp r1, #10000
        bge endfor

    increment_x:
        add r1, #1
        b next_x

    for_loop_y:
        mov r2, #10000

    next_y:
        cmp r2, #10000
        bge increment_x

    increment_y:
        add r2, #1
        b next_y

    for_loop_z:
        mov r3, #0
        cmp r3, #10000
        bge increment_y
        add r3, #1
        b for_loop_z

    endfor:
    //end of delay





    bx lr

//Labels needed to acess data
addr_of_var1: .word var1
addr_of_var2: .word var2
