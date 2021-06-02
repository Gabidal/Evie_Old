.intel_syntax noprefix
.file 1 "Tests/IO/Cast.e"
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
test_all_format_casts_START:
.loc 1 17 1
test_all_format_casts:
.cfi_startproc 
.cfi_def_cfa_offset 16
ret 
test_all_format_casts_END:


.cfi_endproc 
Start_Test_START:
.loc 1 30 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
.loc 1 31 2
call test_all_format_casts
lea rcx, qword ptr [rsp ]
.loc 1 32 8
mov rcx, rcx
call Mid
.loc 1 9 2
movss xmm0, dword ptr [rsp + 12 ]
cvttss2si ecx, xmm0
.loc 1 33 2
mov eax, ecx
add rsp, 16
ret 
add rsp, 16
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 36 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 38 2
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
Base_START:
.loc 1 3 1
Base:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 1 4 11
mov dword ptr [rcx + 8 ], 0
.loc 1 3 1
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
Base_END:


.cfi_endproc 
____Deallocate_Base__START:
.loc 14 1 1
____Deallocate_Base_:
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
____Deallocate_Base__END:


.cfi_endproc 
Mid_START:
.loc 1 7 1
Mid:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
call Base
mov rcx, qword ptr [rsp + 0 ]
.loc 1 8 7
mov dword ptr [rcx + 8 ], 1
mov rcx, qword ptr [rsp + 0 ]
mov r8d, 1074261268
mov dword ptr [rcx + 12 ], r8d
.loc 1 7 1
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
Mid_END:


.cfi_endproc 
____Deallocate_Mid__START:
.loc 14 1 1
____Deallocate_Mid_:
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
____Deallocate_Mid__END:


.cfi_endproc 
____Deallocate_Top__START:
.loc 14 1 1
____Deallocate_Top_:
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
____Deallocate_Top__END:


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
.byte 73
.byte 19
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
.byte 11
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
_Base_START:
.byte 4
.byte 1
.asciz "Base"
.byte 4
.byte 1
.byte 3
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 0
_Mid_START:
.byte 6
.byte 1
.asciz "Mid"
.byte 8
.byte 1
.byte 7
.long _Base_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "feature"
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 0
_Top_START:
.byte 6
.byte 1
.asciz "Top"
.byte 12
.byte 1
.byte 12
.long _Mid_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "feature"
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "feature"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 12
.long _long_START-Debug_Info_Start
.byte 0
.byte 5
.quad test_all_format_casts_START
.long test_all_format_casts_END-test_all_format_casts_START
.byte 1
.byte 87
.asciz "test_all_format_casts"
.byte 1
.byte 17
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "i"
.byte 1
.byte 18
.long _int_START-Debug_Info_Start
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 20
.long _float_START-Debug_Info_Start
.byte 0
.byte 8
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 30
.byte 7
.byte 2
.byte 145
.byte 0
.asciz "m"
.byte 1
.byte 32
.long _Mid_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "feature"
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 9
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 36
.byte 10
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
.byte 10
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
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 5
.quad ____Deallocate_Base__START
.long ____Deallocate_Base__END-____Deallocate_Base__START
.byte 1
.byte 87
.asciz "____Deallocate_Base_"
.byte 14
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "feature"
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 5
.quad ____Deallocate_Mid__START
.long ____Deallocate_Mid__END-____Deallocate_Mid__START
.byte 1
.byte 87
.asciz "____Deallocate_Mid_"
.byte 14
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "feature"
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 5
.quad ____Deallocate_Top__START
.long ____Deallocate_Top__END-____Deallocate_Top__START
.byte 1
.byte 87
.asciz "____Deallocate_Top_"
.byte 14
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 12
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "feature"
.byte 1
.byte 9
.long _float_START-Debug_Info_Start
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Cast.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
