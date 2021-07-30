.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text		#.text
_Z4mainv:
lea rcx, qword ptr [rip + foo ]		#foo_REG0, .RIP_foo
mov rcx, rcx		#fuz_87, foo_REG0
jmp Return_Here_123		#Return_Here_123
Return_Here_123:
mov eax, 1		#Returning_REG1, 1
ret 		#
ret 		#


foo:
mov eax, 5		#Returning_REG0, 5
ret 		#
ret 		#


_Z10Start_Testv:
lea rcx, qword ptr [rip + foo ]		#foo_REG0, .RIP_foo
mov rcx, rcx		#fuz, foo_REG0
call rcx
mov eax, eax		#Returning_REG2, RetREG_1
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
