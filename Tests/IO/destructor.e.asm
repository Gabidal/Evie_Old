.intel_syntax noprefix
.file 1 "Tests/IO/Destructor.e"
.file 2 "C:/Users/GabenRTX/.Repos/Evie/IO/cstd.e"
.file 3 "C:/Users/GabenRTX/.Repos/Evie/IO/sys.e"
.file 4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 12 "C:/Users/GabenRTX/.Repos/Evie/IO/STD.e"
.file 13 "C:/Users/GabenRTX/.Repos/Evie/IO/Memory.e"
.file 14 "C:/Users/GabenRTX/.Repos/Evie/IO/List.e"
Code_Start:
.global Start_Test
.global main
.section .text
main_START:
.loc 1 3 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 4 2
mov eax, 1
ret 
ret 
main_END:


.cfi_endproc 
Start_Test_START:
.loc 1 12 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
.loc 1 13 13
call ____New_foo_
mov rcx, rax
call foo
mov rcx, qword ptr [rax + 0 ]
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rax + 8 ]
mov qword ptr [rsp + 8 ], rcx
.loc 1 14 19
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 26
add qword ptr [rcx + 0 ], 1
.loc 1 14 19
mov rcx, rcx
.loc 1 8 2
mov r8d, dword ptr [rcx + 12 ]
.loc 1 16 8
mov r8d, r8d
.loc 1 17 2
mov eax, r8d
add rsp, 16
ret 
.loc 14 1 10
mov rcx, rcx
call Destructor
add rsp, 16
ret 
Start_Test_END:


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
foo_START:
.loc 1 7 1
foo:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 1 8 8
mov dword ptr [rcx + 12 ], 1
mov rcx, qword ptr [rsp + 0 ]
.loc 1 9 8
mov dword ptr [rcx + 8 ], 2
.loc 1 7 1
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
foo_END:


.cfi_endproc 
____Deallocate_foo__START:
.loc 14 1 1
____Deallocate_foo_:
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
____Deallocate_foo__END:


.cfi_endproc 
____New_foo__START:
.loc 14 1 1
____New_foo_:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 13 26 9
mov ecx, 8
call _V17internal_allocatex_rPh
lea rcx, qword ptr [rax ]
mov rax, rcx
ret 
ret 
____New_foo__END:


.cfi_endproc 
Destructor_START:
.loc 1 7 1
Destructor:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
.loc 14 1 1
if8:
.loc 14 2 1
mov rcx, qword ptr [rsp + 0 ]
call ____Deallocate_foo_
.loc 14 1 1
if8_END:
add rsp, 8
ret 
Destructor_END:


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
.byte 11
.byte 46
.byte 0
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
.byte 6
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 3
_foo_START:
.byte 4
.byte 1
.asciz "foo"
.byte 8
.byte 1
.byte 7
.byte 3
.byte 12
.asciz "X"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Y"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 0
.byte 7
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 12
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "F"
.byte 1
.byte 13
.long _foo_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Y"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "X"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "handle_1"
.byte 1
.byte 14
.long _foo_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Y"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "X"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "x"
.byte 1
.byte 16
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "_31416240"
.byte 1
.byte 14
.long _foo_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Y"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "X"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 0
.byte 9
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
.byte 9
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
.byte 12
.asciz "X"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Y"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 5
.quad ____Deallocate_foo__START
.long ____Deallocate_foo__END-____Deallocate_foo__START
.byte 1
.byte 87
.asciz "____Deallocate_foo_"
.byte 14
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 7
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Y"
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "X"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 0
.byte 11
.quad ____New_foo__START
.long ____New_foo__END-____New_foo__START
.byte 1
.byte 87
.asciz "____New_foo_"
.byte 14
.byte 1
.long _foo_START-Debug_Info_Start
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Destructor.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
