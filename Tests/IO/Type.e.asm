.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_1710133559488, x_REG0
add qword ptr [rcx + 0 ], 1		#x_TMP_1710133559488_0, 1
mov rcx, rcx		#this_69, x_TMP_1710133559488
mov r8, rcx		#this_69_TMP_1710133564864, this_69
add qword ptr [r8 + 0 ], 1		#this_69_TMP_1710133564864_0, 1
mov r8, r8		#this_68_69, this_69_TMP_1710133564864
mov r8, rcx		#this_68_69, this_69
mov dword ptr [r8 + 8 ], 4		#this_68_69_8, 4
Return_Here_89:
mov dword ptr [rcx + 12 ], 1		#this_69_12, 1
mov dword ptr [rcx + 16 ], 2		#this_69_16, 2
mov dword ptr [rcx + 20 ], 6		#this_69_20, 6
mov dword ptr [rcx + 8 ], 5		#this_69_8, 5
jmp Return_Here_88		#Return_Here_88
Return_Here_88:
lea rcx, qword ptr [rsp + 0 ]		#x_REG1, .STACK_0
mov rcx, rcx		#x_TMP_1710133581888, x_REG1
add qword ptr [rcx + 0 ], 1		#x_TMP_1710133581888_0, 1
mov rcx, rcx		#f_70, x_TMP_1710133581888
mov r8, rcx		#f_70_TMP_1710133575616, f_70
add qword ptr [r8 + 0 ], 1		#f_70_TMP_1710133575616_0, 1
mov r8, r8		#b_67_70, f_70_TMP_1710133575616
mov r8, rcx		#b_67_70, f_70
jmp Return_Here_91		#Return_Here_91
Return_Here_91:
mov ecx, dword ptr [r8 + 12 ]		#b_67_70_12_REG2, b_67_70_12
mov ecx, ecx		#Return_Value70, b_67_70_12_REG2
jmp Return_Here_90		#Return_Here_90
Return_Here_90:
mov eax, ecx		#Returning_REG3, Return_Value70
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_Z4mainv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_71_REG0, .STACK_0
mov rcx, rcx		#x_71_TMP_1710133598016, x_71_REG0
add qword ptr [rcx + 0 ], 1		#x_71_TMP_1710133598016_0, 1
mov rcx, rcx		#this_69_71, x_71_TMP_1710133598016
mov r8, rcx		#this_69_71_TMP_1710133614144, this_69_71
add qword ptr [r8 + 0 ], 1		#this_69_71_TMP_1710133614144_0, 1
mov r8, r8		#this_68_69_71, this_69_71_TMP_1710133614144
mov r8, rcx		#this_68_69_71, this_69_71
mov dword ptr [r8 + 8 ], 4		#this_68_69_71_8, 4
Return_Here_93:
mov dword ptr [rcx + 12 ], 1		#this_69_71_12, 1
mov dword ptr [rcx + 16 ], 2		#this_69_71_16, 2
mov dword ptr [rcx + 20 ], 6		#this_69_71_20, 6
mov dword ptr [rcx + 8 ], 5		#this_69_71_8, 5
jmp Return_Here_94		#Return_Here_94
Return_Here_94:
lea rcx, qword ptr [rsp + 0 ]		#x_71_REG1, .STACK_0
mov rcx, rcx		#x_71_TMP_1710133612352, x_71_REG1
add qword ptr [rcx + 0 ], 1		#x_71_TMP_1710133612352_0, 1
mov rcx, rcx		#f_70_71, x_71_TMP_1710133612352
mov r8, rcx		#f_70_71_TMP_1710133622208, f_70_71
add qword ptr [r8 + 0 ], 1		#f_70_71_TMP_1710133622208_0, 1
mov r8, r8		#b_67_70_71, f_70_71_TMP_1710133622208
mov r8, rcx		#b_67_70_71, f_70_71
jmp Return_Here_95		#Return_Here_95
Return_Here_95:
mov ecx, dword ptr [r8 + 12 ]		#b_67_70_71_12_REG2, b_67_70_71_12
mov ecx, ecx		#Return_Value70_71, b_67_70_71_12_REG2
jmp Return_Here_96		#Return_Here_96
Return_Here_96:
jmp Return_Here_92		#Return_Here_92
Return_Here_92:
mov eax, 1		#Returning_REG3, 1
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_25:
cmp rcx, 0		#this, 0
je if_25_END		#if_25_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_25_END		#if_25_END
mov r8, rcx		#this_TMP_1710134653104, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1710134653104_0, 1
mov rbx, r8		#Address_66, this_TMP_1710134653104
mov rbx, rcx		#Address_66, this
mov rcx, rbx		#REG_Address_66_Parameter19072, Address_66
mov r8d, dword ptr [rbx + 20 ]		#Address_66_20_REG1, Address_66_20
mov edx, r8d		#REG_Address_66_20_REG1_Parameter6270, Address_66_20_REG1
call _V19internal_deallocatePhx
Return_Here_85:
mov rcx, rbx		#REG_Address_66_Parameter5829, Address_66
call _ZN6Banana10DestructorEP6Banana
if_25_END:
pop rbx		#rbx
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
