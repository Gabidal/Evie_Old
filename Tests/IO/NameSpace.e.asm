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
mov rcx, rcx		#b_TMP_1541955802464, b_REG0
add qword ptr [rcx + 0 ], 1		#b_TMP_1541955802464_0, 1
mov rcx, rcx		#this_77, b_TMP_1541955802464
mov dword ptr [rcx + 8 ], 1		#this_77_8, 1
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_104		#Return_Here_104
Return_Here_104:
lea rcx, qword ptr [rsp + 0 ]		#b_REG1, .STACK_0
mov rcx, rcx		#b_TMP_1541955814560, b_REG1
add qword ptr [rcx + 0 ], 1		#b_TMP_1541955814560_0, 1
mov rcx, rcx		#this_75, b_TMP_1541955814560
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8d, dword ptr [rcx + 8 ]		#this_75_8_REG2, this_75_8
add ebx, r8d		#Banana_Y_REGISTER, this_75_8_REG2
mov r8d, ebx		#Return_Value75, Banana_Y_REGISTER
jmp Return_Here_102		#Return_Here_102
Return_Here_102:
lea r9, qword ptr [rsp + 0 ]		#b_REG3, .STACK_0
mov r9, r9		#b_TMP_1541955826656, b_REG3
add qword ptr [r9 + 0 ], 1		#b_TMP_1541955826656_0, 1
mov rdi, r9		#this_76, b_TMP_1541955826656
mov dword ptr [rdi + 8 ], 1		#this_76_8, 1
mov r9d, dword ptr [rdi + 8 ]		#this_76_8_REG4, this_76_8
add r9d, 1		#this_76_8_REG4, 1
mov r9d, r9d		#Return_Value76, this_76_8_REG4
jmp Return_Here_103		#Return_Here_103
Return_Here_103:
mov r8d, r8d		#REG_Return_Value755, Return_Value75
add r8d, r9d		#REG_Return_Value755, Return_Value76
mov esi, r8d		#B_X, REG_Return_Value755
mov rcx, rcx		#REG_this_75_Parameter32209, this_75
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi		#REG_this_76_Parameter9758, this_76
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
lea rcx, qword ptr [rsp + 0 ]		#b_78_REG0, .STACK_0
mov rcx, rcx		#b_78_TMP_1541955805056, b_78_REG0
add qword ptr [rcx + 0 ], 1		#b_78_TMP_1541955805056_0, 1
mov rcx, rcx		#this_77_78, b_78_TMP_1541955805056
mov dword ptr [rcx + 8 ], 1		#this_77_78_8, 1
mov dword ptr [rip + Banana_Y ], 2		#.RIP_Banana_Y, 2
jmp Return_Here_106		#Return_Here_106
Return_Here_106:
lea rcx, qword ptr [rsp + 0 ]		#b_78_REG1, .STACK_0
mov rcx, rcx		#b_78_TMP_1541955808512, b_78_REG1
add qword ptr [rcx + 0 ], 1		#b_78_TMP_1541955808512_0, 1
mov rcx, rcx		#this_75_78, b_78_TMP_1541955808512
mov r8d, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r9d, dword ptr [rcx + 8 ]		#this_75_78_8_REG2, this_75_78_8
add r8d, r9d		#Banana_Y_REGISTER, this_75_78_8_REG2
mov r8d, r8d		#Return_Value75_78, Banana_Y_REGISTER
jmp Return_Here_107		#Return_Here_107
Return_Here_107:
lea r9, qword ptr [rsp + 0 ]		#b_78_REG3, .STACK_0
mov r9, r9		#b_78_TMP_1541955849984, b_78_REG3
add qword ptr [r9 + 0 ], 1		#b_78_TMP_1541955849984_0, 1
mov rbx, r9		#this_76_78, b_78_TMP_1541955849984
mov dword ptr [rbx + 8 ], 1		#this_76_78_8, 1
mov r9d, dword ptr [rbx + 8 ]		#this_76_78_8_REG4, this_76_78_8
add r9d, 1		#this_76_78_8_REG4, 1
mov r9d, r9d		#Return_Value76_78, this_76_78_8_REG4
jmp Return_Here_108		#Return_Here_108
Return_Here_108:
mov r8d, r8d		#REG_Return_Value75_785, Return_Value75_78
add r8d, r9d		#REG_Return_Value75_785, Return_Value76_78
mov r8d, r8d		#B_X_78, REG_Return_Value75_785
mov rcx, rcx		#REG_this_75_78_Parameter24221, this_75_78
call _ZN6Banana10DestructorEP6Banana
mov rcx, rbx		#REG_this_76_78_Parameter18588, this_76_78
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_105		#Return_Here_105
Return_Here_105:
mov eax, 1		#Returning_REG8, 1
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_30:
cmp rcx, 0		#this, 0
je if_30_END		#if_30_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_30_END		#if_30_END
mov r8, rcx		#this_TMP_1541955863808, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1541955863808_0, 1
mov rbx, r8		#Address_74, this_TMP_1541955863808
mov rbx, rcx		#Address_74, this
mov rcx, rbx		#REG_Address_74_Parameter6422, Address_74
mov edx, 8		#REG_8_Parameter24946, 8
call _V19internal_deallocatePhx
Return_Here_101:
mov rcx, rbx		#REG_Address_74_Parameter27506, Address_74
call _ZN6Banana10DestructorEP6Banana
if_30_END:
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
