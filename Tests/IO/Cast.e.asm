.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
Return_Here_120:
lea rcx, qword ptr [rsp + 0 ]		#m_REG0, .STACK_0
mov rcx, rcx		#m_TMP_2097122059984, m_REG0
add qword ptr [rcx + 0 ], 1		#m_TMP_2097122059984_0, 1
mov rcx, rcx		#this_87, m_TMP_2097122059984
mov r8, rcx		#this_87_TMP_2097122054800, this_87
add qword ptr [r8 + 0 ], 1		#this_87_TMP_2097122054800_0, 1
mov r8, r8		#this_86_87, this_87_TMP_2097122054800
mov r8, rcx		#this_86_87, this_87
mov dword ptr [r8 + 8 ], 0		#this_86_87_8, 0
jmp Return_Here_123		#Return_Here_123
Return_Here_123:
mov dword ptr [rcx + 8 ], 1		#this_87_8, 1
mov r8d, 1074261268		#REG_1074290436, 1074261268
mov dword ptr [rcx + 12 ], r8d		#this_87_12, REG_1074290436
jmp Return_Here_122		#Return_Here_122
Return_Here_122:
movss xmm0, dword ptr [rsp + 0 + 12 ]		#m_12_REG1, +_12
cvttss2si ecx, xmm0		#REG_feature2, m_12_REG1
mov eax, ecx		#Returning_REG3, REG_feature2
add rsp, 16		#.STACK, 16
ret 		#
add rsp, 16		#.STACK, 16
ret 		#


_Z4mainv:
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_ZN4Base10DestructorEP4Base:
push rbx		#rbx
if_31:
cmp rcx, 0		#this, 0
je if_31_END		#if_31_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_31_END		#if_31_END
mov r8, rcx		#this_TMP_2097122056528, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2097122056528_0, 1
mov rbx, r8		#Address_82, this_TMP_2097122056528
mov rbx, rcx		#Address_82, this
mov rcx, rbx		#REG_Address_82_Parameter32209, Address_82
mov edx, 8		#REG_8_Parameter9758, 8
call _V19internal_deallocatePhx
Return_Here_117:
mov rcx, rbx		#REG_Address_82_Parameter24221, Address_82
call _ZN4Base10DestructorEP4Base
if_31_END:
pop rbx		#rbx
ret 		#


_ZN3Mid10DestructorEP3Mid:
push rbx		#rbx
if_32:
cmp rcx, 0		#this, 0
je if_32_END		#if_32_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_32_END		#if_32_END
mov r8, rcx		#this_TMP_2097122053936, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2097122053936_0, 1
mov rbx, r8		#Address_83, this_TMP_2097122053936
mov rbx, rcx		#Address_83, this
mov rcx, rbx		#REG_Address_83_Parameter18588, Address_83
mov edx, 8		#REG_8_Parameter6422, 8
call _V19internal_deallocatePhx
Return_Here_118:
mov rcx, rbx		#REG_Address_83_Parameter24946, Address_83
call _ZN3Mid10DestructorEP3Mid
if_32_END:
pop rbx		#rbx
ret 		#


_ZN3Top10DestructorEP3Top:
push rbx		#rbx
if_33:
cmp rcx, 0		#this, 0
je if_33_END		#if_33_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_33_END		#if_33_END
mov r8, rcx		#this_TMP_2097122971952, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2097122971952_0, 1
mov rbx, r8		#Address_84, this_TMP_2097122971952
mov rbx, rcx		#Address_84, this
mov rcx, rbx		#REG_Address_84_Parameter27506, Address_84
mov edx, 8		#REG_8_Parameter13030, 8
call _V19internal_deallocatePhx
Return_Here_119:
mov rcx, rbx		#REG_Address_84_Parameter16413, Address_84
call _ZN3Top10DestructorEP3Top
if_33_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
