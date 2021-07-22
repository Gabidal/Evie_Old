.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
push rbx		#rbx
sub rsp, 32		#.STACK, 32
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_2787280706224, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_2787280706224_0, 1
mov rbx, rcx		#this_109, a_TMP_2787280706224
mov dword ptr [rbx + 8 ], 1		#this_109_8, 1
mov dword ptr [rbx + 12 ], 0		#this_109_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_109_8_REG1, this_109_8
mov ecx, ecx		#Size_105_109, this_109_8_REG1
mov r8d, ecx		#REG_Size_105_1092, Size_105_109
mov r9, rdx		#REG_Size_105_1092_REMAINDER2421, REMAINDER_14310
mov eax, 4		#4_QUOTIENT17807, 4
mul r8d		#REG_Size_105_1092
mov r8d, eax		#REG_Size_105_1092, 4_QUOTIENT17807
mov rdx, r9		#REMAINDER_14310, REG_Size_105_1092_REMAINDER2421
mov ecx, ecx		#REG_Size_105_1093, Size_105_109
mov r8, rdx		#REG_Size_105_1093_REMAINDER22813, REMAINDER_9514
mov eax, 4		#4_QUOTIENT6617, 4
mul ecx		#REG_Size_105_1093
mov ecx, eax		#REG_Size_105_1093, 4_QUOTIENT6617
mov rdx, r8		#REMAINDER_9514, REG_Size_105_1093_REMAINDER22813
mov ecx, ecx		#REG_REG_Size_105_1093_Parameter3728, REG_Size_105_1093
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_151		#Return_Here_151
Return_Here_151:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value105_1095, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_109_16, REG_Return_Value105_1095
jmp Return_Here_150		#Return_Here_150
Return_Here_150:
mov ecx, 1		#Return_Value110, 1
jmp Return_Here_152		#Return_Here_152
Return_Here_152:
mov eax, ecx		#Returning_REG6, Return_Value110
add rsp, 32		#.STACK, 32
pop rbx		#rbx
ret 		#
add rsp, 32		#.STACK, 32
pop rbx		#rbx
ret 		#


_Z4mainv:
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_ZN13____List_int_10DestructorEP13____List_int_:
push rbx		#rbx
if_45:
cmp rcx, 0		#this, 0
je if_45_END		#if_45_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_45_END		#if_45_END
mov r8, rcx		#this_TMP_2787280734512, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2787280734512_0, 1
mov rbx, r8		#Address_108, this_TMP_2787280734512
mov rbx, rcx		#Address_108, this
mov rcx, rbx		#REG_Address_108_Parameter14893, Address_108
mov edx, 8		#REG_8_Parameter24648, 8
call _V19internal_deallocatePhx
Return_Here_149:
mov rcx, rbx		#REG_Address_108_Parameter22483, Address_108
call _ZN13____List_int_10DestructorEP13____List_int_
if_45_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
