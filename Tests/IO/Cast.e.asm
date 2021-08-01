.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
Return_Here_125:
lea rcx, qword ptr [rsp + 0 ]		#m_REG0, .STACK_0
mov rcx, rcx		#m_TMP_1722827472048, m_REG0
add qword ptr [rcx + 0 ], 1		#m_TMP_1722827472048_0, 1
mov rcx, rcx		#this_91, m_TMP_1722827472048
mov r8, rcx		#this_91_TMP_1722827446992, this_91
add qword ptr [r8 + 0 ], 1		#this_91_TMP_1722827446992_0, 1
mov r8, r8		#this_90_91, this_91_TMP_1722827446992
mov r8, rcx		#this_90_91, this_91
mov dword ptr [r8 + 8 ], 0		#this_90_91_8, 0
jmp Return_Here_128		#Return_Here_128
Return_Here_128:
mov dword ptr [rcx + 8 ], 1		#this_91_8, 1
mov r8d, 1074261268		#REG_1074267751, 1074261268
mov dword ptr [rcx + 12 ], r8d		#this_91_12, REG_1074267751
jmp Return_Here_127		#Return_Here_127
Return_Here_127:
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
if_32:
cmp rcx, 0		#this, 0
je if_32_END		#if_32_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_32_END		#if_32_END
mov r8, rcx		#this_TMP_1722827478960, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1722827478960_0, 1
mov rbx, r8		#Address_86, this_TMP_1722827478960
mov rbx, rcx		#Address_86, this
mov rcx, rbx		#REG_Address_86_Parameter900, Address_86
mov edx, 8		#REG_8_Parameter32591, 8
call _V19internal_deallocatePhx
Return_Here_122:
mov rcx, rbx		#REG_Address_86_Parameter18762, Address_86
call _ZN4Base10DestructorEP4Base
if_32_END:
pop rbx		#rbx
ret 		#


_ZN3Mid10DestructorEP3Mid:
push rbx		#rbx
if_33:
cmp rcx, 0		#this, 0
je if_33_END		#if_33_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_33_END		#if_33_END
mov r8, rcx		#this_TMP_1722827497968, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1722827497968_0, 1
mov rbx, r8		#Address_87, this_TMP_1722827497968
mov rbx, rcx		#Address_87, this
mov rcx, rbx		#REG_Address_87_Parameter1655, Address_87
mov edx, 8		#REG_8_Parameter17410, 8
call _V19internal_deallocatePhx
Return_Here_123:
mov rcx, rbx		#REG_Address_87_Parameter6359, Address_87
call _ZN3Mid10DestructorEP3Mid
if_33_END:
pop rbx		#rbx
ret 		#


_ZN3Top10DestructorEP3Top:
push rbx		#rbx
if_34:
cmp rcx, 0		#this, 0
je if_34_END		#if_34_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_34_END		#if_34_END
mov r8, rcx		#this_TMP_1722827512656, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1722827512656_0, 1
mov rbx, r8		#Address_88, this_TMP_1722827512656
mov rbx, rcx		#Address_88, this
mov rcx, rbx		#REG_Address_88_Parameter27624, Address_88
mov edx, 8		#REG_8_Parameter20537, 8
call _V19internal_deallocatePhx
Return_Here_124:
mov rcx, rbx		#REG_Address_88_Parameter21548, Address_88
call _ZN3Top10DestructorEP3Top
if_34_END:
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
