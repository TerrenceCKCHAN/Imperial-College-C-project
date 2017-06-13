set_pin_16_to_output_pin:
ldr r2,=0x40000
ldr r3,=0x20200004
str r2, [r3]
loop:
clear_pin:
ldr r4,=0x20200028
ldr r6,=0x10000
str r6, [r4]
ldr r5,=0x2020001c
ldr r7,=0x0000000
str r7, [r5]
ldr r0,=0xf00000
wait:
sub r0, r0, #1
cmp r0, #0
bne wait
light_pin:
str r6, [r5]
ldr r0,=0xf00000
wait2:
sub r0, r0, #1
cmp r0, #0
bne wait2
b loop
andeq r0, r0, r0
