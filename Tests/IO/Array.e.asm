.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
mov ecx, 10		#Size_99, 10
mov r8d, ecx		#REG_Size_990, Size_99
mov r9, rdx		#REG_Size_990_REMAINDER3602, REMAINDER_24350
mov eax, 4		#4_QUOTIENT4041, 4
mul r8d		#REG_Size_990
mov r8d, eax		#REG_Size_990, 4_QUOTIENT4041
mov rdx, r9		#REMAINDER_24350, REG_Size_990_REMAINDER3602
mov ecx, ecx		#REG_Size_991, Size_99
mov r8, rdx		#REG_Size_991_REMAINDER30836, REMAINDER_9374
mov eax, 4		#4_QUOTIENT10291, 4
mul ecx		#REG_Size_991
mov ecx, eax		#REG_Size_991, 4_QUOTIENT10291
mov rdx, r8		#REMAINDER_9374, REG_Size_991_REMAINDER30836
mov ecx, ecx		#REG_REG_Size_991_Parameter27595, REG_Size_991
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 8 ], rax		#.STACK_8, RetREG_2
jmp Return_Here_137		#Return_Here_137
Return_Here_137:
mov rcx, qword ptr [rsp + 8 ]		#REG_Return_Value993, .STACK_8
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_Return_Value993
lea rcx, qword ptr [rsp + 0 ]		#a_REG4, .STACK_0
mov rcx, rcx		#b, a_REG4
mov r8, qword ptr [rcx + 0 * 8 ]		#b_REG5, *
lea r8, qword ptr [r8 + 1 * 4 ]		#b_REG5_REG6, *
mov dword ptr [r8 ], 1		#b_REG5_REG6, 1
mov rcx, qword ptr [rcx + 0 * 8 ]		#b_REG7, *
mov ecx, dword ptr [rcx + 1 * 4 ]		#b_REG7_REG8, *
mov ecx, ecx		#c, b_REG7_REG8
mov eax, ecx		#Returning_REG9, c
add rsp, 16		#.STACK, 16
ret 		#
add rsp, 16		#.STACK, 16
ret 		#


_Z4mainv:
mov eax, 1		#Returning_REG0, 1
ret 		#
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
