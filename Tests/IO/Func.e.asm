.intel_syntax noprefix
.section .text
Code_Start:
.global Start_Test
.global main
main_START:
main:
call Start_Test
mov eax, 1
ret 
ret 
main_END:


foo_START:
foo:
mov eax, 5
ret 
ret 
foo_END:


Start_Test_START:
Start_Test:
lea rcx, qword ptr [foo ]
mov rcx, rcx
call rcx
mov eax, eax
ret 
ret 
Start_Test_END:


Code_End:
.file 1 "Tests/IO/Func.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
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
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.secrel32 main_NAME
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 2
.quad foo_START
.long foo_END-foo_START
.byte 1
.byte 87
.secrel32 foo_NAME
.byte 1
.byte 9
.long _int_START-Debug_Info_Start
.byte 2
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.secrel32 Start_Test_NAME
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.secrel32 fuz_NAME
.byte 1
.byte 14
.quad _int_START-Debug_Info_Start
.byte 0
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
.asciz "Tests/IO/Func.e"
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
main_NAME:
.asciz "main"
foo_NAME:
.asciz "foo"
Start_Test_NAME:
.asciz "Start_Test"
fuz_NAME:
.asciz "fuz"
func_NAME:
.asciz "func_NAME"
type_NAME:
.asciz "type_NAME"
.section .LINE_TABLE
.LINE_TABLE:
