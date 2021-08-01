.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
mov ecx, 8		#REG_8_Parameter3788, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_1722852226448, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1722852226448_0, 1
mov rbx, rcx		#Return_Value100_102, internal_allocate_TMP_1722852226448
jmp Return_Here_143		#Return_Here_143
Return_Here_143:
mov rcx, rbx		#Return_Value100_102_TMP_1722852230768, Return_Value100_102
add qword ptr [rcx + 0 ], 1		#Return_Value100_102_TMP_1722852230768_0, 1
mov rdi, rcx		#this_101_102, Return_Value100_102_TMP_1722852230768
mov rdi, rbx		#this_101_102, Return_Value100_102
mov dword ptr [rdi + 8 ], 1		#this_101_102_8, 1
mov dword ptr [rdi + 12 ], 2		#this_101_102_12, 2
mov rcx, rdi		#this_101_102_TMP_1722852247184, this_101_102
add qword ptr [rcx + 0 ], 1		#this_101_102_TMP_1722852247184_0, 1
mov rsi, rcx		#Return_Value101_102, this_101_102_TMP_1722852247184
mov rsi, rdi		#Return_Value101_102, this_101_102
jmp Return_Here_144		#Return_Here_144
Return_Here_144:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value101_10208, Return_Value101_102_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value101_10208
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value101_10218, Return_Value101_102_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value101_10218
lea rcx, qword ptr [rsp + 0 ]		#F_102_REG1, .STACK_0
mov rcx, rcx		#F_102_TMP_1722852245456, F_102_REG1
add qword ptr [rcx + 0 ], 1		#F_102_TMP_1722852245456_0, 1
mov rcx, rcx		#handle_1_102, F_102_TMP_1722852245456
mov r8d, dword ptr [rcx + 8 ]		#handle_1_102_8_REG2, handle_1_102_8
mov r8d, r8d		#x_102, handle_1_102_8_REG2
mov rcx, rcx		#REG_handle_1_102_Parameter18127, handle_1_102
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value100_102_Parameter467, Return_Value100_102
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value101_102_Parameter3728, Return_Value101_102
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_101_102_Parameter14893, this_101_102
call _ZN3foo10DestructorEP3foo
jmp Return_Here_142		#Return_Here_142
Return_Here_142:
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
mov ecx, 8		#REG_8_Parameter24648, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_1722852261872, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1722852261872_0, 1
mov rbx, rcx		#Return_Value100, internal_allocate_TMP_1722852261872
jmp Return_Here_140		#Return_Here_140
Return_Here_140:
mov rcx, rbx		#Return_Value100_TMP_1722852280880, Return_Value100
add qword ptr [rcx + 0 ], 1		#Return_Value100_TMP_1722852280880_0, 1
mov rdi, rcx		#this_101, Return_Value100_TMP_1722852280880
mov rdi, rbx		#this_101, Return_Value100
mov dword ptr [rdi + 8 ], 1		#this_101_8, 1
mov dword ptr [rdi + 12 ], 2		#this_101_12, 2
mov rcx, rdi		#this_101_TMP_1722852251504, this_101
add qword ptr [rcx + 0 ], 1		#this_101_TMP_1722852251504_0, 1
mov rsi, rcx		#Return_Value101, this_101_TMP_1722852251504
mov rsi, rdi		#Return_Value101, this_101
jmp Return_Here_141		#Return_Here_141
Return_Here_141:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value10108, Return_Value101_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value10108
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value10118, Return_Value101_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value10118
lea rcx, qword ptr [rsp + 0 ]		#F_REG1, .STACK_0
mov rcx, rcx		#F_TMP_1722852259280, F_REG1
add qword ptr [rcx + 0 ], 1		#F_TMP_1722852259280_0, 1
mov rcx, rcx		#handle_1, F_TMP_1722852259280
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG2, handle_1_8
mov ebp, r8d		#x, handle_1_8_REG2
mov rcx, rcx		#REG_handle_1_Parameter22483, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value100_Parameter17807, Return_Value100
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value101_Parameter2421, Return_Value101
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_101_Parameter14310, this_101
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
if_45:
cmp rcx, 0		#this, 0
je if_45_END		#if_45_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_45_END		#if_45_END
mov r8, rcx		#this_TMP_1722852292112, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1722852292112_0, 1
mov rbx, r8		#Address_99, this_TMP_1722852292112
mov rbx, rcx		#Address_99, this
mov rcx, rbx		#REG_Address_99_Parameter6617, Address_99
mov edx, 8		#REG_8_Parameter22813, 8
call _V19internal_deallocatePhx
Return_Here_139:
mov rcx, rbx		#REG_Address_99_Parameter9514, Address_99
call _ZN3foo10DestructorEP3foo
if_45_END:
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
