.intel_syntax noprefix
.file 1 "Tests/IO/Comment.e"
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
.global main
.global Start_Test
.section .text
banana_START:
.loc 1 7 1
banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 8 2
mov eax, 1
ret 
ret 
banana_END:


.cfi_endproc 
Start_Test_START:
.loc 1 11 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 24
lea rcx, qword ptr [rsp ]
.loc 1 12 14
mov rcx, rcx
call ____List_int_
.loc 1 14 9
call banana
mov eax, eax
add rsp, 24
ret 
add rsp, 24
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 17 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 18 2
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
____Allocate_int__START:
.loc 14 1 1
____Allocate_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov dword ptr [rsp + 0 ], ecx
mov rcx, rdx
mov eax, 4
mul dword ptr [rsp + 0 ]
mov dword ptr [rsp + 0 ], eax
mov rdx, rcx
.loc 13 5 9
mov ecx, dword ptr [rsp + 0 ]
call _V17internal_allocatex_rPh
mov rax, rax
add rsp, 8
ret 
add rsp, 8
ret 
____Allocate_int__END:


.cfi_endproc 
____List_int__START:
.loc 14 1 1
____List_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
push rbx
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 14 2 15
mov dword ptr [rcx + 20 ], 1
mov rcx, qword ptr [rsp + 0 ]
.loc 14 3 11
mov dword ptr [rcx + 16 ], 0
mov rbx, qword ptr [rsp + 0 ]
mov rcx, qword ptr [rsp + 0 ]
.loc 14 2 2
mov ecx, dword ptr [rcx + 20 ]
.loc 14 4 16
mov ecx, ecx
call ____Allocate_int_
mov qword ptr [rbx + 8 ], rax
.loc 14 1 1
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
pop rbx
ret 
add rsp, 8
pop rbx
ret 
____List_int__END:


.cfi_endproc 
____memcpy_int__START:
____memcpy_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 40
mov qword ptr [rsp + 0 ], rcx
mov qword ptr [rsp + 8 ], rdx
mov dword ptr [rsp + 16 ], r8d
.loc 2 38 17
mov ecx, 0
cmp ecx, dword ptr [rsp + 16 ]
jge while6166_END
while6166:
mov r8, qword ptr [rsp + 0 ]
.loc 2 39 9
lea r8, qword ptr [r8 + rcx * 4 ]
mov r9, qword ptr [rsp + 8 ]
mov r9d, dword ptr [r9 + rcx * 4 ]
mov dword ptr [r8 ], r9d
.loc 2 38 33
add ecx, 1
cmp ecx, dword ptr [rsp + 16 ]
jge while6166_END
jmp while6166
while6166_END:
add rsp, 40
.loc 2 41 5
ret 
add rsp, 40
ret 
____memcpy_int__END:


.cfi_endproc 
____Deallocate_____List_int___START:
.loc 14 1 1
____Deallocate_____List_int__:
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
____Deallocate_____List_int___END:


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
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
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
.byte 6
.quad banana_START
.long banana_END-banana_START
.byte 1
.byte 87
.asciz "banana"
.byte 1
.byte 7
.byte 7
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 11
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 12
.long _____List_int__START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 14
.byte 1
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 14
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Size"
.byte 14
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Capacity"
.byte 14
.byte 2
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
.byte 17
_____List_int__START:
.byte 4
.byte 1
.asciz "____List_int_"
.byte 16
.byte 14
.byte 1
.byte 3
.byte 20
.asciz "Capacity"
.byte 14
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Size"
.byte 14
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 14
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 14
.byte 1
.long _long_START-Debug_Info_Start
.byte 0
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
.byte 5
.quad ____Allocate_int__START
.long ____Allocate_int__END-____Allocate_int__START
.byte 1
.byte 87
.asciz "____Allocate_int_"
.byte 14
.byte 1
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "Return_Cast_Type"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 3
.byte 20
.asciz "Capacity"
.byte 14
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Size"
.byte 14
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 14
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 14
.byte 1
.long _long_START-Debug_Info_Start
.byte 5
.quad ____memcpy_int__START
.long ____memcpy_int__END-____memcpy_int__START
.byte 1
.byte 87
.asciz "____memcpy_int_"
.byte 14
.byte 1
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "dest"
.byte 2
.byte 37
.long _int_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 8
.asciz "source"
.byte 2
.byte 37
.long _int_START-Debug_Info_Start
.byte 0
.byte 5
.quad ____Deallocate_____List_int___START
.long ____Deallocate_____List_int___END-____Deallocate_____List_int___START
.byte 1
.byte 87
.asciz "____Deallocate_____List_int__"
.byte 14
.byte 1
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 14
.byte 1
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 14
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Size"
.byte 14
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "Capacity"
.byte 14
.byte 2
.long _int_START-Debug_Info_Start
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Comment.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
