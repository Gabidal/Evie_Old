.intel_syntax noprefix
.global main
.global Start_Test
sum:
add w0, w0, 3
mov w0, w0
ret 
ret 


Start_Test:
str x21,  [sp ]
sub sp, sp, 8
str x20,  [sp ]
sub sp, sp, 8
str x19,  [sp ]
sub sp, sp, 8
mov w0, 3
bl sum
mov w19, w0
mov w20, w19
mov w21, -2
mul w20, w20, w21
add w20, w20, 6
mov w0, w20
ldr x21,  [sp ]
add sp, sp, 8
ldr x20,  [sp ]
add sp, sp, 8
ldr x19,  [sp ]
add sp, sp, 8
ret 
ldr x21,  [sp ]
add sp, sp, 8
ldr x20,  [sp ]
add sp, sp, 8
ldr x19,  [sp ]
add sp, sp, 8
ret 


main:
mov w0, 1
ret 
ret 


