.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
push r15		#r15
push r14		#r14
push r13		#r13
push r12		#r12
push rbp		#rbp
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 32		#.STACK, 32
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_1724608078416, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1724608078416_0, 1
mov rbx, rcx		#this_69, a_TMP_1724608078416
mov dword ptr [rbx + 8 ], 1		#this_69_8, 1
mov dword ptr [rbx + 12 ], 0		#this_69_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_69_8_REG1, this_69_8
mov ecx, ecx		#Size_65_69, this_69_8_REG1
mov r8d, ecx		#REG_Size_65_692, Size_65_69
mov r9, rdx		#REG_Size_65_692_REMAINDER19072, REMAINDER_6270
mov eax, 4		#4_QUOTIENT26924, 4
mul r8d		#REG_Size_65_692
mov r8d, eax		#REG_Size_65_692, 4_QUOTIENT26924
mov rdx, r9		#REMAINDER_6270, REG_Size_65_692_REMAINDER19072
mov ecx, ecx		#REG_Size_65_693, Size_65_69
mov r8, rdx		#REG_Size_65_693_REMAINDER26777, REMAINDER_15573
mov eax, 4		#4_QUOTIENT5829, 4
mul ecx		#REG_Size_65_693
mov ecx, eax		#REG_Size_65_693, 4_QUOTIENT5829
mov rdx, r8		#REMAINDER_15573, REG_Size_65_693_REMAINDER26777
mov ecx, ecx		#REG_REG_Size_65_693_Parameter13977, REG_Size_65_693
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_94		#Return_Here_94
Return_Here_94:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value65_695, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_69_16, REG_Return_Value65_695
jmp Return_Here_93		#Return_Here_93
Return_Here_93:
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#a_TMP_1724608070640, a_REG6
add qword ptr [rcx + 0 ], 1		#a_TMP_1724608070640_0, 1
mov rbx, rcx		#this_70, a_TMP_1724608070640
if_25:
mov ecx, dword ptr [rbx + 12 ]		#this_70_12_REG7, this_70_12
mov r8d, dword ptr [rbx + 8 ]		#this_70_8_REG8, this_70_8
cmp ecx, r8d		#this_70_12_REG7, this_70_8_REG8
jl if_25_END		#if_25_END
mov ecx, dword ptr [rbx + 12 ]		#this_70_12_REG9, this_70_12
mov r8, rdx		#this_70_12_REG9_REMAINDER16512, REMAINDER_23986
mov eax, 2		#2_QUOTIENT5097, 2
mul ecx		#this_70_12_REG9
mov ecx, eax		#this_70_12_REG9, 2_QUOTIENT5097
mov rdx, r8		#REMAINDER_23986, this_70_12_REG9_REMAINDER16512
mov dword ptr [rbx + 8 ], ecx		#this_70_8, this_70_12_REG9
mov ecx, dword ptr [rbx + 8 ]		#this_70_8_REG10, this_70_8
mov edi, ecx		#Size_66, this_70_8_REG10
mov ecx, edi		#REG_Size_6611, Size_66
mov r8, rdx		#REG_Size_6611_REMAINDER9161, REMAINDER_18636
mov eax, 4		#4_QUOTIENT13290, 4
mul ecx		#REG_Size_6611
mov ecx, eax		#REG_Size_6611, 4_QUOTIENT13290
mov rdx, r8		#REMAINDER_18636, REG_Size_6611_REMAINDER9161
mov ecx, edi		#REG_Size_6612, Size_66
mov r8, rdx		#REG_Size_6612_REMAINDER24767, REMAINDER_23655
mov eax, 4		#4_QUOTIENT22355, 4
mul ecx		#REG_Size_6612
mov ecx, eax		#REG_Size_6612, 4_QUOTIENT22355
mov rdx, r8		#REMAINDER_23655, REG_Size_6612_REMAINDER24767
mov ecx, ecx		#REG_REG_Size_6612_Parameter2306, REG_Size_6612
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value66, RetREG_13
jmp Return_Here_96		#Return_Here_96
Return_Here_96:
mov rbp, rsi		#tmp, Return_Value66
mov ecx, dword ptr [rbx + 12 ]		#this_70_12_REG14, this_70_12
mov r8, rdx		#this_70_12_REG14_REMAINDER4031, REMAINDER_12052
mov eax, 4		#4_QUOTIENT15574, 4
mul ecx		#this_70_12_REG14
mov ecx, eax		#this_70_12_REG14, 4_QUOTIENT15574
mov rdx, r8		#REMAINDER_12052, this_70_12_REG14_REMAINDER4031
mov r12d, ecx		#Size_67, this_70_12_REG14
mov rcx, qword ptr [rbx + 16 ]		#this_70_16_REG15, this_70_16
mov r13, rcx		#source_67, this_70_16_REG15
mov r14, rbp		#dest_67, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_67
jge while_26_END		#while_26_END
while_26:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_67_REG16, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_67_REG17, *
mov dword ptr [rcx ], r8d		#dest_67_REG16, source_67_REG17
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_67
jge while_26_END		#while_26_END
jmp while_26		#while_26
while_26_END:
jmp Return_Here_97		#Return_Here_97
Return_Here_97:
mov qword ptr [rbx + 16 ], rbp		#this_70_16, tmp
if_25_END:
mov rcx, qword ptr [rbx + 16 ]		#this_70_16_REG18, this_70_16
mov r8d, dword ptr [rbx + 12 ]		#this_70_12_REG20, this_70_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_70_16_REG18_REG19, *
mov dword ptr [rcx ], 5		#this_70_16_REG18_REG19, 5
add dword ptr [rbx + 12 ], 1		#this_70_12, 1
Return_Here_95:
lea rcx, qword ptr [rsp + 0 ]		#a_REG21, .STACK_0
mov rcx, rcx		#a_TMP_1724608116432, a_REG21
add qword ptr [rcx + 0 ], 1		#a_TMP_1724608116432_0, 1
mov rbx, rcx		#this_71, a_TMP_1724608116432
if_27:
mov ecx, dword ptr [rbx + 12 ]		#this_71_12_REG22, this_71_12
mov r8d, dword ptr [rbx + 8 ]		#this_71_8_REG23, this_71_8
cmp ecx, r8d		#this_71_12_REG22, this_71_8_REG23
jl if_27_END		#if_27_END
mov ecx, dword ptr [rbx + 12 ]		#this_71_12_REG24, this_71_12
mov r8, rdx		#this_71_12_REG24_REMAINDER1150, REMAINDER_16941
mov eax, 2		#2_QUOTIENT27350, 2
mul ecx		#this_71_12_REG24
mov ecx, eax		#this_71_12_REG24, 2_QUOTIENT27350
mov rdx, r8		#REMAINDER_16941, this_71_12_REG24_REMAINDER1150
mov dword ptr [rbx + 8 ], ecx		#this_71_8, this_71_12_REG24
mov ecx, dword ptr [rbx + 8 ]		#this_71_8_REG25, this_71_8
mov edi, ecx		#Size_66, this_71_8_REG25
mov ecx, edi		#REG_Size_6626, Size_66
mov r8, rdx		#REG_Size_6626_REMAINDER13966, REMAINDER_3430
mov eax, 4		#4_QUOTIENT21724, 4
mul ecx		#REG_Size_6626
mov ecx, eax		#REG_Size_6626, 4_QUOTIENT21724
mov rdx, r8		#REMAINDER_3430, REG_Size_6626_REMAINDER13966
mov ecx, edi		#REG_Size_6627, Size_66
mov r8, rdx		#REG_Size_6627_REMAINDER30191, REMAINDER_18007
mov eax, 4		#4_QUOTIENT31107, 4
mul ecx		#REG_Size_6627
mov ecx, eax		#REG_Size_6627, 4_QUOTIENT31107
mov rdx, r8		#REMAINDER_18007, REG_Size_6627_REMAINDER30191
mov ecx, ecx		#REG_REG_Size_6627_Parameter31673, REG_Size_6627
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value66, RetREG_28
jmp Return_Here_99		#Return_Here_99
Return_Here_99:
mov rbp, rsi		#tmp, Return_Value66
mov ecx, dword ptr [rbx + 12 ]		#this_71_12_REG29, this_71_12
mov r8, rdx		#this_71_12_REG29_REMAINDER15457, REMAINDER_12287
mov eax, 4		#4_QUOTIENT11337, 4
mul ecx		#this_71_12_REG29
mov ecx, eax		#this_71_12_REG29, 4_QUOTIENT11337
mov rdx, r8		#REMAINDER_12287, this_71_12_REG29_REMAINDER15457
mov r12d, ecx		#Size_67, this_71_12_REG29
mov rcx, qword ptr [rbx + 16 ]		#this_71_16_REG30, this_71_16
mov r13, rcx		#source_67, this_71_16_REG30
mov r14, rbp		#dest_67, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_67
jge while_28_END		#while_28_END
while_28:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_67_REG31, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_67_REG32, *
mov dword ptr [rcx ], r8d		#dest_67_REG31, source_67_REG32
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_67
jge while_28_END		#while_28_END
jmp while_28		#while_28
while_28_END:
jmp Return_Here_100		#Return_Here_100
Return_Here_100:
mov qword ptr [rbx + 16 ], rbp		#this_71_16, tmp
if_27_END:
mov rcx, qword ptr [rbx + 16 ]		#this_71_16_REG33, this_71_16
mov r8d, dword ptr [rbx + 12 ]		#this_71_12_REG35, this_71_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_71_16_REG33_REG34, *
mov dword ptr [rcx ], 2		#this_71_16_REG33_REG34, 2
add dword ptr [rbx + 12 ], 1		#this_71_12, 1
Return_Here_98:
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_1724608114704, a_REG36
add qword ptr [rcx + 0 ], 1		#a_TMP_1724608114704_0, 1
mov rcx, rcx		#this_72, a_TMP_1724608114704
sub dword ptr [rcx + 12 ], 1		#this_72_12, 1
Return_Here_101:
mov ecx, 0		#i_73, 0
lea r8, qword ptr [rsp + 0 ]		#a_REG37, .STACK_0
mov r8, r8		#a_TMP_1724608104336, a_REG37
add qword ptr [r8 + 0 ], 1		#a_TMP_1724608104336_0, 1
mov r8, r8		#this_73, a_TMP_1724608104336
if_29:
mov r9d, dword ptr [r8 + 12 ]		#this_73_12_REG38, this_73_12
cmp ecx, r9d		#i_73, this_73_12_REG38
jle if_29_END		#if_29_END
mov ecx, 0		#Return_Value73, 0
jmp Return_Here_102		#Return_Here_102
if_29_END:
mov r8, qword ptr [r8 + 16 ]		#this_73_16_REG39, this_73_16
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_73_16_REG39_REG40, *
mov ecx, r8d		#Return_Value73, this_73_16_REG39_REG40
jmp Return_Here_102		#Return_Here_102
Return_Here_102:
mov eax, ecx		#Returning_REG41, Return_Value73
add rsp, 32		#.STACK, 32
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
pop r13		#r13
pop r14		#r14
pop r15		#r15
ret 		#
add rsp, 32		#.STACK, 32
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
pop r13		#r13
pop r14		#r14
pop r15		#r15
ret 		#


_Z4mainv:
jmp _Z10Start_Testv		#_Z10Start_Testv
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_ZN13____List_int_10DestructorEP13____List_int_:
push rbx		#rbx
if_30:
cmp rcx, 0		#this, 0
je if_30_END		#if_30_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_30_END		#if_30_END
mov r8, rcx		#this_TMP_1724608095696, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1724608095696_0, 1
mov rbx, r8		#Address_68, this_TMP_1724608095696
mov rbx, rcx		#Address_68, this
mov rcx, rbx		#REG_Address_68_Parameter22386, Address_68
mov edx, 8		#REG_8_Parameter5021, 8
call _V19internal_deallocatePhx
Return_Here_92:
mov rcx, rbx		#REG_Address_68_Parameter28745, Address_68
call _ZN13____List_int_10DestructorEP13____List_int_
if_30_END:
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
