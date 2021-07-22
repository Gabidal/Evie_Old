.intel_syntax noprefix
.file 1 "Tests/IO/Type.e"		#1 "Tests/IO/Type.e"
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
.loc 1 26 1		#1 26 1
_Z10Start_Testv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 56		#.STACK, 56
.loc 1 27 2		#1 27 2
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_1563891749264, x_REG0
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#x_TMP_1563891749264_0, 1
.loc 1 27 2		#1 27 2
mov qword ptr [rsp + 24 ], rcx		#.STACK_24, x_TMP_1563891749264
.loc 1 11 1		#1 11 1
mov rcx, qword ptr [rsp + 24 ]		#this_13_TMP_1563891738448, .STACK_24
.loc 14 2 42		#14 2 42
add qword ptr [rcx + 0 ], 1		#this_13_TMP_1563891738448_0, 1
.loc 1 11 1		#1 11 1
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, this_13_TMP_1563891738448
mov rcx, qword ptr [rsp + 24 ]		#REG_this_131, .STACK_24
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, REG_this_131
mov rcx, qword ptr [rsp + 32 ]		#this_12_13_REG2, .STACK_32
.loc 1 8 12		#1 8 12
mov dword ptr [rcx + 8 ], 4		#this_12_13_REG2_8, 4
.loc 1 11 1		#1 11 1
Return_Here_19:
mov rcx, qword ptr [rsp + 24 ]		#this_13_REG3, .STACK_24
.loc 1 12 12		#1 12 12
mov dword ptr [rcx + 12 ], 1		#this_13_REG3_12, 1
mov rcx, qword ptr [rsp + 24 ]		#this_13_REG4, .STACK_24
.loc 1 13 14		#1 13 14
mov dword ptr [rcx + 16 ], 2		#this_13_REG4_16, 2
mov rcx, qword ptr [rsp + 24 ]		#this_13_REG5, .STACK_24
.loc 1 14 11		#1 14 11
mov dword ptr [rcx + 20 ], 6		#this_13_REG5_20, 6
mov rcx, qword ptr [rsp + 24 ]		#this_13_REG6, .STACK_24
.loc 1 15 7		#1 15 7
mov dword ptr [rcx + 8 ], 5		#this_13_REG6_8, 5
jmp Return_Here_18		#Return_Here_18
.loc 1 27 11		#1 27 11
Return_Here_18:
.loc 1 28 18		#1 28 18
lea rcx, qword ptr [rsp + 0 ]		#x_REG7, .STACK_0
mov rcx, rcx		#x_TMP_1563891762576, x_REG7
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#x_TMP_1563891762576_0, 1
.loc 1 28 18		#1 28 18
mov qword ptr [rsp + 40 ], rcx		#.STACK_40, x_TMP_1563891762576
.loc 1 23 18		#1 23 18
mov rcx, qword ptr [rsp + 40 ]		#f_14_TMP_1563891771728, .STACK_40
.loc 14 2 39		#14 2 39
add qword ptr [rcx + 0 ], 1		#f_14_TMP_1563891771728_0, 1
.loc 1 23 18		#1 23 18
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, f_14_TMP_1563891771728
mov rcx, qword ptr [rsp + 40 ]		#REG_f_148, .STACK_40
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, REG_f_148
jmp Return_Here_21		#Return_Here_21
Return_Here_21:
mov rcx, qword ptr [rsp + 48 ]		#b_11_14_REG9, .STACK_48
.loc 1 12 2		#1 12 2
mov ecx, dword ptr [rcx + 12 ]		#b_11_14_REG9_12_REG10, b_11_14_REG9_12
.loc 1 23 2		#1 23 2
mov ecx, ecx		#Return_Value14, b_11_14_REG9_12_REG10
jmp Return_Here_20		#Return_Here_20
.loc 1 28 9		#1 28 9
Return_Here_20:
mov eax, ecx		#Returning_REG11, Return_Value14
add rsp, 56		#.STACK, 56
ret 		#
add rsp, 56		#.STACK, 56
ret 		#
_Z10Start_Testv_END:


.cfi_endproc 		#
_Z4mainv_START:
.loc 1 31 1		#1 31 1
_Z4mainv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 56		#.STACK, 56
.loc 1 27 2		#1 27 2
lea rcx, qword ptr [rsp + 0 ]		#x_15_REG0, .STACK_0
mov rcx, rcx		#x_15_TMP_1563891777552, x_15_REG0
.loc 14 2 39		#14 2 39
add qword ptr [rcx + 0 ], 1		#x_15_TMP_1563891777552_0, 1
.loc 1 27 2		#1 27 2
mov qword ptr [rsp + 24 ], rcx		#.STACK_24, x_15_TMP_1563891777552
.loc 1 11 1		#1 11 1
mov rcx, qword ptr [rsp + 24 ]		#this_13_15_TMP_1563891788368, .STACK_24
.loc 14 2 45		#14 2 45
add qword ptr [rcx + 0 ], 1		#this_13_15_TMP_1563891788368_0, 1
.loc 1 11 1		#1 11 1
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, this_13_15_TMP_1563891788368
mov rcx, qword ptr [rsp + 24 ]		#REG_this_13_151, .STACK_24
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, REG_this_13_151
mov rcx, qword ptr [rsp + 32 ]		#this_12_13_15_REG2, .STACK_32
.loc 1 8 12		#1 8 12
mov dword ptr [rcx + 8 ], 4		#this_12_13_15_REG2_8, 4
.loc 1 11 1		#1 11 1
Return_Here_23:
mov rcx, qword ptr [rsp + 24 ]		#this_13_15_REG3, .STACK_24
.loc 1 12 12		#1 12 12
mov dword ptr [rcx + 12 ], 1		#this_13_15_REG3_12, 1
mov rcx, qword ptr [rsp + 24 ]		#this_13_15_REG4, .STACK_24
.loc 1 13 14		#1 13 14
mov dword ptr [rcx + 16 ], 2		#this_13_15_REG4_16, 2
mov rcx, qword ptr [rsp + 24 ]		#this_13_15_REG5, .STACK_24
.loc 1 14 11		#1 14 11
mov dword ptr [rcx + 20 ], 6		#this_13_15_REG5_20, 6
mov rcx, qword ptr [rsp + 24 ]		#this_13_15_REG6, .STACK_24
.loc 1 15 7		#1 15 7
mov dword ptr [rcx + 8 ], 5		#this_13_15_REG6_8, 5
jmp Return_Here_24		#Return_Here_24
.loc 1 27 11		#1 27 11
Return_Here_24:
.loc 1 28 18		#1 28 18
lea rcx, qword ptr [rsp + 0 ]		#x_15_REG7, .STACK_0
mov rcx, rcx		#x_15_TMP_1563892674368, x_15_REG7
.loc 14 2 39		#14 2 39
add qword ptr [rcx + 0 ], 1		#x_15_TMP_1563892674368_0, 1
.loc 1 28 18		#1 28 18
mov qword ptr [rsp + 40 ], rcx		#.STACK_40, x_15_TMP_1563892674368
.loc 1 23 18		#1 23 18
mov rcx, qword ptr [rsp + 40 ]		#f_14_15_TMP_1563892678528, .STACK_40
.loc 14 2 42		#14 2 42
add qword ptr [rcx + 0 ], 1		#f_14_15_TMP_1563892678528_0, 1
.loc 1 23 18		#1 23 18
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, f_14_15_TMP_1563892678528
mov rcx, qword ptr [rsp + 40 ]		#REG_f_14_158, .STACK_40
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, REG_f_14_158
jmp Return_Here_25		#Return_Here_25
Return_Here_25:
mov rcx, qword ptr [rsp + 48 ]		#b_11_14_15_REG9, .STACK_48
.loc 1 12 2		#1 12 2
mov ecx, dword ptr [rcx + 12 ]		#b_11_14_15_REG9_12_REG10, b_11_14_15_REG9_12
.loc 1 23 2		#1 23 2
mov ecx, ecx		#Return_Value14_15, b_11_14_15_REG9_12_REG10
jmp Return_Here_26		#Return_Here_26
.loc 1 28 9		#1 28 9
Return_Here_26:
jmp Return_Here_22		#Return_Here_22
.loc 1 32 2		#1 32 2
Return_Here_22:
.loc 1 33 2		#1 33 2
mov eax, 1		#Returning_REG11, 1
add rsp, 56		#.STACK, 56
ret 		#
add rsp, 56		#.STACK, 56
ret 		#
_Z4mainv_END:


.cfi_endproc 		#
_ZN6Banana10DestructorEP6Banana_START:
.loc 1 11 1		#1 11 1
_ZN6Banana10DestructorEP6Banana:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 16		#.STACK, 16
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this
.loc 14 1 1		#14 1 1
if_6:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_6_END		#if_6_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
.loc 1 11 1		#1 11 1
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
.loc 14 1 26		#14 1 26
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_6_END		#if_6_END
.loc 14 2 19		#14 2 19
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_1563892680192, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_1563892680192_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_1563892680192
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 13 18 2		#13 18 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_10_Parameter25667, .STACK_0
mov edx, r8d		#REG_size_Parameter26299, size
call _V19internal_deallocatePhx
.loc 14 2 1		#14 2 1
Return_Here_15:
.loc 14 1 12		#14 1 12
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_10_Parameter17035, .STACK_0
call _ZN6Banana10DestructorEP6Banana
if_6_END:
add rsp, 16		#.STACK, 16
ret 		#
_ZN6Banana10DestructorEP6Banana_END:


.cfi_endproc 		#
Code_End:
.section .data		#.data
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
.byte 8		#8
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
.byte 9		#9
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
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 10		#10
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
.byte 11		#11
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
_5Fruit_START:
.byte 5		#5
.byte 1		#1
.asciz "Fruit"		#Fruit
.byte 4		#4
.byte 1		#1
.byte 3		#3
.byte 3		#3
.word 0		#0
.asciz "Reference_Count"		#Reference_Count
.byte 1		#1
.byte 3		#3
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 8		#8
.asciz "Type"		#Type
.byte 1		#1
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
_6Banana_START:
.byte 9		#9
.byte 1		#1
.asciz "Banana"		#Banana
.byte 16		#16
.byte 1		#1
.byte 11		#11
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Reference_Count"		#Reference_Count
.byte 1		#1
.byte 11		#11
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 8		#8
.asciz "Type"		#Type
.byte 1		#1
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 12		#12
.asciz "Sugar"		#Sugar
.byte 1		#1
.byte 12		#12
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 16		#16
.asciz "Protein"		#Protein
.byte 1		#1
.byte 13		#13
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 20		#20
.asciz "size"		#size
.byte 1		#1
.byte 14		#14
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
.byte 11		#11
.quad _Z10Start_Testv_START		#_Z10Start_Testv_START
.long _Z10Start_Testv_END		#_Z10Start_Testv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z10Start_Testv"		#_Z10Start_Testv
.asciz "Start_Test"		#Start_Test
.byte 1		#1
.byte 26		#26
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x"		#x
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_13"		#this_13
.byte 1		#1
.byte 11		#11
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_12_13"		#this_12_13
.byte 1		#1
.byte 7		#7
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value14"		#Return_Value14
.byte 1		#1
.byte 28		#28
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "f_14"		#f_14
.byte 1		#1
.byte 22		#22
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value11_14"		#Return_Value11_14
.byte 1		#1
.byte 23		#23
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 48		#48
.asciz "b_11_14"		#b_11_14
.byte 1		#1
.byte 18		#18
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_TMP_1563891749264"		#x_TMP_1563891749264
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "this_13_TMP_1563891738448"		#this_13_TMP_1563891738448
.byte 1		#1
.byte 11		#11
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_TMP_1563891762576"		#x_TMP_1563891762576
.byte 1		#1
.byte 28		#28
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "f_14_TMP_1563891771728"		#f_14_TMP_1563891771728
.byte 1		#1
.byte 23		#23
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 0		#0
.byte 11		#11
.quad _Z4mainv_START		#_Z4mainv_START
.long _Z4mainv_END		#_Z4mainv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z4mainv"		#_Z4mainv
.asciz "main"		#main
.byte 1		#1
.byte 31		#31
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_15"		#x_15
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_13_15"		#this_13_15
.byte 1		#1
.byte 11		#11
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_12_13_15"		#this_12_13_15
.byte 1		#1
.byte 7		#7
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value14_15"		#Return_Value14_15
.byte 1		#1
.byte 28		#28
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "f_14_15"		#f_14_15
.byte 1		#1
.byte 22		#22
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value11_14_15"		#Return_Value11_14_15
.byte 1		#1
.byte 23		#23
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 48		#48
.asciz "b_11_14_15"		#b_11_14_15
.byte 1		#1
.byte 18		#18
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_15_TMP_1563891777552"		#x_15_TMP_1563891777552
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "this_13_15_TMP_1563891788368"		#this_13_15_TMP_1563891788368
.byte 1		#1
.byte 11		#11
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_15_TMP_1563892674368"		#x_15_TMP_1563892674368
.byte 1		#1
.byte 28		#28
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "f_14_15_TMP_1563892678528"		#f_14_15_TMP_1563892678528
.byte 1		#1
.byte 23		#23
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 0		#0
.byte 0		#0
Debug_Info_End:
.section .debug_str		#.debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"		#Evie engine 3.0.0 https://github.com/Gabidal/Evie
.FILE_NAME:
.asciz "Tests/IO/Type.e"		#Tests/IO/Type.e
.DIRECTORY:
.asciz "Tests/IO/"		#Tests/IO/
.section .LINE_TABLE		#.LINE_TABLE
.LINE_TABLE:
