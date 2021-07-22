.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
mov ecx, 8		#REG_8_Parameter10291, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_2787269255808, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_2787269255808_0, 1
mov rbx, rcx		#Return_Value93_95, internal_allocate_TMP_2787269255808
jmp Return_Here_132		#Return_Here_132
Return_Here_132:
mov rcx, rbx		#Return_Value93_95_TMP_2787269244992, Return_Value93_95
add qword ptr [rcx + 0 ], 1		#Return_Value93_95_TMP_2787269244992_0, 1
mov rdi, rcx		#this_94_95, Return_Value93_95_TMP_2787269244992
mov rdi, rbx		#this_94_95, Return_Value93_95
mov dword ptr [rdi + 8 ], 1		#this_94_95_8, 1
mov dword ptr [rdi + 12 ], 2		#this_94_95_12, 2
mov rcx, rdi		#this_94_95_TMP_2787269260800, this_94_95
add qword ptr [rcx + 0 ], 1		#this_94_95_TMP_2787269260800_0, 1
mov rsi, rcx		#Return_Value94_95, this_94_95_TMP_2787269260800
mov rsi, rdi		#Return_Value94_95, this_94_95
jmp Return_Here_133		#Return_Here_133
Return_Here_133:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value94_9508, Return_Value94_95_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value94_9508
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value94_9518, Return_Value94_95_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value94_9518
lea rcx, qword ptr [rsp + 0 ]		#F_95_REG1, .STACK_0
mov rcx, rcx		#F_95_TMP_2787269265792, F_95_REG1
add qword ptr [rcx + 0 ], 1		#F_95_TMP_2787269265792_0, 1
mov rcx, rcx		#handle_1_95, F_95_TMP_2787269265792
mov r8d, dword ptr [rcx + 8 ]		#handle_1_95_8_REG2, handle_1_95_8
mov r8d, r8d		#x_95, handle_1_95_8_REG2
mov rcx, rcx		#REG_handle_1_95_Parameter30836, handle_1_95
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value93_95_Parameter9374, Return_Value93_95
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value94_95_Parameter11020, Return_Value94_95
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_94_95_Parameter4596, this_94_95
call _ZN3foo10DestructorEP3foo
jmp Return_Here_131		#Return_Here_131
Return_Here_131:
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
mov ecx, 8		#REG_8_Parameter24021, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_2787269239168, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_2787269239168_0, 1
mov rbx, rcx		#Return_Value93, internal_allocate_TMP_2787269239168
jmp Return_Here_129		#Return_Here_129
Return_Here_129:
mov rcx, rbx		#Return_Value93_TMP_2787269304896, Return_Value93
add qword ptr [rcx + 0 ], 1		#Return_Value93_TMP_2787269304896_0, 1
mov rdi, rcx		#this_94, Return_Value93_TMP_2787269304896
mov rdi, rbx		#this_94, Return_Value93
mov dword ptr [rdi + 8 ], 1		#this_94_8, 1
mov dword ptr [rdi + 12 ], 2		#this_94_12, 2
mov rcx, rdi		#this_94_TMP_2787269284928, this_94
add qword ptr [rcx + 0 ], 1		#this_94_TMP_2787269284928_0, 1
mov rsi, rcx		#Return_Value94, this_94_TMP_2787269284928
mov rsi, rdi		#Return_Value94, this_94
jmp Return_Here_130		#Return_Here_130
Return_Here_130:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value9408, Return_Value94_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value9408
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value9418, Return_Value94_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value9418
lea rcx, qword ptr [rsp + 0 ]		#F_REG1, .STACK_0
mov rcx, rcx		#F_TMP_2787269308224, F_REG1
add qword ptr [rcx + 0 ], 1		#F_TMP_2787269308224_0, 1
mov rcx, rcx		#handle_1, F_TMP_2787269308224
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG2, handle_1_8
mov ebp, r8d		#x, handle_1_8_REG2
mov rcx, rcx		#REG_handle_1_Parameter27348, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value93_Parameter23199, Return_Value93
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value94_Parameter19668, Return_Value94
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_94_Parameter24484, this_94
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
if_43:
cmp rcx, 0		#this, 0
je if_43_END		#if_43_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_43_END		#if_43_END
mov r8, rcx		#this_TMP_2787269307392, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2787269307392_0, 1
mov rbx, r8		#Address_92, this_TMP_2787269307392
mov rbx, rcx		#Address_92, this
mov rcx, rbx		#REG_Address_92_Parameter8281, Address_92
mov edx, 8		#REG_8_Parameter4734, 8
call _V19internal_deallocatePhx
Return_Here_128:
mov rcx, rbx		#REG_Address_92_Parameter53, Address_92
call _ZN3foo10DestructorEP3foo
if_43_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
