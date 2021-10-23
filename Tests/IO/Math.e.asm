.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 6		#Return_Value100, 6
jmp Return_Here_132		#Return_Here_132
Return_Here_132:
mov r8d, ecx		#REG_Return_Value1000, Return_Value100
mov r9, rdx		#REG_Return_Value1000_REMAINDER28253, REMAINDER_6868
mov eax, 3		#3_QUOTIENT7711, 3
mul r8d		#REG_Return_Value1000
mov r8d, eax		#REG_Return_Value1000, 3_QUOTIENT7711
mov rdx, r9		#REMAINDER_6868, REG_Return_Value1000_REMAINDER28253
mov r8d, r8d		#c, REG_Return_Value1000
mov r9d, r8d		#REG_c1, c
xor edx, edx		#REG_c1_REMAINDER27644, REG_c1_REMAINDER27644
mov eax, r9d		#REG_c1_QUOTIENT25547, REG_c1
div ecx		#Return_Value100
mov r9d, eax		#REG_c1, REG_c1_QUOTIENT25547
mov ecx, r9d		#d, REG_c1
add ecx, 3		#d, 3
add ecx, 6		#d, 6
sub ecx, r8d		#d, c
mov eax, ecx		#Returning_REG2, d
ret 		#
mov ecx, 1065353216		#REG_1065385878, 1065353216
movd xmm0, ecx		#MEDIA_1065385973, REG_1065385878
movss xmm0, xmm0		#Return_Value101, MEDIA_1065385973
jmp Return_Here_133		#Return_Here_133
Return_Here_133:
cvttss2si ecx, xmm0		#REG_Return_Value1013, Return_Value101
mov eax, ecx		#Returning_REG4, REG_Return_Value1013
ret 		#
mov eax, -6		#Returning_REG5, -6
ret 		#
ret 		#


_Z4mainv:
mov ecx, 6		#Return_Value100_102, 6
jmp Return_Here_135		#Return_Here_135
Return_Here_135:
mov r8d, ecx		#REG_Return_Value100_1020, Return_Value100_102
mov r9, rdx		#REG_Return_Value100_1020_REMAINDER12859, REMAINDER_8723
mov eax, 3		#3_QUOTIENT20037, 3
mul r8d		#REG_Return_Value100_1020
mov r8d, eax		#REG_Return_Value100_1020, 3_QUOTIENT20037
mov rdx, r9		#REMAINDER_8723, REG_Return_Value100_1020_REMAINDER12859
mov r8d, r8d		#c_102, REG_Return_Value100_1020
mov r8d, r8d		#REG_c_1021, c_102
xor edx, edx		#REG_c_1021_REMAINDER27529, REG_c_1021_REMAINDER27529
mov eax, r8d		#REG_c_1021_QUOTIENT9741, REG_c_1021
div ecx		#Return_Value100_102
mov r8d, eax		#REG_c_1021, REG_c_1021_QUOTIENT9741
mov ecx, r8d		#d_102, REG_c_1021
jmp Return_Here_134		#Return_Here_134
mov ecx, 1065353216		#REG_1065353994, 1065353216
movd xmm0, ecx		#MEDIA_1065365532, REG_1065353994
movss xmm0, xmm0		#Return_Value101_102, MEDIA_1065365532
jmp Return_Here_136		#Return_Here_136
Return_Here_136:
jmp Return_Here_134		#Return_Here_134
jmp Return_Here_134		#Return_Here_134
Return_Here_134:
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
