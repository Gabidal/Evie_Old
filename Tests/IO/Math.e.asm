.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
mov ecx, 6
jmp Return_Here_44
Return_Here_44:
mov r8d, ecx
mov r9, rdx
mov eax, 3
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
mov r9d, r8d
xor edx, edx
mov eax, r9d
div ecx
mov r9d, eax
mov ecx, r9d
add ecx, 3
add ecx, 6
sub ecx, r8d
mov eax, ecx
ret 
mov ecx, 1065353216
movd xmm0, ecx
movss xmm0, xmm0
jmp Return_Here_45
Return_Here_45:
cvttss2si ecx, xmm0
mov eax, ecx
ret 
mov eax, -6
ret 
ret 


_Z4mainv:
mov ecx, 6
jmp Return_Here_47
Return_Here_47:
mov r8d, ecx
mov r9, rdx
mov eax, 3
mul r8d
mov r8d, eax
mov rdx, r9
mov r8d, r8d
mov r8d, r8d
xor edx, edx
mov eax, r8d
div ecx
mov r8d, eax
mov ecx, r8d
jmp Return_Here_46
mov ecx, 1065353216
movd xmm0, ecx
movss xmm0, xmm0
jmp Return_Here_48
Return_Here_48:
jmp Return_Here_46
jmp Return_Here_46
Return_Here_46:
mov eax, 1
ret 
ret 


.section .data
