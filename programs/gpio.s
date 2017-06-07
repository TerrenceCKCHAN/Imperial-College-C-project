
    main:
                 ldr r4, =0x0
    for_LED:
                 cmp r4, #0x100
                 bge end_LED

    //Clearing pin 16 - write a 1 into pin 16 - set 18th bit at address 0x2020 0028 to 1
                 ldr r2, =0x40000
                 str r2, 0x20200028

    // Delay LED switching
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
    //end of delay

    //Setting pin 16
                 ldr r2, =0x40000
                 str r2, =0x20200004
    // turning on pin 16
                 str r2, =0x2020001C

       // Delay LED switching
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
    //end of delay

                 add r4, r4, #1;
    end_LED:
                 bx lr


