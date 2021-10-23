.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
push rbx		#rbx
sub rsp, 28		#.STACK, 28
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_2241996320048, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_2241996320048_0, 1
mov rbx, rcx		#this_78, a_TMP_2241996320048
mov dword ptr [rbx + 8 ], 1		#this_78_8, 1
mov dword ptr [rbx + 12 ], 0		#this_78_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_78_8_REG1, this_78_8
mov ecx, ecx		#Size_45_78, this_78_8_REG1
mov r8d, ecx		#REG_Size_45_782, Size_45_78
mov r9, rdx		#REG_Size_45_782_REMAINDER1869, REMAINDER_19912
mov eax, 4		#4_QUOTIENT11538, 4
mul r8d		#REG_Size_45_782
mov r8d, eax		#REG_Size_45_782, 4_QUOTIENT11538
mov rdx, r9		#REMAINDER_19912, REG_Size_45_782_REMAINDER1869
mov ecx, ecx		#REG_Size_45_783, Size_45_78
mov r8, rdx		#REG_Size_45_783_REMAINDER26299, REMAINDER_17035
mov eax, 4		#4_QUOTIENT25667, 4
mul ecx		#REG_Size_45_783
mov ecx, eax		#REG_Size_45_783, 4_QUOTIENT25667
mov rdx, r8		#REMAINDER_17035, REG_Size_45_783_REMAINDER26299
mov ecx, ecx		#REG_REG_Size_45_783_Parameter14771, REG_Size_45_783
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 20 ], rax		#.STACK_20, RetREG_4
jmp Return_Here_102		#Return_Here_102
Return_Here_102:
mov rcx, qword ptr [rsp + 20 ]		#REG_Return_Value45_785, .STACK_20
mov qword ptr [rbx + 16 ], rcx		#this_78_16, REG_Return_Value45_785
jmp Return_Here_101		#Return_Here_101
Return_Here_101:
mov ecx, 1		#Return_Value79, 1
jmp Return_Here_103		#Return_Here_103
Return_Here_103:
mov eax, ecx		#Returning_REG6, Return_Value79
add rsp, 28		#.STACK, 28
pop rbx		#rbx
ret 		#
add rsp, 28		#.STACK, 28
pop rbx		#rbx
ret 		#


_Z4mainv:
mov eax, 1		#Returning_REG0, 1
ret 		#
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
