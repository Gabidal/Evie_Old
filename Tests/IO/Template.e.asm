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
sub rsp, 28		#.STACK, 28
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_2239552694336, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_2239552694336_0, 1
mov rbx, rcx		#this_33, a_TMP_2239552694336
mov dword ptr [rbx + 8 ], 1		#this_33_8, 1
mov dword ptr [rbx + 12 ], 0		#this_33_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_33_8_REG1, this_33_8
mov ecx, ecx		#Size_0_33, this_33_8_REG1
mov r8d, ecx		#REG_Size_0_332, Size_0_33
mov r9, rdx		#REG_Size_0_332_REMAINDER19169, REMAINDER_15724
mov eax, 4		#4_QUOTIENT26500, 4
mul r8d		#REG_Size_0_332
mov r8d, eax		#REG_Size_0_332, 4_QUOTIENT26500
mov rdx, r9		#REMAINDER_15724, REG_Size_0_332_REMAINDER19169
mov ecx, ecx		#REG_Size_0_333, Size_0_33
mov r8, rdx		#REG_Size_0_333_REMAINDER29358, REMAINDER_26962
mov eax, 4		#4_QUOTIENT11478, 4
mul ecx		#REG_Size_0_333
mov ecx, eax		#REG_Size_0_333, 4_QUOTIENT11478
mov rdx, r8		#REMAINDER_26962, REG_Size_0_333_REMAINDER29358
mov ecx, ecx		#REG_REG_Size_0_333_Parameter41, REG_Size_0_333
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 20 ], rax		#.STACK_20, RetREG_4
jmp Return_Here_43		#Return_Here_43
Return_Here_43:
mov rcx, qword ptr [rsp + 20 ]		#REG_Return_Value0_335, .STACK_20
mov qword ptr [rbx + 16 ], rcx		#this_33_16, REG_Return_Value0_335
jmp Return_Here_42		#Return_Here_42
Return_Here_42:
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#a_TMP_2239552727488, a_REG6
add qword ptr [rcx + 0 ], 1		#a_TMP_2239552727488_0, 1
mov rbx, rcx		#this_34, a_TMP_2239552727488
if_0:
mov ecx, dword ptr [rbx + 12 ]		#this_34_12_REG7, this_34_12
mov r8d, dword ptr [rbx + 8 ]		#this_34_8_REG8, this_34_8
cmp ecx, r8d		#this_34_12_REG7, this_34_8_REG8
jl if_0_END		#if_0_END
mov ecx, dword ptr [rbx + 12 ]		#this_34_12_REG9, this_34_12
mov r8, rdx		#this_34_12_REG9_REMAINDER5705, REMAINDER_28145
mov eax, 2		#2_QUOTIENT24464, 2
mul ecx		#this_34_12_REG9
mov ecx, eax		#this_34_12_REG9, 2_QUOTIENT24464
mov rdx, r8		#REMAINDER_28145, this_34_12_REG9_REMAINDER5705
mov dword ptr [rbx + 8 ], ecx		#this_34_8, this_34_12_REG9
mov ecx, dword ptr [rbx + 8 ]		#this_34_8_REG10, this_34_8
mov edi, ecx		#Size_1, this_34_8_REG10
mov ecx, edi		#REG_Size_111, Size_1
mov r8, rdx		#REG_Size_111_REMAINDER16827, REMAINDER_9961
mov eax, 4		#4_QUOTIENT23281, 4
mul ecx		#REG_Size_111
mov ecx, eax		#REG_Size_111, 4_QUOTIENT23281
mov rdx, r8		#REMAINDER_9961, REG_Size_111_REMAINDER16827
mov ecx, edi		#REG_Size_112, Size_1
mov r8, rdx		#REG_Size_112_REMAINDER2995, REMAINDER_11942
mov eax, 4		#4_QUOTIENT491, 4
mul ecx		#REG_Size_112
mov ecx, eax		#REG_Size_112, 4_QUOTIENT491
mov rdx, r8		#REMAINDER_11942, REG_Size_112_REMAINDER2995
mov ecx, ecx		#REG_REG_Size_112_Parameter18467, REG_Size_112
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value1, RetREG_13
jmp Return_Here_45		#Return_Here_45
Return_Here_45:
mov rbp, rsi		#tmp, Return_Value1
mov ecx, dword ptr [rbx + 12 ]		#this_34_12_REG14, this_34_12
mov r12d, ecx		#Size_2, this_34_12_REG14
mov rcx, qword ptr [rbx + 16 ]		#this_34_16_REG15, this_34_16
mov r13, rcx		#source_2, this_34_16_REG15
mov r14, rbp		#dest_2, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_2
jge while_1_END		#while_1_END
while_1:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_2_REG16, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_2_REG17, *
mov dword ptr [rcx ], r8d		#dest_2_REG16, source_2_REG17
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_2
jge while_1_END		#while_1_END
jmp while_1		#while_1
while_1_END:
jmp Return_Here_46		#Return_Here_46
Return_Here_46:
mov qword ptr [rbx + 16 ], rbp		#this_34_16, tmp
if_0_END:
mov rcx, qword ptr [rbx + 16 ]		#this_34_16_REG18, this_34_16
mov r8d, dword ptr [rbx + 12 ]		#this_34_12_REG20, this_34_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_34_16_REG18_REG19, *
mov dword ptr [rcx ], 5		#this_34_16_REG18_REG19, 5
add dword ptr [rbx + 12 ], 1		#this_34_12, 1
Return_Here_44:
lea rcx, qword ptr [rsp + 0 ]		#a_REG21, .STACK_0
mov rcx, rcx		#a_TMP_2239552731968, a_REG21
add qword ptr [rcx + 0 ], 1		#a_TMP_2239552731968_0, 1
mov rbx, rcx		#this_35, a_TMP_2239552731968
if_2:
mov ecx, dword ptr [rbx + 12 ]		#this_35_12_REG22, this_35_12
mov r8d, dword ptr [rbx + 8 ]		#this_35_8_REG23, this_35_8
cmp ecx, r8d		#this_35_12_REG22, this_35_8_REG23
jl if_2_END		#if_2_END
mov ecx, dword ptr [rbx + 12 ]		#this_35_12_REG24, this_35_12
mov r8, rdx		#this_35_12_REG24_REMAINDER5436, REMAINDER_32391
mov eax, 2		#2_QUOTIENT4827, 2
mul ecx		#this_35_12_REG24
mov ecx, eax		#this_35_12_REG24, 2_QUOTIENT4827
mov rdx, r8		#REMAINDER_32391, this_35_12_REG24_REMAINDER5436
mov dword ptr [rbx + 8 ], ecx		#this_35_8, this_35_12_REG24
mov ecx, dword ptr [rbx + 8 ]		#this_35_8_REG25, this_35_8
mov edi, ecx		#Size_1, this_35_8_REG25
mov ecx, edi		#REG_Size_126, Size_1
mov r8, rdx		#REG_Size_126_REMAINDER3902, REMAINDER_153
mov eax, 4		#4_QUOTIENT14604, 4
mul ecx		#REG_Size_126
mov ecx, eax		#REG_Size_126, 4_QUOTIENT14604
mov rdx, r8		#REMAINDER_153, REG_Size_126_REMAINDER3902
mov ecx, edi		#REG_Size_127, Size_1
mov r8, rdx		#REG_Size_127_REMAINDER12382, REMAINDER_17421
mov eax, 4		#4_QUOTIENT292, 4
mul ecx		#REG_Size_127
mov ecx, eax		#REG_Size_127, 4_QUOTIENT292
mov rdx, r8		#REMAINDER_17421, REG_Size_127_REMAINDER12382
mov ecx, ecx		#REG_REG_Size_127_Parameter6334, REG_Size_127
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value1, RetREG_28
jmp Return_Here_48		#Return_Here_48
Return_Here_48:
mov rbp, rsi		#tmp, Return_Value1
mov ecx, dword ptr [rbx + 12 ]		#this_35_12_REG29, this_35_12
mov r12d, ecx		#Size_2, this_35_12_REG29
mov rcx, qword ptr [rbx + 16 ]		#this_35_16_REG30, this_35_16
mov r13, rcx		#source_2, this_35_16_REG30
mov r14, rbp		#dest_2, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_2
jge while_3_END		#while_3_END
while_3:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_2_REG31, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_2_REG32, *
mov dword ptr [rcx ], r8d		#dest_2_REG31, source_2_REG32
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_2
jge while_3_END		#while_3_END
jmp while_3		#while_3
while_3_END:
jmp Return_Here_49		#Return_Here_49
Return_Here_49:
mov qword ptr [rbx + 16 ], rbp		#this_35_16, tmp
if_2_END:
mov rcx, qword ptr [rbx + 16 ]		#this_35_16_REG33, this_35_16
mov r8d, dword ptr [rbx + 12 ]		#this_35_12_REG35, this_35_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_35_16_REG33_REG34, *
mov dword ptr [rcx ], 2		#this_35_16_REG33_REG34, 2
add dword ptr [rbx + 12 ], 1		#this_35_12, 1
Return_Here_47:
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_2239552755264, a_REG36
add qword ptr [rcx + 0 ], 1		#a_TMP_2239552755264_0, 1
mov rcx, rcx		#this_36, a_TMP_2239552755264
sub dword ptr [rcx + 12 ], 1		#this_36_12, 1
Return_Here_50:
mov ecx, 0		#i_37, 0
lea r8, qword ptr [rsp + 0 ]		#a_REG37, .STACK_0
mov r8, r8		#a_TMP_2239552750784, a_REG37
add qword ptr [r8 + 0 ], 1		#a_TMP_2239552750784_0, 1
mov r8, r8		#this_37, a_TMP_2239552750784
if_4:
mov r9d, dword ptr [r8 + 12 ]		#this_37_12_REG38, this_37_12
cmp ecx, r9d		#i_37, this_37_12_REG38
jle if_4_END		#if_4_END
mov ecx, 0		#Return_Value37, 0
jmp Return_Here_51		#Return_Here_51
if_4_END:
mov r8, qword ptr [r8 + 16 ]		#this_37_16_REG39, this_37_16
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_37_16_REG39_REG40, *
mov ecx, r8d		#Return_Value37, this_37_16_REG39_REG40
jmp Return_Here_51		#Return_Here_51
Return_Here_51:
mov eax, ecx		#Returning_REG41, Return_Value37
add rsp, 28		#.STACK, 28
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
pop r13		#r13
pop r14		#r14
pop r15		#r15
ret 		#
add rsp, 28		#.STACK, 28
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
