.intel_syntax noprefix
.file 1 "Tests/IO/Template.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
.file 7 "STD.e"
.file 8 "List.e"
Code_Start:
.global main
.global Start_Test
.section .text
Start_Test_START:
.loc 1 3 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 48
lea rcx, qword ptr [rsp + 16 ]
.loc 1 4 14
mov rcx, rcx
call .List_int__
mov rcx, qword ptr [rsp + 16 + 8 ]
.loc 1 5 4
lea rcx, qword ptr [rcx + 1 * 4 ]
mov dword ptr [rcx ], 5
lea rcx, qword ptr [rsp + 16 ]
.loc 1 6 4
mov rcx, rcx
mov edx, 2
call .Add_int__
.loc 8 4 2
mov rcx, qword ptr [rsp + 16 + 8 ]
.loc 1 7 11
lea rcx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rcx ]
add rsp, 48
ret 
add rsp, 48
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 10 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 11 2
call Start_Test
.loc 1 12 2
mov eax, 1
ret 
ret 
main_END:


.cfi_endproc 
.Add_int___START:
.loc 8 1 1
.Add_int__:
.cfi_startproc 
.cfi_def_cfa_offset 16
push rbx
sub rsp, 12
mov qword ptr [rsp + 32 ], rcx
mov dword ptr [rsp + 28 ], edx
.loc 8 8 2
if01:
mov rcx, qword ptr [rsp + 32 ]
.loc 8 3 2
mov ecx, dword ptr [rcx + 4 ]
.loc 8 8 12
add ecx, 4
mov r8, qword ptr [rsp + 32 ]
.loc 8 2 2
mov r8d, dword ptr [r8 + 0 ]
.loc 8 8 19
cmp ecx, r8d
jle if01_END
mov rcx, qword ptr [rsp + 32 ]
mov r8, qword ptr [rsp + 32 ]
.loc 8 3 2
mov r8d, dword ptr [r8 + 4 ]
mov eax, 2
mul r8d
mov r8d, eax
.loc 8 10 18
mov dword ptr [rcx + 0 ], r8d
mov rcx, qword ptr [rsp + 32 ]
.loc 8 2 2
mov ecx, dword ptr [rcx + 0 ]
mov eax, 4
mul ecx
mov ecx, eax
.loc 8 11 21
mov ecx, ecx
call _Z8allocatei
mov rbx, rax
.loc 8 13 9
mov rcx, rbx
mov r8, qword ptr [rsp + 32 ]
.loc 8 4 2
mov r8, qword ptr [r8 + 8 ]
.loc 8 13 9
mov rdx, r8
mov r8, qword ptr [rsp + 32 ]
.loc 8 3 2
mov r8d, dword ptr [r8 + 4 ]
mov eax, 4
mul r8d
mov r8d, eax
.loc 8 13 9
mov r8d, r8d
call .memcpy_int__
mov rcx, qword ptr [rsp + 32 ]
.loc 8 14 15
mov qword ptr [rcx + 8 ], rbx
.loc 8 8 2
if01_END:
mov rcx, qword ptr [rsp + 32 ]
.loc 8 4 2
mov rcx, qword ptr [rcx + 8 ]
mov r8, qword ptr [rsp + 32 ]
.loc 8 3 2
mov r8d, dword ptr [r8 + 4 ]
.loc 8 16 2
lea rcx, qword ptr [rcx + r8 * 4 ]
mov r8d, dword ptr [rsp + 28 ]
mov dword ptr [rcx ], r8d
mov rcx, qword ptr [rsp + 32 ]
.loc 8 17 6
add dword ptr [rcx + 4 ], 1
add rsp, 12
pop rbx
ret 
.Add_int___END:


.cfi_endproc 
.memcpy_int___START:
.loc 8 1 1
.memcpy_int__:
.cfi_startproc 
.cfi_def_cfa_offset 16
mov qword ptr [rsp + 8 ], rcx
mov qword ptr [rsp + 16 ], rdx
mov dword ptr [rsp + 24 ], r8d
.loc 2 38 17
mov ecx, 0
cmp ecx, dword ptr [rsp + 24 ]
jge while2_END
while2:
.loc 2 39 9
lea r8, qword ptr [rsp + 8 + rcx * 4 ]
mov r9d, dword ptr [rsp + 16 + rcx * 4 ]
mov dword ptr [r8 ], r9d
.loc 2 38 33
add ecx, 1
cmp ecx, dword ptr [rsp + 24 ]
jge while2_END
jmp while2
while2_END:
.loc 2 41 5
ret 
ret 
.memcpy_int___END:


.cfi_endproc 
.List_int___START:
.loc 8 1 1
.List_int__:
.cfi_startproc 
.cfi_def_cfa_offset 16
push rbx
sub rsp, 4
mov qword ptr [rsp + 20 ], rcx
mov rcx, qword ptr [rsp + 20 ]
.loc 8 2 15
mov dword ptr [rcx + 0 ], 1
mov rcx, qword ptr [rsp + 20 ]
.loc 8 3 11
mov dword ptr [rcx + 4 ], 0
mov rbx, qword ptr [rsp + 20 ]
mov rcx, qword ptr [rsp + 20 ]
.loc 8 2 2
mov ecx, dword ptr [rcx + 0 ]
mov eax, 4
mul ecx
mov ecx, eax
.loc 8 4 16
mov ecx, ecx
call _Z8allocatei
mov qword ptr [rbx + 8 ], rax
.loc 8 1 1
mov rax, qword ptr [rsp + 20 ]
add rsp, 4
pop rbx
ret 
add rsp, 4
pop rbx
ret 
.List_int___END:


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
.byte 8
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
.byte 16
.asciz "a"
.byte 1
.byte 4
.long _.List_int___START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 8
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 8
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Capacity"
.byte 8
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
.byte 10
_.List_int___START:
.byte 7
.byte 1
.asciz ".List_int__"
.byte 16
.byte 8
.byte 1
.byte 3
.byte 0
.asciz "Capacity"
.byte 8
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 8
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 8
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 8
.quad .Add_int___START
.long .Add_int___END-.Add_int___START
.byte 1
.byte 87
.asciz ".Add_int__"
.byte 8
.byte 1
.byte 9
.byte 2
.byte 145
.byte 20
.asciz "Element"
.byte 8
.byte 7
.long _int_START-Debug_Info_Start
.byte 9
.byte 2
.byte 145
.byte 24
.asciz "this"
.byte 8
.byte 1
.long _.List_int___START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Capacity"
.byte 8
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 8
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 8
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 8
.quad .memcpy_int___START
.long .memcpy_int___END-.memcpy_int___START
.byte 1
.byte 87
.asciz ".memcpy_int__"
.byte 8
.byte 1
.byte 9
.byte 2
.byte 145
.byte 8
.asciz "dest"
.byte 2
.byte 37
.long _int_START-Debug_Info_Start
.byte 9
.byte 2
.byte 145
.byte 16
.asciz "source"
.byte 2
.byte 37
.long _int_START-Debug_Info_Start
.byte 0
.byte 3
.byte 0
.asciz "Capacity"
.byte 8
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Size"
.byte 8
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Array"
.byte 8
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
