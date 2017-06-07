
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
    bx lr

//Labels needed to acess data
addr_of_var1: .word var1
addr_of_var2: .word var2
