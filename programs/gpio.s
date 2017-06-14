
    main_SETOUTPUTPIN:

                 ldr r7, =0x40000
                 ldr r8, =0x20200004
                 str r7, [r8]

    LED_LOOP:
                 ldr r5, =0x10000
                 ldr r6, =0x20200028
                 str r5, [r6]

                 ldr r3, =0x0
                 ldr r4, =0x2020001c
                 str r3, [r4]
                 ldr r1, =0x0

    DELAY:
                 add r1, r1, #0x1
                 cmp r1, #0x2710
                 blt  DELAY

    PIN_ON:
                 str r5, [r4]
                 ldr r1, =0x0

    DELAY2:
                 add r1, r1, #0x1
                 cmp r1, #0x2710
                 blt DELAY2

    END:
                 b LED_LOOP
                 andeq r0, r0, r0


