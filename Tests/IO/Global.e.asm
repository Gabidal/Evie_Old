.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, dword ptr [rip + a ]		#REG_a0, .RIP_a
add ecx, dword ptr [rip + b ]		#REG_a0, .RIP_b
mov eax, ecx		#Returning_REG1, REG_a0
ret 		#
ret 		#


_Z4mainv:
jmp Return_Here_139		#Return_Here_139
Return_Here_139:
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


.section .data		#.data
a:
.long 1		#1
b:
.long 3		#3
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
GLOBAL_SCOPE_a:
.long 0		#0
GLOBAL_SCOPE_b:
.long 0		#0
