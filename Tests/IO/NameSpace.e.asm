.intel_syntax noprefix
.file 1 "Tests/IO/NameSpace.e"		#1 "Tests/IO/NameSpace.e"
.file 2 "Tests/IO/../../IO/cstd.e"		#2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"		#3 "Tests/IO/../../IO/sys.e"
.file 4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"		#4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"		#5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"		#6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"		#7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"		#8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"		#9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"		#10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"		#11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 12 "Tests/IO/../../IO/STD.e"		#12 "Tests/IO/../../IO/STD.e"
.file 13 "Tests/IO/../../IO/Memory.e"		#13 "Tests/IO/../../IO/Memory.e"
.file 14 "Tests/IO/../../IO/List.e"		#14 "Tests/IO/../../IO/List.e"
Code_Start:
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv_START:
.loc 1 34 1		#1 34 1
_Z10Start_Testv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
push rdi		#rdi
push rbx		#rbx
sub rsp, 40		#.STACK, 40
.loc 1 35 2		#1 35 2
lea rcx, qword ptr [rsp + 0 ]		#b_REG0, .STACK_0
mov rcx, rcx		#b_TMP_1857393458704, b_REG0
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#b_TMP_1857393458704_0, 1
.loc 1 35 2		#1 35 2
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, b_TMP_1857393458704
mov rcx, qword ptr [rsp + 32 ]		#this_3_REG1, .STACK_32
.loc 1 12 8		#1 12 8
mov dword ptr [rcx + 8 ], 1		#this_3_REG1_8, 1
jmp Return_Here_3		#Return_Here_3
.loc 1 35 11		#1 35 11
Return_Here_3:
.loc 1 36 12		#1 36 12
lea rcx, qword ptr [rsp + 0 ]		#b_REG2, .STACK_0
mov rcx, rcx		#b_TMP_1857393457040, b_REG2
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#b_TMP_1857393457040_0, 1
.loc 1 36 12		#1 36 12
mov qword ptr [rsp + 16 ], rcx		#.STACK_16, b_TMP_1857393457040
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov rcx, qword ptr [rsp + 16 ]		#this_1_REG3, .STACK_16
.loc 1 12 2		#1 12 2
mov ecx, dword ptr [rcx + 8 ]		#this_1_REG3_8_REG4, this_1_REG3_8
.loc 1 21 11		#1 21 11
add ebx, ecx		#Banana_Y_REGISTER, this_1_REG3_8_REG4
mov ecx, ebx		#Return_Value1, Banana_Y_REGISTER
jmp Return_Here_1		#Return_Here_1
.loc 1 36 14		#1 36 14
Return_Here_1:
lea r8, qword ptr [rsp + 0 ]		#b_REG5, .STACK_0
mov r8, r8		#b_TMP_1857393460368, b_REG5
.loc 14 2 36		#14 2 36
add qword ptr [r8 + 0 ], 1		#b_TMP_1857393460368_0, 1
.loc 1 36 22		#1 36 22
mov qword ptr [rsp + 24 ], r8		#.STACK_24, b_TMP_1857393460368
mov r8, qword ptr [rsp + 24 ]		#this_2_REG6, .STACK_24
.loc 1 15 5		#1 15 5
mov dword ptr [r8 + 8 ], 1		#this_2_REG6_8, 1
mov r8, qword ptr [rsp + 24 ]		#this_2_REG7, .STACK_24
.loc 1 12 2		#1 12 2
mov r8d, dword ptr [r8 + 8 ]		#this_2_REG7_8_REG8, this_2_REG7_8
.loc 1 16 12		#1 16 12
add r8d, 1		#this_2_REG7_8_REG8, 1
mov r8d, r8d		#Return_Value2, this_2_REG7_8_REG8
jmp Return_Here_2		#Return_Here_2
.loc 1 36 24		#1 36 24
Return_Here_2:
mov ecx, ecx		#REG_Return_Value19, Return_Value1
add ecx, r8d		#REG_Return_Value19, Return_Value2
mov edi, ecx		#B_X, REG_Return_Value19
.loc 14 1 8		#14 1 8
mov rcx, qword ptr [rsp + 16 ]		#REG_this_1_Parameter41, .STACK_16
call _ZN6Banana10DestructorEP6Banana
mov rcx, qword ptr [rsp + 24 ]		#REG_this_2_Parameter18467, .STACK_24
call _ZN6Banana10DestructorEP6Banana
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov ecx, dword ptr [rip + Apple_Y ]		#Apple_Y_REGISTER, .RIP_Apple_Y
.loc 1 37 18		#1 37 18
add ebx, ecx		#Banana_Y_REGISTER, Apple_Y_REGISTER
sub ebx, edi		#Banana_Y_REGISTER, B_X
mov eax, ebx		#Returning_REG12, Banana_Y_REGISTER
add rsp, 40		#.STACK, 40
pop rbx		#rbx
pop rdi		#rdi
ret 		#
add rsp, 40		#.STACK, 40
pop rbx		#rbx
pop rdi		#rdi
ret 		#
_Z10Start_Testv_END:


.cfi_endproc 		#
_Z4mainv_START:
.loc 1 40 1		#1 40 1
_Z4mainv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 40		#.STACK, 40
.loc 1 35 2		#1 35 2
lea rcx, qword ptr [rsp + 0 ]		#b_4_REG0, .STACK_0
mov rcx, rcx		#b_4_TMP_1857393467024, b_4_REG0
.loc 14 2 38		#14 2 38
add qword ptr [rcx + 0 ], 1		#b_4_TMP_1857393467024_0, 1
.loc 1 35 2		#1 35 2
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, b_4_TMP_1857393467024
mov rcx, qword ptr [rsp + 32 ]		#this_3_4_REG1, .STACK_32
.loc 1 12 8		#1 12 8
mov dword ptr [rcx + 8 ], 1		#this_3_4_REG1_8, 1
jmp Return_Here_5		#Return_Here_5
.loc 1 35 11		#1 35 11
Return_Here_5:
.loc 1 36 12		#1 36 12
lea rcx, qword ptr [rsp + 0 ]		#b_4_REG2, .STACK_0
mov rcx, rcx		#b_4_TMP_1857393492816, b_4_REG2
.loc 14 2 38		#14 2 38
add qword ptr [rcx + 0 ], 1		#b_4_TMP_1857393492816_0, 1
.loc 1 36 12		#1 36 12
mov qword ptr [rsp + 16 ], rcx		#.STACK_16, b_4_TMP_1857393492816
mov ecx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8, qword ptr [rsp + 16 ]		#this_1_4_REG3, .STACK_16
.loc 1 12 2		#1 12 2
mov r8d, dword ptr [r8 + 8 ]		#this_1_4_REG3_8_REG4, this_1_4_REG3_8
.loc 1 21 11		#1 21 11
add ecx, r8d		#Banana_Y_REGISTER, this_1_4_REG3_8_REG4
mov ecx, ecx		#Return_Value1_4, Banana_Y_REGISTER
jmp Return_Here_6		#Return_Here_6
.loc 1 36 14		#1 36 14
Return_Here_6:
lea r8, qword ptr [rsp + 0 ]		#b_4_REG5, .STACK_0
mov r8, r8		#b_4_TMP_1857393503632, b_4_REG5
.loc 14 2 38		#14 2 38
add qword ptr [r8 + 0 ], 1		#b_4_TMP_1857393503632_0, 1
.loc 1 36 22		#1 36 22
mov qword ptr [rsp + 24 ], r8		#.STACK_24, b_4_TMP_1857393503632
mov r8, qword ptr [rsp + 24 ]		#this_2_4_REG6, .STACK_24
.loc 1 15 5		#1 15 5
mov dword ptr [r8 + 8 ], 1		#this_2_4_REG6_8, 1
mov r8, qword ptr [rsp + 24 ]		#this_2_4_REG7, .STACK_24
.loc 1 12 2		#1 12 2
mov r8d, dword ptr [r8 + 8 ]		#this_2_4_REG7_8_REG8, this_2_4_REG7_8
.loc 1 16 12		#1 16 12
add r8d, 1		#this_2_4_REG7_8_REG8, 1
mov r8d, r8d		#Return_Value2_4, this_2_4_REG7_8_REG8
jmp Return_Here_7		#Return_Here_7
.loc 1 36 24		#1 36 24
Return_Here_7:
mov ecx, ecx		#REG_Return_Value1_49, Return_Value1_4
add ecx, r8d		#REG_Return_Value1_49, Return_Value2_4
mov ecx, ecx		#B_X_4, REG_Return_Value1_49
.loc 14 1 8		#14 1 8
mov rcx, qword ptr [rsp + 16 ]		#REG_this_1_4_Parameter6334, .STACK_16
call _ZN6Banana10DestructorEP6Banana
mov rcx, qword ptr [rsp + 24 ]		#REG_this_2_4_Parameter26500, .STACK_24
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_4		#Return_Here_4
.loc 1 41 2		#1 41 2
Return_Here_4:
.loc 1 42 2		#1 42 2
mov eax, 1		#Returning_REG12, 1
add rsp, 40		#.STACK, 40
ret 		#
add rsp, 40		#.STACK, 40
ret 		#
_Z4mainv_END:


.cfi_endproc 		#
_ZN6Banana10DestructorEP6Banana_START:
.loc 1 8 1		#1 8 1
_ZN6Banana10DestructorEP6Banana:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 16		#.STACK, 16
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this
.loc 14 1 1		#14 1 1
if_0:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_0_END		#if_0_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
.loc 1 8 1		#1 8 1
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
.loc 14 1 26		#14 1 26
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_0_END		#if_0_END
.loc 14 2 19		#14 2 19
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_1857393520272, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_1857393520272_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_1857393520272
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 13 18 2		#13 18 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_0_Parameter19169, .STACK_0
mov edx, 8		#REG_8_Parameter15724, 8
call _V19internal_deallocatePhx
.loc 14 2 1		#14 2 1
Return_Here_0:
.loc 14 1 11		#14 1 11
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_0_Parameter11478, .STACK_0
call _ZN6Banana10DestructorEP6Banana
if_0_END:
add rsp, 16		#.STACK, 16
ret 		#
_ZN6Banana10DestructorEP6Banana_END:


.cfi_endproc 		#
Code_End:
.section .data		#.data
Banana_Y:
.long 2		#2
Apple_X:
.long 2		#2
Apple_Y:
.long 3		#3
Apple_Z:
.long 3		#3
.section .debug_abbrev		#.debug_abbrev
debug_abbrev:
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 37		#37
.byte 14		#14
.byte 19		#19
.byte 5		#5
.byte 3		#3
.byte 14		#14
.byte 16		#16
.byte 23		#23
.byte 27		#27
.byte 14		#14
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 0		#0
.byte 0		#0
.byte 2		#2
.byte 36		#36
.byte 0		#0
.byte 3		#3
.byte 8		#8
.byte 62		#62
.byte 11		#11
.byte 11		#11
.byte 11		#11
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 3		#3
.byte 52		#52
.byte 0		#0
.byte 56		#56
.byte 5		#5
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 4		#4
.byte 2		#2
.byte 0		#0
.byte 54		#54
.byte 11		#11
.byte 3		#3
.byte 8		#8
.byte 11		#11
.byte 11		#11
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 5		#5
.byte 2		#2
.byte 1		#1
.byte 54		#54
.byte 11		#11
.byte 3		#3
.byte 8		#8
.byte 11		#11
.byte 11		#11
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 6		#6
.byte 46		#46
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 7		#7
.byte 46		#46
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 110		#110
.byte 8		#8
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 63		#63
.byte 25		#25
.byte 0		#0
.byte 0		#0
.byte 8		#8
.byte 52		#52
.byte 0		#0
.byte 2		#2
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 9		#9
.byte 5		#5
.byte 0		#0
.byte 2		#2
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 10		#10
.byte 46		#46
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 0		#0
.section .debug_info		#.debug_info
Debug_Info_Start:
.long Debug_Info_End-Debug_Info		#Debug_Info_End-Debug_Info
Debug_Info:
.word 4		#4
.secrel32 debug_abbrev		#debug_abbrev
.byte 8		#8
.byte 1		#1
.secrel32 .COMPILER_NAME		#.COMPILER_NAME
.word 0x29A		#0x29A
.secrel32 .FILE_NAME		#.FILE_NAME
.secrel32 .LINE_TABLE		#.LINE_TABLE
.secrel32 .DIRECTORY		#.DIRECTORY
.quad Code_Start		#Code_Start
.long Code_End		#Code_End
_int_START:
.byte 2		#2
.asciz "int"		#int
.byte 5		#5
.byte 4		#4
.byte 2		#2
.byte 3		#3
_short_START:
.byte 2		#2
.asciz "short"		#short
.byte 5		#5
.byte 2		#2
.byte 2		#2
.byte 7		#7
_char_START:
.byte 2		#2
.asciz "char"		#char
.byte 6		#6
.byte 1		#1
.byte 2		#2
.byte 11		#11
_float_START:
.byte 2		#2
.asciz "float"		#float
.byte 4		#4
.byte 4		#4
.byte 2		#2
.byte 15		#15
_double_START:
.byte 2		#2
.asciz "double"		#double
.byte 4		#4
.byte 8		#8
.byte 2		#2
.byte 20		#20
_long_START:
.byte 2		#2
.asciz "long"		#long
.byte 5		#5
.byte 8		#8
.byte 2		#2
.byte 25		#25
_string_START:
.byte 2		#2
.asciz "string"		#string
.byte 6		#6
.byte 1		#1
.byte 2		#2
.byte 29		#29
_12BYTE_POINTER_START:
.byte 4		#4
.byte 1		#1
.asciz "BYTE_POINTER"		#BYTE_POINTER
.byte 8		#8
.byte 13		#13
.byte 1		#1
_6Banana_START:
.byte 5		#5
.byte 1		#1
.asciz "Banana"		#Banana
.byte 8		#8
.byte 1		#1
.byte 8		#8
.byte 3		#3
.word 0		#0
.asciz "Reference_Count"		#Reference_Count
.byte 1		#1
.byte 8		#8
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 8		#8
.asciz "X"		#X
.byte 1		#1
.byte 12		#12
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 12		#12
.asciz "Y"		#Y
.byte 1		#1
.byte 13		#13
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
_5Apple_START:
.byte 5		#5
.byte 1		#1
.asciz "Apple"		#Apple
.byte 12		#12
.byte 1		#1
.byte 24		#24
.byte 3		#3
.word 0		#0
.asciz "X"		#X
.byte 1		#1
.byte 26		#26
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Y"		#Y
.byte 1		#1
.byte 27		#27
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Z"		#Z
.byte 1		#1
.byte 31		#31
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
.byte 7		#7
.quad _Z10Start_Testv_START		#_Z10Start_Testv_START
.long _Z10Start_Testv_END		#_Z10Start_Testv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z10Start_Testv"		#_Z10Start_Testv
.asciz "Start_Test"		#Start_Test
.byte 1		#1
.byte 34		#34
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b"		#b
.byte 1		#1
.byte 35		#35
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "B_X"		#B_X
.byte 1		#1
.byte 36		#36
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value1"		#Return_Value1
.byte 1		#1
.byte 36		#36
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 16		#16
.asciz "this_1"		#this_1
.byte 1		#1
.byte 20		#20
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value2"		#Return_Value2
.byte 1		#1
.byte 36		#36
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_2"		#this_2
.byte 1		#1
.byte 14		#14
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_3"		#this_3
.byte 1		#1
.byte 8		#8
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_TMP_1857393458704"		#b_TMP_1857393458704
.byte 1		#1
.byte 35		#35
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_TMP_1857393457040"		#b_TMP_1857393457040
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_TMP_1857393460368"		#b_TMP_1857393460368
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 0		#0
.byte 7		#7
.quad _Z4mainv_START		#_Z4mainv_START
.long _Z4mainv_END		#_Z4mainv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z4mainv"		#_Z4mainv
.asciz "main"		#main
.byte 1		#1
.byte 40		#40
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_4"		#b_4
.byte 1		#1
.byte 35		#35
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "B_X_4"		#B_X_4
.byte 1		#1
.byte 36		#36
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value1_4"		#Return_Value1_4
.byte 1		#1
.byte 36		#36
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 16		#16
.asciz "this_1_4"		#this_1_4
.byte 1		#1
.byte 20		#20
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value2_4"		#Return_Value2_4
.byte 1		#1
.byte 36		#36
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_2_4"		#this_2_4
.byte 1		#1
.byte 14		#14
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_3_4"		#this_3_4
.byte 1		#1
.byte 8		#8
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_4_TMP_1857393467024"		#b_4_TMP_1857393467024
.byte 1		#1
.byte 35		#35
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_4_TMP_1857393492816"		#b_4_TMP_1857393492816
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 8		#8
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_4_TMP_1857393503632"		#b_4_TMP_1857393503632
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 0		#0
.byte 0		#0
Debug_Info_End:
.section .debug_str		#.debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"		#Evie engine 3.0.0 https://github.com/Gabidal/Evie
.FILE_NAME:
.asciz "Tests/IO/NameSpace.e"		#Tests/IO/NameSpace.e
.DIRECTORY:
.asciz "Tests/IO/"		#Tests/IO/
.section .LINE_TABLE		#.LINE_TABLE
.LINE_TABLE:
