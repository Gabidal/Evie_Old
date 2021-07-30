.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_1541963928912, x_REG0
add qword ptr [rcx + 0 ], 1		#x_TMP_1541963928912_0, 1
mov rcx, rcx		#this_83, x_TMP_1541963928912
mov r8, rcx		#this_83_TMP_1541963927184, this_83
add qword ptr [r8 + 0 ], 1		#this_83_TMP_1541963927184_0, 1
mov r8, r8		#this_82_83, this_83_TMP_1541963927184
mov r8, rcx		#this_82_83, this_83
mov dword ptr [r8 + 8 ], 4		#this_82_83_8, 4
Return_Here_114:
mov dword ptr [rcx + 12 ], 1		#this_83_12, 1
mov dword ptr [rcx + 16 ], 2		#this_83_16, 2
mov dword ptr [rcx + 20 ], 6		#this_83_20, 6
mov dword ptr [rcx + 8 ], 5		#this_83_8, 5
jmp Return_Here_113		#Return_Here_113
Return_Here_113:
lea rcx, qword ptr [rsp + 0 ]		#x_REG1, .STACK_0
mov rcx, rcx		#x_TMP_1541963960016, x_REG1
add qword ptr [rcx + 0 ], 1		#x_TMP_1541963960016_0, 1
mov rcx, rcx		#f_84, x_TMP_1541963960016
mov r8, rcx		#f_84_TMP_1541963960880, f_84
add qword ptr [r8 + 0 ], 1		#f_84_TMP_1541963960880_0, 1
mov r8, r8		#b_81_84, f_84_TMP_1541963960880
mov r8, rcx		#b_81_84, f_84
jmp Return_Here_116		#Return_Here_116
Return_Here_116:
mov ecx, dword ptr [r8 + 12 ]		#b_81_84_12_REG2, b_81_84_12
mov ecx, ecx		#Return_Value84, b_81_84_12_REG2
jmp Return_Here_115		#Return_Here_115
Return_Here_115:
mov eax, ecx		#Returning_REG3, Return_Value84
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_Z4mainv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_85_REG0, .STACK_0
mov rcx, rcx		#x_85_TMP_1541963957424, x_85_REG0
add qword ptr [rcx + 0 ], 1		#x_85_TMP_1541963957424_0, 1
mov rcx, rcx		#this_83_85, x_85_TMP_1541963957424
mov r8, rcx		#this_83_85_TMP_1541963974704, this_83_85
add qword ptr [r8 + 0 ], 1		#this_83_85_TMP_1541963974704_0, 1
mov r8, r8		#this_82_83_85, this_83_85_TMP_1541963974704
mov r8, rcx		#this_82_83_85, this_83_85
mov dword ptr [r8 + 8 ], 4		#this_82_83_85_8, 4
Return_Here_118:
mov dword ptr [rcx + 12 ], 1		#this_83_85_12, 1
mov dword ptr [rcx + 16 ], 2		#this_83_85_16, 2
mov dword ptr [rcx + 20 ], 6		#this_83_85_20, 6
mov dword ptr [rcx + 8 ], 5		#this_83_85_8, 5
jmp Return_Here_119		#Return_Here_119
Return_Here_119:
lea rcx, qword ptr [rsp + 0 ]		#x_85_REG1, .STACK_0
mov rcx, rcx		#x_85_TMP_1541963973840, x_85_REG1
add qword ptr [rcx + 0 ], 1		#x_85_TMP_1541963973840_0, 1
mov rcx, rcx		#f_84_85, x_85_TMP_1541963973840
mov r8, rcx		#f_84_85_TMP_1541963998896, f_84_85
add qword ptr [r8 + 0 ], 1		#f_84_85_TMP_1541963998896_0, 1
mov r8, r8		#b_81_84_85, f_84_85_TMP_1541963998896
mov r8, rcx		#b_81_84_85, f_84_85
jmp Return_Here_120		#Return_Here_120
Return_Here_120:
mov ecx, dword ptr [r8 + 12 ]		#b_81_84_85_12_REG2, b_81_84_85_12
mov ecx, ecx		#Return_Value84_85, b_81_84_85_12_REG2
jmp Return_Here_121		#Return_Here_121
Return_Here_121:
jmp Return_Here_117		#Return_Here_117
Return_Here_117:
mov eax, 1		#Returning_REG3, 1
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_31:
cmp rcx, 0		#this, 0
je if_31_END		#if_31_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_31_END		#if_31_END
mov r8, rcx		#this_TMP_1541964014448, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1541964014448_0, 1
mov rbx, r8		#Address_80, this_TMP_1541964014448
mov rbx, rcx		#Address_80, this
mov rcx, rbx		#REG_Address_80_Parameter13030, Address_80
mov r8d, dword ptr [rbx + 20 ]		#Address_80_20_REG1, Address_80_20
mov edx, r8d		#REG_Address_80_20_REG1_Parameter16413, Address_80_20_REG1
call _V19internal_deallocatePhx
Return_Here_110:
mov rcx, rbx		#REG_Address_80_Parameter29168, Address_80
call _ZN6Banana10DestructorEP6Banana
if_31_END:
pop rbx		#rbx
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
