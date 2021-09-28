.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
push rbx		#rbx
sub rsp, 32		#.STACK, 32
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_1710120792368, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1710120792368_0, 1
mov rbx, rcx		#this_61, a_TMP_1710120792368
mov dword ptr [rbx + 8 ], 1		#this_61_8, 1
mov dword ptr [rbx + 12 ], 0		#this_61_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_61_8_REG1, this_61_8
mov ecx, ecx		#Size_57_61, this_61_8_REG1
mov r8d, ecx		#REG_Size_57_612, Size_57_61
mov r9, rdx		#REG_Size_57_612_REMAINDER31673, REMAINDER_22386
mov eax, 4		#4_QUOTIENT2306, 4
mul r8d		#REG_Size_57_612
mov r8d, eax		#REG_Size_57_612, 4_QUOTIENT2306
mov rdx, r9		#REMAINDER_22386, REG_Size_57_612_REMAINDER31673
mov ecx, ecx		#REG_Size_57_613, Size_57_61
mov r8, rdx		#REG_Size_57_613_REMAINDER28745, REMAINDER_26924
mov eax, 4		#4_QUOTIENT5021, 4
mul ecx		#REG_Size_57_613
mov ecx, eax		#REG_Size_57_613, 4_QUOTIENT5021
mov rdx, r8		#REMAINDER_26924, REG_Size_57_613_REMAINDER28745
mov ecx, ecx		#REG_REG_Size_57_613_Parameter29658, REG_Size_57_613
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_80		#Return_Here_80
Return_Here_80:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value57_615, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_61_16, REG_Return_Value57_615
jmp Return_Here_79		#Return_Here_79
Return_Here_79:
mov ecx, 1		#Return_Value62, 1
jmp Return_Here_81		#Return_Here_81
Return_Here_81:
mov eax, ecx		#Returning_REG6, Return_Value62
add rsp, 32		#.STACK, 32
pop rbx		#rbx
ret 		#
add rsp, 32		#.STACK, 32
pop rbx		#rbx
ret 		#


_Z4mainv:
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_ZN13____List_int_10DestructorEP13____List_int_:
push rbx		#rbx
if_24:
cmp rcx, 0		#this, 0
je if_24_END		#if_24_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_24_END		#if_24_END
mov r8, rcx		#this_TMP_1710120794160, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1710120794160_0, 1
mov rbx, r8		#Address_60, this_TMP_1710120794160
mov rbx, rcx		#Address_60, this
mov rcx, rbx		#REG_Address_60_Parameter22704, Address_60
mov edx, 8		#REG_8_Parameter9930, 8
call _V19internal_deallocatePhx
Return_Here_78:
mov rcx, rbx		#REG_Address_60_Parameter13977, Address_60
call _ZN13____List_int_10DestructorEP13____List_int_
if_24_END:
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
