.intel_syntax noprefix
.global main
.global Start_Test
.section .text
sum:
add ecx, 3
mov eax, ecx
ret 
ret 


Start_Test:
mov ecx, 1
add ecx, 2
mov ecx, ecx
call sum
mov ecx, eax
mov r8, rdx
mov eax, 0
mul ecx
mov ecx, eax
mov rdx, r8
mov eax, ecx
ret 
mov ecx, 1075000115
movd xmm0, ecx
movd ecx, xmm0
mov r8d, 1067030938
movd xmm0, r8d
movd r8d, xmm0
movd xmm0, ecx
mov ecx, 4608083138725491507
movd xmm1, ecx
addss xmm0, xmm1
subss xmm0, r8d
mov ecx, -4614838538166547251
movd xmm1, ecx
subss xmm0, xmm1
movd ecx, xmm0
jmp Return_Here_61
Return_Here_61:
mov eax, ecx
ret 
mov eax, -6
ret 
ret 


main:
mov ecx, 1
add ecx, 2
mov ecx, ecx
call sum
mov ecx, eax
jmp Return_Here_65
mov ecx, 1075000115
movd xmm0, ecx
movd ecx, xmm0
mov r8d, 1067030938
movd xmm0, r8d
movd r8d, xmm0
movd xmm0, ecx
mov ecx, 4608083138725491507
movd xmm1, ecx
addss xmm0, xmm1
subss xmm0, r8d
mov ecx, -4614838538166547251
movd xmm1, ecx
subss xmm0, xmm1
movd ecx, xmm0
jmp Return_Here_94
Return_Here_94:
jmp Return_Here_65
jmp Return_Here_65
Return_Here_65:
mov eax, 1
ret 
ret 


.section .data
