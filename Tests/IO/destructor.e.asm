.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
mov ecx, 8		#REG_8_Parameter23199, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_2097132013760, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_2097132013760_0, 1
mov rbx, rcx		#Return_Value99_101, internal_allocate_TMP_2097132013760
jmp Return_Here_141		#Return_Here_141
Return_Here_141:
mov rcx, rbx		#Return_Value99_101_TMP_2097132045728, Return_Value99_101
add qword ptr [rcx + 0 ], 1		#Return_Value99_101_TMP_2097132045728_0, 1
mov rdi, rcx		#this_100_101, Return_Value99_101_TMP_2097132045728
mov rdi, rbx		#this_100_101, Return_Value99_101
mov dword ptr [rdi + 8 ], 1		#this_100_101_8, 1
mov dword ptr [rdi + 12 ], 2		#this_100_101_12, 2
mov rcx, rdi		#this_100_101_TMP_2097132038816, this_100_101
add qword ptr [rcx + 0 ], 1		#this_100_101_TMP_2097132038816_0, 1
mov rsi, rcx		#Return_Value100_101, this_100_101_TMP_2097132038816
mov rsi, rdi		#Return_Value100_101, this_100_101
jmp Return_Here_142		#Return_Here_142
Return_Here_142:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value100_10108, Return_Value100_101_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value100_10108
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value100_10118, Return_Value100_101_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value100_10118
lea rcx, qword ptr [rsp + 0 ]		#F_101_REG1, .STACK_0
mov rcx, rcx		#F_101_TMP_2097132049184, F_101_REG1
add qword ptr [rcx + 0 ], 1		#F_101_TMP_2097132049184_0, 1
mov rcx, rcx		#handle_1_101, F_101_TMP_2097132049184
mov r8d, dword ptr [rcx + 8 ]		#handle_1_101_8_REG2, handle_1_101_8
mov r8d, r8d		#x_101, handle_1_101_8_REG2
mov rcx, rcx		#REG_handle_1_101_Parameter19668, handle_1_101
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value99_101_Parameter24484, Return_Value99_101
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value100_101_Parameter8281, Return_Value100_101
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_100_101_Parameter4734, this_100_101
call _ZN3foo10DestructorEP3foo
jmp Return_Here_140		#Return_Here_140
Return_Here_140:
mov eax, 1		#Returning_REG7, 1
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


_Z10Start_Testv:
push rbp		#rbp
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
mov ecx, 8		#REG_8_Parameter53, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_2097132056096, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_2097132056096_0, 1
mov rbx, rcx		#Return_Value99, internal_allocate_TMP_2097132056096
jmp Return_Here_138		#Return_Here_138
Return_Here_138:
mov rcx, rbx		#Return_Value99_TMP_2097132065600, Return_Value99
add qword ptr [rcx + 0 ], 1		#Return_Value99_TMP_2097132065600_0, 1
mov rdi, rcx		#this_100, Return_Value99_TMP_2097132065600
mov rdi, rbx		#this_100, Return_Value99
mov dword ptr [rdi + 8 ], 1		#this_100_8, 1
mov dword ptr [rdi + 12 ], 2		#this_100_12, 2
mov rcx, rdi		#this_100_TMP_2097132089792, this_100
add qword ptr [rcx + 0 ], 1		#this_100_TMP_2097132089792_0, 1
mov rsi, rcx		#Return_Value100, this_100_TMP_2097132089792
mov rsi, rdi		#Return_Value100, this_100
jmp Return_Here_139		#Return_Here_139
Return_Here_139:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value10008, Return_Value100_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value10008
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value10018, Return_Value100_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value10018
lea rcx, qword ptr [rsp + 0 ]		#F_REG1, .STACK_0
mov rcx, rcx		#F_TMP_2097132071648, F_REG1
add qword ptr [rcx + 0 ], 1		#F_TMP_2097132071648_0, 1
mov rcx, rcx		#handle_1, F_TMP_2097132071648
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG2, handle_1_8
mov ebp, r8d		#x, handle_1_8_REG2
mov rcx, rcx		#REG_handle_1_Parameter1999, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value99_Parameter26418, Return_Value99
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value100_Parameter27938, Return_Value100
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_100_Parameter6900, this_100
call _ZN3foo10DestructorEP3foo
mov eax, ebp		#Returning_REG7, x
add rsp, 16		#.STACK, 16
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
ret 		#
add rsp, 16		#.STACK, 16
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
ret 		#


_ZN3foo10DestructorEP3foo:
push rbx		#rbx
if_44:
cmp rcx, 0		#this, 0
je if_44_END		#if_44_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_44_END		#if_44_END
mov r8, rcx		#this_TMP_2097132072512, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2097132072512_0, 1
mov rbx, r8		#Address_98, this_TMP_2097132072512
mov rbx, rcx		#Address_98, this
mov rcx, rbx		#REG_Address_98_Parameter3788, Address_98
mov edx, 8		#REG_8_Parameter18127, 8
call _V19internal_deallocatePhx
Return_Here_137:
mov rcx, rbx		#REG_Address_98_Parameter467, Address_98
call _ZN3foo10DestructorEP3foo
if_44_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
