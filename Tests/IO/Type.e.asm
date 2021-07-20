.intel_syntax noprefix
.file 1 "Tests/IO/Type.e"
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
.file 13 "Tests/IO/../../IO/Memory.e"
.file 14 "Tests/IO/../../IO/List.e"
Code_Start:
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv_START:
.loc 1 26 1
_Z10Start_Testv:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 152
.loc 1 27 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 27 2
mov qword ptr [rsp + 24 ], rcx
.loc 1 11 1
mov rcx, qword ptr [rsp + 24 ]
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 11 1
mov qword ptr [rsp + 32 ], rcx
mov rcx, qword ptr [rsp + 24 ]
mov qword ptr [rsp + 32 ], rcx
mov rcx, qword ptr [rsp + 32 ]
.loc 1 8 12
mov dword ptr [rcx + 8 ], 4
.loc 1 11 1
Return_Here_4:
mov rcx, qword ptr [rsp + 24 ]
.loc 1 12 12
mov dword ptr [rcx + 12 ], 1
mov rcx, qword ptr [rsp + 24 ]
.loc 1 13 14
mov dword ptr [rcx + 16 ], 2
mov rcx, qword ptr [rsp + 24 ]
.loc 1 14 11
mov dword ptr [rcx + 20 ], 6
mov rcx, qword ptr [rsp + 24 ]
.loc 1 15 7
mov dword ptr [rcx + 8 ], 5
jmp Return_Here_3
.loc 1 27 11
Return_Here_3:
.loc 1 28 18
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 28 18
mov qword ptr [rsp + 40 ], rcx
.loc 1 23 18
mov rcx, qword ptr [rsp + 40 ]
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 23 18
mov qword ptr [rsp + 48 ], rcx
mov rcx, qword ptr [rsp + 40 ]
mov qword ptr [rsp + 48 ], rcx
jmp Return_Here_6
Return_Here_6:
mov rcx, qword ptr [rsp + 48 ]
.loc 1 12 2
mov ecx, dword ptr [rcx + 12 ]
.loc 1 23 2
mov ecx, ecx
jmp Return_Here_5
.loc 1 28 9
Return_Here_5:
mov eax, ecx
add rsp, 152
ret 
add rsp, 152
ret 
_Z10Start_Testv_END:


.cfi_endproc 
_Z4mainv_START:
.loc 1 31 1
_Z4mainv:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 112
.loc 1 27 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 27 2
mov qword ptr [rsp + 24 ], rcx
.loc 1 11 1
mov rcx, qword ptr [rsp + 24 ]
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 11 1
mov qword ptr [rsp + 32 ], rcx
mov rcx, qword ptr [rsp + 24 ]
mov qword ptr [rsp + 32 ], rcx
mov rcx, qword ptr [rsp + 32 ]
.loc 1 8 12
mov dword ptr [rcx + 8 ], 4
.loc 1 11 1
Return_Here_8:
mov rcx, qword ptr [rsp + 24 ]
.loc 1 12 12
mov dword ptr [rcx + 12 ], 1
mov rcx, qword ptr [rsp + 24 ]
.loc 1 13 14
mov dword ptr [rcx + 16 ], 2
mov rcx, qword ptr [rsp + 24 ]
.loc 1 14 11
mov dword ptr [rcx + 20 ], 6
mov rcx, qword ptr [rsp + 24 ]
.loc 1 15 7
mov dword ptr [rcx + 8 ], 5
jmp Return_Here_9
.loc 1 27 11
Return_Here_9:
.loc 1 28 18
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 28 18
mov qword ptr [rsp + 40 ], rcx
.loc 1 23 18
mov rcx, qword ptr [rsp + 40 ]
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 23 18
mov qword ptr [rsp + 48 ], rcx
mov rcx, qword ptr [rsp + 40 ]
mov qword ptr [rsp + 48 ], rcx
jmp Return_Here_10
Return_Here_10:
mov rcx, qword ptr [rsp + 48 ]
.loc 1 12 2
mov ecx, dword ptr [rcx + 12 ]
.loc 1 23 2
mov ecx, ecx
jmp Return_Here_11
.loc 1 28 9
Return_Here_11:
jmp Return_Here_7
.loc 1 32 2
Return_Here_7:
.loc 1 33 2
mov eax, 1
add rsp, 112
ret 
add rsp, 112
ret 
_Z4mainv_END:


.cfi_endproc 
_ZN6Banana10DestructorEP6Banana_START:
.loc 1 11 1
_ZN6Banana10DestructorEP6Banana:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
.loc 14 1 1
if_0:
cmp qword ptr [rsp + 0 ], 0
je if_0_END
mov rcx, qword ptr [rsp + 0 ]
.loc 1 11 1
mov rcx, qword ptr [rcx + 0 ]
.loc 14 1 26
sub rcx, 1
cmp rcx, 1
jge if_0_END
.loc 14 2 19
mov rcx, qword ptr [rsp + 0 ]
add qword ptr [rcx + 0 ], 1
mov qword ptr [rsp ], rcx
mov rcx, qword ptr [rsp + 0 ]
mov qword ptr [rsp ], rcx
.loc 13 18 2
mov rcx, qword ptr [rsp ]
mov edx, r8d
call _V19internal_deallocatePhx
.loc 14 2 1
Return_Here_0:
.loc 14 1 11
mov rcx, qword ptr [rsp ]
call _ZN6Banana10DestructorEP6Banana
if_0_END:
add rsp, 8
ret 
_ZN6Banana10DestructorEP6Banana_END:


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
.byte 2
.byte 0
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
.byte 5
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
.byte 73
.byte 19
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
_BYTE_POINTER_START:
.byte 4
.byte 1
.asciz "BYTE_POINTER"
.byte 8
.byte 13
.byte 1
_Fruit_START:
.byte 5
.byte 1
.asciz "Fruit"
.byte 4
.byte 1
.byte 3
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 3
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
_Banana_START:
.byte 9
.byte 1
.asciz "Banana"
.byte 16
.byte 1
.byte 11
.long _Fruit_START-Debug_Info_Start
.byte 3
.byte 0
.asciz "Reference_Count"
.byte 1
.byte 11
.long _long_START-Debug_Info_Start
.byte 3
.byte 8
.asciz "Type"
.byte 1
.byte 4
.long _int_START-Debug_Info_Start
.byte 3
.byte 12
.asciz "Sugar"
.byte 1
.byte 12
.long _int_START-Debug_Info_Start
.byte 3
.byte 16
.asciz "Protein"
.byte 1
.byte 13
.long _int_START-Debug_Info_Start
.byte 3
.byte 20
.asciz "size"
.byte 1
.byte 14
.long _int_START-Debug_Info_Start
.byte 0
.byte 11
.quad _Z10Start_Testv_START
.long _Z10Start_Testv_END-_Z10Start_Testv_START
.byte 1
.byte 87
.asciz "_Z10Start_Testv"
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
.byte 10
.byte 2
.byte 145
.byte 24
.asciz "this_3"
.byte 1
.byte 11
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 32
.asciz "this_2_3"
.byte 1
.byte 7
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "Return_Value4"
.byte 1
.byte 28
.long _int_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 40
.asciz "f_4"
.byte 1
.byte 22
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "Return_Value1_4"
.byte 1
.byte 23
.long _int_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 48
.asciz "b_1_4"
.byte 1
.byte 18
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691023495168"
.byte 1
.byte 27
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691023502656"
.byte 1
.byte 11
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691023527616"
.byte 1
.byte 28
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691023518464"
.byte 1
.byte 23
.long _Banana_START-Debug_Info_Start
.byte 0
.byte 11
.quad _Z4mainv_START
.long _Z4mainv_END-_Z4mainv_START
.byte 1
.byte 87
.asciz "_Z4mainv"
.asciz "main"
.byte 1
.byte 31
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "x_5"
.byte 1
.byte 27
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 24
.asciz "this_3_5"
.byte 1
.byte 11
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 32
.asciz "this_2_3_5"
.byte 1
.byte 7
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "Return_Value4_5"
.byte 1
.byte 28
.long _int_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 40
.asciz "f_4_5"
.byte 1
.byte 22
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "Return_Value1_4_5"
.byte 1
.byte 23
.long _int_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 48
.asciz "b_1_4_5"
.byte 1
.byte 18
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691023520960"
.byte 1
.byte 27
.long _Banana_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691024113200"
.byte 1
.byte 11
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691024132336"
.byte 1
.byte 28
.long _Fruit_START-Debug_Info_Start
.byte 10
.byte 2
.byte 145
.byte 0
.asciz "_Reference2691024124848"
.byte 1
.byte 23
.long _Banana_START-Debug_Info_Start
.byte 0
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
