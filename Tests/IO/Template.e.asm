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
mov rcx, rcx		#a_TMP_1541947113312, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1541947113312_0, 1
mov rbx, rcx		#this_68, a_TMP_1541947113312
mov dword ptr [rbx + 8 ], 1		#this_68_8, 1
mov dword ptr [rbx + 12 ], 0		#this_68_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_68_8_REG1, this_68_8
mov ecx, ecx		#Size_64_68, this_68_8_REG1
mov r8d, ecx		#REG_Size_64_682, Size_64_68
mov r9, rdx		#REG_Size_64_682_REMAINDER15573, REMAINDER_5097
mov eax, 4		#4_QUOTIENT26777, 4
mul r8d		#REG_Size_64_682
mov r8d, eax		#REG_Size_64_682, 4_QUOTIENT26777
mov rdx, r9		#REMAINDER_5097, REG_Size_64_682_REMAINDER15573
mov ecx, ecx		#REG_Size_64_683, Size_64_68
mov r8, rdx		#REG_Size_64_683_REMAINDER23986, REMAINDER_13290
mov eax, 4		#4_QUOTIENT16512, 4
mul ecx		#REG_Size_64_683
mov ecx, eax		#REG_Size_64_683, 4_QUOTIENT16512
mov rdx, r8		#REMAINDER_13290, REG_Size_64_683_REMAINDER23986
mov ecx, ecx		#REG_REG_Size_64_683_Parameter5021, REG_Size_64_683
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_91		#Return_Here_91
Return_Here_91:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value64_685, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_68_16, REG_Return_Value64_685
jmp Return_Here_90		#Return_Here_90
Return_Here_90:
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#a_TMP_1541947893344, a_REG6
add qword ptr [rcx + 0 ], 1		#a_TMP_1541947893344_0, 1
mov rbx, rcx		#this_69, a_TMP_1541947893344
if_24:
mov ecx, dword ptr [rbx + 12 ]		#this_69_12_REG7, this_69_12
mov r8d, dword ptr [rbx + 8 ]		#this_69_8_REG8, this_69_8
cmp ecx, r8d		#this_69_12_REG7, this_69_8_REG8
jl if_24_END		#if_24_END
mov ecx, dword ptr [rbx + 12 ]		#this_69_12_REG9, this_69_12
mov r8, rdx		#this_69_12_REG9_REMAINDER18636, REMAINDER_22355
mov eax, 2		#2_QUOTIENT9161, 2
mul ecx		#this_69_12_REG9
mov ecx, eax		#this_69_12_REG9, 2_QUOTIENT9161
mov rdx, r8		#REMAINDER_22355, this_69_12_REG9_REMAINDER18636
mov dword ptr [rbx + 8 ], ecx		#this_69_8, this_69_12_REG9
mov ecx, dword ptr [rbx + 8 ]		#this_69_8_REG10, this_69_8
mov edi, ecx		#Size_65, this_69_8_REG10
mov ecx, edi		#REG_Size_6511, Size_65
mov r8, rdx		#REG_Size_6511_REMAINDER23655, REMAINDER_15574
mov eax, 4		#4_QUOTIENT24767, 4
mul ecx		#REG_Size_6511
mov ecx, eax		#REG_Size_6511, 4_QUOTIENT24767
mov rdx, r8		#REMAINDER_15574, REG_Size_6511_REMAINDER23655
mov ecx, edi		#REG_Size_6512, Size_65
mov r8, rdx		#REG_Size_6512_REMAINDER12052, REMAINDER_27350
mov eax, 4		#4_QUOTIENT4031, 4
mul ecx		#REG_Size_6512
mov ecx, eax		#REG_Size_6512, 4_QUOTIENT4031
mov rdx, r8		#REMAINDER_27350, REG_Size_6512_REMAINDER12052
mov ecx, ecx		#REG_REG_Size_6512_Parameter28745, REG_Size_6512
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value65, RetREG_13
jmp Return_Here_93		#Return_Here_93
Return_Here_93:
mov rbp, rsi		#tmp, Return_Value65
mov ecx, dword ptr [rbx + 12 ]		#this_69_12_REG14, this_69_12
mov r8, rdx		#this_69_12_REG14_REMAINDER16941, REMAINDER_21724
mov eax, 4		#4_QUOTIENT1150, 4
mul ecx		#this_69_12_REG14
mov ecx, eax		#this_69_12_REG14, 4_QUOTIENT1150
mov rdx, r8		#REMAINDER_21724, this_69_12_REG14_REMAINDER16941
mov r12d, ecx		#Size_66, this_69_12_REG14
mov rcx, qword ptr [rbx + 16 ]		#this_69_16_REG15, this_69_16
mov r13, rcx		#source_66, this_69_16_REG15
mov r14, rbp		#dest_66, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_66
jge while_25_END		#while_25_END
while_25:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_66_REG16, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_66_REG17, *
mov dword ptr [rcx ], r8d		#dest_66_REG16, source_66_REG17
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_66
jge while_25_END		#while_25_END
jmp while_25		#while_25
while_25_END:
jmp Return_Here_94		#Return_Here_94
Return_Here_94:
mov qword ptr [rbx + 16 ], rbp		#this_69_16, tmp
if_24_END:
mov rcx, qword ptr [rbx + 16 ]		#this_69_16_REG18, this_69_16
mov r8d, dword ptr [rbx + 12 ]		#this_69_12_REG20, this_69_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_69_16_REG18_REG19, *
mov dword ptr [rcx ], 5		#this_69_16_REG18_REG19, 5
add dword ptr [rbx + 12 ], 1		#this_69_12, 1
Return_Here_92:
lea rcx, qword ptr [rsp + 0 ]		#a_REG21, .STACK_0
mov rcx, rcx		#a_TMP_1541947894208, a_REG21
add qword ptr [rcx + 0 ], 1		#a_TMP_1541947894208_0, 1
mov rbx, rcx		#this_70, a_TMP_1541947894208
if_26:
mov ecx, dword ptr [rbx + 12 ]		#this_70_12_REG22, this_70_12
mov r8d, dword ptr [rbx + 8 ]		#this_70_8_REG23, this_70_8
cmp ecx, r8d		#this_70_12_REG22, this_70_8_REG23
jl if_26_END		#if_26_END
mov ecx, dword ptr [rbx + 12 ]		#this_70_12_REG24, this_70_12
mov r8, rdx		#this_70_12_REG24_REMAINDER3430, REMAINDER_31107
mov eax, 2		#2_QUOTIENT13966, 2
mul ecx		#this_70_12_REG24
mov ecx, eax		#this_70_12_REG24, 2_QUOTIENT13966
mov rdx, r8		#REMAINDER_31107, this_70_12_REG24_REMAINDER3430
mov dword ptr [rbx + 8 ], ecx		#this_70_8, this_70_12_REG24
mov ecx, dword ptr [rbx + 8 ]		#this_70_8_REG25, this_70_8
mov edi, ecx		#Size_65, this_70_8_REG25
mov ecx, edi		#REG_Size_6526, Size_65
mov r8, rdx		#REG_Size_6526_REMAINDER18007, REMAINDER_11337
mov eax, 4		#4_QUOTIENT30191, 4
mul ecx		#REG_Size_6526
mov ecx, eax		#REG_Size_6526, 4_QUOTIENT30191
mov rdx, r8		#REMAINDER_11337, REG_Size_6526_REMAINDER18007
mov ecx, edi		#REG_Size_6527, Size_65
mov r8, rdx		#REG_Size_6527_REMAINDER12287, REMAINDER_27753
mov eax, 4		#4_QUOTIENT15457, 4
mul ecx		#REG_Size_6527
mov ecx, eax		#REG_Size_6527, 4_QUOTIENT15457
mov rdx, r8		#REMAINDER_27753, REG_Size_6527_REMAINDER12287
mov ecx, ecx		#REG_REG_Size_6527_Parameter26924, REG_Size_6527
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value65, RetREG_28
jmp Return_Here_96		#Return_Here_96
Return_Here_96:
mov rbp, rsi		#tmp, Return_Value65
mov ecx, dword ptr [rbx + 12 ]		#this_70_12_REG29, this_70_12
mov r8, rdx		#this_70_12_REG29_REMAINDER14945, REMAINDER_8909
mov eax, 4		#4_QUOTIENT10383, 4
mul ecx		#this_70_12_REG29
mov ecx, eax		#this_70_12_REG29, 4_QUOTIENT10383
mov rdx, r8		#REMAINDER_8909, this_70_12_REG29_REMAINDER14945
mov r12d, ecx		#Size_66, this_70_12_REG29
mov rcx, qword ptr [rbx + 16 ]		#this_70_16_REG30, this_70_16
mov r13, rcx		#source_66, this_70_16_REG30
mov r14, rbp		#dest_66, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_66
jge while_27_END		#while_27_END
while_27:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_66_REG31, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_66_REG32, *
mov dword ptr [rcx ], r8d		#dest_66_REG31, source_66_REG32
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_66
jge while_27_END		#while_27_END
jmp while_27		#while_27
while_27_END:
jmp Return_Here_97		#Return_Here_97
Return_Here_97:
mov qword ptr [rbx + 16 ], rbp		#this_70_16, tmp
if_26_END:
mov rcx, qword ptr [rbx + 16 ]		#this_70_16_REG33, this_70_16
mov r8d, dword ptr [rbx + 12 ]		#this_70_12_REG35, this_70_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_70_16_REG33_REG34, *
mov dword ptr [rcx ], 2		#this_70_16_REG33_REG34, 2
add dword ptr [rbx + 12 ], 1		#this_70_12, 1
Return_Here_95:
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_1541947896800, a_REG36
add qword ptr [rcx + 0 ], 1		#a_TMP_1541947896800_0, 1
mov rcx, rcx		#this_71, a_TMP_1541947896800
sub dword ptr [rcx + 12 ], 1		#this_71_12, 1
Return_Here_98:
mov ecx, 0		#i_72, 0
lea r8, qword ptr [rsp + 0 ]		#a_REG37, .STACK_0
mov r8, r8		#a_TMP_1541947917536, a_REG37
add qword ptr [r8 + 0 ], 1		#a_TMP_1541947917536_0, 1
mov r8, r8		#this_72, a_TMP_1541947917536
if_28:
mov r9d, dword ptr [r8 + 12 ]		#this_72_12_REG38, this_72_12
cmp ecx, r9d		#i_72, this_72_12_REG38
jle if_28_END		#if_28_END
mov ecx, 0		#Return_Value72, 0
jmp Return_Here_99		#Return_Here_99
if_28_END:
mov r8, qword ptr [r8 + 16 ]		#this_72_16_REG39, this_72_16
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_72_16_REG39_REG40, *
mov ecx, r8d		#Return_Value72, this_72_16_REG39_REG40
jmp Return_Here_99		#Return_Here_99
Return_Here_99:
mov eax, ecx		#Returning_REG41, Return_Value72
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
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_ZN13____List_int_10DestructorEP13____List_int_:
push rbx		#rbx
if_29:
cmp rcx, 0		#this, 0
je if_29_END		#if_29_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_29_END		#if_29_END
mov r8, rcx		#this_TMP_1541947899392, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1541947899392_0, 1
mov rbx, r8		#Address_67, this_TMP_1541947899392
mov rbx, rcx		#Address_67, this
mov rcx, rbx		#REG_Address_67_Parameter19072, Address_67
mov edx, 8		#REG_8_Parameter6270, 8
call _V19internal_deallocatePhx
Return_Here_89:
mov rcx, rbx		#REG_Address_67_Parameter5829, Address_67
call _ZN13____List_int_10DestructorEP13____List_int_
if_29_END:
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
