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
mov rcx, rcx		#b_TMP_1445914144464, b_REG0
add qword ptr [rcx + 0 ], 1		#b_TMP_1445914144464_0, 1
mov rcx, rcx		#this_100, b_TMP_1445914144464
mov dword ptr [rcx + 8 ], 1		#this_100_8, 1
jmp Return_Here_138		#Return_Here_138
Return_Here_138:
lea rcx, qword ptr [rsp + 0 ]		#b_REG1, .STACK_0
mov rcx, rcx		#b_TMP_1445914154448, b_REG1
add qword ptr [rcx + 0 ], 1		#b_TMP_1445914154448_0, 1
mov rcx, rcx		#this_98, b_TMP_1445914154448
mov ebx, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r8d, dword ptr [rcx + 8 ]		#this_98_8_REG2, this_98_8
add ebx, r8d		#Banana_Y_REGISTER, this_98_8_REG2
mov r8d, ebx		#Return_Value98, Banana_Y_REGISTER
jmp Return_Here_136		#Return_Here_136
Return_Here_136:
lea r9, qword ptr [rsp + 0 ]		#b_REG3, .STACK_0
mov r9, r9		#b_TMP_1445914152784, b_REG3
add qword ptr [r9 + 0 ], 1		#b_TMP_1445914152784_0, 1
mov rdi, r9		#this_99, b_TMP_1445914152784
mov dword ptr [rdi + 8 ], 1		#this_99_8, 1
mov r9d, dword ptr [rdi + 8 ]		#this_99_8_REG4, this_99_8
add r9d, 1		#this_99_8_REG4, 1
mov r9d, r9d		#Return_Value99, this_99_8_REG4
jmp Return_Here_137		#Return_Here_137
Return_Here_137:
mov r8d, r8d		#REG_Return_Value985, Return_Value98
add r8d, r9d		#REG_Return_Value985, Return_Value99
mov esi, r8d		#B_X, REG_Return_Value985
mov rcx, rcx		#REG_this_98_Parameter1999, this_98
call _ZN6Banana10DestructorEP6Banana
mov rcx, rdi		#REG_this_99_Parameter26418, this_99
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
lea rcx, qword ptr [rsp + 0 ]		#b_101_REG0, .STACK_0
mov rcx, rcx		#b_101_TMP_1445914176912, b_101_REG0
add qword ptr [rcx + 0 ], 1		#b_101_TMP_1445914176912_0, 1
mov rcx, rcx		#this_100_101, b_101_TMP_1445914176912
mov dword ptr [rcx + 8 ], 1		#this_100_101_8, 1
jmp Return_Here_140		#Return_Here_140
Return_Here_140:
lea rcx, qword ptr [rsp + 0 ]		#b_101_REG1, .STACK_0
mov rcx, rcx		#b_101_TMP_1445914176080, b_101_REG1
add qword ptr [rcx + 0 ], 1		#b_101_TMP_1445914176080_0, 1
mov rcx, rcx		#this_98_101, b_101_TMP_1445914176080
mov r8d, dword ptr [rip + Banana_Y ]		#Banana_Y_REGISTER, .RIP_Banana_Y
mov r9d, dword ptr [rcx + 8 ]		#this_98_101_8_REG2, this_98_101_8
add r8d, r9d		#Banana_Y_REGISTER, this_98_101_8_REG2
mov r8d, r8d		#Return_Value98_101, Banana_Y_REGISTER
jmp Return_Here_141		#Return_Here_141
Return_Here_141:
lea r9, qword ptr [rsp + 0 ]		#b_101_REG3, .STACK_0
mov r9, r9		#b_101_TMP_1445915175168, b_101_REG3
add qword ptr [r9 + 0 ], 1		#b_101_TMP_1445915175168_0, 1
mov rbx, r9		#this_99_101, b_101_TMP_1445915175168
mov dword ptr [rbx + 8 ], 1		#this_99_101_8, 1
mov r9d, dword ptr [rbx + 8 ]		#this_99_101_8_REG4, this_99_101_8
add r9d, 1		#this_99_101_8_REG4, 1
mov r9d, r9d		#Return_Value99_101, this_99_101_8_REG4
jmp Return_Here_142		#Return_Here_142
Return_Here_142:
mov r8d, r8d		#REG_Return_Value98_1015, Return_Value98_101
add r8d, r9d		#REG_Return_Value98_1015, Return_Value99_101
mov r8d, r8d		#B_X_101, REG_Return_Value98_1015
mov rcx, rcx		#REG_this_98_101_Parameter27938, this_98_101
call _ZN6Banana10DestructorEP6Banana
mov rcx, rbx		#REG_this_99_101_Parameter6900, this_99_101
call _ZN6Banana10DestructorEP6Banana
jmp Return_Here_139		#Return_Here_139
Return_Here_139:
mov eax, 1		#Returning_REG8, 1
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#
add rsp, 16		#.STACK, 16
pop rbx		#rbx
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_44:
cmp rcx, 0		#this, 0
je if_44_END		#if_44_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_44_END		#if_44_END
mov r8, rcx		#this_TMP_1445915145216, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1445915145216_0, 1
mov rbx, r8		#Address_97, this_TMP_1445915145216
mov rbx, rcx		#Address_97, this
mov rcx, rbx		#REG_Address_97_Parameter3788, Address_97
mov edx, 8		#REG_8_Parameter18127, 8
call _V19internal_deallocatePhx
Return_Here_135:
mov rcx, rbx		#REG_Address_97_Parameter467, Address_97
call _ZN6Banana10DestructorEP6Banana
if_44_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
Banana_Y:
.long 2		#2
Apple_X:
.long 2		#2
Apple_Y:
.long 3		#3
