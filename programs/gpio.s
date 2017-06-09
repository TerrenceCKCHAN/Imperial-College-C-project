
    main:
                 ldr r4, =0x0
                 mov r5, #0x40000
                 ldr r6, =0x20200004
                 str r5, [r6]

    for_LED:
                 cmp r4, #0x100
                 bge end_LED
                 mov r5, #0x10000
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

    endfor:

                 mov r5, #0x0
                 ldr r7, =0x2020001C
                 str r5, [r7]

    for_loop_x1:
                 ldr r1, =0x0

    next_x1:
                 cmp r1, #0x2710
                 bge endfor1

    increment_x1:
                 add r1, r1, #0x1
                 b next_x1

    endfor1:
                 add r4, r4, #1
                 b for_LED
    end_LED:
                 andeq r0, r0, r0



