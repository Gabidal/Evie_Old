.intel_syntax noprefix
.file 1 "Tests/IO/Template.e"
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
.file 13 "Tests/IO/../../IO/List.e"
Code_Start:
.global main
.global Start_Test
.section .text
Start_Test_START:
.loc 1 3 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
lea rcx, qword ptr [rsp ]
.loc 1 4 14
mov rcx, rcx
call .List_int_
lea rcx, qword ptr [rsp ]
.loc 1 5 4
mov rcx, rcx
mov edx, 5
call .Add_int_
lea rcx, qword ptr [rsp ]
.loc 1 6 4
mov rcx, rcx
mov edx, 2
call .Add_int_
lea rcx, qword ptr [rsp ]
.loc 1 7 4
mov rcx, rcx
call Pop_Back
.loc 13 4 2
mov rcx, qword ptr [rsp + 8 ]
.loc 1 8 11
lea rcx, qword ptr [rcx + 0 * 4 ]
mov eax, dword ptr [rcx ]
add rsp, 16
ret 
add rsp, 16
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 11 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 12 2
call Start_Test
.loc 1 13 2
mov eax, 1
ret 
ret 
main_END:


.cfi_endproc 
.Add_int__START:
.loc 13 1 1
.Add_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
push rdi
push rbx
sub rsp, 24
mov qword ptr [rsp + 4 ], rcx
mov dword ptr [rsp + 0 ], edx
.loc 13 8 2
if1617:
mov rcx, qword ptr [rsp + 4 ]
.loc 13 3 2
mov ecx, dword ptr [rcx + 4 ]
mov r8, qword ptr [rsp + 4 ]
.loc 13 2 2
mov r8d, dword ptr [r8 + 0 ]
.loc 13 8 10
cmp ecx, r8d
jl if1617_END
mov rcx, qword ptr [rsp + 4 ]
mov r8, qword ptr [rsp + 4 ]
.loc 13 3 2
mov r8d, dword ptr [r8 + 4 ]
mov r9, rdx
mov eax, 2
mul r8d
mov r8d, eax
mov rdx, r9
.loc 13 10 18
mov dword ptr [rcx + 0 ], r8d
mov rcx, qword ptr [rsp + 4 ]
.loc 13 2 2
mov ecx, dword ptr [rcx + 0 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
.loc 13 11 21
mov ecx, ecx
call _V17internal_allocatex_rPh
lea rcx, qword ptr [rax ]
mov rbx, rcx
.loc 13 13 9
mov rcx, rbx
mov r8, qword ptr [rsp + 4 ]
.loc 13 4 2
mov r8, qword ptr [r8 + 8 ]
.loc 13 13 9
mov rdx, r8
mov r8, qword ptr [rsp + 4 ]
.loc 13 3 2
mov r8d, dword ptr [r8 + 4 ]
mov rdi, rdx
mov r9, rdx
mov eax, 4
mul r8d
mov r8d, eax
mov rdx, r9
.loc 13 13 9
mov r8d, r8d
call .memcpy_int_
mov rcx, qword ptr [rsp + 4 ]
.loc 13 17 15
mov qword ptr [rcx + 8 ], rbx
.loc 13 8 2
if1617_END:
mov rcx, qword ptr [rsp + 4 ]
.loc 13 4 2
mov rcx, qword ptr [rcx + 8 ]
mov r8, qword ptr [rsp + 4 ]
.loc 13 3 2
mov r8d, dword ptr [r8 + 4 ]
.loc 13 19 2
lea rcx, qword ptr [rcx + r8 * 4 ]
mov r8d, dword ptr [rsp + 0 ]
mov dword ptr [rcx ], r8d
mov rcx, qword ptr [rsp + 4 ]
.loc 13 20 6
add dword ptr [rcx + 4 ], 1
add rsp, 24
pop rbx
pop rdi
ret 
.Add_int__END:


.cfi_endproc 
Pop_Back_START:
.loc 13 1 1
Pop_Back:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 16
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 13 24 6
add dword ptr [rcx + 4 ], 1
add rsp, 16
ret 
Pop_Back_END:


.cfi_endproc 
.memcpy_int__START:
.loc 13 1 1
.memcpy_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 20
mov qword ptr [rsp + 0 ], rcx
mov qword ptr [rsp + 8 ], rdx
mov dword ptr [rsp + 16 ], r8d
.loc 2 38 17
mov ecx, 0
cmp ecx, dword ptr [rsp + 16 ]
jge while18_END
while18:
mov r8, qword ptr [rsp + 0 ]
.loc 2 39 9
lea r8, qword ptr [r8 + rcx * 4 ]
mov r9, qword ptr [rsp + 8 ]
mov r9d, dword ptr [r9 + rcx * 4 ]
mov dword ptr [r8 ], r9d
.loc 2 38 33
add ecx, 1
cmp ecx, dword ptr [rsp + 16 ]
jge while18_END
jmp while18
while18_END:
add rsp, 20
.loc 2 41 5
ret 
add rsp, 20
ret 
.memcpy_int__END:


.cfi_endproc 
.List_int__START:
.loc 13 1 1
.List_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rsp + 0 ]
.loc 13 2 15
mov dword ptr [rcx + 0 ], 1
mov rcx, qword ptr [rsp + 0 ]
.loc 13 3 11
mov dword ptr [rcx + 4 ], 0
mov rcx, qword ptr [rsp + 0 ]
.loc 13 2 2
mov ecx, dword ptr [rcx + 0 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
.loc 13 4 16
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rcx, qword ptr [rsp + 0 ]
lea r8, qword ptr [rax ]
mov qword ptr [rcx + 8 ], r8
.loc 13 1 1
mov rax, qword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 
.List_int__END:


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
.byte 5
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
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 8
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
.byte 9
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
.byte 4
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 3
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 4
.long _.List_int__START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 13
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Capacity"
.byte 13
.byte 2
.long _int_START-Debug_Info_Start
.byte 0
.byte 6
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 11
_.List_int__START:
.byte 9
.byte 1
.asciz ".List_int_"
.byte 16
.byte 13
.byte 1
.byte 3
.byte 0
.asciz "Capacity"
.byte 13
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 13
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 7
.quad .Add_int__START
.long .Add_int__END-.Add_int__START
.byte 1
.byte 87
.asciz ".Add_int_"
.byte 13
.byte 1
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "Element"
.byte 13
.byte 7
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 4
.asciz "this"
.byte 13
.byte 1
.long _.List_int__START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Capacity"
.byte 13
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 13
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 7
.quad Pop_Back_START
.long Pop_Back_END-Pop_Back_START
.byte 1
.byte 87
.asciz "Pop_Back"
.byte 13
.byte 1
.byte 3
.byte 0
.asciz "Capacity"
.byte 13
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 13
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 7
.quad .memcpy_int__START
.long .memcpy_int__END-.memcpy_int__START
.byte 1
.byte 87
.asciz ".memcpy_int_"
.byte 13
.byte 1
.byte 8
.byte 2
.byte 145
.byte 0
.asciz "dest"
.byte 2
.byte 37
.long _int_START-Debug_Info_Start
.byte 8
.byte 2
.byte 145
.byte 8
.asciz "source"
.byte 2
.byte 37
.long _int_START-Debug_Info_Start
.byte 0
.byte 3
.byte 0
.asciz "Capacity"
.byte 13
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 13
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Template.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
