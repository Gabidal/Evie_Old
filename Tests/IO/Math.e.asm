.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
jmp Return_Here_9
Return_Here_9:
mov eax, -6
ret 
mov ecx, 1065353216
movd xmm0, ecx
movss xmm0, xmm0
jmp Return_Here_13
Return_Here_13:
cvttss2si ecx, xmm0
mov eax, ecx
ret 
mov eax, -6
ret 
ret 


main:
jmp Return_Here_18
Return_Here_18:
jmp Return_Here_17
mov ecx, 1065353216
movd xmm0, ecx
movss xmm0, xmm0
jmp Return_Here_22
Return_Here_22:
jmp Return_Here_17
jmp Return_Here_17
Return_Here_17:
mov eax, 1
ret 
ret 


.section .data
