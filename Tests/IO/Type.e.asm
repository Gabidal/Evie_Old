.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_2250270739344, x_REG0
add qword ptr [rcx + 0 ], 1		#x_TMP_2250270739344_0, 1
mov rcx, rcx		#this_61, x_TMP_2250270739344
mov r8, rcx		#this_61_TMP_2250270755760, this_61
add qword ptr [r8 + 0 ], 1		#this_61_TMP_2250270755760_0, 1
mov r8, r8		#this_60_61, this_61_TMP_2250270755760
mov r8, rcx		#this_60_61, this_61
mov dword ptr [r8 + 8 ], 4		#this_60_61_8, 4
Return_Here_80:
mov dword ptr [rcx + 12 ], 1		#this_61_12, 1
mov dword ptr [rcx + 16 ], 2		#this_61_16, 2
mov dword ptr [rcx + 20 ], 6		#this_61_20, 6
mov dword ptr [rcx + 8 ], 5		#this_61_8, 5
jmp Return_Here_79		#Return_Here_79
Return_Here_79:
lea rcx, qword ptr [rsp + 0 ]		#x_REG1, .STACK_0
mov rcx, rcx		#x_TMP_2250270779952, x_REG1
add qword ptr [rcx + 0 ], 1		#x_TMP_2250270779952_0, 1
mov rcx, rcx		#f_62, x_TMP_2250270779952
mov r8, rcx		#f_62_TMP_2250270754032, f_62
add qword ptr [r8 + 0 ], 1		#f_62_TMP_2250270754032_0, 1
mov r8, r8		#b_59_62, f_62_TMP_2250270754032
mov r8, rcx		#b_59_62, f_62
jmp Return_Here_82		#Return_Here_82
Return_Here_82:
mov ecx, dword ptr [r8 + 12 ]		#b_59_62_12_REG2, b_59_62_12
mov ecx, ecx		#Return_Value62, b_59_62_12_REG2
jmp Return_Here_81		#Return_Here_81
Return_Here_81:
mov eax, ecx		#Returning_REG3, Return_Value62
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_Z4mainv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_63_REG0, .STACK_0
mov rcx, rcx		#x_63_TMP_2250270775632, x_63_REG0
add qword ptr [rcx + 0 ], 1		#x_63_TMP_2250270775632_0, 1
mov rcx, rcx		#this_61_63, x_63_TMP_2250270775632
mov r8, rcx		#this_61_63_TMP_2250270792912, this_61_63
add qword ptr [r8 + 0 ], 1		#this_61_63_TMP_2250270792912_0, 1
mov r8, r8		#this_60_61_63, this_61_63_TMP_2250270792912
mov r8, rcx		#this_60_61_63, this_61_63
mov dword ptr [r8 + 8 ], 4		#this_60_61_63_8, 4
Return_Here_84:
mov dword ptr [rcx + 12 ], 1		#this_61_63_12, 1
mov dword ptr [rcx + 16 ], 2		#this_61_63_16, 2
mov dword ptr [rcx + 20 ], 6		#this_61_63_20, 6
mov dword ptr [rcx + 8 ], 5		#this_61_63_8, 5
jmp Return_Here_85		#Return_Here_85
Return_Here_85:
lea rcx, qword ptr [rsp + 0 ]		#x_63_REG1, .STACK_0
mov rcx, rcx		#x_63_TMP_2250271437152, x_63_REG1
add qword ptr [rcx + 0 ], 1		#x_63_TMP_2250271437152_0, 1
mov rcx, rcx		#f_62_63, x_63_TMP_2250271437152
mov r8, rcx		#f_62_63_TMP_2250271440608, f_62_63
add qword ptr [r8 + 0 ], 1		#f_62_63_TMP_2250271440608_0, 1
mov r8, r8		#b_59_62_63, f_62_63_TMP_2250271440608
mov r8, rcx		#b_59_62_63, f_62_63
jmp Return_Here_86		#Return_Here_86
Return_Here_86:
mov ecx, dword ptr [r8 + 12 ]		#b_59_62_63_12_REG2, b_59_62_63_12
mov ecx, ecx		#Return_Value62_63, b_59_62_63_12_REG2
jmp Return_Here_87		#Return_Here_87
Return_Here_87:
jmp Return_Here_83		#Return_Here_83
Return_Here_83:
mov eax, 1		#Returning_REG3, 1
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_24:
cmp rcx, 0		#this, 0
je if_24_END		#if_24_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_24_END		#if_24_END
mov r8, rcx		#this_TMP_2250271445792, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2250271445792_0, 1
mov rbx, r8		#Address_58, this_TMP_2250271445792
mov rbx, rcx		#Address_58, this
mov rcx, rbx		#REG_Address_58_Parameter29658, Address_58
mov r8d, dword ptr [rbx + 20 ]		#Address_58_20_REG1, Address_58_20
mov edx, r8d		#REG_Address_58_20_REG1_Parameter22704, Address_58_20_REG1
call _V19internal_deallocatePhx
Return_Here_76:
mov rcx, rbx		#REG_Address_58_Parameter9930, Address_58
call _ZN6Banana10DestructorEP6Banana
if_24_END:
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
