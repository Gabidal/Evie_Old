.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
mov ecx, 8		#REG_8_Parameter1999, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_1724654753648, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1724654753648_0, 1
mov rbx, rcx		#Return_Value98_100, internal_allocate_TMP_1724654753648
jmp Return_Here_135		#Return_Here_135
Return_Here_135:
mov rcx, rbx		#Return_Value98_100_TMP_1724654758832, Return_Value98_100
add qword ptr [rcx + 0 ], 1		#Return_Value98_100_TMP_1724654758832_0, 1
mov rdi, rcx		#this_99_100, Return_Value98_100_TMP_1724654758832
mov rdi, rbx		#this_99_100, Return_Value98_100
mov dword ptr [rdi + 8 ], 1		#this_99_100_8, 1
mov dword ptr [rdi + 12 ], 2		#this_99_100_12, 2
mov rcx, rdi		#this_99_100_TMP_1724654802896, this_99_100
add qword ptr [rcx + 0 ], 1		#this_99_100_TMP_1724654802896_0, 1
mov rsi, rcx		#Return_Value99_100, this_99_100_TMP_1724654802896
mov rsi, rdi		#Return_Value99_100, this_99_100
jmp Return_Here_136		#Return_Here_136
Return_Here_136:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value99_10008, Return_Value99_100_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value99_10008
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value99_10018, Return_Value99_100_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value99_10018
lea rcx, qword ptr [rsp + 0 ]		#F_100_REG1, .STACK_0
mov rcx, rcx		#F_100_TMP_1724654806352, F_100_REG1
add qword ptr [rcx + 0 ], 1		#F_100_TMP_1724654806352_0, 1
mov rcx, rcx		#handle_1_100, F_100_TMP_1724654806352
mov r8d, dword ptr [rcx + 8 ]		#handle_1_100_8_REG2, handle_1_100_8
mov r8d, r8d		#x_100, handle_1_100_8_REG2
mov rcx, rcx		#REG_handle_1_100_Parameter26418, handle_1_100
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value98_100_Parameter27938, Return_Value98_100
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value99_100_Parameter6900, Return_Value99_100
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_99_100_Parameter3788, this_99_100
call _ZN3foo10DestructorEP3foo
jmp Return_Here_134		#Return_Here_134
Return_Here_134:
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
mov ecx, 8		#REG_8_Parameter18127, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_1724654793392, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_1724654793392_0, 1
mov rbx, rcx		#Return_Value98, internal_allocate_TMP_1724654793392
jmp Return_Here_132		#Return_Here_132
Return_Here_132:
mov rcx, rbx		#Return_Value98_TMP_1724654816720, Return_Value98
add qword ptr [rcx + 0 ], 1		#Return_Value98_TMP_1724654816720_0, 1
mov rdi, rcx		#this_99, Return_Value98_TMP_1724654816720
mov rdi, rbx		#this_99, Return_Value98
mov dword ptr [rdi + 8 ], 1		#this_99_8, 1
mov dword ptr [rdi + 12 ], 2		#this_99_12, 2
mov rcx, rdi		#this_99_TMP_1724654815856, this_99
add qword ptr [rcx + 0 ], 1		#this_99_TMP_1724654815856_0, 1
mov rsi, rcx		#Return_Value99, this_99_TMP_1724654815856
mov rsi, rdi		#Return_Value99, this_99
jmp Return_Here_133		#Return_Here_133
Return_Here_133:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value9908, Return_Value99_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value9908
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value9918, Return_Value99_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value9918
lea rcx, qword ptr [rsp + 0 ]		#F_REG1, .STACK_0
mov rcx, rcx		#F_TMP_1724654827952, F_REG1
add qword ptr [rcx + 0 ], 1		#F_TMP_1724654827952_0, 1
mov rcx, rcx		#handle_1, F_TMP_1724654827952
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG2, handle_1_8
mov ebp, r8d		#x, handle_1_8_REG2
mov rcx, rcx		#REG_handle_1_Parameter467, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value98_Parameter3728, Return_Value98
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value99_Parameter14893, Return_Value99
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_99_Parameter24648, this_99
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
mov r8, rcx		#this_TMP_1724654843504, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1724654843504_0, 1
mov rbx, r8		#Address_97, this_TMP_1724654843504
mov rbx, rcx		#Address_97, this
mov rcx, rbx		#REG_Address_97_Parameter22483, Address_97
mov edx, 8		#REG_8_Parameter17807, 8
call _V19internal_deallocatePhx
Return_Here_131:
mov rcx, rbx		#REG_Address_97_Parameter2421, Address_97
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
