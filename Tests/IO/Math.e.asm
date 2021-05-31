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
mov ecx, 3
call sum
mov ecx, eax
mov ecx, ecx
mov r8, rdx
mov eax, -2
mul ecx
mov ecx, eax
mov rdx, r8
add ecx, 6
mov eax, ecx
ret 
mov ecx, 1067030938
movd xmm0, ecx
movss xmm0, xmm0
mov ecx, 1075000115
movd xmm1, ecx
movss xmm1, xmm1
call Test_Fpu
cvttss2si ecx, xmm0
mov eax, ecx
ret 
mov eax, -6
ret 
ret 


Test_Fpu:
mov ecx, -1110651699
movd xmm0, ecx
movss xmm0, xmm0
ret 
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


____Deallocate_BYTE_POINTER_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
