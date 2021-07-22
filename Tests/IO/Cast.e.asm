.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
Return_Here_111:
lea rcx, qword ptr [rsp + 0 ]		#m_REG0, .STACK_0
mov rcx, rcx		#m_TMP_1445901104240, m_REG0
add qword ptr [rcx + 0 ], 1		#m_TMP_1445901104240_0, 1
mov rcx, rcx		#this_81, m_TMP_1445901104240
mov r8, rcx		#this_81_TMP_1445901098416, this_81
add qword ptr [r8 + 0 ], 1		#this_81_TMP_1445901098416_0, 1
mov r8, r8		#this_80_81, this_81_TMP_1445901098416
mov r8, rcx		#this_80_81, this_81
mov dword ptr [r8 + 8 ], 0		#this_80_81_8, 0
jmp Return_Here_114		#Return_Here_114
Return_Here_114:
mov dword ptr [rcx + 8 ], 1		#this_81_8, 1
mov r8d, 1074261268		#REG_1074285489, 1074261268
mov dword ptr [rcx + 12 ], r8d		#this_81_12, REG_1074285489
jmp Return_Here_113		#Return_Here_113
Return_Here_113:
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
if_30:
cmp rcx, 0		#this, 0
je if_30_END		#if_30_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_30_END		#if_30_END
mov r8, rcx		#this_TMP_1445901134192, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1445901134192_0, 1
mov rbx, r8		#Address_76, this_TMP_1445901134192
mov rbx, rcx		#Address_76, this
mov rcx, rbx		#REG_Address_76_Parameter11337, Address_76
mov edx, 8		#REG_8_Parameter15457, 8
call _V19internal_deallocatePhx
Return_Here_108:
mov rcx, rbx		#REG_Address_76_Parameter12287, Address_76
call _ZN4Base10DestructorEP4Base
if_30_END:
pop rbx		#rbx
ret 		#


_ZN3Mid10DestructorEP3Mid:
push rbx		#rbx
if_31:
cmp rcx, 0		#this, 0
je if_31_END		#if_31_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_31_END		#if_31_END
mov r8, rcx		#this_TMP_1445901142512, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1445901142512_0, 1
mov rbx, r8		#Address_77, this_TMP_1445901142512
mov rbx, rcx		#Address_77, this
mov rcx, rbx		#REG_Address_77_Parameter27753, Address_77
mov edx, 8		#REG_8_Parameter10383, 8
call _V19internal_deallocatePhx
Return_Here_109:
mov rcx, rbx		#REG_Address_77_Parameter14945, Address_77
call _ZN3Mid10DestructorEP3Mid
if_31_END:
pop rbx		#rbx
ret 		#


_ZN3Top10DestructorEP3Top:
push rbx		#rbx
if_32:
cmp rcx, 0		#this, 0
je if_32_END		#if_32_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_32_END		#if_32_END
mov r8, rcx		#this_TMP_1445901172464, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1445901172464_0, 1
mov rbx, r8		#Address_78, this_TMP_1445901172464
mov rbx, rcx		#Address_78, this
mov rcx, rbx		#REG_Address_78_Parameter8909, Address_78
mov edx, 8		#REG_8_Parameter32209, 8
call _V19internal_deallocatePhx
Return_Here_110:
mov rcx, rbx		#REG_Address_78_Parameter9758, Address_78
call _ZN3Top10DestructorEP3Top
if_32_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
