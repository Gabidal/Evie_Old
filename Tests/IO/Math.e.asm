.intel_syntax noprefix
.file 1 "Tests/IO/Math.e"
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
.loc 1 7 1
.cfi_startproc 
.cfi_def_cfa_offset 16
Start_Test:
.loc 1 16 2
mov eax, -6
ret 
.loc 1 7 1
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 23 1
.cfi_startproc 
.cfi_def_cfa_offset 16
main:
.loc 1 24 2
mov eax, 1
ret 
.loc 1 23 1
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
.byte 7
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.secrel32 Start_Test_NAME
.byte 1
.byte 7
.byte 7
.quad main_START
.long main_END-main_START
.secrel32 main_NAME
.byte 1
.byte 23
_int_START:
.byte 3
.secrel32 i_NAME
.secrel32 int_NAME
.byte 5
_short_START:
.byte 3
.secrel32 s_NAME
.secrel32 short_NAME
.byte 5
_char_START:
.byte 3
.secrel32 c_NAME
.secrel32 char_NAME
.byte 6
_float_START:
.byte 3
.secrel32 f_NAME
.secrel32 float_NAME
.byte 4
_double_START:
.byte 3
.secrel32 d_NAME
.secrel32 double_NAME
.byte 4
_long_START:
.byte 3
.secrel32 l_NAME
.secrel32 long_NAME
.byte 5
_string_START:
.byte 3
.secrel32 string_NAME
.secrel32 string_NAME
.byte 6
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Math.e"
.DIRECTORY:
.asciz "Tests/IO/"
i_NAME:
.asciz "i"
int_NAME:
.asciz "int"
t_NAME:
.asciz "t"
size_NAME:
.asciz "size"
s_NAME:
.asciz "s"
short_NAME:
.asciz "short"
c_NAME:
.asciz "c"
char_NAME:
.asciz "char"
f_NAME:
.asciz "f"
float_NAME:
.asciz "float"
format_NAME:
.asciz "format"
d_NAME:
.asciz "d"
double_NAME:
.asciz "double"
l_NAME:
.asciz "l"
long_NAME:
.asciz "long"
string_NAME:
.asciz "string"
Start_Test_NAME:
.asciz "Start_Test"
main_NAME:
.asciz "main"
.section .LINE_TABLE
.LINE_TABLE:
