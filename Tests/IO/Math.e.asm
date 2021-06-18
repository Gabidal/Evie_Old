.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
jmp Return_Here_1
Return_Here_1:
mov eax, -6
ret 
mov ecx, 1065353216
movd xmm0, ecx
movd ecx, xmm0
jmp Return_Here_5
Return_Here_5:
mov eax, ecx
ret 
mov eax, -6
ret 
ret 


main:
jmp Return_Here_6
Return_Here_6:
jmp Return_Here_9
mov ecx, 1065353216
movd xmm0, ecx
movd ecx, xmm0
jmp Return_Here_10
Return_Here_10:
jmp Return_Here_9
jmp Return_Here_9
Return_Here_9:
mov eax, 1
ret 
ret 


.section .data
