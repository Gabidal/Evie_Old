.intel_syntax noprefix
.file 1 "Tests/IO/Type.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
.section .text
Code_Start:
.global main
.global Start_Test
Banana_START:
Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 11 1
mov rbx, rcx
push rbx
mov rcx, rbx
call Fruit
mov dword ptr [rbx + 4 ], 1
.loc 1 12 12
mov dword ptr [rbx + 8 ], 2
.loc 1 13 14
mov dword ptr [rbx + 12 ], 6
.loc 1 14 11
mov dword ptr [rbx + 0 ], 5
.loc 1 15 7
mov rax, rbx
.loc 1 11 1
pop rbx
ret 
pop rbx
ret 
Banana_END:


.cfi_endproc 
Fruit_START:
Fruit:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 7 1
mov dword ptr [rcx + 0 ], 4
.loc 1 8 12
ret 
.loc 1 7 1
Fruit_END:


.cfi_endproc 
Get_Sugar_START:
Get_Sugar:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 18 1
sub rsp, 8
mov eax, dword ptr [rcx + 4 ]
.loc 1 19 2
add rsp, 8
ret 
add rsp, 8
ret 
.loc 1 18 1
Get_Sugar_END:


.cfi_endproc 
is_Banana_START:
is_Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 22 1
sub rsp, 8
mov rcx, rcx
.loc 1 23 9
call Get_Sugar
mov eax, eax
add rsp, 8
ret 
add rsp, 8
ret 
.loc 1 22 1
is_Banana_END:


.cfi_endproc 
Start_Test_START:
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 26 1
sub rsp, 32
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 1 27 11
call Banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 1 28 9
call is_Banana
mov eax, eax
add rsp, 32
ret 
add rsp, 32
ret 
.loc 1 26 1
Start_Test_END:


.cfi_endproc 
main_START:
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 31 1
mov eax, 1
.loc 1 32 2
ret 
ret 
.loc 1 31 1
main_END:


.cfi_endproc 
Code_End:
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
.byte 73
.byte 19
.byte 0
.byte 0
.byte 8
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
.byte 9
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
.byte 10
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
.byte 11
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
_Fruit_START:
.byte 6
.byte 1
.asciz "Fruit"
.byte 4
.byte 1
.byte 3
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "this"
.byte 1
.byte 7
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
_Banana_START:
.byte 8
.byte 1
.asciz "Banana"
.byte 16
.byte 1
.byte 11
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 0
.byte 4
.quad Get_Sugar_START
.long Get_Sugar_END-Get_Sugar_START
.byte 1
.byte 87
.asciz "Get_Sugar"
.byte 1
.byte 18
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "b"
.byte 1
.byte 18
.long _Banana_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 0
.byte 4
.quad is_Banana_START
.long is_Banana_END-is_Banana_START
.byte 1
.byte 87
.asciz "is_Banana"
.byte 1
.byte 22
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 9
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 26
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "x"
.byte 1
.byte 27
.long _Banana_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 0
.byte 11
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 31
.byte 3
.byte 0
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 4
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Type.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
