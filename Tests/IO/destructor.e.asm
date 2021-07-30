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
mov rcx, rax		#internal_allocate_TMP_1542002326240, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1542002326240_0, 1
mov rbx, rcx		#Return_Value106_108, internal_allocate_TMP_1542002326240
jmp Return_Here_149		#Return_Here_149
Return_Here_149:
mov rcx, rbx		#Return_Value106_108_TMP_1542002327104, Return_Value106_108
add qword ptr [rcx + 0 ], 1		#Return_Value106_108_TMP_1542002327104_0, 1
mov rdi, rcx		#this_107_108, Return_Value106_108_TMP_1542002327104
mov rdi, rbx		#this_107_108, Return_Value106_108
mov dword ptr [rdi + 8 ], 1		#this_107_108_8, 1
mov dword ptr [rdi + 12 ], 2		#this_107_108_12, 2
mov rcx, rdi		#this_107_108_TMP_1542002331424, this_107_108
add qword ptr [rcx + 0 ], 1		#this_107_108_TMP_1542002331424_0, 1
mov rsi, rcx		#Return_Value107_108, this_107_108_TMP_1542002331424
mov rsi, rdi		#Return_Value107_108, this_107_108
jmp Return_Here_150		#Return_Here_150
Return_Here_150:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value107_10808, Return_Value107_108_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value107_10808
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value107_10818, Return_Value107_108_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value107_10818
lea rcx, qword ptr [rsp + 0 ]		#F_108_REG1, .STACK_0
mov rcx, rcx		#F_108_TMP_1542002369440, F_108_REG1
add qword ptr [rcx + 0 ], 1		#F_108_TMP_1542002369440_0, 1
mov rcx, rcx		#handle_1_108, F_108_TMP_1542002369440
mov r8d, dword ptr [rcx + 8 ]		#handle_1_108_8_REG2, handle_1_108_8
mov r8d, r8d		#x_108, handle_1_108_8_REG2
mov rcx, rcx		#REG_handle_1_108_Parameter18127, handle_1_108
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value106_108_Parameter467, Return_Value106_108
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value107_108_Parameter3728, Return_Value107_108
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_107_108_Parameter14893, this_107_108
call _ZN3foo10DestructorEP3foo
jmp Return_Here_148		#Return_Here_148
Return_Here_148:
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
mov rcx, rax		#internal_allocate_TMP_1542003214960, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1542003214960_0, 1
mov rbx, rcx		#Return_Value106, internal_allocate_TMP_1542003214960
jmp Return_Here_146		#Return_Here_146
Return_Here_146:
mov rcx, rbx		#Return_Value106_TMP_1542003218416, Return_Value106
add qword ptr [rcx + 0 ], 1		#Return_Value106_TMP_1542003218416_0, 1
mov rdi, rcx		#this_107, Return_Value106_TMP_1542003218416
mov rdi, rbx		#this_107, Return_Value106
mov dword ptr [rdi + 8 ], 1		#this_107_8, 1
mov dword ptr [rdi + 12 ], 2		#this_107_12, 2
mov rcx, rdi		#this_107_TMP_1542003227920, this_107
add qword ptr [rcx + 0 ], 1		#this_107_TMP_1542003227920_0, 1
mov rsi, rcx		#Return_Value107, this_107_TMP_1542003227920
mov rsi, rdi		#Return_Value107, this_107
jmp Return_Here_147		#Return_Here_147
Return_Here_147:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value10708, Return_Value107_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value10708
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value10718, Return_Value107_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value10718
lea rcx, qword ptr [rsp + 0 ]		#F_REG1, .STACK_0
mov rcx, rcx		#F_TMP_1542003207184, F_REG1
add qword ptr [rcx + 0 ], 1		#F_TMP_1542003207184_0, 1
mov rcx, rcx		#handle_1, F_TMP_1542003207184
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG2, handle_1_8
mov ebp, r8d		#x, handle_1_8_REG2
mov rcx, rcx		#REG_handle_1_Parameter22483, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value106_Parameter17807, Return_Value106
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value107_Parameter2421, Return_Value107
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_107_Parameter14310, this_107
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
mov r8, rcx		#this_TMP_1542003250384, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1542003250384_0, 1
mov rbx, r8		#Address_105, this_TMP_1542003250384
mov rbx, rcx		#Address_105, this
mov rcx, rbx		#REG_Address_105_Parameter6617, Address_105
mov edx, 8		#REG_8_Parameter22813, 8
call _V19internal_deallocatePhx
Return_Here_145:
mov rcx, rbx		#REG_Address_105_Parameter9514, Address_105
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
