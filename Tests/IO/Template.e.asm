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
mov rcx, rcx		#a_TMP_1710148175936, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1710148175936_0, 1
mov rbx, rcx		#this_77, a_TMP_1710148175936
mov dword ptr [rbx + 8 ], 1		#this_77_8, 1
mov dword ptr [rbx + 12 ], 0		#this_77_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_77_8_REG1, this_77_8
mov ecx, ecx		#Size_73_77, this_77_8_REG1
mov r8d, ecx		#REG_Size_73_772, Size_73_77
mov r9, rdx		#REG_Size_73_772_REMAINDER18636, REMAINDER_22355
mov eax, 4		#4_QUOTIENT9161, 4
mul r8d		#REG_Size_73_772
mov r8d, eax		#REG_Size_73_772, 4_QUOTIENT9161
mov rdx, r9		#REMAINDER_22355, REG_Size_73_772_REMAINDER18636
mov ecx, ecx		#REG_Size_73_773, Size_73_77
mov r8, rdx		#REG_Size_73_773_REMAINDER23655, REMAINDER_15574
mov eax, 4		#4_QUOTIENT24767, 4
mul ecx		#REG_Size_73_773
mov ecx, eax		#REG_Size_73_773, 4_QUOTIENT24767
mov rdx, r8		#REMAINDER_15574, REG_Size_73_773_REMAINDER23655
mov ecx, ecx		#REG_REG_Size_73_773_Parameter26777, REG_Size_73_773
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_103		#Return_Here_103
Return_Here_103:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value73_775, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_77_16, REG_Return_Value73_775
jmp Return_Here_102		#Return_Here_102
Return_Here_102:
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#a_TMP_1710148165184, a_REG6
add qword ptr [rcx + 0 ], 1		#a_TMP_1710148165184_0, 1
mov rbx, rcx		#this_78, a_TMP_1710148165184
if_26:
mov ecx, dword ptr [rbx + 12 ]		#this_78_12_REG7, this_78_12
mov r8d, dword ptr [rbx + 8 ]		#this_78_8_REG8, this_78_8
cmp ecx, r8d		#this_78_12_REG7, this_78_8_REG8
jl if_26_END		#if_26_END
mov ecx, dword ptr [rbx + 12 ]		#this_78_12_REG9, this_78_12
mov r8, rdx		#this_78_12_REG9_REMAINDER12052, REMAINDER_27350
mov eax, 2		#2_QUOTIENT4031, 2
mul ecx		#this_78_12_REG9
mov ecx, eax		#this_78_12_REG9, 2_QUOTIENT4031
mov rdx, r8		#REMAINDER_27350, this_78_12_REG9_REMAINDER12052
mov dword ptr [rbx + 8 ], ecx		#this_78_8, this_78_12_REG9
mov ecx, dword ptr [rbx + 8 ]		#this_78_8_REG10, this_78_8
mov edi, ecx		#Size_74, this_78_8_REG10
mov ecx, edi		#REG_Size_7411, Size_74
mov r8, rdx		#REG_Size_7411_REMAINDER16941, REMAINDER_21724
mov eax, 4		#4_QUOTIENT1150, 4
mul ecx		#REG_Size_7411
mov ecx, eax		#REG_Size_7411, 4_QUOTIENT1150
mov rdx, r8		#REMAINDER_21724, REG_Size_7411_REMAINDER16941
mov ecx, edi		#REG_Size_7412, Size_74
mov r8, rdx		#REG_Size_7412_REMAINDER3430, REMAINDER_31107
mov eax, 4		#4_QUOTIENT13966, 4
mul ecx		#REG_Size_7412
mov ecx, eax		#REG_Size_7412, 4_QUOTIENT13966
mov rdx, r8		#REMAINDER_31107, REG_Size_7412_REMAINDER3430
mov ecx, ecx		#REG_REG_Size_7412_Parameter15573, REG_Size_7412
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value74, RetREG_13
jmp Return_Here_105		#Return_Here_105
Return_Here_105:
mov rbp, rsi		#tmp, Return_Value74
mov ecx, dword ptr [rbx + 12 ]		#this_78_12_REG14, this_78_12
mov r8, rdx		#this_78_12_REG14_REMAINDER18007, REMAINDER_11337
mov eax, 4		#4_QUOTIENT30191, 4
mul ecx		#this_78_12_REG14
mov ecx, eax		#this_78_12_REG14, 4_QUOTIENT30191
mov rdx, r8		#REMAINDER_11337, this_78_12_REG14_REMAINDER18007
mov r12d, ecx		#Size_75, this_78_12_REG14
mov rcx, qword ptr [rbx + 16 ]		#this_78_16_REG15, this_78_16
mov r13, rcx		#source_75, this_78_16_REG15
mov r14, rbp		#dest_75, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_75
jge while_27_END		#while_27_END
while_27:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_75_REG16, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_75_REG17, *
mov dword ptr [rcx ], r8d		#dest_75_REG16, source_75_REG17
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_75
jge while_27_END		#while_27_END
jmp while_27		#while_27
while_27_END:
jmp Return_Here_106		#Return_Here_106
Return_Here_106:
mov qword ptr [rbx + 16 ], rbp		#this_78_16, tmp
if_26_END:
mov rcx, qword ptr [rbx + 16 ]		#this_78_16_REG18, this_78_16
mov r8d, dword ptr [rbx + 12 ]		#this_78_12_REG20, this_78_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_78_16_REG18_REG19, *
mov dword ptr [rcx ], 5		#this_78_16_REG18_REG19, 5
add dword ptr [rbx + 12 ], 1		#this_78_12, 1
Return_Here_104:
lea rcx, qword ptr [rsp + 0 ]		#a_REG21, .STACK_0
mov rcx, rcx		#a_TMP_1710148161600, a_REG21
add qword ptr [rcx + 0 ], 1		#a_TMP_1710148161600_0, 1
mov rbx, rcx		#this_79, a_TMP_1710148161600
if_28:
mov ecx, dword ptr [rbx + 12 ]		#this_79_12_REG22, this_79_12
mov r8d, dword ptr [rbx + 8 ]		#this_79_8_REG23, this_79_8
cmp ecx, r8d		#this_79_12_REG22, this_79_8_REG23
jl if_28_END		#if_28_END
mov ecx, dword ptr [rbx + 12 ]		#this_79_12_REG24, this_79_12
mov r8, rdx		#this_79_12_REG24_REMAINDER12287, REMAINDER_27753
mov eax, 2		#2_QUOTIENT15457, 2
mul ecx		#this_79_12_REG24
mov ecx, eax		#this_79_12_REG24, 2_QUOTIENT15457
mov rdx, r8		#REMAINDER_27753, this_79_12_REG24_REMAINDER12287
mov dword ptr [rbx + 8 ], ecx		#this_79_8, this_79_12_REG24
mov ecx, dword ptr [rbx + 8 ]		#this_79_8_REG25, this_79_8
mov edi, ecx		#Size_74, this_79_8_REG25
mov ecx, edi		#REG_Size_7426, Size_74
mov r8, rdx		#REG_Size_7426_REMAINDER14945, REMAINDER_8909
mov eax, 4		#4_QUOTIENT10383, 4
mul ecx		#REG_Size_7426
mov ecx, eax		#REG_Size_7426, 4_QUOTIENT10383
mov rdx, r8		#REMAINDER_8909, REG_Size_7426_REMAINDER14945
mov ecx, edi		#REG_Size_7427, Size_74
mov r8, rdx		#REG_Size_7427_REMAINDER9758, REMAINDER_24221
mov eax, 4		#4_QUOTIENT32209, 4
mul ecx		#REG_Size_7427
mov ecx, eax		#REG_Size_7427, 4_QUOTIENT32209
mov rdx, r8		#REMAINDER_24221, REG_Size_7427_REMAINDER9758
mov ecx, ecx		#REG_REG_Size_7427_Parameter5097, REG_Size_7427
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value74, RetREG_28
jmp Return_Here_108		#Return_Here_108
Return_Here_108:
mov rbp, rsi		#tmp, Return_Value74
mov ecx, dword ptr [rbx + 12 ]		#this_79_12_REG29, this_79_12
mov r8, rdx		#this_79_12_REG29_REMAINDER6422, REMAINDER_24946
mov eax, 4		#4_QUOTIENT18588, 4
mul ecx		#this_79_12_REG29
mov ecx, eax		#this_79_12_REG29, 4_QUOTIENT18588
mov rdx, r8		#REMAINDER_24946, this_79_12_REG29_REMAINDER6422
mov r12d, ecx		#Size_75, this_79_12_REG29
mov rcx, qword ptr [rbx + 16 ]		#this_79_16_REG30, this_79_16
mov r13, rcx		#source_75, this_79_16_REG30
mov r14, rbp		#dest_75, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_75
jge while_29_END		#while_29_END
while_29:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_75_REG31, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_75_REG32, *
mov dword ptr [rcx ], r8d		#dest_75_REG31, source_75_REG32
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_75
jge while_29_END		#while_29_END
jmp while_29		#while_29
while_29_END:
jmp Return_Here_109		#Return_Here_109
Return_Here_109:
mov qword ptr [rbx + 16 ], rbp		#this_79_16, tmp
if_28_END:
mov rcx, qword ptr [rbx + 16 ]		#this_79_16_REG33, this_79_16
mov r8d, dword ptr [rbx + 12 ]		#this_79_12_REG35, this_79_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_79_16_REG33_REG34, *
mov dword ptr [rcx ], 2		#this_79_16_REG33_REG34, 2
add dword ptr [rbx + 12 ], 1		#this_79_12, 1
Return_Here_107:
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_1710148159808, a_REG36
add qword ptr [rcx + 0 ], 1		#a_TMP_1710148159808_0, 1
mov rcx, rcx		#this_80, a_TMP_1710148159808
sub dword ptr [rcx + 12 ], 1		#this_80_12, 1
Return_Here_110:
mov ecx, 0		#i_81, 0
lea r8, qword ptr [rsp + 0 ]		#a_REG37, .STACK_0
mov r8, r8		#a_TMP_1710148194752, a_REG37
add qword ptr [r8 + 0 ], 1		#a_TMP_1710148194752_0, 1
mov r8, r8		#this_81, a_TMP_1710148194752
if_30:
mov r9d, dword ptr [r8 + 12 ]		#this_81_12_REG38, this_81_12
cmp ecx, r9d		#i_81, this_81_12_REG38
jle if_30_END		#if_30_END
mov ecx, 0		#Return_Value81, 0
jmp Return_Here_111		#Return_Here_111
if_30_END:
mov r8, qword ptr [r8 + 16 ]		#this_81_16_REG39, this_81_16
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_81_16_REG39_REG40, *
mov ecx, r8d		#Return_Value81, this_81_16_REG39_REG40
jmp Return_Here_111		#Return_Here_111
Return_Here_111:
mov eax, ecx		#Returning_REG41, Return_Value81
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
if_31:
cmp rcx, 0		#this, 0
je if_31_END		#if_31_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_31_END		#if_31_END
mov r8, rcx		#this_TMP_1710148219840, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1710148219840_0, 1
mov rbx, r8		#Address_76, this_TMP_1710148219840
mov rbx, rcx		#Address_76, this
mov rcx, rbx		#REG_Address_76_Parameter16512, Address_76
mov edx, 8		#REG_8_Parameter23986, 8
call _V19internal_deallocatePhx
Return_Here_101:
mov rcx, rbx		#REG_Address_76_Parameter13290, Address_76
call _ZN13____List_int_10DestructorEP13____List_int_
if_31_END:
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
