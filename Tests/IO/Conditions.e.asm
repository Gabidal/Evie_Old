.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 0		#i, 0
cmp ecx, 100		#i, 100
jge while_6_END		#while_6_END
while_6:
add ecx, 1		#i, 1
cmp ecx, 100		#i, 100
jge while_6_END		#while_6_END
jmp while_6		#while_6
while_6_END:
if_7:
cmp ecx, 100		#i, 100
jne if_7_END		#if_7_END
mov ecx, 10		#i, 10
if_7_END:
if_8:
cmp ecx, 100		#i, 100
jne else_9		#else_9
mov ecx, 100		#i, 100
jmp else_9_END		#else_9_END
if_8_END:
else_9:
cmp ecx, 10		#i, 10
jne else_9_END		#else_9_END
mov ecx, 100		#i, 100
else_9_END:
mov eax, ecx		#Returning_REG0, i
ret 		#
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_10_END		#while_10_END
while_10:
mov ecx, 1		#REG_12, 1
cmp ecx, 2		#REG_12, 2
jge while_10_END		#while_10_END
jmp while_10		#while_10
while_10_END:
mov eax, 0		#Returning_REG3, 0
ret 		#
ret 		#


_Z4mainv:
mov ecx, 0		#i_98, 0
cmp ecx, 100		#i_98, 100
jge while_11_END		#while_11_END
while_11:
add ecx, 1		#i_98, 1
cmp ecx, 100		#i_98, 100
jge while_11_END		#while_11_END
jmp while_11		#while_11
while_11_END:
if_12:
cmp ecx, 100		#i_98, 100
jne if_12_END		#if_12_END
mov ecx, 10		#i_98, 10
if_12_END:
if_13:
cmp ecx, 100		#i_98, 100
jne else_14		#else_14
mov ecx, 100		#i_98, 100
jmp else_14_END		#else_14_END
if_13_END:
else_14:
cmp ecx, 10		#i_98, 10
jne else_14_END		#else_14_END
mov ecx, 100		#i_98, 100
else_14_END:
jmp Return_Here_130		#Return_Here_130
mov ecx, 1		#REG_10, 1
cmp ecx, 2		#REG_10, 2
jge while_15_END		#while_15_END
while_15:
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_15_END		#while_15_END
jmp while_15		#while_15
while_15_END:
jmp Return_Here_130		#Return_Here_130
Return_Here_130:
mov eax, 1		#Returning_REG2, 1
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
