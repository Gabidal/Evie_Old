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
.loc 1 11 1
.cfi_startproc 
.cfi_def_cfa_offset 16
Banana:
push rbx
mov rbx, rcx
mov rcx, rbx
call Fruit
.loc 1 12 12
mov dword ptr [rbx + 4 ], 1
.loc 1 13 14
mov dword ptr [rbx + 8 ], 2
.loc 1 14 11
mov dword ptr [rbx + 12 ], 6
.loc 1 15 7
mov dword ptr [rbx + 0 ], 5
.loc 1 11 1
mov rax, rbx
pop rbx
ret 
pop rbx
ret 
Banana_END:


.cfi_endproc 
Fruit_START:
.loc 1 7 1
.cfi_startproc 
.cfi_def_cfa_offset 16
Fruit:
.loc 1 8 12
mov dword ptr [rcx + 0 ], 4
.loc 1 7 1
ret 
Fruit_END:


.cfi_endproc 
Get_Sugar_START:
.loc 1 18 1
.cfi_startproc 
.cfi_def_cfa_offset 16
Get_Sugar:
.loc 1 19 2
mov eax, dword ptr [rcx + 4 ]
ret 
.loc 1 18 1
ret 
Get_Sugar_END:


.cfi_endproc 
is_Banana_START:
.loc 1 22 1
.cfi_startproc 
.cfi_def_cfa_offset 16
is_Banana:
.loc 1 23 9
mov rcx, rcx
call Get_Sugar
mov eax, eax
ret 
.loc 1 22 1
ret 
is_Banana_END:


.cfi_endproc 
Start_Test_START:
.loc 1 26 1
.cfi_startproc 
.cfi_def_cfa_offset 16
Start_Test:
sub rsp, 16
lea rcx, qword ptr [rsp ]
.loc 1 27 11
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
.loc 1 28 9
mov rcx, rcx
call is_Banana
mov eax, eax
add rsp, 16
ret 
add rsp, 16
.loc 1 26 1
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 31 1
.cfi_startproc 
.cfi_def_cfa_offset 16
main:
.loc 1 32 2
mov eax, 1
ret 
.loc 1 31 1
ret 
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
.byte 18
.byte 6
.byte 0
.byte 0
.byte 2
.byte 0
.byte 110
.byte 14
.byte 3
.byte 14
.byte 62
.byte 11
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
.byte 0
.byte 2
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
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
.byte 4
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
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 5
.byte 0
.byte 2
.byte 24
.byte 110
.byte 14
.byte 3
.byte 14
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
.byte 6
.byte 1
.byte 54
.byte 11
.byte 110
.byte 14
.byte 3
.byte 14
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
.byte 7
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
.byte 14
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
.byte 8
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 9
.byte 0
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 0
.section .debug_info
.long Debug_Info_End-Debug_Info_Start
Debug_Info_Start:
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
.byte 8
.quad Fruit_START
.long Fruit_END-Fruit_START
.byte 1
.byte 87
.secrel32 Fruit_NAME
.byte 1
.byte 7
.long _Fruit_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.secrel32 this_NAME
.byte 1
.byte 7
.quad _Fruit_START-Debug_Info_Start
.byte 0
.byte 5
.quad Get_Sugar_START
.long Get_Sugar_END-Get_Sugar_START
.byte 1
.byte 87
.secrel32 Get_Sugar_NAME
.byte 1
.byte 18
.byte 6
.byte 2
.byte 145
.byte 0
.secrel32 b_NAME
.byte 1
.byte 18
.quad _Banana_START-Debug_Info_Start
.byte 0
.byte 5
.quad is_Banana_START
.long is_Banana_END-is_Banana_START
.byte 1
.byte 87
.secrel32 is_Banana_NAME
.byte 1
.byte 22
.byte 6
.byte 2
.byte 145
.byte 0
.secrel32 f_NAME
.byte 1
.byte 22
.quad _Fruit_START-Debug_Info_Start
.byte 0
.byte 9
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.secrel32 Start_Test_NAME
.byte 1
.byte 26
.byte 4
.byte 2
.byte 145
.byte 0
.secrel32 x_NAME
.byte 1
.byte 27
.quad _Banana_START-Debug_Info_Start
.byte 0
.byte 10
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.secrel32 main_NAME
.byte 1
.byte 31
.byte 8
.quad Banana_START
.long Banana_END-Banana_START
.byte 1
.byte 87
.secrel32 Banana_NAME
.byte 1
.byte 11
.long _Banana_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.secrel32 this_NAME
.byte 1
.byte 11
.quad _Banana_START-Debug_Info_Start
.byte 0
_int_START:
.byte 3
.secrel32 int_NAME
.byte 5
.byte 4
_short_START:
.byte 3
.secrel32 short_NAME
.byte 5
.byte 2
_char_START:
.byte 3
.secrel32 char_NAME
.byte 6
.byte 1
_float_START:
.byte 3
.secrel32 float_NAME
.byte 4
.byte 4
_double_START:
.byte 3
.secrel32 double_NAME
.byte 4
.byte 8
_long_START:
.byte 3
.secrel32 long_NAME
.byte 5
.byte 8
_string_START:
.byte 3
.secrel32 string_NAME
.byte 6
.byte 1
_Fruit_START:
.byte 7
.byte 1
.secrel32 Fruit_NAME
.byte 4
.byte 1
.byte 3
.byte 7
.long Type_NAME
.quad _int_START-Debug_Info_Start
.byte 1
.byte 4
.byte 0
.byte 1
_Banana_START:
.byte 7
.byte 1
.secrel32 Banana_NAME
.byte 16
.byte 1
.byte 11
.byte 7
.long Type_NAME
.quad _int_START-Debug_Info_Start
.byte 1
.byte 4
.byte 0
.byte 1
.byte 7
.long Sugar_NAME
.quad _int_START-Debug_Info_Start
.byte 1
.byte 12
.byte 4
.byte 1
.byte 7
.long Protein_NAME
.quad _int_START-Debug_Info_Start
.byte 1
.byte 13
.byte 8
.byte 1
.byte 7
.long size_NAME
.quad _int_START-Debug_Info_Start
.byte 1
.byte 14
.byte 12
.byte 1
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Type.e"
.DIRECTORY:
.asciz "Tests/IO/"
int_NAME:
.asciz "int"
size_NAME:
.asciz "size"
short_NAME:
.asciz "short"
char_NAME:
.asciz "char"
float_NAME:
.asciz "float"
format_NAME:
.asciz "format"
double_NAME:
.asciz "double"
long_NAME:
.asciz "long"
string_NAME:
.asciz "string"
Fruit_NAME:
.asciz "Fruit"
Type_NAME:
.asciz "Type"
this_NAME:
.asciz "this"
Banana_NAME:
.asciz "Banana"
Sugar_NAME:
.asciz "Sugar"
Protein_NAME:
.asciz "Protein"
Get_Sugar_NAME:
.asciz "Get_Sugar"
b_NAME:
.asciz "b"
is_Banana_NAME:
.asciz "is_Banana"
f_NAME:
.asciz "f"
Start_Test_NAME:
.asciz "Start_Test"
x_NAME:
.asciz "x"
main_NAME:
.asciz "main"
func_NAME:
.asciz "func_NAME"
type_NAME:
.asciz "type_NAME"
.section .LINE_TABLE
.LINE_TABLE:
