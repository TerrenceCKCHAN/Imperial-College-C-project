main:
                 ldr r4, =0x0
                 mov r2, #0x40000
                 ldr r3, #0x20200004
                 ldr r5, =0x2020001C
                 str r2, [r3]
