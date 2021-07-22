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
mov rcx, rcx		#a_TMP_1445890174640, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1445890174640_0, 1
mov rbx, rcx		#this_61, a_TMP_1445890174640
mov dword ptr [rbx + 8 ], 1		#this_61_8, 1
mov dword ptr [rbx + 12 ], 0		#this_61_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_61_8_REG1, this_61_8
mov ecx, ecx		#Size_57_61, this_61_8_REG1
mov r8d, ecx		#REG_Size_57_612, Size_57_61
mov r9, rdx		#REG_Size_57_612_REMAINDER2306, REMAINDER_31673
mov eax, 4		#4_QUOTIENT13977, 4
mul r8d		#REG_Size_57_612
mov r8d, eax		#REG_Size_57_612, 4_QUOTIENT13977
mov rdx, r9		#REMAINDER_31673, REG_Size_57_612_REMAINDER2306
mov ecx, ecx		#REG_Size_57_613, Size_57_61
mov r8, rdx		#REG_Size_57_613_REMAINDER5021, REMAINDER_28745
mov eax, 4		#4_QUOTIENT22386, 4
mul ecx		#REG_Size_57_613
mov ecx, eax		#REG_Size_57_613, 4_QUOTIENT22386
mov rdx, r8		#REMAINDER_28745, REG_Size_57_613_REMAINDER5021
mov ecx, ecx		#REG_REG_Size_57_613_Parameter4833, REG_Size_57_613
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_83		#Return_Here_83
Return_Here_83:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value57_615, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_61_16, REG_Return_Value57_615
jmp Return_Here_82		#Return_Here_82
Return_Here_82:
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#a_TMP_1445890196272, a_REG6
add qword ptr [rcx + 0 ], 1		#a_TMP_1445890196272_0, 1
mov rbx, rcx		#this_62, a_TMP_1445890196272
if_23:
mov ecx, dword ptr [rbx + 12 ]		#this_62_12_REG7, this_62_12
mov r8d, dword ptr [rbx + 8 ]		#this_62_8_REG8, this_62_8
cmp ecx, r8d		#this_62_12_REG7, this_62_8_REG8
jl if_23_END		#if_23_END
mov ecx, dword ptr [rbx + 12 ]		#this_62_12_REG9, this_62_12
mov r8, rdx		#this_62_12_REG9_REMAINDER19072, REMAINDER_6270
mov eax, 2		#2_QUOTIENT26924, 2
mul ecx		#this_62_12_REG9
mov ecx, eax		#this_62_12_REG9, 2_QUOTIENT26924
mov rdx, r8		#REMAINDER_6270, this_62_12_REG9_REMAINDER19072
mov dword ptr [rbx + 8 ], ecx		#this_62_8, this_62_12_REG9
mov ecx, dword ptr [rbx + 8 ]		#this_62_8_REG10, this_62_8
mov edi, ecx		#Size_58, this_62_8_REG10
mov ecx, edi		#REG_Size_5811, Size_58
mov r8, rdx		#REG_Size_5811_REMAINDER26777, REMAINDER_15573
mov eax, 4		#4_QUOTIENT5829, 4
mul ecx		#REG_Size_5811
mov ecx, eax		#REG_Size_5811, 4_QUOTIENT5829
mov rdx, r8		#REMAINDER_15573, REG_Size_5811_REMAINDER26777
mov ecx, edi		#REG_Size_5812, Size_58
mov r8, rdx		#REG_Size_5812_REMAINDER16512, REMAINDER_23986
mov eax, 4		#4_QUOTIENT5097, 4
mul ecx		#REG_Size_5812
mov ecx, eax		#REG_Size_5812, 4_QUOTIENT5097
mov rdx, r8		#REMAINDER_23986, REG_Size_5812_REMAINDER16512
mov ecx, ecx		#REG_REG_Size_5812_Parameter31115, REG_Size_5812
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value58, RetREG_13
jmp Return_Here_85		#Return_Here_85
Return_Here_85:
mov rbp, rsi		#tmp, Return_Value58
mov ecx, dword ptr [rbx + 12 ]		#this_62_12_REG14, this_62_12
mov r8, rdx		#this_62_12_REG14_REMAINDER9161, REMAINDER_18636
mov eax, 4		#4_QUOTIENT13290, 4
mul ecx		#this_62_12_REG14
mov ecx, eax		#this_62_12_REG14, 4_QUOTIENT13290
mov rdx, r8		#REMAINDER_18636, this_62_12_REG14_REMAINDER9161
mov r12d, ecx		#Size_59, this_62_12_REG14
mov rcx, qword ptr [rbx + 16 ]		#this_62_16_REG15, this_62_16
mov r13, rcx		#source_59, this_62_16_REG15
mov r14, rbp		#dest_59, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_59
jge while_24_END		#while_24_END
while_24:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_59_REG16, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_59_REG17, *
mov dword ptr [rcx ], r8d		#dest_59_REG16, source_59_REG17
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_59
jge while_24_END		#while_24_END
jmp while_24		#while_24
while_24_END:
jmp Return_Here_86		#Return_Here_86
Return_Here_86:
mov qword ptr [rbx + 16 ], rbp		#this_62_16, tmp
if_23_END:
mov rcx, qword ptr [rbx + 16 ]		#this_62_16_REG18, this_62_16
mov r8d, dword ptr [rbx + 12 ]		#this_62_12_REG20, this_62_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_62_16_REG18_REG19, *
mov dword ptr [rcx ], 5		#this_62_16_REG18_REG19, 5
add dword ptr [rbx + 12 ], 1		#this_62_12, 1
Return_Here_84:
lea rcx, qword ptr [rsp + 0 ]		#a_REG21, .STACK_0
mov rcx, rcx		#a_TMP_1445890222896, a_REG21
add qword ptr [rcx + 0 ], 1		#a_TMP_1445890222896_0, 1
mov rbx, rcx		#this_63, a_TMP_1445890222896
if_25:
mov ecx, dword ptr [rbx + 12 ]		#this_63_12_REG22, this_63_12
mov r8d, dword ptr [rbx + 8 ]		#this_63_8_REG23, this_63_8
cmp ecx, r8d		#this_63_12_REG22, this_63_8_REG23
jl if_25_END		#if_25_END
mov ecx, dword ptr [rbx + 12 ]		#this_63_12_REG24, this_63_12
mov r8, rdx		#this_63_12_REG24_REMAINDER24767, REMAINDER_23655
mov eax, 2		#2_QUOTIENT22355, 2
mul ecx		#this_63_12_REG24
mov ecx, eax		#this_63_12_REG24, 2_QUOTIENT22355
mov rdx, r8		#REMAINDER_23655, this_63_12_REG24_REMAINDER24767
mov dword ptr [rbx + 8 ], ecx		#this_63_8, this_63_12_REG24
mov ecx, dword ptr [rbx + 8 ]		#this_63_8_REG25, this_63_8
mov edi, ecx		#Size_58, this_63_8_REG25
mov ecx, edi		#REG_Size_5826, Size_58
mov r8, rdx		#REG_Size_5826_REMAINDER4031, REMAINDER_12052
mov eax, 4		#4_QUOTIENT15574, 4
mul ecx		#REG_Size_5826
mov ecx, eax		#REG_Size_5826, 4_QUOTIENT15574
mov rdx, r8		#REMAINDER_12052, REG_Size_5826_REMAINDER4031
mov ecx, edi		#REG_Size_5827, Size_58
mov r8, rdx		#REG_Size_5827_REMAINDER1150, REMAINDER_16941
mov eax, 4		#4_QUOTIENT27350, 4
mul ecx		#REG_Size_5827
mov ecx, eax		#REG_Size_5827, 4_QUOTIENT27350
mov rdx, r8		#REMAINDER_16941, REG_Size_5827_REMAINDER1150
mov ecx, ecx		#REG_REG_Size_5827_Parameter4639, REG_Size_5827
call _V17internal_allocatex_rPh
mov rsi, rax		#Return_Value58, RetREG_28
jmp Return_Here_88		#Return_Here_88
Return_Here_88:
mov rbp, rsi		#tmp, Return_Value58
mov ecx, dword ptr [rbx + 12 ]		#this_63_12_REG29, this_63_12
mov r8, rdx		#this_63_12_REG29_REMAINDER13966, REMAINDER_3430
mov eax, 4		#4_QUOTIENT21724, 4
mul ecx		#this_63_12_REG29
mov ecx, eax		#this_63_12_REG29, 4_QUOTIENT21724
mov rdx, r8		#REMAINDER_3430, this_63_12_REG29_REMAINDER13966
mov r12d, ecx		#Size_59, this_63_12_REG29
mov rcx, qword ptr [rbx + 16 ]		#this_63_16_REG30, this_63_16
mov r13, rcx		#source_59, this_63_16_REG30
mov r14, rbp		#dest_59, tmp
mov r15d, 0		#i, 0
cmp r15d, r12d		#i, Size_59
jge while_26_END		#while_26_END
while_26:
lea rcx, qword ptr [r14 + r15 * 4 ]		#dest_59_REG31, *
mov r8d, dword ptr [r13 + r15 * 4 ]		#source_59_REG32, *
mov dword ptr [rcx ], r8d		#dest_59_REG31, source_59_REG32
add r15d, 1		#i, 1
cmp r15d, r12d		#i, Size_59
jge while_26_END		#while_26_END
jmp while_26		#while_26
while_26_END:
jmp Return_Here_89		#Return_Here_89
Return_Here_89:
mov qword ptr [rbx + 16 ], rbp		#this_63_16, tmp
if_25_END:
mov rcx, qword ptr [rbx + 16 ]		#this_63_16_REG33, this_63_16
mov r8d, dword ptr [rbx + 12 ]		#this_63_12_REG35, this_63_12
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_63_16_REG33_REG34, *
mov dword ptr [rcx ], 2		#this_63_16_REG33_REG34, 2
add dword ptr [rbx + 12 ], 1		#this_63_12, 1
Return_Here_87:
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_1445890213744, a_REG36
add qword ptr [rcx + 0 ], 1		#a_TMP_1445890213744_0, 1
mov rcx, rcx		#this_64, a_TMP_1445890213744
sub dword ptr [rcx + 12 ], 1		#this_64_12, 1
Return_Here_90:
mov ecx, 0		#i_65, 0
lea r8, qword ptr [rsp + 0 ]		#a_REG37, .STACK_0
mov r8, r8		#a_TMP_1445890229552, a_REG37
add qword ptr [r8 + 0 ], 1		#a_TMP_1445890229552_0, 1
mov r8, r8		#this_65, a_TMP_1445890229552
if_27:
mov r9d, dword ptr [r8 + 12 ]		#this_65_12_REG38, this_65_12
cmp ecx, r9d		#i_65, this_65_12_REG38
jle if_27_END		#if_27_END
mov ecx, 0		#Return_Value65, 0
jmp Return_Here_91		#Return_Here_91
if_27_END:
mov r8, qword ptr [r8 + 16 ]		#this_65_16_REG39, this_65_16
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_65_16_REG39_REG40, *
mov ecx, r8d		#Return_Value65, this_65_16_REG39_REG40
jmp Return_Here_91		#Return_Here_91
Return_Here_91:
mov eax, ecx		#Returning_REG41, Return_Value65
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
if_28:
cmp rcx, 0		#this, 0
je if_28_END		#if_28_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_28_END		#if_28_END
mov r8, rcx		#this_TMP_1445890218736, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1445890218736_0, 1
mov rbx, r8		#Address_60, this_TMP_1445890218736
mov rbx, rcx		#Address_60, this
mov rcx, rbx		#REG_Address_60_Parameter29658, Address_60
mov edx, 8		#REG_8_Parameter22704, 8
call _V19internal_deallocatePhx
Return_Here_81:
mov rcx, rbx		#REG_Address_60_Parameter9930, Address_60
call _ZN13____List_int_10DestructorEP13____List_int_
if_28_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
