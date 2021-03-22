.global main
.global Start_Test
sum:
add w0, w0, 3
mov w0, w0
ret 
ret 


Start_Test:
str x19,  [sp ]
sub sp, sp, 8
mov w19, 3
mov w0, w19
bl sum
mov w0, w0
mov w1, w0
mul w1, w1, w19
mov w1, w1
mov w2, w1
sdiv w2, w2, w0
mov w2, w2
add w2, w2, w19
add w2, w2, w0
sub w2, w2, w1
mov w0, w2
ldr x19,  [sp ]
add sp, sp, 8
ret 
fmov s0, 39322
fmov s0, 16281
lsl s1, s1, 16
orr s0, s0, s1
fmov s0, s0
fmov s1, 13107
fmov s1, 16403
lsl s2, s2, 16
orr s1, s1, s2
fmov s1, s1
bl Test_Fpu
fcvtzs w0, s0
mov w0, w0
ldr x19,  [sp ]
add sp, sp, 8
ret 
mov w0, -6
ldr x19,  [sp ]
add sp, sp, 8
ret 
ldr x19,  [sp ]
add sp, sp, 8
ret 


Test_Fpu:
fmov s0, -0.100000
ret 
ret 


main:
bl Start_Test
mov w0, 1
ret 
ret 


