.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 6		#Return_Value96, 6
jmp Return_Here_134		#Return_Here_134
Return_Here_134:
mov r8d, ecx		#REG_Return_Value960, Return_Value96
mov r9, rdx		#REG_Return_Value960_REMAINDER4596, REMAINDER_24021
mov eax, 3		#3_QUOTIENT11020, 3
mul r8d		#REG_Return_Value960
mov r8d, eax		#REG_Return_Value960, 3_QUOTIENT11020
mov rdx, r9		#REMAINDER_24021, REG_Return_Value960_REMAINDER4596
mov r8d, r8d		#c, REG_Return_Value960
mov r9d, r8d		#REG_c1, c
xor edx, edx		#REG_c1_REMAINDER23199, REG_c1_REMAINDER23199
mov eax, r9d		#REG_c1_QUOTIENT27348, REG_c1
div ecx		#Return_Value96
mov r9d, eax		#REG_c1, REG_c1_QUOTIENT27348
mov ecx, r9d		#d, REG_c1
add ecx, 3		#d, 3
add ecx, 6		#d, 6
sub ecx, r8d		#d, c
mov eax, ecx		#Returning_REG2, d
ret 		#
mov ecx, 1065353216		#REG_1065372884, 1065353216
movd xmm0, ecx		#MEDIA_1065377700, REG_1065372884
movss xmm0, xmm0		#Return_Value97, MEDIA_1065377700
jmp Return_Here_135		#Return_Here_135
Return_Here_135:
cvttss2si ecx, xmm0		#REG_Return_Value973, Return_Value97
mov eax, ecx		#Returning_REG4, REG_Return_Value973
ret 		#
mov eax, -6		#Returning_REG5, -6
ret 		#
ret 		#


_Z4mainv:
mov ecx, 6		#Return_Value96_98, 6
jmp Return_Here_137		#Return_Here_137
Return_Here_137:
mov r8d, ecx		#REG_Return_Value96_980, Return_Value96_98
mov r9, rdx		#REG_Return_Value96_980_REMAINDER4734, REMAINDER_53
mov eax, 3		#3_QUOTIENT8281, 3
mul r8d		#REG_Return_Value96_980
mov r8d, eax		#REG_Return_Value96_980, 3_QUOTIENT8281
mov rdx, r9		#REMAINDER_53, REG_Return_Value96_980_REMAINDER4734
mov r8d, r8d		#c_98, REG_Return_Value96_980
mov r8d, r8d		#REG_c_981, c_98
xor edx, edx		#REG_c_981_REMAINDER26418, REG_c_981_REMAINDER26418
mov eax, r8d		#REG_c_981_QUOTIENT1999, REG_c_981
div ecx		#Return_Value96_98
mov r8d, eax		#REG_c_981, REG_c_981_QUOTIENT1999
mov ecx, r8d		#d_98, REG_c_981
jmp Return_Here_136		#Return_Here_136
mov ecx, 1065353216		#REG_1065381154, 1065353216
movd xmm0, ecx		#MEDIA_1065360116, REG_1065381154
movss xmm0, xmm0		#Return_Value97_98, MEDIA_1065360116
jmp Return_Here_138		#Return_Here_138
Return_Here_138:
jmp Return_Here_136		#Return_Here_136
jmp Return_Here_136		#Return_Here_136
Return_Here_136:
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
