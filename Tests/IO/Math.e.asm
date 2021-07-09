.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
jmp Return_Here_2
Return_Here_2:
mov eax, -6
ret 
mov ecx, 1065353216
movd xmm0, ecx
movss xmm0, xmm0
jmp Return_Here_3
Return_Here_3:
cvttss2si ecx, xmm0
mov eax, ecx
ret 
mov eax, -6
ret 
ret 


main:
jmp Return_Here_5
Return_Here_5:
jmp Return_Here_4
mov ecx, 1065353216
movd xmm0, ecx
movss xmm0, xmm0
jmp Return_Here_6
Return_Here_6:
jmp Return_Here_4
jmp Return_Here_4
Return_Here_4:
mov eax, 1
ret 
ret 


.section .data
