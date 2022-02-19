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
mov rcx, rcx		#b_TMP_2244092917568, b_REG0
add qword ptr [rcx + 0 ], 1		#b_TMP_2244092917568_0, 1
mov rcx, rcx		#this_43, b_TMP_2244092917568
mov dword ptr [rcx + 8 ], 1		#this_43_8, 1
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_57		#Return_Here_57
Return_Here_57:
lea rcx, qword ptr [rsp + 0 ]		#b_REG1, .STACK_0
mov rcx, rcx		#b_TMP_2244092925632, b_REG1
add qword ptr [rcx + 0 ], 1		#b_TMP_2244092925632_0, 1
mov rcx, rcx		#this_41, b_TMP_2244092925632
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8d, dword ptr [rcx + 8 ]		#this_41_8_REG2, this_41_8
add ebx, r8d		#Banana_Y_REGISTER, this_41_8_REG2
mov r8d, ebx		#Return_Value41, Banana_Y_REGISTER
jmp Return_Here_55		#Return_Here_55
Return_Here_55:
lea r9, qword ptr [rsp + 0 ]		#b_REG3, .STACK_0
mov r9, r9		#b_TMP_2244092956096, b_REG3
add qword ptr [r9 + 0 ], 1		#b_TMP_2244092956096_0, 1
mov rdi, r9		#this_42, b_TMP_2244092956096
mov dword ptr [rdi + 8 ], 1		#this_42_8, 1
mov r9d, dword ptr [rdi + 8 ]		#this_42_8_REG4, this_42_8
add r9d, 1		#this_42_8_REG4, 1
mov r9d, r9d		#Return_Value42, this_42_8_REG4
jmp Return_Here_56		#Return_Here_56
Return_Here_56:
mov r8d, r8d		#REG_Return_Value415, Return_Value41
add r8d, r9d		#REG_Return_Value415, Return_Value42
mov esi, r8d		#B_X, REG_Return_Value415
mov rcx, rcx		#REG_this_41_Parameter18716, this_41
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi		#REG_this_42_Parameter19718, this_42
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
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_5:
cmp rcx, 0		#this, 0
je if_5_END		#if_5_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_5_END		#if_5_END
mov r8, rcx		#this_TMP_2244092974912, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2244092974912_0, 1
mov rbx, r8		#Address_40, this_TMP_2244092974912
mov rbx, rcx		#Address_40, this
mov rcx, rbx		#REG_Address_40_Parameter19895, Address_40
mov edx, 8		#REG_8_Parameter5447, 8
call _V19internal_deallocatePhx
Return_Here_54:
mov rcx, rbx		#REG_Address_40_Parameter21726, Address_40
call _ZN6Banana10DestructorEP6Banana
if_5_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
std_MAX_CONSOLE_BUFFER_LENGHT:
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
