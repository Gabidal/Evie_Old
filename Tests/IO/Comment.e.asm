.intel_syntax noprefix
.file 1 "Tests/IO/Comment.e"
.file 2 "C:\Users\GabenRTX\.Repos/Evie/IO/cstd.e"
.file 3 "https://github.com/Gabidal/Evie/IO/cstd.e"
.file 4 "sys.e"
.file 5 "win32.asm.obj"
.file 6 "asm.h"
.file 7 "win32.asm"
.file 8 "STD.e"
.file 9 "List.e"
Code_Start:
.global main
.global Start_Test
.section .text
Start_Test_START:
.loc 1 10 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 11 2
mov eax, 1
ret 
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 14 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 15 2
mov eax, 1
ret 
ret 
main_END:


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
.byte 5
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
.byte 6
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
.byte 7
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
.byte 3
.byte 3
_short_START:
.byte 2
.asciz "short"
.byte 5
.byte 2
.byte 3
.byte 7
_char_START:
.byte 2
.asciz "char"
.byte 6
.byte 1
.byte 3
.byte 11
_float_START:
.byte 2
.asciz "float"
.byte 4
.byte 4
.byte 3
.byte 15
_double_START:
.byte 2
.asciz "double"
.byte 4
.byte 8
.byte 3
.byte 20
_long_START:
.byte 2
.asciz "long"
.byte 5
.byte 8
.byte 3
.byte 25
_string_START:
.byte 2
.asciz "string"
.byte 6
.byte 1
.byte 3
.byte 29
.byte 5
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 10
.byte 5
.quad main_START
.long main_END-main_START
.byte 1
.byte 87
.asciz "main"
.asciz "main"
.byte 1
.byte 14
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
