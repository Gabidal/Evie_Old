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
mov rcx, rcx		#a_TMP_1722797671648, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1722797671648_0, 1
mov rbx, rcx		#this_65, a_TMP_1722797671648
mov dword ptr [rbx + 8 ], 1		#this_65_8, 1
mov dword ptr [rbx + 12 ], 0		#this_65_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_65_8_REG1, this_65_8
mov ecx, ecx		#Size_61_65, this_65_8_REG1
mov r8d, ecx		#REG_Size_61_652, Size_61_65
mov r9, rdx		#REG_Size_61_652_REMAINDER5021, REMAINDER_28745
mov eax, 4		#4_QUOTIENT22386, 4
mul r8d		#REG_Size_61_652
mov r8d, eax		#REG_Size_61_652, 4_QUOTIENT22386
mov rdx, r9		#REMAINDER_28745, REG_Size_61_652_REMAINDER5021
mov ecx, ecx		#REG_Size_61_653, Size_61_65
mov r8, rdx		#REG_Size_61_653_REMAINDER19072, REMAINDER_6270
mov eax, 4		#4_QUOTIENT26924, 4
mul ecx		#REG_Size_61_653
mov ecx, eax		#REG_Size_61_653, 4_QUOTIENT26924
mov rdx, r8		#REMAINDER_6270, REG_Size_61_653_REMAINDER19072
mov ecx, ecx		#REG_REG_Size_61_653_Parameter29658, REG_Size_61_653
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_93		#Return_Here_93
Return_Here_93:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value61_655, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_65_16, REG_Return_Value61_655
jmp Return_Here_92		#Return_Here_92
Return_Here_92:
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#a_TMP_1722797692384, a_REG6
add qword ptr [rcx + 0 ], 1		#a_TMP_1722797692384_0, 1
mov rbx, rcx		#this_66, a_TMP_1722797692384
if_24:
mov ecx, dword ptr [rbx + 12 ]		#this_66_12_REG7, this_66_12
mov r8d, dword ptr [rbx + 8 ]		#this_66_8_REG8, this_66_8
cmp ecx, r8d		#this_66_12_REG7, this_66_8_REG8
jl if_24_END		#if_24_END
mov ecx, dword ptr [rbx + 12 ]		#this_66_12_REG9, this_66_12
mov r8, rdx		#this_66_12_REG9_REMAINDER26777, REMAINDER_15573
mov eax, 2		#2_QUOTIENT5829, 2
mul ecx		#this_66_12_REG9
mov ecx, eax		#this_66_12_REG9, 2_QUOTIENT5829
mov rdx, r8		#REMAINDER_15573, this_66_12_REG9_REMAINDER26777
mov dword ptr [rbx + 8 ], ecx		#this_66_8, this_66_12_REG9
mov ecx, dword ptr [rbx + 8 ]		#this_66_8_REG10, this_66_8
mov edi, ecx		#Size_62, this_66_8_REG10
mov ecx, edi		#REG_Size_6211, Size_62
mov r8, rdx		#REG_Size_6211_REMAINDER16512, REMAINDER_23986
mov eax, 4		#4_QUOTIENT5097, 4
mul ecx		#REG_Size_6211
mov ecx, eax		#REG_Size_6211, 4_QUOTIENT5097
mov rdx, r8		#REMAINDER_23986, REG_Size_6211_REMAINDER16512
mov ecx, edi		#REG_Size_6212, Size_62
mov r8, rdx		#REG_Size_6212_REMAINDER9161, REMAINDER_18636
mov eax, 4		#4_QUOTIENT13290, 4
mul ecx		#REG_Size_6212
mov ecx, eax		#REG_Size_6212, 4_QUOTIENT13290
mov rdx, r8		#REMAINDER_18636, REG_Size_6212_REMAINDER9161
mov ecx, ecx		#REG_REG_Size_6212_Parameter22704, REG_Size_6212
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value62, RetREG_13
jmp Return_Here_95		#Return_Here_95
Return_Here_95:
mov rbp, rsi		#tmp, Return_Value62
mov ecx, dword ptr [rbx + 12 ]		#this_66_12_REG14, this_66_12
mov r8, rdx		#this_66_12_REG14_REMAINDER24767, REMAINDER_23655
mov eax, 4		#4_QUOTIENT22355, 4
mul ecx		#this_66_12_REG14
mov ecx, eax		#this_66_12_REG14, 4_QUOTIENT22355
mov rdx, r8		#REMAINDER_23655, this_66_12_REG14_REMAINDER24767
mov r12d, ecx		#Size_63, this_66_12_REG14
mov rcx, qword ptr [rbx + 16 ]		#this_66_16_REG15, this_66_16
mov r13, rcx		#source_63, this_66_16_REG15
mov r14, rbp		#dest_63, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_63
jge while_25_END		#while_25_END
while_25:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_63_REG16, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_63_REG17, *
mov dword ptr [rcx ], r8d		#dest_63_REG16, source_63_REG17
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_63
jge while_25_END		#while_25_END
jmp while_25		#while_25
while_25_END:
jmp Return_Here_96		#Return_Here_96
Return_Here_96:
mov qword ptr [rbx + 16 ], rbp		#this_66_16, tmp
if_24_END:
mov rcx, qword ptr [rbx + 16 ]		#this_66_16_REG18, this_66_16
mov r8d, dword ptr [rbx + 12 ]		#this_66_12_REG20, this_66_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_66_16_REG18_REG19, *
mov dword ptr [rcx ], 5		#this_66_16_REG18_REG19, 5
add dword ptr [rbx + 12 ], 1		#this_66_12, 1
Return_Here_94:
lea rcx, qword ptr [rsp + 0 ]		#a_REG21, .STACK_0
mov rcx, rcx		#a_TMP_1722797712256, a_REG21
add qword ptr [rcx + 0 ], 1		#a_TMP_1722797712256_0, 1
mov rbx, rcx		#this_67, a_TMP_1722797712256
if_26:
mov ecx, dword ptr [rbx + 12 ]		#this_67_12_REG22, this_67_12
mov r8d, dword ptr [rbx + 8 ]		#this_67_8_REG23, this_67_8
cmp ecx, r8d		#this_67_12_REG22, this_67_8_REG23
jl if_26_END		#if_26_END
mov ecx, dword ptr [rbx + 12 ]		#this_67_12_REG24, this_67_12
mov r8, rdx		#this_67_12_REG24_REMAINDER4031, REMAINDER_12052
mov eax, 2		#2_QUOTIENT15574, 2
mul ecx		#this_67_12_REG24
mov ecx, eax		#this_67_12_REG24, 2_QUOTIENT15574
mov rdx, r8		#REMAINDER_12052, this_67_12_REG24_REMAINDER4031
mov dword ptr [rbx + 8 ], ecx		#this_67_8, this_67_12_REG24
mov ecx, dword ptr [rbx + 8 ]		#this_67_8_REG25, this_67_8
mov edi, ecx		#Size_62, this_67_8_REG25
mov ecx, edi		#REG_Size_6226, Size_62
mov r8, rdx		#REG_Size_6226_REMAINDER1150, REMAINDER_16941
mov eax, 4		#4_QUOTIENT27350, 4
mul ecx		#REG_Size_6226
mov ecx, eax		#REG_Size_6226, 4_QUOTIENT27350
mov rdx, r8		#REMAINDER_16941, REG_Size_6226_REMAINDER1150
mov ecx, edi		#REG_Size_6227, Size_62
mov r8, rdx		#REG_Size_6227_REMAINDER13966, REMAINDER_3430
mov eax, 4		#4_QUOTIENT21724, 4
mul ecx		#REG_Size_6227
mov ecx, eax		#REG_Size_6227, 4_QUOTIENT21724
mov rdx, r8		#REMAINDER_3430, REG_Size_6227_REMAINDER13966
mov ecx, ecx		#REG_REG_Size_6227_Parameter9930, REG_Size_6227
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value62, RetREG_28
jmp Return_Here_98		#Return_Here_98
Return_Here_98:
mov rbp, rsi		#tmp, Return_Value62
mov ecx, dword ptr [rbx + 12 ]		#this_67_12_REG29, this_67_12
mov r8, rdx		#this_67_12_REG29_REMAINDER30191, REMAINDER_18007
mov eax, 4		#4_QUOTIENT31107, 4
mul ecx		#this_67_12_REG29
mov ecx, eax		#this_67_12_REG29, 4_QUOTIENT31107
mov rdx, r8		#REMAINDER_18007, this_67_12_REG29_REMAINDER30191
mov r12d, ecx		#Size_63, this_67_12_REG29
mov rcx, qword ptr [rbx + 16 ]		#this_67_16_REG30, this_67_16
mov r13, rcx		#source_63, this_67_16_REG30
mov r14, rbp		#dest_63, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_63
jge while_27_END		#while_27_END
while_27:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_63_REG31, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_63_REG32, *
mov dword ptr [rcx ], r8d		#dest_63_REG31, source_63_REG32
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_63
jge while_27_END		#while_27_END
jmp while_27		#while_27
while_27_END:
jmp Return_Here_99		#Return_Here_99
Return_Here_99:
mov qword ptr [rbx + 16 ], rbp		#this_67_16, tmp
if_26_END:
mov rcx, qword ptr [rbx + 16 ]		#this_67_16_REG33, this_67_16
mov r8d, dword ptr [rbx + 12 ]		#this_67_12_REG35, this_67_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_67_16_REG33_REG34, *
mov dword ptr [rcx ], 2		#this_67_16_REG33_REG34, 2
add dword ptr [rbx + 12 ], 1		#this_67_12, 1
Return_Here_97:
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_1722797702752, a_REG36
add qword ptr [rcx + 0 ], 1		#a_TMP_1722797702752_0, 1
mov rcx, rcx		#this_68, a_TMP_1722797702752
sub dword ptr [rcx + 12 ], 1		#this_68_12, 1
Return_Here_100:
mov ecx, 0		#i_69, 0
lea r8, qword ptr [rsp + 0 ]		#a_REG37, .STACK_0
mov r8, r8		#a_TMP_1722797720032, a_REG37
add qword ptr [r8 + 0 ], 1		#a_TMP_1722797720032_0, 1
mov r8, r8		#this_69, a_TMP_1722797720032
if_28:
mov r9d, dword ptr [r8 + 12 ]		#this_69_12_REG38, this_69_12
cmp ecx, r9d		#i_69, this_69_12_REG38
jle if_28_END		#if_28_END
mov ecx, 0		#Return_Value69, 0
jmp Return_Here_101		#Return_Here_101
if_28_END:
mov r8, qword ptr [r8 + 16 ]		#this_69_16_REG39, this_69_16
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_69_16_REG39_REG40, *
mov ecx, r8d		#Return_Value69, this_69_16_REG39_REG40
jmp Return_Here_101		#Return_Here_101
Return_Here_101:
mov eax, ecx		#Returning_REG41, Return_Value69
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
if_29:
cmp rcx, 0		#this, 0
je if_29_END		#if_29_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_29_END		#if_29_END
mov r8, rcx		#this_TMP_1722797725216, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1722797725216_0, 1
mov rbx, r8		#Address_64, this_TMP_1722797725216
mov rbx, rcx		#Address_64, this
mov rcx, rbx		#REG_Address_64_Parameter13977, Address_64
mov edx, 8		#REG_8_Parameter2306, 8
call _V19internal_deallocatePhx
Return_Here_91:
mov rcx, rbx		#REG_Address_64_Parameter31673, Address_64
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
