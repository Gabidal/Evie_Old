.intel_syntax noprefix
.file 1 "Tests/IO/Ptr.e"
.file 2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"
.file 4 "Tests/IO/../../IO/win32.asm.obj"
.file 5 "Tests/IO/../../IO/win32.asm"
.file 6 "Tests/IO/../../IO/STD.e"
.file 7 "Tests/IO/../../IO/List.e"
Code_Start:
.global main
.global Start_Test
.section .text
Start_Test_START:
.loc 1 5 1
Start_Test:
.cfi_startproc 
.cfi_def_cfa_offset 16
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
ret 
Start_Test_END:


.cfi_endproc 
main_START:
.loc 1 24 1
main:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 25 2
call Start_Test
.loc 1 26 2
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
_Static_Cast_START:
.byte 2
.asciz "Static_Cast"
.byte 1
.byte 8
.byte 1
.byte 3
.byte 4
.quad Start_Test_START
.long Start_Test_END-Start_Test_START
.byte 1
.byte 87
.asciz "Start_Test"
.asciz "Start_Test"
.byte 1
.byte 5
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "val"
.byte 1
.byte 6
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 4
.asciz "a"
.byte 1
.byte 7
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 12
.asciz "b"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 20
.asciz "c"
.byte 1
.byte 11
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 28
.asciz "d"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 36
.asciz "e"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "f"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "Normal_Cast_needing_Var"
.byte 1
.byte 17
.long _int_START-Debug_Info_Start
.byte 5
.byte 2
.byte 145
.byte 0
.asciz "Dynamic_needing_Var"
.byte 1
.byte 20
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
.byte 24
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Ptr.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
