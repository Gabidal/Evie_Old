.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
Return_Here_123:
lea rcx, qword ptr [rsp + 0 ]		#m_REG0, .STACK_0
mov rcx, rcx		#m_TMP_2242033719216, m_REG0
add qword ptr [rcx + 0 ], 1		#m_TMP_2242033719216_0, 1
mov rcx, rcx		#this_95, m_TMP_2242033719216
mov r8, rcx		#this_95_TMP_2242033705776, this_95
add qword ptr [r8 + 0 ], 1		#this_95_TMP_2242033705776_0, 1
mov r8, r8		#this_94_95, this_95_TMP_2242033705776
mov r8, rcx		#this_94_95, this_95
mov dword ptr [r8 + 8 ], 0		#this_94_95_8, 0
jmp Return_Here_126		#Return_Here_126
Return_Here_126:
mov dword ptr [rcx + 8 ], 1		#this_95_8, 1
mov r8d, 1074261268		#REG_1074271162, 1074261268
mov dword ptr [rcx + 12 ], r8d		#this_95_12, REG_1074271162
jmp Return_Here_125		#Return_Here_125
Return_Here_125:
movss xmm0, dword ptr [rsp + 0 + 12 ]		#m_12_REG1, +_12
cvttss2si ecx, xmm0		#REG_feature2, m_12_REG1
mov eax, ecx		#Returning_REG3, REG_feature2
add rsp, 16		#.STACK, 16
ret 		#
add rsp, 16		#.STACK, 16
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
