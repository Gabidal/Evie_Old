.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 6		#Return_Value101, 6
jmp Return_Here_139		#Return_Here_139
Return_Here_139:
mov r8d, ecx		#REG_Return_Value1010, Return_Value101
mov r9, rdx		#REG_Return_Value1010_REMAINDER4596, REMAINDER_24021
mov eax, 3		#3_QUOTIENT11020, 3
mul r8d		#REG_Return_Value1010
mov r8d, eax		#REG_Return_Value1010, 3_QUOTIENT11020
mov rdx, r9		#REMAINDER_24021, REG_Return_Value1010_REMAINDER4596
mov r8d, r8d		#c, REG_Return_Value1010
mov r9d, r8d		#REG_c1, c
xor edx, edx		#REG_c1_REMAINDER23199, REG_c1_REMAINDER23199
mov eax, r9d		#REG_c1_QUOTIENT27348, REG_c1
div ecx		#Return_Value101
mov r9d, eax		#REG_c1, REG_c1_QUOTIENT27348
mov ecx, r9d		#d, REG_c1
add ecx, 3		#d, 3
add ecx, 6		#d, 6
sub ecx, r8d		#d, c
mov eax, ecx		#Returning_REG2, d
ret 		#
mov ecx, 1065353216		#REG_1065372884, 1065353216
movd xmm0, ecx		#MEDIA_1065377700, REG_1065372884
movss xmm0, xmm0		#Return_Value102, MEDIA_1065377700
jmp Return_Here_140		#Return_Here_140
Return_Here_140:
cvttss2si ecx, xmm0		#REG_Return_Value1023, Return_Value102
mov eax, ecx		#Returning_REG4, REG_Return_Value1023
ret 		#
mov eax, -6		#Returning_REG5, -6
ret 		#
ret 		#


_Z4mainv:
mov ecx, 6		#Return_Value101_103, 6
jmp Return_Here_142		#Return_Here_142
Return_Here_142:
mov r8d, ecx		#REG_Return_Value101_1030, Return_Value101_103
mov r9, rdx		#REG_Return_Value101_1030_REMAINDER4734, REMAINDER_53
mov eax, 3		#3_QUOTIENT8281, 3
mul r8d		#REG_Return_Value101_1030
mov r8d, eax		#REG_Return_Value101_1030, 3_QUOTIENT8281
mov rdx, r9		#REMAINDER_53, REG_Return_Value101_1030_REMAINDER4734
mov r8d, r8d		#c_103, REG_Return_Value101_1030
mov r8d, r8d		#REG_c_1031, c_103
xor edx, edx		#REG_c_1031_REMAINDER26418, REG_c_1031_REMAINDER26418
mov eax, r8d		#REG_c_1031_QUOTIENT1999, REG_c_1031
div ecx		#Return_Value101_103
mov r8d, eax		#REG_c_1031, REG_c_1031_QUOTIENT1999
mov ecx, r8d		#d_103, REG_c_1031
jmp Return_Here_141		#Return_Here_141
mov ecx, 1065353216		#REG_1065381154, 1065353216
movd xmm0, ecx		#MEDIA_1065360116, REG_1065381154
movss xmm0, xmm0		#Return_Value102_103, MEDIA_1065360116
jmp Return_Here_143		#Return_Here_143
Return_Here_143:
jmp Return_Here_141		#Return_Here_141
jmp Return_Here_141		#Return_Here_141
Return_Here_141:
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
