.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_2242019697712, x_REG0
add qword ptr [rcx + 0 ], 1		#x_TMP_2242019697712_0, 1
mov rcx, rcx		#this_86, x_TMP_2242019697712
mov r8, rcx		#this_86_TMP_2242019702192, this_86
add qword ptr [r8 + 0 ], 1		#this_86_TMP_2242019702192_0, 1
mov r8, r8		#this_85_86, this_86_TMP_2242019702192
mov r8, rcx		#this_85_86, this_86
mov dword ptr [r8 + 8 ], 4		#this_85_86_8, 4
Return_Here_111:
mov dword ptr [rcx + 12 ], 1		#this_86_12, 1
mov dword ptr [rcx + 16 ], 2		#this_86_16, 2
mov dword ptr [rcx + 20 ], 6		#this_86_20, 6
mov dword ptr [rcx + 8 ], 5		#this_86_8, 5
jmp Return_Here_110		#Return_Here_110
Return_Here_110:
lea rcx, qword ptr [rsp + 0 ]		#x_REG1, .STACK_0
mov rcx, rcx		#x_TMP_2242020510256, x_REG1
add qword ptr [rcx + 0 ], 1		#x_TMP_2242020510256_0, 1
mov rcx, rcx		#f_87, x_TMP_2242020510256
mov r8, rcx		#f_87_TMP_2242020494128, f_87
add qword ptr [r8 + 0 ], 1		#f_87_TMP_2242020494128_0, 1
mov r8, r8		#b_84_87, f_87_TMP_2242020494128
mov r8, rcx		#b_84_87, f_87
jmp Return_Here_113		#Return_Here_113
Return_Here_113:
mov ecx, dword ptr [r8 + 12 ]		#b_84_87_12_REG2, b_84_87_12
mov ecx, ecx		#Return_Value87, b_84_87_12_REG2
jmp Return_Here_112		#Return_Here_112
Return_Here_112:
mov eax, ecx		#Returning_REG3, Return_Value87
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_Z4mainv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_88_REG0, .STACK_0
mov rcx, rcx		#x_88_TMP_2242020530864, x_88_REG0
add qword ptr [rcx + 0 ], 1		#x_88_TMP_2242020530864_0, 1
mov rcx, rcx		#this_86_88, x_88_TMP_2242020530864
mov r8, rcx		#this_86_88_TMP_2242020572080, this_86_88
add qword ptr [r8 + 0 ], 1		#this_86_88_TMP_2242020572080_0, 1
mov r8, r8		#this_85_86_88, this_86_88_TMP_2242020572080
mov r8, rcx		#this_85_86_88, this_86_88
mov dword ptr [r8 + 8 ], 4		#this_85_86_88_8, 4
Return_Here_115:
mov dword ptr [rcx + 12 ], 1		#this_86_88_12, 1
mov dword ptr [rcx + 16 ], 2		#this_86_88_16, 2
mov dword ptr [rcx + 20 ], 6		#this_86_88_20, 6
mov dword ptr [rcx + 8 ], 5		#this_86_88_8, 5
jmp Return_Here_116		#Return_Here_116
Return_Here_116:
lea rcx, qword ptr [rsp + 0 ]		#x_88_REG1, .STACK_0
mov rcx, rcx		#x_88_TMP_2242020548784, x_88_REG1
add qword ptr [rcx + 0 ], 1		#x_88_TMP_2242020548784_0, 1
mov rcx, rcx		#f_87_88, x_88_TMP_2242020548784
mov r8, rcx		#f_87_88_TMP_2242020575664, f_87_88
add qword ptr [r8 + 0 ], 1		#f_87_88_TMP_2242020575664_0, 1
mov r8, r8		#b_84_87_88, f_87_88_TMP_2242020575664
mov r8, rcx		#b_84_87_88, f_87_88
jmp Return_Here_117		#Return_Here_117
Return_Here_117:
mov ecx, dword ptr [r8 + 12 ]		#b_84_87_88_12_REG2, b_84_87_88_12
mov ecx, ecx		#Return_Value87_88, b_84_87_88_12_REG2
jmp Return_Here_118		#Return_Here_118
Return_Here_118:
jmp Return_Here_114		#Return_Here_114
Return_Here_114:
mov eax, 1		#Returning_REG3, 1
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
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
