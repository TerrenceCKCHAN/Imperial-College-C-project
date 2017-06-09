
    main:
                 ldr r4, =0x0
                 mov r5, #0x40000
                 ldr r6, =0x20200004
                 str r5, [r6]

    for_LED:
                 cmp r4, #0x100
                 bge end_LED
                 mov r5, #0x40000
                 ldr r6, =0x20200028
                 str r5, [r6]

    for_loop_x:
                 ldr r1, =0x0

    next_x:
                 cmp r1, #0x2710
                 bge endfor

    increment_x:
                 add r1, r1, #0x1
                 b next_x

    for_loop_y:
                 ldr r2, =0x2710

    next_y:
                 cmp r2, #0x2710
                 bge increment_x

    increment_y:
                 add r2, r2, #0x1
                 b next_y

    for_loop_z:
                 ldr r3, =0x0
                 cmp r3, #0x2710
                 bge increment_y
                 add r3, r3, #0x1
                 b for_loop_z

    endfor:

                 mov r5, #0x40000
                 ldr r7, =0x2020001C
                 str r5, [r7]

    for_loop_x:
                 ldr r1, =0x0
    next_x:
                 cmp r1, #0x2710
                 bge endfor

    increment_x:
                 add r1, r1, #0x1
                 b next_x

    for_loop_y:
                 ldr r2, =0x2710

    next_y:
                 cmp r2, #0x2710
                 bge increment_x

    increment_y:
                 add r2, r2, #0x1
                 b next_y

    for_loop_z:
                 ldr r3, =0x0
                 cmp r3, #0x2710
                 bge increment_y
                 add r3, r3, #0x1
                 b for_loop_z

    endfor:
                 add r4, r4, #1
    end_LED:
                 andeq r0, r0, r0


