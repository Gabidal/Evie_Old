.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
lea rcx, qword ptr [rsp + 0 ]		#b_REG0, .STACK_0
mov rcx, rcx		#b_TMP_1722818465376, b_REG0
add qword ptr [rcx + 0 ], 1		#b_TMP_1722818465376_0, 1
mov rcx, rcx		#this_83, b_TMP_1722818465376
mov dword ptr [rcx + 8 ], 1		#this_83_8, 1
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_116		#Return_Here_116
Return_Here_116:
lea rcx, qword ptr [rsp + 0 ]		#b_REG1, .STACK_0
mov rcx, rcx		#b_TMP_1722818448096, b_REG1
add qword ptr [rcx + 0 ], 1		#b_TMP_1722818448096_0, 1
mov rcx, rcx		#this_81, b_TMP_1722818448096
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8d, dword ptr [rcx + 8 ]		#this_81_8_REG2, this_81_8
add ebx, r8d		#Banana_Y_REGISTER, this_81_8_REG2
mov r8d, ebx		#Return_Value81, Banana_Y_REGISTER
jmp Return_Here_114		#Return_Here_114
Return_Here_114:
lea r9, qword ptr [rsp + 0 ]		#b_REG3, .STACK_0
mov r9, r9		#b_TMP_1722818454144, b_REG3
add qword ptr [r9 + 0 ], 1		#b_TMP_1722818454144_0, 1
mov rdi, r9		#this_82, b_TMP_1722818454144
mov dword ptr [rdi + 8 ], 1		#this_82_8, 1
mov r9d, dword ptr [rdi + 8 ]		#this_82_8_REG4, this_82_8
add r9d, 1		#this_82_8_REG4, 1
mov r9d, r9d		#Return_Value82, this_82_8_REG4
jmp Return_Here_115		#Return_Here_115
Return_Here_115:
mov r8d, r8d		#REG_Return_Value815, Return_Value81
add r8d, r9d		#REG_Return_Value815, Return_Value82
mov esi, r8d		#B_X, REG_Return_Value815
mov rcx, rcx		#REG_this_81_Parameter18588, this_81
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi		#REG_this_82_Parameter6422, this_82
call _ZN6Banana10DestructorEP6Banana
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov ecx, dword ptr [rip + Apple_Y ]		#Apple_Y_REGISTER, .RIP_Apple_Y
add ebx, ecx		#Banana_Y_REGISTER, Apple_Y_REGISTER
sub ebx, esi		#Banana_Y_REGISTER, B_X
mov eax, ebx		#Returning_REG8, Banana_Y_REGISTER
add rsp, 16		#.STACK, 16
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
ret 		#
add rsp, 16		#.STACK, 16
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
ret 		#


_Z4mainv:
push rbx		#rbx
sub rsp, 16		#.STACK, 16
lea rcx, qword ptr [rsp + 0 ]		#b_84_REG0, .STACK_0
mov rcx, rcx		#b_84_TMP_1722818470560, b_84_REG0
add qword ptr [rcx + 0 ], 1		#b_84_TMP_1722818470560_0, 1
mov rcx, rcx		#this_83_84, b_84_TMP_1722818470560
mov dword ptr [rcx + 8 ], 1		#this_83_84_8, 1
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_118		#Return_Here_118
Return_Here_118:
lea rcx, qword ptr [rsp + 0 ]		#b_84_REG1, .STACK_0
mov rcx, rcx		#b_84_TMP_1722818498208, b_84_REG1
add qword ptr [rcx + 0 ], 1		#b_84_TMP_1722818498208_0, 1
mov rcx, rcx		#this_81_84, b_84_TMP_1722818498208
mov r8d, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r9d, dword ptr [rcx + 8 ]		#this_81_84_8_REG2, this_81_84_8
add r8d, r9d		#Banana_Y_REGISTER, this_81_84_8_REG2
mov r8d, r8d		#Return_Value81_84, Banana_Y_REGISTER
jmp Return_Here_119		#Return_Here_119
Return_Here_119:
lea r9, qword ptr [rsp + 0 ]		#b_84_REG3, .STACK_0
mov r9, r9		#b_84_TMP_1722818518944, b_84_REG3
add qword ptr [r9 + 0 ], 1		#b_84_TMP_1722818518944_0, 1
mov rbx, r9		#this_82_84, b_84_TMP_1722818518944
mov dword ptr [rbx + 8 ], 1		#this_82_84_8, 1
mov r9d, dword ptr [rbx + 8 ]		#this_82_84_8_REG4, this_82_84_8
add r9d, 1		#this_82_84_8_REG4, 1
mov r9d, r9d		#Return_Value82_84, this_82_84_8_REG4
jmp Return_Here_120		#Return_Here_120
Return_Here_120:
mov r8d, r8d		#REG_Return_Value81_845, Return_Value81_84
add r8d, r9d		#REG_Return_Value81_845, Return_Value82_84
mov r8d, r8d		#B_X_84, REG_Return_Value81_845
mov rcx, rcx		#REG_this_81_84_Parameter24946, this_81_84
call _ZN6Banana10DestructorEP6Banana
mov rcx, rbx		#REG_this_82_84_Parameter27506, this_82_84
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_117		#Return_Here_117
Return_Here_117:
mov eax, 1		#Returning_REG8, 1
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_31:
cmp rcx, 0		#this, 0
je if_31_END		#if_31_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_31_END		#if_31_END
mov r8, rcx		#this_TMP_1722818532768, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1722818532768_0, 1
mov rbx, r8		#Address_80, this_TMP_1722818532768
mov rbx, rcx		#Address_80, this
mov rcx, rbx		#REG_Address_80_Parameter13030, Address_80
mov edx, 8		#REG_8_Parameter16413, 8
call _V19internal_deallocatePhx
Return_Here_113:
mov rcx, rbx		#REG_Address_80_Parameter29168, Address_80
call _ZN6Banana10DestructorEP6Banana
if_31_END:
pop rbx		#rbx
ret 		#


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
