.intel_syntax noprefix
.file 1 "Tests/IO/Math.e"
.file 2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"
.file 4 "Tests/IO/../../IO/win32.asm.obj"
.file 5 "Tests/IO/../../IO/asm.h"
.file 6 "Tests/IO/../../IO/win32.asm"
.file 7 "Tests/IO/../../IO/STD.e"
.file 8 "Tests/IO/../../IO/List.e"
Code_Start:
.global main
.global Start_Test
.section .text
sum_START:
.loc 1 3 1
sum:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 4
mov dword ptr [rsp + 0 ], ecx
.loc 1 4 11
add dword ptr [rsp + 0 ], 3
mov eax, dword ptr [rsp + 0 ]
add rsp, 4
ret 
add rsp, 4
ret 
sum_END:


.cfi_endproc 
Start_Test_START:
.loc 1 7 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
push rbx
.loc 1 8 8
mov ebx, 3
.loc 1 9 10
mov ecx, ebx
call sum
mov ecx, eax
.loc 1 10 12
mov r8d, ecx
mov r9, rdx
mov eax, r8d
mul ebx
mov r8d, eax
mov rdx, r9
mov r8d, r8d
.loc 1 11 12
mov r9d, r8d
xor edx, edx
mov eax, r9d
div ecx
mov r9d, eax
mov r9d, r9d
.loc 1 12 11
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
.loc 1 14 9
call Test_Fpu
cvttss2si ecx, xmm0
mov eax, ecx
.loc 1 16 2
pop rbx
.loc 1 14 2
ret 
.loc 1 16 2
mov eax, -6
pop rbx
ret 
pop rbx
ret 
Start_Test_END:


.cfi_endproc 
Test_Fpu_START:
.loc 1 19 1
Test_Fpu:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
movss dword ptr [rsp + 0 ], xmm0
movss dword ptr [rsp + 4 ], xmm1
mov ecx, -1110651699
movd xmm0, ecx
movss xmm0, xmm0
add rsp, 8
.loc 1 20 2
ret 
add rsp, 8
ret 
Test_Fpu_END:


.cfi_endproc 
main_START:
.loc 1 23 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 24 2
call Start_Test
.loc 1 25 2
mov eax, 1
ret 
ret 
main_END:


.cfi_endproc 
Code_End:
.section .data
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
.byte 85
.byte 23
.byte 0
.byte 0
.byte 2
.byte 36
.byte 0
.byte 3
.byte 8
.byte 62
.byte 11
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 56
.byte 5
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 4
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 5
.byte 5
.byte 0
.byte 2
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 6
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 8
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 7
.byte 52
.byte 0
.byte 2
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 8
.byte 46
.byte 0
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 8
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 0
.section .debug_info
Debug_Info_Start:
.long Debug_Info_End-Debug_Info
Debug_Info:
.word 4
.secrel32 debug_abbrev
.byte 8
.byte 1
.secrel32 .COMPILER_NAME
.word 0x29A
.secrel32 .FILE_NAME
.secrel32 .LINE_TABLE
.secrel32 .DIRECTORY
.quad Code_Start
.long Code_End-Code_Start
_int_START:
.byte 2
.asciz "int"
.byte 5
.byte 4
.byte 2
.byte 3
_short_START:
.byte 2
.asciz "short"
.byte 5
.byte 2
.byte 2
.byte 7
_char_START:
.byte 2
.asciz "char"
.byte 6
.byte 1
.byte 2
.byte 11
_float_START:
.byte 2
.asciz "float"
.byte 4
.byte 4
.byte 2
.byte 15
_double_START:
.byte 2
.asciz "double"
.byte 4
.byte 8
.byte 2
.byte 20
_long_START:
.byte 2
.asciz "long"
.byte 5
.byte 8
.byte 2
.byte 25
_string_START:
.byte 2
.asciz "string"
.byte 6
.byte 1
.byte 2
.byte 29
.byte 4
.quad sum_START
.long sum_END-sum_START
.byte 1
.byte 87
.asciz "sum"
.byte 1
.byte 3
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 3
.long _int_START-Debug_Info_Start
.byte 0
.byte 6
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 7
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "b"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "c"
.byte 1
.byte 10
.long _int_START-Debug_Info_Start
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "d"
.byte 1
.byte 11
.long _int_START-Debug_Info_Start
.byte 0
.byte 4
.quad Test_Fpu_START
.long Test_Fpu_END-Test_Fpu_START
.byte 1
.byte 87
.asciz "Test_Fpu"
.byte 1
.byte 19
.byte 0
.byte 8
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 23
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Math.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
