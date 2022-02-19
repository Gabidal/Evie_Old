.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 16		#.STACK, 16
mov ecx, 8		#REG_8_Parameter3035, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_2242078961568, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_2242078961568_0, 1
mov rbx, rcx		#Return_Value104_106, internal_allocate_TMP_2242078961568
jmp Return_Here_141		#Return_Here_141
Return_Here_141:
mov rcx, rbx		#Return_Value104_106_TMP_2242078963360, Return_Value104_106
add qword ptr [rcx + 0 ], 1		#Return_Value104_106_TMP_2242078963360_0, 1
mov rdi, rcx		#this_105_106, Return_Value104_106_TMP_2242078963360
mov rdi, rbx		#this_105_106, Return_Value104_106
mov dword ptr [rdi + 8 ], 1		#this_105_106_8, 1
mov dword ptr [rdi + 12 ], 2		#this_105_106_12, 2
mov rcx, rdi		#this_105_106_TMP_2242078985760, this_105_106
add qword ptr [rcx + 0 ], 1		#this_105_106_TMP_2242078985760_0, 1
mov rsi, rcx		#Return_Value105_106, this_105_106_TMP_2242078985760
mov rsi, rdi		#Return_Value105_106, this_105_106
jmp Return_Here_142		#Return_Here_142
Return_Here_142:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value105_10608, Return_Value105_106_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value105_10608
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value105_10618, Return_Value105_106_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value105_10618
lea rcx, qword ptr [rsp + 0 ]		#F_106_REG1, .STACK_0
mov rcx, rcx		#F_106_TMP_2242078993824, F_106_REG1
add qword ptr [rcx + 0 ], 1		#F_106_TMP_2242078993824_0, 1
mov rcx, rcx		#handle_1_106, F_106_TMP_2242078993824
mov r8d, dword ptr [rcx + 8 ]		#handle_1_106_8_REG2, handle_1_106_8
mov r8d, r8d		#x_106, handle_1_106_8_REG2
mov rcx, rcx		#REG_handle_1_106_Parameter22190, handle_1_106
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value104_106_Parameter1842, Return_Value104_106
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value105_106_Parameter288, Return_Value105_106
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_105_106_Parameter30106, this_105_106
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
mov ecx, 8		#REG_8_Parameter9040, 8
call _V17internal_allocatex_rPh
mov rcx, rax		#internal_allocate_TMP_2242079015328, RetREG_0
add qword ptr [rcx + 0 ], 1		#internal_allocate_TMP_2242079015328_0, 1
mov rbx, rcx		#Return_Value104, internal_allocate_TMP_2242079015328
jmp Return_Here_138		#Return_Here_138
Return_Here_138:
mov rcx, rbx		#Return_Value104_TMP_2242079018016, Return_Value104
add qword ptr [rcx + 0 ], 1		#Return_Value104_TMP_2242079018016_0, 1
mov rdi, rcx		#this_105, Return_Value104_TMP_2242079018016
mov rdi, rbx		#this_105, Return_Value104
mov dword ptr [rdi + 8 ], 1		#this_105_8, 1
mov dword ptr [rdi + 12 ], 2		#this_105_12, 2
mov rcx, rdi		#this_105_TMP_2242079059232, this_105
add qword ptr [rcx + 0 ], 1		#this_105_TMP_2242079059232_0, 1
mov rsi, rcx		#Return_Value105, this_105_TMP_2242079059232
mov rsi, rdi		#Return_Value105, this_105
jmp Return_Here_139		#Return_Here_139
Return_Here_139:
mov rcx, qword ptr [rsi + 0 ]		#REG_Return_Value10508, Return_Value105_0
mov qword ptr [rsp + 0 + 0 ], rcx		#+_0, REG_Return_Value10508
mov rcx, qword ptr [rsi + 8 ]		#REG_Return_Value10518, Return_Value105_8
mov qword ptr [rsp + 0 + 8 ], rcx		#+_8, REG_Return_Value10518
lea rcx, qword ptr [rsp + 0 ]		#F_REG1, .STACK_0
mov rcx, rcx		#F_TMP_2242079044896, F_REG1
add qword ptr [rcx + 0 ], 1		#F_TMP_2242079044896_0, 1
mov rcx, rcx		#handle_1, F_TMP_2242079044896
mov r8d, dword ptr [rcx + 8 ]		#handle_1_8_REG2, handle_1_8
mov ebp, r8d		#x, handle_1_8_REG2
mov rcx, rcx		#REG_handle_1_Parameter8942, handle_1
call _ZN3foo10DestructorEP3foo
mov rcx, rbx		#REG_Return_Value104_Parameter19264, Return_Value104
call _ZN3foo10DestructorEP3foo
mov rcx, rsi		#REG_Return_Value105_Parameter22648, Return_Value105
call _ZN3foo10DestructorEP3foo
mov rcx, rdi		#REG_this_105_Parameter27446, this_105
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
if_16:
cmp rcx, 0		#this, 0
je if_16_END		#if_16_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_16_END		#if_16_END
mov r8, rcx		#this_TMP_2242079075360, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2242079075360_0, 1
mov rbx, r8		#Address_103, this_TMP_2242079075360
mov rbx, rcx		#Address_103, this
mov rcx, rbx		#REG_Address_103_Parameter23805, Address_103
mov edx, 8		#REG_8_Parameter15890, 8
call _V19internal_deallocatePhx
Return_Here_137:
mov rcx, rbx		#REG_Address_103_Parameter6729, Address_103
call _ZN3foo10DestructorEP3foo
if_16_END:
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
