
// Setting the pins as output pins

// GPIO pin0,10,20 on

                 ldr r5, =0x1
                 ldr r6, =0x20200004
                 str r5, [r6]


// GPIO pin1,11,21 r5 = 0x8
// GPIO pin2,12,22 r5 = 0x40
// GPIO pin3,13,23 r5 = 0x200
// GPIO pin4,14,24 r5 = 0x1000
// GPIO pin5,15,25 r5 = 0x8000
// GPIO pin6,16,26 r5 = 0x40000
// 7,17,27 r5 = 0x200000
// 8,18,28 r5 = 0x1000000
// 9,19,29 r5 = 0x8000000

// r6 20200000 -> 0-9
// r6 20200004 -> 10-19
// r6 20200008 -> 20-29

pinOff:
                 ldr r5, =0x10000
                 ldr r6, =0x20200028
                 str r5, [r6]

pinOn:
                 mov r5, =0x10000
                 ldr r7, =0x2020001C
                 str r5, [r7]

// r5 = 0x1 0 this corresponds to the setting 1 at this position of the bit
//     0x2 1
//     0x4 2
//     0x8 3
//     0x10 4
//     0x20 5
//     0x40 6
//     0x80 7
//     0x100 8
//     etc...

