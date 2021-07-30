.intel_syntax noprefix
.file 1 "Tests/IO/Destructor.e"		#1 "Tests/IO/Destructor.e"
.file 2 "C:/Users/GabenRTX/.Repos/Evie/STD/STD.e"		#2 "C:/Users/GabenRTX/.Repos/Evie/STD/STD.e"
.file 3 "C:/Users/GabenRTX/.Repos/Evie/STD/Types.e"		#3 "C:/Users/GabenRTX/.Repos/Evie/STD/Types.e"
.file 4 "C:/Users/GabenRTX/.Repos/Evie/STD/Memory.e"		#4 "C:/Users/GabenRTX/.Repos/Evie/STD/Memory.e"
.file 5 "C:/Users/GabenRTX/.Repos/Evie/STD/List.e"		#5 "C:/Users/GabenRTX/.Repos/Evie/STD/List.e"
.file 6 "C:/Users/GabenRTX/.Repos/Evie/STD/String.e"		#6 "C:/Users/GabenRTX/.Repos/Evie/STD/String.e"
.file 7 "C:/Users/GabenRTX/.Repos/Evie/STD/Console.e"		#7 "C:/Users/GabenRTX/.Repos/Evie/STD/Console.e"
.file 8 "C:/Users/GabenRTX/.Repos/Evie/STD/sys.e"		#8 "C:/Users/GabenRTX/.Repos/Evie/STD/sys.e"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"		#9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"		#10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"		#11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 12 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"		#12 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 13 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"		#13 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 14 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"		#14 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 15 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"		#15 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 16 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"		#16 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 17 "C:/Users/GabenRTX/.Repos/Evie/STD/Win/File.e"		#17 "C:/Users/GabenRTX/.Repos/Evie/STD/Win/File.e"
Code_Start:
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv_START:
.loc 1 3 1		#1 3 1
_Z4mainv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
push rdi		#rdi
push rbx		#rbx
sub rsp, 24		#.STACK, 24
.loc 4 27 9		#4 27 9
mov ecx, 8		#REG_8_Parameter31101, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_1770843322096, RetREG_0
.loc 17 2 52		#17 2 52
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1770843322096_0, 1
.loc 4 27 2		#4 27 2
mov rbx, rcx		#Return_Value42_44, internal_allocate_TMP_1770843322096
jmp Return_Here_63		#Return_Here_63
.loc 1 14 13		#1 14 13
Return_Here_63:
mov rcx, rbx		#Return_Value42_44_TMP_1770844277472, Return_Value42_44
.loc 17 2 52		#17 2 52
add qword ptr [rcx + 0 ], 1		#Return_Value42_44_TMP_1770844277472_0, 1
.loc 1 14 13		#1 14 13
mov qword ptr [rsp + 16 ], rcx		#.STACK_16, Return_Value42_44_TMP_1770844277472
mov qword ptr [rsp + 16 ], rbx		#.STACK_16, Return_Value42_44
mov rcx, qword ptr [rsp + 16 ]		#this_43_44_REG1, .STACK_16
.loc 1 9 8		#1 9 8
mov dword ptr [rcx + 8 ], 1		#this_43_44_REG1_8, 1
mov rcx, qword ptr [rsp + 16 ]		#this_43_44_REG2, .STACK_16
.loc 1 10 8		#1 10 8
mov dword ptr [rcx + 12 ], 2		#this_43_44_REG2_12, 2
.loc 1 8 1		#1 8 1
mov rcx, qword ptr [rsp + 16 ]		#this_43_44_TMP_1770844280064, .STACK_16
.loc 17 2 45		#17 2 45
add qword ptr [rcx + 0 ], 1		#this_43_44_TMP_1770844280064_0, 1
.loc 1 8 1		#1 8 1
mov rdi, rcx		#Return_Value43_44, this_43_44_TMP_1770844280064
mov rdi, qword ptr [rsp + 16 ]		#Return_Value43_44, .STACK_16
jmp Return_Here_64		#Return_Here_64
.loc 1 14 10		#1 14 10
Return_Here_64:
mov rcx, qword ptr [rdi + 0 ]		#REG_Return_Value43_4408, Return_Value43_44_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value43_4408
mov rcx, qword ptr [rdi + 8 ]		#REG_Return_Value43_4418, Return_Value43_44_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value43_4418
.loc 1 15 19		#1 15 19
lea rcx, qword ptr [rsp + 0 ]		#F_44_REG3, .STACK_0
mov rcx, rcx		#F_44_TMP_1770844299936, F_44_REG3
.loc 17 2 39		#17 2 39
add qword ptr [rcx + 0 ], 1		#F_44_TMP_1770844299936_0, 1
.loc 1 15 19		#1 15 19
mov rcx, rcx		#handle_1_44, F_44_TMP_1770844299936
.loc 1 9 2		#1 9 2
mov r8d, dword ptr [rcx + 8 ]		#handle_1_44_8_REG4, handle_1_44_8
.loc 1 17 8		#1 17 8
mov r8d, r8d		#x_44, handle_1_44_8_REG4
.loc 17 1 10		#17 1 10
mov rcx, rcx		#REG_handle_1_44_Parameter24393, handle_1_44
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value42_44_Parameter3548, Return_Value42_44
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_Return_Value43_44_Parameter19629, Return_Value43_44
call _ZN3foo10DestructorEP3foo
mov rcx, qword ptr [rsp + 16 ]		#REG_this_43_44_Parameter12623, .STACK_16
call _ZN3foo10DestructorEP3foo
jmp Return_Here_62		#Return_Here_62
.loc 1 4 2		#1 4 2
Return_Here_62:
.loc 1 5 2		#1 5 2
mov eax, 1		#Returning_REG9, 1
add rsp, 24		#.STACK, 24
pop rbx		#rbx
pop rdi		#rdi
ret 		#
add rsp, 24		#.STACK, 24
pop rbx		#rbx
pop rdi		#rdi
ret 		#
_Z4mainv_END:


.cfi_endproc 		#
_Z10Start_Testv_START:
.loc 1 13 1		#1 13 1
_Z10Start_Testv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
.loc 1 18 2		#1 18 2
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 24		#.STACK, 24
.loc 4 27 9		#4 27 9
mov ecx, 8		#REG_8_Parameter24084, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_1770844316352, RetREG_0
.loc 17 2 52		#17 2 52
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1770844316352_0, 1
.loc 4 27 2		#4 27 2
mov rbx, rcx		#Return_Value42, internal_allocate_TMP_1770844316352
jmp Return_Here_60		#Return_Here_60
.loc 1 14 13		#1 14 13
Return_Here_60:
mov rcx, rbx		#Return_Value42_TMP_1770844320672, Return_Value42
.loc 17 2 49		#17 2 49
add qword ptr [rcx + 0 ], 1		#Return_Value42_TMP_1770844320672_0, 1
.loc 1 14 13		#1 14 13
mov qword ptr [rsp + 16 ], rcx		#.STACK_16, Return_Value42_TMP_1770844320672
mov qword ptr [rsp + 16 ], rbx		#.STACK_16, Return_Value42
mov rcx, qword ptr [rsp + 16 ]		#this_43_REG1, .STACK_16
.loc 1 9 8		#1 9 8
mov dword ptr [rcx + 8 ], 1		#this_43_REG1_8, 1
mov rcx, qword ptr [rsp + 16 ]		#this_43_REG2, .STACK_16
.loc 1 10 8		#1 10 8
mov dword ptr [rcx + 12 ], 2		#this_43_REG2_12, 2
.loc 1 8 1		#1 8 1
mov rcx, qword ptr [rsp + 16 ]		#this_43_TMP_1770844328448, .STACK_16
.loc 17 2 42		#17 2 42
add qword ptr [rcx + 0 ], 1		#this_43_TMP_1770844328448_0, 1
.loc 1 8 1		#1 8 1
mov rdi, rcx		#Return_Value43, this_43_TMP_1770844328448
mov rdi, qword ptr [rsp + 16 ]		#Return_Value43, .STACK_16
jmp Return_Here_61		#Return_Here_61
.loc 1 14 10		#1 14 10
Return_Here_61:
mov rcx, qword ptr [rdi + 0 ]		#REG_Return_Value4308, Return_Value43_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value4308
mov rcx, qword ptr [rdi + 8 ]		#REG_Return_Value4318, Return_Value43_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value4318
.loc 1 15 19		#1 15 19
lea rcx, qword ptr [rsp + 0 ]		#F_REG3, .STACK_0
mov rcx, rcx		#F_TMP_1770844349184, F_REG3
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#F_TMP_1770844349184_0, 1
.loc 1 15 19		#1 15 19
mov rcx, rcx		#handle_1, F_TMP_1770844349184
.loc 1 9 2		#1 9 2
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG4, handle_1_8
.loc 1 17 8		#1 17 8
mov esi, r8d		#x, handle_1_8_REG4
.loc 17 1 10		#17 1 10
mov rcx, rcx		#REG_handle_1_Parameter19954, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value42_Parameter18756, Return_Value42
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_Return_Value43_Parameter11840, Return_Value43
call _ZN3foo10DestructorEP3foo
mov rcx, qword ptr [rsp + 16 ]		#REG_this_43_Parameter4966, .STACK_16
call _ZN3foo10DestructorEP3foo
.loc 1 18 2		#1 18 2
mov eax, esi		#Returning_REG9, x
add rsp, 24		#.STACK, 24
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
ret 		#
add rsp, 24		#.STACK, 24
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
ret 		#
_Z10Start_Testv_END:


.cfi_endproc 		#
_ZN3foo10DestructorEP3foo_START:
.loc 1 8 1		#1 8 1
_ZN3foo10DestructorEP3foo:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 16		#.STACK, 16
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this
.loc 17 1 1		#17 1 1
if_21:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_21_END		#if_21_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
.loc 1 8 1		#1 8 1
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
.loc 17 1 26		#17 1 26
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_21_END		#if_21_END
.loc 17 2 16		#17 2 16
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_1770844341408, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_1770844341408_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_1770844341408
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 4 19 2		#4 19 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_41_Parameter7376, .STACK_0
mov edx, 8		#REG_8_Parameter13931, 8
call _V19internal_deallocatePhx
.loc 17 2 1		#17 2 1
Return_Here_59:
.loc 17 1 12		#17 1 12
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_41_Parameter26308, .STACK_0
call _ZN3foo10DestructorEP3foo
if_21_END:
add rsp, 16		#.STACK, 16
ret 		#
_ZN3foo10DestructorEP3foo_END:


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
.byte 12		#12
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
.byte 9		#9
.quad _Z4mainv_START		#_Z4mainv_START
.long _Z4mainv_END		#_Z4mainv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z4mainv"		#_Z4mainv
.asciz "main"		#main
.byte 1		#1
.byte 3		#3
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "F_44"		#F_44
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "handle_1_44"		#handle_1_44
.byte 1		#1
.byte 15		#15
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x_44"		#x_44
.byte 1		#1
.byte 17		#17
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value42_44"		#Return_Value42_44
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value43_44"		#Return_Value43_44
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 16		#16
.asciz "this_43_44"		#this_43_44
.byte 1		#1
.byte 8		#8
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "internal_allocate_TMP_1770843322096"		#internal_allocate_TMP_1770843322096
.byte 4		#4
.byte 27		#27
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value42_44_TMP_1770844277472"		#Return_Value42_44_TMP_1770844277472
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "this_43_44_TMP_1770844280064"		#this_43_44_TMP_1770844280064
.byte 1		#1
.byte 8		#8
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "F_44_TMP_1770844299936"		#F_44_TMP_1770844299936
.byte 1		#1
.byte 15		#15
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 0		#0
_3foo_START:
.byte 5		#5
.byte 1		#1
.asciz "foo"		#foo
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
.byte 9		#9
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 12		#12
.asciz "Y"		#Y
.byte 1		#1
.byte 10		#10
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
.byte 13		#13
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "F"		#F
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "handle_1"		#handle_1
.byte 1		#1
.byte 15		#15
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "x"		#x
.byte 1		#1
.byte 17		#17
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value42"		#Return_Value42
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value43"		#Return_Value43
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 16		#16
.asciz "this_43"		#this_43
.byte 1		#1
.byte 8		#8
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "internal_allocate_TMP_1770844316352"		#internal_allocate_TMP_1770844316352
.byte 4		#4
.byte 27		#27
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value42_TMP_1770844320672"		#Return_Value42_TMP_1770844320672
.byte 1		#1
.byte 14		#14
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "this_43_TMP_1770844328448"		#this_43_TMP_1770844328448
.byte 1		#1
.byte 8		#8
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 10		#10
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "F_TMP_1770844349184"		#F_TMP_1770844349184
.byte 1		#1
.byte 15		#15
.long _3foo_START-Debug_Info_Start		#_3foo_START-Debug_Info_Start
.byte 0		#0
.byte 0		#0
Debug_Info_End:
.section .debug_str		#.debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"		#Evie engine 3.0.0 https://github.com/Gabidal/Evie
.FILE_NAME:
.asciz "Tests/IO/Destructor.e"		#Tests/IO/Destructor.e
.DIRECTORY:
.asciz "Tests/IO/"		#Tests/IO/
.section .LINE_TABLE		#.LINE_TABLE
.LINE_TABLE:
