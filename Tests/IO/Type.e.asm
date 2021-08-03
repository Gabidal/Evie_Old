.intel_syntax noprefix
.file 1 "Tests/IO/Type.e"		#1 "Tests/IO/Type.e"
.file 2 "Tests/IO/../../STD/STD.e"		#2 "Tests/IO/../../STD/STD.e"
.file 3 "Tests/IO/../../STD/Types.e"		#3 "Tests/IO/../../STD/Types.e"
.file 4 "Tests/IO/../../STD/Memory.e"		#4 "Tests/IO/../../STD/Memory.e"
.file 5 "Tests/IO/../../STD/List.e"		#5 "Tests/IO/../../STD/List.e"
.file 6 "Tests/IO/../../STD/String.e"		#6 "Tests/IO/../../STD/String.e"
.file 7 "Tests/IO/../../STD/Console.e"		#7 "Tests/IO/../../STD/Console.e"
.file 8 "Tests/IO/../../STD/sys.e"		#8 "Tests/IO/../../STD/sys.e"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"		#9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"		#10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"		#11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 12 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"		#12 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 13 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"		#13 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 14 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"		#14 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 15 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"		#15 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 16 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"		#16 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 17 "Tests/IO/../../STD/Win/File.e"		#17 "Tests/IO/../../STD/Win/File.e"
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
mov rcx, rcx		#x_TMP_2143091378224, x_REG0
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#x_TMP_2143091378224_0, 1
.loc 1 27 2		#1 27 2
mov qword ptr [rsp + 24 ], rcx		#.STACK_24, x_TMP_2143091378224
.loc 1 11 1		#1 11 1
mov rcx, qword ptr [rsp + 24 ]		#this_4_TMP_2143091401552, .STACK_24
.loc 17 2 41		#17 2 41
add qword ptr [rcx + 0 ], 1		#this_4_TMP_2143091401552_0, 1
.loc 1 11 1		#1 11 1
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, this_4_TMP_2143091401552
mov rcx, qword ptr [rsp + 24 ]		#REG_this_41, .STACK_24
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, REG_this_41
mov rcx, qword ptr [rsp + 32 ]		#this_3_4_REG2, .STACK_32
.loc 1 8 12		#1 8 12
mov dword ptr [rcx + 8 ], 4		#this_3_4_REG2_8, 4
.loc 1 11 1		#1 11 1
Return_Here_5:
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG3, .STACK_24
.loc 1 12 12		#1 12 12
mov dword ptr [rcx + 12 ], 1		#this_4_REG3_12, 1
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG4, .STACK_24
.loc 1 13 14		#1 13 14
mov dword ptr [rcx + 16 ], 2		#this_4_REG4_16, 2
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG5, .STACK_24
.loc 1 14 11		#1 14 11
mov dword ptr [rcx + 20 ], 6		#this_4_REG5_20, 6
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG6, .STACK_24
.loc 1 15 7		#1 15 7
mov dword ptr [rcx + 8 ], 5		#this_4_REG6_8, 5
jmp Return_Here_4		#Return_Here_4
.loc 1 27 11		#1 27 11
Return_Here_4:
.loc 1 28 18		#1 28 18
lea rcx, qword ptr [rsp + 0 ]		#x_REG7, .STACK_0
mov rcx, rcx		#x_TMP_2143091395504, x_REG7
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#x_TMP_2143091395504_0, 1
.loc 1 28 18		#1 28 18
mov qword ptr [rsp + 40 ], rcx		#.STACK_40, x_TMP_2143091395504
.loc 1 23 18		#1 23 18
mov rcx, qword ptr [rsp + 40 ]		#f_5_TMP_2143091413648, .STACK_40
.loc 17 2 38		#17 2 38
add qword ptr [rcx + 0 ], 1		#f_5_TMP_2143091413648_0, 1
.loc 1 23 18		#1 23 18
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, f_5_TMP_2143091413648
mov rcx, qword ptr [rsp + 40 ]		#REG_f_58, .STACK_40
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, REG_f_58
jmp Return_Here_7		#Return_Here_7
Return_Here_7:
mov rcx, qword ptr [rsp + 48 ]		#b_2_5_REG9, .STACK_48
.loc 1 12 2		#1 12 2
mov ecx, dword ptr [rcx + 12 ]		#b_2_5_REG9_12_REG10, b_2_5_REG9_12
.loc 1 23 2		#1 23 2
mov ecx, ecx		#Return_Value5, b_2_5_REG9_12_REG10
jmp Return_Here_6		#Return_Here_6
.loc 1 28 9		#1 28 9
Return_Here_6:
mov eax, ecx		#Returning_REG11, Return_Value5
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
lea rcx, qword ptr [rsp + 0 ]		#x_6_REG0, .STACK_0
mov rcx, rcx		#x_6_TMP_2143091391184, x_6_REG0
.loc 17 2 38		#17 2 38
add qword ptr [rcx + 0 ], 1		#x_6_TMP_2143091391184_0, 1
.loc 1 27 2		#1 27 2
mov qword ptr [rsp + 24 ], rcx		#.STACK_24, x_6_TMP_2143091391184
.loc 1 11 1		#1 11 1
mov rcx, qword ptr [rsp + 24 ]		#this_4_6_TMP_2143091431792, .STACK_24
.loc 17 2 43		#17 2 43
add qword ptr [rcx + 0 ], 1		#this_4_6_TMP_2143091431792_0, 1
.loc 1 11 1		#1 11 1
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, this_4_6_TMP_2143091431792
mov rcx, qword ptr [rsp + 24 ]		#REG_this_4_61, .STACK_24
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, REG_this_4_61
mov rcx, qword ptr [rsp + 32 ]		#this_3_4_6_REG2, .STACK_32
.loc 1 8 12		#1 8 12
mov dword ptr [rcx + 8 ], 4		#this_3_4_6_REG2_8, 4
.loc 1 11 1		#1 11 1
Return_Here_9:
mov rcx, qword ptr [rsp + 24 ]		#this_4_6_REG3, .STACK_24
.loc 1 12 12		#1 12 12
mov dword ptr [rcx + 12 ], 1		#this_4_6_REG3_12, 1
mov rcx, qword ptr [rsp + 24 ]		#this_4_6_REG4, .STACK_24
.loc 1 13 14		#1 13 14
mov dword ptr [rcx + 16 ], 2		#this_4_6_REG4_16, 2
mov rcx, qword ptr [rsp + 24 ]		#this_4_6_REG5, .STACK_24
.loc 1 14 11		#1 14 11
mov dword ptr [rcx + 20 ], 6		#this_4_6_REG5_20, 6
mov rcx, qword ptr [rsp + 24 ]		#this_4_6_REG6, .STACK_24
.loc 1 15 7		#1 15 7
mov dword ptr [rcx + 8 ], 5		#this_4_6_REG6_8, 5
jmp Return_Here_10		#Return_Here_10
.loc 1 27 11		#1 27 11
Return_Here_10:
.loc 1 28 18		#1 28 18
lea rcx, qword ptr [rsp + 0 ]		#x_6_REG7, .STACK_0
mov rcx, rcx		#x_6_TMP_2143091436976, x_6_REG7
.loc 17 2 38		#17 2 38
add qword ptr [rcx + 0 ], 1		#x_6_TMP_2143091436976_0, 1
.loc 1 28 18		#1 28 18
mov qword ptr [rsp + 40 ], rcx		#.STACK_40, x_6_TMP_2143091436976
.loc 1 23 18		#1 23 18
mov rcx, qword ptr [rsp + 40 ]		#f_5_6_TMP_2143091460304, .STACK_40
.loc 17 2 40		#17 2 40
add qword ptr [rcx + 0 ], 1		#f_5_6_TMP_2143091460304_0, 1
.loc 1 23 18		#1 23 18
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, f_5_6_TMP_2143091460304
mov rcx, qword ptr [rsp + 40 ]		#REG_f_5_68, .STACK_40
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, REG_f_5_68
jmp Return_Here_11		#Return_Here_11
Return_Here_11:
mov rcx, qword ptr [rsp + 48 ]		#b_2_5_6_REG9, .STACK_48
.loc 1 12 2		#1 12 2
mov ecx, dword ptr [rcx + 12 ]		#b_2_5_6_REG9_12_REG10, b_2_5_6_REG9_12
.loc 1 23 2		#1 23 2
mov ecx, ecx		#Return_Value5_6, b_2_5_6_REG9_12_REG10
jmp Return_Here_12		#Return_Here_12
.loc 1 28 9		#1 28 9
Return_Here_12:
jmp Return_Here_8		#Return_Here_8
.loc 1 32 2		#1 32 2
Return_Here_8:
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
.loc 17 1 1		#17 1 1
if_0:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_0_END		#if_0_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
.loc 1 11 1		#1 11 1
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
.loc 17 1 26		#17 1 26
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_0_END		#if_0_END
.loc 17 2 19		#17 2 19
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_2143091464624, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_2143091464624_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_2143091464624
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 4 14 2		#4 14 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_1_Parameter41, .STACK_0
mov r8, qword ptr [rsp + 0 ]		#Address_1_REG3, .STACK_0
mov r8d, dword ptr [r8 + 20 ]		#Address_1_REG3_20_REG4, Address_1_REG3_20
mov edx, r8d		#REG_Address_1_REG3_20_REG4_Parameter18467, Address_1_REG3_20_REG4
call _V19internal_deallocatePhx
.loc 17 2 1		#17 2 1
Return_Here_1:
.loc 17 1 11		#17 1 11
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_1_Parameter6334, .STACK_0
call _ZN6Banana10DestructorEP6Banana
if_0_END:
add rsp, 16		#.STACK, 16
ret 		#
_ZN6Banana10DestructorEP6Banana_END:


.cfi_endproc 		#
Code_End:
.section .data		#.data
std_MAX_CONCOLE_BUFFER_LENGHT:
.long 4096		#4096
std_GENERIC_WRITE:
.long 1073741824		#1073741824
std_GENERIC_READ:
.quad 2147483648		#2147483648
std_FILE_SHARE_NONE:
.long 0		#0
std_FILE_SHARE_READ:
.long 1		#1
std_FILE_SHARE_WRITE:
.long 2		#2
std_FILE_SHARE_DELETE:
.long 4		#4
std_CREATE_NEW:
.long 1		#1
std_CREATE_ALWAYS:
.long 2		#2
std_OPEN_EXISTING:
.long 3		#3
std_OPEN_ALWAYS:
.long 4		#4
std_TRUNCATE_EXISTING:
.long 4		#4
std_FILE_ATTRIBUTE_NORMAL:
.long 128		#128
std_FILE_ATTRIBUTE_FOLDER:
.long 16		#16
std_MAXIMUM_PATH_LENGTH:
.long 260		#260
std_ERROR_INSUFFICIENT_BUFFER:
.long 122		#122
std_MINIMUM_PROCESS_FILENAME_LENGTH:
.long 50		#50
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
.byte 5		#5
.byte 46		#46
.byte 0		#0
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
.byte 73		#73
.byte 19		#19
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
.byte 12		#12
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
_char_START:
.byte 2		#2
.asciz "char"		#char
.byte 6		#6
.byte 1		#1
.byte 3		#3
.byte 1		#1
_bool_START:
.byte 2		#2
.asciz "bool"		#bool
.byte 6		#6
.byte 1		#1
.byte 3		#3
.byte 5		#5
_short_START:
.byte 2		#2
.asciz "short"		#short
.byte 5		#5
.byte 2		#2
.byte 3		#3
.byte 9		#9
_int_START:
.byte 2		#2
.asciz "int"		#int
.byte 5		#5
.byte 4		#4
.byte 3		#3
.byte 13		#13
_long_START:
.byte 2		#2
.asciz "long"		#long
.byte 5		#5
.byte 8		#8
.byte 3		#3
.byte 17		#17
_float_START:
.byte 2		#2
.asciz "float"		#float
.byte 4		#4
.byte 4		#4
.byte 3		#3
.byte 21		#21
_double_START:
.byte 2		#2
.asciz "double"		#double
.byte 4		#4
.byte 8		#8
.byte 3		#3
.byte 26		#26
_3std_START:
.byte 4		#4
.byte 1		#1
.asciz "std"		#std
.byte 698		#698
.byte 5		#5
.byte 1		#1
_6string_START:
.byte 4		#4
.byte 1		#1
.asciz "string"		#string
.byte 8		#8
.byte 6		#6
.byte 2		#2
.byte 3		#3
.word 0		#0
.asciz "Characters"		#Characters
.byte 6		#6
.byte 3		#3
.long _14____List_char__START-Debug_Info_Start		#_14____List_char__START-Debug_Info_Start
.byte 0		#0
_14____List_char__START:
.byte 4		#4
.byte 1		#1
.asciz "____List_char_"		#____List_char_
.byte 16		#16
.byte 5		#5
.byte 2		#2
.byte 3		#3
.word 0		#0
.asciz "Capacity"		#Capacity
.byte 5		#5
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Size"		#Size
.byte 5		#5
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Array"		#Array
.byte 5		#5
.byte 5		#5
.long _char_START-Debug_Info_Start		#_char_START-Debug_Info_Start
.byte 0		#0
.byte 3		#3
.word 0		#0
.asciz "MAX_CONCOLE_BUFFER_LENGHT"		#MAX_CONCOLE_BUFFER_LENGHT
.byte 7		#7
.byte 3		#3
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "GENERIC_WRITE"		#GENERIC_WRITE
.byte 17		#17
.byte 2		#2
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "GENERIC_READ"		#GENERIC_READ
.byte 17		#17
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_NONE"		#FILE_SHARE_NONE
.byte 17		#17
.byte 5		#5
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_READ"		#FILE_SHARE_READ
.byte 17		#17
.byte 6		#6
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_WRITE"		#FILE_SHARE_WRITE
.byte 17		#17
.byte 7		#7
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_DELETE"		#FILE_SHARE_DELETE
.byte 17		#17
.byte 8		#8
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "CREATE_NEW"		#CREATE_NEW
.byte 17		#17
.byte 10		#10
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "CREATE_ALWAYS"		#CREATE_ALWAYS
.byte 17		#17
.byte 11		#11
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "OPEN_EXISTING"		#OPEN_EXISTING
.byte 17		#17
.byte 12		#12
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "OPEN_ALWAYS"		#OPEN_ALWAYS
.byte 17		#17
.byte 13		#13
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "TRUNCATE_EXISTING"		#TRUNCATE_EXISTING
.byte 17		#17
.byte 14		#14
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_ATTRIBUTE_NORMAL"		#FILE_ATTRIBUTE_NORMAL
.byte 17		#17
.byte 16		#16
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_ATTRIBUTE_FOLDER"		#FILE_ATTRIBUTE_FOLDER
.byte 17		#17
.byte 17		#17
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "MAXIMUM_PATH_LENGTH"		#MAXIMUM_PATH_LENGTH
.byte 17		#17
.byte 19		#19
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "ERROR_INSUFFICIENT_BUFFER"		#ERROR_INSUFFICIENT_BUFFER
.byte 17		#17
.byte 21		#21
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "MINIMUM_PROCESS_FILENAME_LENGTH"		#MINIMUM_PROCESS_FILENAME_LENGTH
.byte 17		#17
.byte 22		#22
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
_Char_260_START:
.byte 2		#2
.asciz "Char_260"		#Char_260
.byte 5		#5
.byte 260		#260
.byte 17		#17
.byte 41		#41
_Char_14_START:
.byte 2		#2
.asciz "Char_14"		#Char_14
.byte 5		#5
.byte 14		#14
.byte 17		#17
.byte 45		#45
_12FileIterator_START:
.byte 4		#4
.byte 1		#1
.asciz "FileIterator"		#FileIterator
.byte 328		#328
.byte 17		#17
.byte 49		#49
.byte 3		#3
.word 0		#0
.asciz "attributes"		#attributes
.byte 17		#17
.byte 50		#50
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "creation_time"		#creation_time
.byte 17		#17
.byte 51		#51
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "last_access_time"		#last_access_time
.byte 17		#17
.byte 52		#52
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "last_write_time"		#last_write_time
.byte 17		#17
.byte 53		#53
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "file_size"		#file_size
.byte 17		#17
.byte 54		#54
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "reserved"		#reserved
.byte 17		#17
.byte 55		#55
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "filename"		#filename
.byte 17		#17
.byte 56		#56
.long _Char_260_START-Debug_Info_Start		#_Char_260_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "alternate_filename"		#alternate_filename
.byte 17		#17
.byte 57		#57
.long _Char_14_START-Debug_Info_Start		#_Char_14_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "file_type"		#file_type
.byte 17		#17
.byte 58		#58
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "creator_type"		#creator_type
.byte 17		#17
.byte 59		#59
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "finder_flags"		#finder_flags
.byte 17		#17
.byte 60		#60
.long _short_START-Debug_Info_Start		#_short_START-Debug_Info_Start
.byte 0		#0
.byte 0		#0
_5Fruit_START:
.byte 4		#4
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
.asciz "this_4"		#this_4
.byte 1		#1
.byte 11		#11
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_3_4"		#this_3_4
.byte 1		#1
.byte 7		#7
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value5"		#Return_Value5
.byte 1		#1
.byte 28		#28
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "f_5"		#f_5
.byte 1		#1
.byte 22		#22
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value2_5"		#Return_Value2_5
.byte 1		#1
.byte 23		#23
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 48		#48
.asciz "b_2_5"		#b_2_5
.byte 1		#1
.byte 18		#18
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_TMP_2143091378224"		#x_TMP_2143091378224
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "this_4_TMP_2143091401552"		#this_4_TMP_2143091401552
.byte 1		#1
.byte 11		#11
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_TMP_2143091395504"		#x_TMP_2143091395504
.byte 1		#1
.byte 28		#28
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "f_5_TMP_2143091413648"		#f_5_TMP_2143091413648
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
.asciz "x_6"		#x_6
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_4_6"		#this_4_6
.byte 1		#1
.byte 11		#11
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_3_4_6"		#this_3_4_6
.byte 1		#1
.byte 7		#7
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value5_6"		#Return_Value5_6
.byte 1		#1
.byte 28		#28
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "f_5_6"		#f_5_6
.byte 1		#1
.byte 22		#22
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value2_5_6"		#Return_Value2_5_6
.byte 1		#1
.byte 23		#23
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 48		#48
.asciz "b_2_5_6"		#b_2_5_6
.byte 1		#1
.byte 18		#18
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_6_TMP_2143091391184"		#x_6_TMP_2143091391184
.byte 1		#1
.byte 27		#27
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "this_4_6_TMP_2143091431792"		#this_4_6_TMP_2143091431792
.byte 1		#1
.byte 11		#11
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_6_TMP_2143091436976"		#x_6_TMP_2143091436976
.byte 1		#1
.byte 28		#28
.long _5Fruit_START-Debug_Info_Start		#_5Fruit_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "f_5_6_TMP_2143091460304"		#f_5_6_TMP_2143091460304
.byte 1		#1
.byte 23		#23
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 0		#0
_26____VIRTUAL_CLASS_char_ptr_START:
.byte 12		#12
.byte 1		#1
.asciz "____VIRTUAL_CLASS_char_ptr"		#____VIRTUAL_CLASS_char_ptr
.byte 8		#8
.byte 4		#4
.byte 14		#14
_func_START:
.byte 2		#2
.asciz "func"		#func
.byte 5		#5
.byte 0		#0
.byte 1		#1
.byte 1		#1
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
