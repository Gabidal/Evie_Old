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
mov rcx, rcx		#b_TMP_2097111965360, b_REG0
add qword ptr [rcx + 0 ], 1		#b_TMP_2097111965360_0, 1
mov rcx, rcx		#this_70, b_TMP_2097111965360
mov dword ptr [rcx + 8 ], 1		#this_70_8, 1
jmp Return_Here_96		#Return_Here_96
Return_Here_96:
lea rcx, qword ptr [rsp + 0 ]		#b_REG1, .STACK_0
mov rcx, rcx		#b_TMP_2097111980048, b_REG1
add qword ptr [rcx + 0 ], 1		#b_TMP_2097111980048_0, 1
mov rcx, rcx		#this_68, b_TMP_2097111980048
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8d, dword ptr [rcx + 8 ]		#this_68_8_REG2, this_68_8
add ebx, r8d		#Banana_Y_REGISTER, this_68_8_REG2
mov r8d, ebx		#Return_Value68, Banana_Y_REGISTER
jmp Return_Here_94		#Return_Here_94
Return_Here_94:
lea r9, qword ptr [rsp + 0 ]		#b_REG3, .STACK_0
mov r9, r9		#b_TMP_2097111972272, b_REG3
add qword ptr [r9 + 0 ], 1		#b_TMP_2097111972272_0, 1
mov rdi, r9		#this_69, b_TMP_2097111972272
mov dword ptr [rdi + 8 ], 1		#this_69_8, 1
mov r9d, dword ptr [rdi + 8 ]		#this_69_8_REG4, this_69_8
add r9d, 1		#this_69_8_REG4, 1
mov r9d, r9d		#Return_Value69, this_69_8_REG4
jmp Return_Here_95		#Return_Here_95
Return_Here_95:
mov r8d, r8d		#REG_Return_Value685, Return_Value68
add r8d, r9d		#REG_Return_Value685, Return_Value69
mov esi, r8d		#B_X, REG_Return_Value685
mov rcx, rcx		#REG_this_68_Parameter31107, this_68
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi		#REG_this_69_Parameter30191, this_69
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
lea rcx, qword ptr [rsp + 0 ]		#b_71_REG0, .STACK_0
mov rcx, rcx		#b_71_TMP_2097111989552, b_71_REG0
add qword ptr [rcx + 0 ], 1		#b_71_TMP_2097111989552_0, 1
mov rcx, rcx		#this_70_71, b_71_TMP_2097111989552
mov dword ptr [rcx + 8 ], 1		#this_70_71_8, 1
jmp Return_Here_98		#Return_Here_98
Return_Here_98:
lea rcx, qword ptr [rsp + 0 ]		#b_71_REG1, .STACK_0
mov rcx, rcx		#b_71_TMP_2097111995600, b_71_REG1
add qword ptr [rcx + 0 ], 1		#b_71_TMP_2097111995600_0, 1
mov rcx, rcx		#this_68_71, b_71_TMP_2097111995600
mov r8d, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r9d, dword ptr [rcx + 8 ]		#this_68_71_8_REG2, this_68_71_8
add r8d, r9d		#Banana_Y_REGISTER, this_68_71_8_REG2
mov r8d, r8d		#Return_Value68_71, Banana_Y_REGISTER
jmp Return_Here_99		#Return_Here_99
Return_Here_99:
lea r9, qword ptr [rsp + 0 ]		#b_71_REG3, .STACK_0
mov r9, r9		#b_71_TMP_2097112003376, b_71_REG3
add qword ptr [r9 + 0 ], 1		#b_71_TMP_2097112003376_0, 1
mov rbx, r9		#this_69_71, b_71_TMP_2097112003376
mov dword ptr [rbx + 8 ], 1		#this_69_71_8, 1
mov r9d, dword ptr [rbx + 8 ]		#this_69_71_8_REG4, this_69_71_8
add r9d, 1		#this_69_71_8_REG4, 1
mov r9d, r9d		#Return_Value69_71, this_69_71_8_REG4
jmp Return_Here_100		#Return_Here_100
Return_Here_100:
mov r8d, r8d		#REG_Return_Value68_715, Return_Value68_71
add r8d, r9d		#REG_Return_Value68_715, Return_Value69_71
mov r8d, r8d		#B_X_71, REG_Return_Value68_715
mov rcx, rcx		#REG_this_68_71_Parameter18007, this_68_71
call _ZN6Banana10DestructorEP6Banana
mov rcx, rbx		#REG_this_69_71_Parameter11337, this_69_71
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_97		#Return_Here_97
Return_Here_97:
mov eax, 1		#Returning_REG8, 1
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_29:
cmp rcx, 0		#this, 0
je if_29_END		#if_29_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_29_END		#if_29_END
mov r8, rcx		#this_TMP_2097112010288, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2097112010288_0, 1
mov rbx, r8		#Address_67, this_TMP_2097112010288
mov rbx, rcx		#Address_67, this
mov rcx, rbx		#REG_Address_67_Parameter15457, Address_67
mov edx, 8		#REG_8_Parameter12287, 8
call _V19internal_deallocatePhx
Return_Here_93:
mov rcx, rbx		#REG_Address_67_Parameter27753, Address_67
call _ZN6Banana10DestructorEP6Banana
if_29_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
Banana_Y:
.long 2		#2
Apple_X:
.long 2		#2
Apple_Y:
.long 3		#3
Apple_Z:
.long 3		#3
