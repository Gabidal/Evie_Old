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
Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
mov rbx, rcx
push rbx
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
Fruit:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 8 12
mov dword ptr [rcx + 0 ], 4
.loc 1 7 1
ret 
Fruit_END:


.cfi_endproc 
Get_Sugar_START:
.loc 1 18 1
Get_Sugar:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 19 2
mov eax, dword ptr [rcx + 4 ]
ret 
.loc 1 18 1
ret 
Get_Sugar_END:


.cfi_endproc 
is_Banana_START:
.loc 1 22 1
is_Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
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
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
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
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
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
.byte 85
.byte 23
.byte 0
.byte 0
.byte 2
.byte 36
.byte 0
.byte 110
.byte 14
.byte 3
.byte 14
.byte 62
.byte 11
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 3
.byte 52
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
.byte 2
.byte 1
.byte 54
.byte 11
.byte 110
.byte 14
.byte 3
.byte 14
.byte 11
.byte 11
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
.byte 2
.byte 1
.byte 54
.byte 11
.byte 110
.byte 14
.byte 3
.byte 14
.byte 11
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
.byte 9
.byte 46
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
.byte 10
.byte 52
.byte 0
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
_int_START:
.byte 2
.secrel32 i_MANGLE
.secrel32 int_NAME
.byte 5
.byte 4
.byte 2
.byte 3
_short_START:
.byte 2
.secrel32 s_MANGLE
.secrel32 short_NAME
.byte 5
.byte 2
.byte 2
.byte 7
_char_START:
.byte 2
.secrel32 c_MANGLE
.secrel32 char_NAME
.byte 6
.byte 1
.byte 2
.byte 11
_float_START:
.byte 2
.secrel32 f_MANGLE
.secrel32 float_NAME
.byte 4
.byte 4
.byte 2
.byte 15
_double_START:
.byte 2
.secrel32 d_MANGLE
.secrel32 double_NAME
.byte 4
.byte 8
.byte 2
.byte 20
_long_START:
.byte 2
.secrel32 l_MANGLE
.secrel32 long_NAME
.byte 5
.byte 8
.byte 2
.byte 25
_string_START:
.byte 2
.secrel32 string_MANGLE
.secrel32 string_NAME
.byte 6
.byte 1
.byte 2
.byte 29
_Fruit_START:
.byte 6
.byte 1
.secrel32 Fruit_MANGLE
.secrel32 Fruit_NAME
.byte 4
.byte 1
.byte 3
.byte 3
.byte 0
.secrel32 Type_MANGLE
.secrel32 Type_NAME
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 5
.byte 0
.secrel32 this_MANGLE
.secrel32 this_NAME
.byte 1
.byte 7
.long _Fruit_START-Debug_Info_Start
_Banana_START:
.byte 8
.byte 1
.secrel32 Banana_MANGLE
.secrel32 Banana_NAME
.byte 16
.byte 1
.byte 11
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 4
.secrel32 Sugar_MANGLE
.secrel32 Sugar_NAME
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 8
.secrel32 Protein_MANGLE
.secrel32 Protein_NAME
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.secrel32 size_MANGLE
.secrel32 size_NAME
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 0
.byte 4
.quad Get_Sugar_START
.long Get_Sugar_END-Get_Sugar_START
.byte 2
.byte 145
.byte 0
.byte 1
.byte 87
.secrel32 Get_Sugar_MANGLE
.secrel32 Get_Sugar_NAME
.byte 1
.byte 18
.byte 5
.byte 0
.secrel32 b_MANGLE
.secrel32 b_NAME
.byte 1
.byte 18
.long _Banana_START-Debug_Info_Start
.byte 0
.byte 4
.quad is_Banana_START
.long is_Banana_END-is_Banana_START
.byte 2
.byte 145
.byte 0
.byte 1
.byte 87
.secrel32 is_Banana_MANGLE
.secrel32 is_Banana_NAME
.byte 1
.byte 22
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Type.e"
.DIRECTORY:
.asciz "Tests/IO/"
i_MANGLE:
.asciz "i"
int_NAME:
.asciz "int"
s_MANGLE:
.asciz "s"
short_NAME:
.asciz "short"
c_MANGLE:
.asciz "c"
char_NAME:
.asciz "char"
f_MANGLE:
.asciz "f"
float_NAME:
.asciz "float"
d_MANGLE:
.asciz "d"
double_NAME:
.asciz "double"
l_MANGLE:
.asciz "l"
long_NAME:
.asciz "long"
string_MANGLE:
.asciz "string"
string_NAME:
.asciz "string"
Fruit_MANGLE:
.asciz "Fruit"
Fruit_NAME:
.asciz "Fruit"
Type_MANGLE:
.asciz "Type"
Type_NAME:
.asciz "Type"
this_MANGLE:
.asciz "this"
this_NAME:
.asciz "this"
Banana_MANGLE:
.asciz "Banana"
Banana_NAME:
.asciz "Banana"
Sugar_MANGLE:
.asciz "Sugar"
Sugar_NAME:
.asciz "Sugar"
Protein_MANGLE:
.asciz "Protein"
Protein_NAME:
.asciz "Protein"
size_MANGLE:
.asciz "size"
size_NAME:
.asciz "size"
Get_Sugar_MANGLE:
.asciz "Get_Sugar"
Get_Sugar_NAME:
.asciz "Get_Sugar"
b_MANGLE:
.asciz "b"
b_NAME:
.asciz "b"
is_Banana_MANGLE:
.asciz "is_Banana"
is_Banana_NAME:
.asciz "is_Banana"
f_NAME:
.asciz "f"
Start_Test_NAME:
.asciz "Start_Test"
x_MANGLE:
.asciz "x"
x_NAME:
.asciz "x"
main_NAME:
.asciz "main"
.section .LINE_TABLE
.LINE_TABLE:
