.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 6		#Return_Value94, 6
jmp Return_Here_126		#Return_Here_126
Return_Here_126:
mov r8d, ecx		#REG_Return_Value940, Return_Value94
mov r9, rdx		#REG_Return_Value940_REMAINDER10291, REMAINDER_30836
mov eax, 3		#3_QUOTIENT24350, 3
mul r8d		#REG_Return_Value940
mov r8d, eax		#REG_Return_Value940, 3_QUOTIENT24350
mov rdx, r9		#REMAINDER_30836, REG_Return_Value940_REMAINDER10291
mov r8d, r8d		#c, REG_Return_Value940
mov r9d, r8d		#REG_c1, c
xor edx, edx		#REG_c1_REMAINDER11020, REG_c1_REMAINDER11020
mov eax, r9d		#REG_c1_QUOTIENT9374, REG_c1
div ecx		#Return_Value94
mov r9d, eax		#REG_c1, REG_c1_QUOTIENT9374
mov ecx, r9d		#d, REG_c1
add ecx, 3		#d, 3
add ecx, 6		#d, 6
sub ecx, r8d		#d, c
mov eax, ecx		#Returning_REG2, d
ret 		#
mov ecx, 1065353216		#REG_1065357812, 1065353216
movd xmm0, ecx		#MEDIA_1065377237, REG_1065357812
movss xmm0, xmm0		#Return_Value95, MEDIA_1065377237
jmp Return_Here_127		#Return_Here_127
Return_Here_127:
cvttss2si ecx, xmm0		#REG_Return_Value953, Return_Value95
mov eax, ecx		#Returning_REG4, REG_Return_Value953
ret 		#
mov eax, -6		#Returning_REG5, -6
ret 		#
ret 		#


_Z4mainv:
mov ecx, 6		#Return_Value94_96, 6
jmp Return_Here_129		#Return_Here_129
Return_Here_129:
mov r8d, ecx		#REG_Return_Value94_960, Return_Value94_96
mov r9, rdx		#REG_Return_Value94_960_REMAINDER23199, REMAINDER_19668
mov eax, 3		#3_QUOTIENT27348, 3
mul r8d		#REG_Return_Value94_960
mov r8d, eax		#REG_Return_Value94_960, 3_QUOTIENT27348
mov rdx, r9		#REMAINDER_19668, REG_Return_Value94_960_REMAINDER23199
mov r8d, r8d		#c_96, REG_Return_Value94_960
mov r8d, r8d		#REG_c_961, c_96
xor edx, edx		#REG_c_961_REMAINDER8281, REG_c_961_REMAINDER8281
mov eax, r8d		#REG_c_961_QUOTIENT24484, REG_c_961
div ecx		#Return_Value94_96
mov r8d, eax		#REG_c_961, REG_c_961_QUOTIENT24484
mov ecx, r8d		#d_96, REG_c_961
jmp Return_Here_128		#Return_Here_128
mov ecx, 1065353216		#REG_1065357950, 1065353216
movd xmm0, ecx		#MEDIA_1065353269, REG_1065357950
movss xmm0, xmm0		#Return_Value95_96, MEDIA_1065353269
jmp Return_Here_130		#Return_Here_130
Return_Here_130:
jmp Return_Here_128		#Return_Here_128
jmp Return_Here_128		#Return_Here_128
Return_Here_128:
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
