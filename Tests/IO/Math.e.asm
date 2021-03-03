.intel_syntax noprefix
.section .text
Code_Start:
.global main
.global Start_Test
sum_START:
sum:
add ecx, 3
mov eax, ecx
ret 
ret 
sum_END:


Start_Test_START:
Start_Test:
push rbx
mov ebx, 3
mov ecx, ebx
call sum
mov ecx, eax
mov r8d, ecx
mov eax, r8d
mul ebx
mov r8d, eax
mov r8d, r8d
mov r9d, r8d
xor edx, edx
mov eax, r9d
div ecx
mov r9d, eax
mov r9d, r9d
add r9d, ebx
add r9d, ecx
sub r9d, r8d
mov eax, r9d
pop rbx
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
pop rbx
ret 
pop rbx
ret 
Start_Test_END:


Test_Fpu_START:
Test_Fpu:
mov ecx, -1110651699
movd xmm0, ecx
movss xmm0, xmm0
ret 
ret 
Test_Fpu_END:


main_START:
main:
mov eax, 1
ret 
ret 
main_END:


Code_End:
.file 1 "Tests/IO/Math.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
.section .debug_abbrev
debug_abbrev:
.byte 1
.byte 17
.byte 1
.byte 37
.byte 14
.byte 19
.byte 5
.byte 3
.byte 14
.byte 16
.byte 23
.byte 27
.byte 14
.byte 17
.byte 1
.byte 18
.byte 6
.byte 0
.byte 0
.byte 2
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 14
.byte 3
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 2
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 4
.byte 36
.byte 0
.byte 3
.byte 14
.byte 62
.byte 11
.byte 11
.byte 11
.byte 0
.byte 0
.byte 0
