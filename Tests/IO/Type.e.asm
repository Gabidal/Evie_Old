.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_1445894859824, x_REG0
add qword ptr [rcx + 0 ], 1		#x_TMP_1445894859824_0, 1
mov rcx, rcx		#this_70, x_TMP_1445894859824
mov r8, rcx		#this_70_TMP_1445894837360, this_70
add qword ptr [r8 + 0 ], 1		#this_70_TMP_1445894837360_0, 1
mov r8, r8		#this_69_70, this_70_TMP_1445894837360
mov r8, rcx		#this_69_70, this_70
mov dword ptr [r8 + 8 ], 4		#this_69_70_8, 4
Return_Here_97:
mov dword ptr [rcx + 12 ], 1		#this_70_12, 1
mov dword ptr [rcx + 16 ], 2		#this_70_16, 2
mov dword ptr [rcx + 20 ], 6		#this_70_20, 6
mov dword ptr [rcx + 8 ], 5		#this_70_8, 5
jmp Return_Here_96		#Return_Here_96
Return_Here_96:
lea rcx, qword ptr [rsp + 0 ]		#x_REG1, .STACK_0
mov rcx, rcx		#x_TMP_1445894838192, x_REG1
add qword ptr [rcx + 0 ], 1		#x_TMP_1445894838192_0, 1
mov rcx, rcx		#f_71, x_TMP_1445894838192
mov r8, rcx		#f_71_TMP_1445894866480, f_71
add qword ptr [r8 + 0 ], 1		#f_71_TMP_1445894866480_0, 1
mov r8, r8		#b_68_71, f_71_TMP_1445894866480
mov r8, rcx		#b_68_71, f_71
jmp Return_Here_99		#Return_Here_99
Return_Here_99:
mov ecx, dword ptr [r8 + 12 ]		#b_68_71_12_REG2, b_68_71_12
mov ecx, ecx		#Return_Value71, b_68_71_12_REG2
jmp Return_Here_98		#Return_Here_98
Return_Here_98:
mov eax, ecx		#Returning_REG3, Return_Value71
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_Z4mainv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_72_REG0, .STACK_0
mov rcx, rcx		#x_72_TMP_1445894876464, x_72_REG0
add qword ptr [rcx + 0 ], 1		#x_72_TMP_1445894876464_0, 1
mov rcx, rcx		#this_70_72, x_72_TMP_1445894876464
mov r8, rcx		#this_70_72_TMP_1445894903920, this_70_72
add qword ptr [r8 + 0 ], 1		#this_70_72_TMP_1445894903920_0, 1
mov r8, r8		#this_69_70_72, this_70_72_TMP_1445894903920
mov r8, rcx		#this_69_70_72, this_70_72
mov dword ptr [r8 + 8 ], 4		#this_69_70_72_8, 4
Return_Here_101:
mov dword ptr [rcx + 12 ], 1		#this_70_72_12, 1
mov dword ptr [rcx + 16 ], 2		#this_70_72_16, 2
mov dword ptr [rcx + 20 ], 6		#this_70_72_20, 6
mov dword ptr [rcx + 8 ], 5		#this_70_72_8, 5
jmp Return_Here_102		#Return_Here_102
Return_Here_102:
lea rcx, qword ptr [rsp + 0 ]		#x_72_REG1, .STACK_0
mov rcx, rcx		#x_72_TMP_1445894906416, x_72_REG1
add qword ptr [rcx + 0 ], 1		#x_72_TMP_1445894906416_0, 1
mov rcx, rcx		#f_71_72, x_72_TMP_1445894906416
mov r8, rcx		#f_71_72_TMP_1445894895600, f_71_72
add qword ptr [r8 + 0 ], 1		#f_71_72_TMP_1445894895600_0, 1
mov r8, r8		#b_68_71_72, f_71_72_TMP_1445894895600
mov r8, rcx		#b_68_71_72, f_71_72
jmp Return_Here_103		#Return_Here_103
Return_Here_103:
mov ecx, dword ptr [r8 + 12 ]		#b_68_71_72_12_REG2, b_68_71_72_12
mov ecx, ecx		#Return_Value71_72, b_68_71_72_12_REG2
jmp Return_Here_104		#Return_Here_104
Return_Here_104:
jmp Return_Here_100		#Return_Here_100
Return_Here_100:
mov eax, 1		#Returning_REG3, 1
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_29:
cmp rcx, 0		#this, 0
je if_29_END		#if_29_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_29_END		#if_29_END
mov r8, rcx		#this_TMP_1445894918896, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1445894918896_0, 1
mov rbx, r8		#Address_67, this_TMP_1445894918896
mov rbx, rcx		#Address_67, this
mov rcx, rbx		#REG_Address_67_Parameter31107, Address_67
mov edx, r8d		#REG_size_Parameter30191, size
call _V19internal_deallocatePhx
Return_Here_93:
mov rcx, rbx		#REG_Address_67_Parameter18007, Address_67
call _ZN6Banana10DestructorEP6Banana
if_29_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
