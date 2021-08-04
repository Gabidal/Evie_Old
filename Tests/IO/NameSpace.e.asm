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
mov rcx, rcx		#b_TMP_2250258636512, b_REG0
add qword ptr [rcx + 0 ], 1		#b_TMP_2250258636512_0, 1
mov rcx, rcx		#this_55, b_TMP_2250258636512
mov dword ptr [rcx + 8 ], 1		#this_55_8, 1
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_73		#Return_Here_73
Return_Here_73:
lea rcx, qword ptr [rsp + 0 ]		#b_REG1, .STACK_0
mov rcx, rcx		#b_TMP_2250258620960, b_REG1
add qword ptr [rcx + 0 ], 1		#b_TMP_2250258620960_0, 1
mov rcx, rcx		#this_53, b_TMP_2250258620960
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8d, dword ptr [rcx + 8 ]		#this_53_8_REG2, this_53_8
add ebx, r8d		#Banana_Y_REGISTER, this_53_8_REG2
mov r8d, ebx		#Return_Value53, Banana_Y_REGISTER
jmp Return_Here_71		#Return_Here_71
Return_Here_71:
lea r9, qword ptr [rsp + 0 ]		#b_REG3, .STACK_0
mov r9, r9		#b_TMP_2250258614048, b_REG3
add qword ptr [r9 + 0 ], 1		#b_TMP_2250258614048_0, 1
mov rdi, r9		#this_54, b_TMP_2250258614048
mov dword ptr [rdi + 8 ], 1		#this_54_8, 1
mov r9d, dword ptr [rdi + 8 ]		#this_54_8_REG4, this_54_8
add r9d, 1		#this_54_8_REG4, 1
mov r9d, r9d		#Return_Value54, this_54_8_REG4
jmp Return_Here_72		#Return_Here_72
Return_Here_72:
mov r8d, r8d		#REG_Return_Value535, Return_Value53
add r8d, r9d		#REG_Return_Value535, Return_Value54
mov esi, r8d		#B_X, REG_Return_Value535
mov rcx, rcx		#REG_this_53_Parameter22929, this_53
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi		#REG_this_54_Parameter16541, this_54
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
if_23:
cmp rcx, 0		#this, 0
je if_23_END		#if_23_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_23_END		#if_23_END
mov r8, rcx		#this_TMP_2250258653792, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2250258653792_0, 1
mov rbx, r8		#Address_52, this_TMP_2250258653792
mov rbx, rcx		#Address_52, this
mov rcx, rbx		#REG_Address_52_Parameter4833, Address_52
mov edx, 8		#REG_8_Parameter31115, 8
call _V19internal_deallocatePhx
Return_Here_70:
mov rcx, rbx		#REG_Address_52_Parameter4639, Address_52
call _ZN6Banana10DestructorEP6Banana
if_23_END:
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
