.intel_syntax noprefix
.file 1 "Tests/IO/Math.e"
.file 2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"
.file 4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 12 "Tests/IO/../../IO/STD.e"
.file 13 "Tests/IO/../../IO/Memory.e"
.file 14 "Tests/IO/../../IO/List.e"
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
.loc 1 8 12
mov ecx, 1
add ecx, 2
.loc 1 9 10
mov ecx, ecx
call sum
mov ecx, eax
xor edx, edx
mov eax, 3
div ecx
mov ecx, eax
.loc 1 12 11
add ecx, 3
sub ecx, 3
mov eax, ecx
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
ret 
.loc 1 16 2
mov eax, -6
ret 
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
mov ecx, 4608083138725491507
movd xmm0, ecx
movss xmm1, dword ptr [rsp + 4 ]
addss xmm1, xmm0
.loc 1 20 17
movss xmm0, dword ptr [rsp + 0 ]
movss xmm1, dword ptr [rsp + 4 ]
subss xmm1, xmm0
mov ecx, -4614838538166547251
movd xmm0, ecx
movss xmm1, dword ptr [rsp + 4 ]
subss xmm1, xmm0
movss xmm0, dword ptr [rsp + 4 ]
add rsp, 8
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
char_START:
.loc 2 11 1
char:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
char_END:


.cfi_endproc 
____Deallocate_BYTE_POINTER__START:
.loc 14 1 1
____Deallocate_BYTE_POINTER_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
mov qword ptr [rsp + 0 ], rcx
.loc 13 18 2
mov rcx, qword ptr [rsp + 0 ]
mov edx, 8
call _V19internal_deallocatePhx
add rsp, 16
ret 
____Deallocate_BYTE_POINTER__END:


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
.byte 2
.byte 1
.byte 54
.byte 11
.byte 3
.byte 8
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 5
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
.byte 6
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
.byte 7
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
.byte 8
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
.byte 9
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
.byte 10
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
.byte 73
.byte 19
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
_BYTE_POINTER_START:
.byte 4
.byte 1
.asciz "BYTE_POINTER"
.byte 8
.byte 13
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 13
.byte 1
.long _long_START-Debug_Info_Start
.byte 0
.byte 5
.quad sum_START
.long sum_END-sum_START
.byte 1
.byte 87
.asciz "sum"
.byte 1
.byte 3
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 3
.long _int_START-Debug_Info_Start
.byte 0
.byte 7
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 7
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "b"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "c"
.byte 1
.byte 10
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "d"
.byte 1
.byte 11
.long _int_START-Debug_Info_Start
.byte 0
.byte 5
.quad Test_Fpu_START
.long Test_Fpu_END-Test_Fpu_START
.byte 1
.byte 87
.asciz "Test_Fpu"
.byte 1
.byte 19
.byte 0
.byte 9
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 23
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "this"
.byte 2
.byte 11
.long _char_START-Debug_Info_Start
.byte 5
.quad ____Deallocate_BYTE_POINTER__START
.long ____Deallocate_BYTE_POINTER__END-____Deallocate_BYTE_POINTER__START
.byte 1
.byte 87
.asciz "____Deallocate_BYTE_POINTER_"
.byte 14
.byte 1
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "Address"
.byte 13
.byte 17
.long _BYTE_POINTER_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 13
.byte 1
.long _long_START-Debug_Info_Start
.byte 0
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
