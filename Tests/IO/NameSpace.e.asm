.intel_syntax noprefix
.file 1 "Tests/IO/NameSpace.e"		#1 "Tests/IO/NameSpace.e"
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
.loc 1 34 1		#1 34 1
_Z10Start_Testv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
push rdi		#rdi
push rbx		#rbx
sub rsp, 40		#.STACK, 40
.loc 1 36 2		#1 36 2
lea rcx, qword ptr [rsp + 0 ]		#b_REG0, .STACK_0
mov rcx, rcx		#b_TMP_1770781871824, b_REG0
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#b_TMP_1770781871824_0, 1
.loc 1 36 2		#1 36 2
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, b_TMP_1770781871824
mov rcx, qword ptr [rsp + 32 ]		#this_13_REG1, .STACK_32
.loc 1 12 8		#1 12 8
mov dword ptr [rcx + 8 ], 1		#this_13_REG1_8, 1
.loc 1 13 15		#1 13 15
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_18		#Return_Here_18
.loc 1 36 11		#1 36 11
Return_Here_18:
.loc 1 37 12		#1 37 12
lea rcx, qword ptr [rsp + 0 ]		#b_REG2, .STACK_0
mov rcx, rcx		#b_TMP_1770781877872, b_REG2
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#b_TMP_1770781877872_0, 1
.loc 1 37 12		#1 37 12
mov qword ptr [rsp + 16 ], rcx		#.STACK_16, b_TMP_1770781877872
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov rcx, qword ptr [rsp + 16 ]		#this_11_REG3, .STACK_16
.loc 1 12 2		#1 12 2
mov ecx, dword ptr [rcx + 8 ]		#this_11_REG3_8_REG4, this_11_REG3_8
.loc 1 21 11		#1 21 11
add ebx, ecx		#Banana_Y_REGISTER, this_11_REG3_8_REG4
mov ecx, ebx		#Return_Value11, Banana_Y_REGISTER
jmp Return_Here_16		#Return_Here_16
.loc 1 37 14		#1 37 14
Return_Here_16:
lea r8, qword ptr [rsp + 0 ]		#b_REG5, .STACK_0
mov r8, r8		#b_TMP_1770781885648, b_REG5
.loc 17 2 36		#17 2 36
add qword ptr [r8 + 0 ], 1		#b_TMP_1770781885648_0, 1
.loc 1 37 22		#1 37 22
mov qword ptr [rsp + 24 ], r8		#.STACK_24, b_TMP_1770781885648
mov r8, qword ptr [rsp + 24 ]		#this_12_REG6, .STACK_24
.loc 1 15 5		#1 15 5
mov dword ptr [r8 + 8 ], 1		#this_12_REG6_8, 1
mov r8, qword ptr [rsp + 24 ]		#this_12_REG7, .STACK_24
.loc 1 12 2		#1 12 2
mov r8d, dword ptr [r8 + 8 ]		#this_12_REG7_8_REG8, this_12_REG7_8
.loc 1 16 12		#1 16 12
add r8d, 1		#this_12_REG7_8_REG8, 1
mov r8d, r8d		#Return_Value12, this_12_REG7_8_REG8
jmp Return_Here_17		#Return_Here_17
.loc 1 37 24		#1 37 24
Return_Here_17:
mov ecx, ecx		#REG_Return_Value119, Return_Value11
add ecx, r8d		#REG_Return_Value119, Return_Value12
mov edi, ecx		#B_X, REG_Return_Value119
.loc 17 1 9		#17 1 9
mov rcx, qword ptr [rsp + 16 ]		#REG_this_11_Parameter25667, .STACK_16
call _ZN6Banana10DestructorEP6Banana
mov rcx, qword ptr [rsp + 24 ]		#REG_this_12_Parameter26299, .STACK_24
call _ZN6Banana10DestructorEP6Banana
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov ecx, dword ptr [rip + Apple_Y ]		#Apple_Y_REGISTER, .RIP_Apple_Y
.loc 1 38 18		#1 38 18
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
.loc 1 41 1		#1 41 1
_Z4mainv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 40		#.STACK, 40
.loc 1 36 2		#1 36 2
lea rcx, qword ptr [rsp + 0 ]		#b_14_REG0, .STACK_0
mov rcx, rcx		#b_14_TMP_1770781891696, b_14_REG0
.loc 17 2 39		#17 2 39
add qword ptr [rcx + 0 ], 1		#b_14_TMP_1770781891696_0, 1
.loc 1 36 2		#1 36 2
mov qword ptr [rsp + 32 ], rcx		#.STACK_32, b_14_TMP_1770781891696
mov rcx, qword ptr [rsp + 32 ]		#this_13_14_REG1, .STACK_32
.loc 1 12 8		#1 12 8
mov dword ptr [rcx + 8 ], 1		#this_13_14_REG1_8, 1
.loc 1 13 15		#1 13 15
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_20		#Return_Here_20
.loc 1 36 11		#1 36 11
Return_Here_20:
.loc 1 37 12		#1 37 12
lea rcx, qword ptr [rsp + 0 ]		#b_14_REG2, .STACK_0
mov rcx, rcx		#b_14_TMP_1770781916752, b_14_REG2
.loc 17 2 39		#17 2 39
add qword ptr [rcx + 0 ], 1		#b_14_TMP_1770781916752_0, 1
.loc 1 37 12		#1 37 12
mov qword ptr [rsp + 16 ], rcx		#.STACK_16, b_14_TMP_1770781916752
mov ecx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8, qword ptr [rsp + 16 ]		#this_11_14_REG3, .STACK_16
.loc 1 12 2		#1 12 2
mov r8d, dword ptr [r8 + 8 ]		#this_11_14_REG3_8_REG4, this_11_14_REG3_8
.loc 1 21 11		#1 21 11
add ecx, r8d		#Banana_Y_REGISTER, this_11_14_REG3_8_REG4
mov ecx, ecx		#Return_Value11_14, Banana_Y_REGISTER
jmp Return_Here_21		#Return_Here_21
.loc 1 37 14		#1 37 14
Return_Here_21:
lea r8, qword ptr [rsp + 0 ]		#b_14_REG5, .STACK_0
mov r8, r8		#b_14_TMP_1770781908976, b_14_REG5
.loc 17 2 39		#17 2 39
add qword ptr [r8 + 0 ], 1		#b_14_TMP_1770781908976_0, 1
.loc 1 37 22		#1 37 22
mov qword ptr [rsp + 24 ], r8		#.STACK_24, b_14_TMP_1770781908976
mov r8, qword ptr [rsp + 24 ]		#this_12_14_REG6, .STACK_24
.loc 1 15 5		#1 15 5
mov dword ptr [r8 + 8 ], 1		#this_12_14_REG6_8, 1
mov r8, qword ptr [rsp + 24 ]		#this_12_14_REG7, .STACK_24
.loc 1 12 2		#1 12 2
mov r8d, dword ptr [r8 + 8 ]		#this_12_14_REG7_8_REG8, this_12_14_REG7_8
.loc 1 16 12		#1 16 12
add r8d, 1		#this_12_14_REG7_8_REG8, 1
mov r8d, r8d		#Return_Value12_14, this_12_14_REG7_8_REG8
jmp Return_Here_22		#Return_Here_22
.loc 1 37 24		#1 37 24
Return_Here_22:
mov ecx, ecx		#REG_Return_Value11_149, Return_Value11_14
add ecx, r8d		#REG_Return_Value11_149, Return_Value12_14
mov ecx, ecx		#B_X_14, REG_Return_Value11_149
.loc 17 1 9		#17 1 9
mov rcx, qword ptr [rsp + 16 ]		#REG_this_11_14_Parameter17035, .STACK_16
call _ZN6Banana10DestructorEP6Banana
mov rcx, qword ptr [rsp + 24 ]		#REG_this_12_14_Parameter9894, .STACK_24
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_19		#Return_Here_19
.loc 1 42 2		#1 42 2
Return_Here_19:
.loc 1 43 2		#1 43 2
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
.loc 17 1 1		#17 1 1
if_6:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_6_END		#if_6_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
.loc 1 8 1		#1 8 1
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
.loc 17 1 26		#17 1 26
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_6_END		#if_6_END
.loc 17 2 19		#17 2 19
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_1770781930576, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_1770781930576_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_1770781930576
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 4 19 2		#4 19 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_10_Parameter28703, .STACK_0
mov edx, 8		#REG_8_Parameter23811, 8
call _V19internal_deallocatePhx
.loc 17 2 1		#17 2 1
Return_Here_15:
.loc 17 1 12		#17 1 12
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_10_Parameter31322, .STACK_0
call _ZN6Banana10DestructorEP6Banana
if_6_END:
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
.byte 9		#9
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
_12BYTE_POINTER_START:
.byte 4		#4
.byte 1		#1
.asciz "BYTE_POINTER"		#BYTE_POINTER
.byte 8		#8
.byte 4		#4
.byte 2		#2
_3std_START:
.byte 5		#5
.byte 1		#1
.asciz "std"		#std
.byte 698		#698
.byte 5		#5
.byte 1		#1
_6string_START:
.byte 5		#5
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
.byte 5		#5
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
.byte 5		#5
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
.byte 9		#9
.quad _Z10Start_Testv_START		#_Z10Start_Testv_START
.long _Z10Start_Testv_END		#_Z10Start_Testv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z10Start_Testv"		#_Z10Start_Testv
.asciz "Start_Test"		#Start_Test
.byte 1		#1
.byte 34		#34
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b"		#b
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "B_X"		#B_X
.byte 1		#1
.byte 37		#37
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value11"		#Return_Value11
.byte 1		#1
.byte 37		#37
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 16		#16
.asciz "this_11"		#this_11
.byte 1		#1
.byte 20		#20
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value12"		#Return_Value12
.byte 1		#1
.byte 37		#37
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_12"		#this_12
.byte 1		#1
.byte 14		#14
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_13"		#this_13
.byte 1		#1
.byte 8		#8
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_TMP_1770781871824"		#b_TMP_1770781871824
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_TMP_1770781877872"		#b_TMP_1770781877872
.byte 1		#1
.byte 37		#37
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_TMP_1770781885648"		#b_TMP_1770781885648
.byte 1		#1
.byte 37		#37
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 0		#0
.byte 9		#9
.quad _Z4mainv_START		#_Z4mainv_START
.long _Z4mainv_END		#_Z4mainv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z4mainv"		#_Z4mainv
.asciz "main"		#main
.byte 1		#1
.byte 41		#41
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_14"		#b_14
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "B_X_14"		#B_X_14
.byte 1		#1
.byte 37		#37
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value11_14"		#Return_Value11_14
.byte 1		#1
.byte 37		#37
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 16		#16
.asciz "this_11_14"		#this_11_14
.byte 1		#1
.byte 20		#20
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value12_14"		#Return_Value12_14
.byte 1		#1
.byte 37		#37
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_12_14"		#this_12_14
.byte 1		#1
.byte 14		#14
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "this_13_14"		#this_13_14
.byte 1		#1
.byte 8		#8
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_14_TMP_1770781891696"		#b_14_TMP_1770781891696
.byte 1		#1
.byte 36		#36
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_14_TMP_1770781916752"		#b_14_TMP_1770781916752
.byte 1		#1
.byte 37		#37
.long _6Banana_START-Debug_Info_Start		#_6Banana_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "b_14_TMP_1770781908976"		#b_14_TMP_1770781908976
.byte 1		#1
.byte 37		#37
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
