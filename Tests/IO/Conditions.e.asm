.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 0		#i, 0
cmp ecx, 100		#i, 100
jge while_35_END		#while_35_END
while_35:
add ecx, 1		#i, 1
cmp ecx, 100		#i, 100
jge while_35_END		#while_35_END
jmp while_35		#while_35
while_35_END:
if_36:
cmp ecx, 100		#i, 100
jne if_36_END		#if_36_END
mov ecx, 10		#i, 10
if_36_END:
if_37:
cmp ecx, 100		#i, 100
jne else_38		#else_38
mov ecx, 100		#i, 100
jmp else_38_END		#else_38_END
if_37_END:
else_38:
cmp ecx, 10		#i, 10
jne else_38_END		#else_38_END
mov ecx, 100		#i, 100
else_38_END:
mov eax, ecx		#Returning_REG0, i
ret 		#
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_39_END		#while_39_END
while_39:
mov ecx, 1		#REG_12, 1
cmp ecx, 2		#REG_12, 2
jge while_39_END		#while_39_END
jmp while_39		#while_39
while_39_END:
mov eax, 0		#Returning_REG3, 0
ret 		#
ret 		#


_Z4mainv:
mov ecx, 0		#i_94, 0
cmp ecx, 100		#i_94, 100
jge while_40_END		#while_40_END
while_40:
add ecx, 1		#i_94, 1
cmp ecx, 100		#i_94, 100
jge while_40_END		#while_40_END
jmp while_40		#while_40
while_40_END:
if_41:
cmp ecx, 100		#i_94, 100
jne if_41_END		#if_41_END
mov ecx, 10		#i_94, 10
if_41_END:
if_42:
cmp ecx, 100		#i_94, 100
jne else_43		#else_43
mov ecx, 100		#i_94, 100
jmp else_43_END		#else_43_END
if_42_END:
else_43:
cmp ecx, 10		#i_94, 10
jne else_43_END		#else_43_END
mov ecx, 100		#i_94, 100
else_43_END:
jmp Return_Here_132		#Return_Here_132
mov ecx, 1		#REG_10, 1
cmp ecx, 2		#REG_10, 2
jge while_44_END		#while_44_END
while_44:
mov ecx, 1		#REG_11, 1
cmp ecx, 2		#REG_11, 2
jge while_44_END		#while_44_END
jmp while_44		#while_44
while_44_END:
jmp Return_Here_132		#Return_Here_132
Return_Here_132:
mov eax, 1		#Returning_REG2, 1
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
