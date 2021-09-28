.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 44		#.STACK, 44
mov dword ptr [rsp + 0 ], 10		#.STACK_0, 10
lea rcx, qword ptr [rsp + 0 ]		#val_REG0, .STACK_0
mov qword ptr [rsp + 4 ], rcx		#.STACK_4, val_REG0
lea rcx, qword ptr [rsp + 4 ]		#a_REG1, .STACK_4
mov qword ptr [rsp + 12 ], rcx		#.STACK_12, a_REG1
mov rcx, qword ptr [rsp + 4 ]		#a_REG2, .STACK_4
mov ecx, dword ptr [rcx ]		#a_REG2_REG3, a_REG2
mov eax, ecx		#Returning_REG4, a_REG2_REG3
add rsp, 44		#.STACK, 44
ret 		#
lea rcx, qword ptr [rsp + 12 ]		#b_REG5, .STACK_12
mov qword ptr [rsp + 20 ], rcx		#.STACK_20, b_REG5
lea rcx, qword ptr [rsp + 20 ]		#c_REG6, .STACK_20
mov qword ptr [rsp + 28 ], rcx		#.STACK_28, c_REG6
lea rcx, qword ptr [rsp + 28 ]		#d_REG7, .STACK_28
mov qword ptr [rsp + 36 ], rcx		#.STACK_36, d_REG7
lea rcx, qword ptr [rsp + 36 ]		#e_REG8, .STACK_36
mov rcx, rcx		#f, e_REG8
mov rcx, qword ptr [rcx ]		#f_REG9, f
mov rcx, qword ptr [rcx ]		#f_REG9_REG10, f_REG9
mov rcx, qword ptr [rcx ]		#f_REG9_REG10_REG11, f_REG9_REG10
mov rcx, qword ptr [rcx ]		#f_REG9_REG10_REG11_REG12, f_REG9_REG10_REG11
mov rcx, qword ptr [rcx ]		#f_REG9_REG10_REG11_REG12_REG13, f_REG9_REG10_REG11_REG12
mov ecx, dword ptr [rcx ]		#f_REG9_REG10_REG11_REG12_REG13_REG14, f_REG9_REG10_REG11_REG12_REG13
mov eax, ecx		#Returning_REG15, f_REG9_REG10_REG11_REG12_REG13_REG14
add rsp, 44		#.STACK, 44
ret 		#
mov rcx, 123		#Normal_Cast_needing_Var, 123
mov ecx, dword ptr [rcx ]		#Normal_Cast_needing_Var_REG16, Normal_Cast_needing_Var
mov eax, ecx		#Returning_REG17, Normal_Cast_needing_Var_REG16
add rsp, 44		#.STACK, 44
ret 		#
mov rcx, 1234		#Dynamic_needing_Var, 1234
mov rcx, qword ptr [rcx ]		#Dynamic_needing_Var_REG18, Dynamic_needing_Var
mov ecx, dword ptr [rcx ]		#Dynamic_needing_Var_REG18_REG19, Dynamic_needing_Var_REG18
mov eax, ecx		#Returning_REG20, Dynamic_needing_Var_REG18_REG19
add rsp, 44		#.STACK, 44
ret 		#
add rsp, 44		#.STACK, 44
ret 		#


_Z4mainv:
sub rsp, 44		#.STACK, 44
mov dword ptr [rsp + 0 ], 10		#.STACK_0, 10
lea rcx, qword ptr [rsp + 0 ]		#val_102_REG0, .STACK_0
mov qword ptr [rsp + 4 ], rcx		#.STACK_4, val_102_REG0
lea rcx, qword ptr [rsp + 4 ]		#a_102_REG1, .STACK_4
mov qword ptr [rsp + 12 ], rcx		#.STACK_12, a_102_REG1
jmp Return_Here_138		#Return_Here_138
lea rcx, qword ptr [rsp + 12 ]		#b_102_REG2, .STACK_12
mov qword ptr [rsp + 20 ], rcx		#.STACK_20, b_102_REG2
lea rcx, qword ptr [rsp + 20 ]		#c_102_REG3, .STACK_20
mov qword ptr [rsp + 28 ], rcx		#.STACK_28, c_102_REG3
lea rcx, qword ptr [rsp + 28 ]		#d_102_REG4, .STACK_28
mov qword ptr [rsp + 36 ], rcx		#.STACK_36, d_102_REG4
lea rcx, qword ptr [rsp + 36 ]		#e_102_REG5, .STACK_36
mov rcx, rcx		#f_102, e_102_REG5
jmp Return_Here_138		#Return_Here_138
mov rcx, 123		#Normal_Cast_needing_Var_102, 123
jmp Return_Here_138		#Return_Here_138
mov rcx, 1234		#Dynamic_needing_Var_102, 1234
jmp Return_Here_138		#Return_Here_138
Return_Here_138:
mov eax, 1		#Returning_REG6, 1
add rsp, 44		#.STACK, 44
ret 		#
add rsp, 44		#.STACK, 44
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
