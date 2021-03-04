.intel_syntax noprefix
.file 1 "Tests/IO/Ptr.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
.section .text
Code_Start:
.global main
.global Start_Test
Start_Test_START:
.loc 1 5 1
.cfi_startproc 
.cfi_def_cfa_offset 16
Start_Test:
sub rsp, 44
.loc 1 6 10
mov dword ptr [rsp ], 10
.loc 1 7 12
lea rcx, qword ptr [rsp ]
mov qword ptr [rsp + 4 ], rcx
.loc 1 8 16
lea rcx, qword ptr [rsp + 4 ]
mov qword ptr [rsp + 12 ], rcx
mov rcx, qword ptr [rsp + 4 ]
mov ecx, dword ptr [rcx ]
.loc 1 9 2
mov eax, ecx
add rsp, 44
ret 
.loc 1 11 20
lea rcx, qword ptr [rsp + 12 ]
mov qword ptr [rsp + 20 ], rcx
.loc 1 12 24
lea rcx, qword ptr [rsp + 20 ]
mov qword ptr [rsp + 28 ], rcx
.loc 1 13 28
lea rcx, qword ptr [rsp + 28 ]
mov qword ptr [rsp + 36 ], rcx
.loc 1 14 32
lea rcx, qword ptr [rsp + 36 ]
mov rcx, rcx
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov ecx, dword ptr [rcx ]
.loc 1 15 2
mov eax, ecx
add rsp, 44
ret 
.loc 1 17 34
mov rcx, 123
mov ecx, dword ptr [rcx ]
.loc 1 18 2
mov eax, ecx
add rsp, 44
ret 
.loc 1 20 34
mov rcx, 1234
mov rcx, qword ptr [rcx ]
mov ecx, dword ptr [rcx ]
.loc 1 21 2
mov eax, ecx
add rsp, 44
ret 
add rsp, 44
.loc 1 5 1
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 24 1
.cfi_startproc 
.cfi_def_cfa_offset 16
main:
.loc 1 25 2
call Start_Test
.loc 1 26 2
mov eax, 1
ret 
.loc 1 24 1
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
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 2
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 4
.byte 36
.byte 0
.byte 3
.byte 14
.byte 62
.byte 11
.byte 11
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
.word 666
.secrel32 .FILE_NAME
.secrel32 .LINE_TABLE
.secrel32 .DIRECTORY
.quad Code_Start
.long Code_End-Code_Start
.byte 2
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.secrel32 Start_Test_NAME
.byte 1
.byte 5
.long _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.secrel32 val_NAME
.byte 1
.byte 6
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 4
.secrel32 a_NAME
.byte 1
.byte 7
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 12
.secrel32 b_NAME
.byte 1
.byte 8
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 20
.secrel32 c_NAME
.byte 1
.byte 11
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 28
.secrel32 d_NAME
.byte 1
.byte 12
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 36
.secrel32 e_NAME
.byte 1
.byte 13
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.secrel32 f_NAME
.byte 1
.byte 14
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.secrel32 Normal_Cast_needing_Var_NAME
.byte 1
.byte 17
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.secrel32 Dynamic_needing_Var_NAME
.byte 1
.byte 20
.quad _int_START-Debug_Info_Start
.byte 0
.byte 2
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.secrel32 main_NAME
.byte 1
.byte 24
.long _int_START-Debug_Info_Start
_int_START:
.byte 4
.secrel32 int_NAME
.byte 5
.byte 4
_short_START:
.byte 4
.secrel32 short_NAME
.byte 5
.byte 2
_char_START:
.byte 4
.secrel32 char_NAME
.byte 6
.byte 1
_float_START:
.byte 4
.secrel32 float_NAME
.byte 4
.byte 4
_double_START:
.byte 4
.secrel32 double_NAME
.byte 4
.byte 8
_long_START:
.byte 4
.secrel32 long_NAME
.byte 5
.byte 8
_string_START:
.byte 4
.secrel32 string_NAME
.byte 6
.byte 1
_Static_Cast_START:
.byte 4
.byte 1
.secrel32 Static_Cast_NAME
.byte 8
.byte 1
.byte 3
_func_START:
.byte 4
.secrel32 func_NAME
.byte 5
.byte 0
_type_START:
.byte 4
.secrel32 type_NAME
.byte 5
.byte 0
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Ptr.e"
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
Static_Cast_NAME:
.asciz "Static_Cast"
Start_Test_NAME:
.asciz "Start_Test"
val_NAME:
.asciz "val"
a_NAME:
.asciz "a"
b_NAME:
.asciz "b"
c_NAME:
.asciz "c"
d_NAME:
.asciz "d"
e_NAME:
.asciz "e"
f_NAME:
.asciz "f"
Normal_Cast_needing_Var_NAME:
.asciz "Normal_Cast_needing_Var"
Dynamic_needing_Var_NAME:
.asciz "Dynamic_needing_Var"
main_NAME:
.asciz "main"
func_NAME:
.asciz "func_NAME"
type_NAME:
.asciz "type_NAME"
.section .LINE_TABLE
.LINE_TABLE:
