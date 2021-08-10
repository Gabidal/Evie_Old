.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
Return_Here_117:
lea rcx, qword ptr [rsp + 0 ]		#m_REG0, .STACK_0
mov rcx, rcx		#m_TMP_1724629905600, m_REG0
add qword ptr [rcx + 0 ], 1		#m_TMP_1724629905600_0, 1
mov rcx, rcx		#this_89, m_TMP_1724629905600
mov r8, rcx		#this_89_TMP_1724629938432, this_89
add qword ptr [r8 + 0 ], 1		#this_89_TMP_1724629938432_0, 1
mov r8, r8		#this_88_89, this_89_TMP_1724629938432
mov r8, rcx		#this_88_89, this_89
mov dword ptr [r8 + 8 ], 0		#this_88_89_8, 0
jmp Return_Here_120		#Return_Here_120
Return_Here_120:
mov dword ptr [rcx + 8 ], 1		#this_89_8, 1
mov r8d, 1074261268		#REG_1074267627, 1074261268
mov dword ptr [rcx + 12 ], r8d		#this_89_12, REG_1074267627
jmp Return_Here_119		#Return_Here_119
Return_Here_119:
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
mov r8, rcx		#this_TMP_1724629941024, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1724629941024_0, 1
mov rbx, r8		#Address_84, this_TMP_1724629941024
mov rbx, rcx		#Address_84, this
mov rcx, rbx		#REG_Address_84_Parameter27506, Address_84
mov edx, 8		#REG_8_Parameter13030, 8
call _V19internal_deallocatePhx
Return_Here_114:
mov rcx, rbx		#REG_Address_84_Parameter16413, Address_84
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
mov r8, rcx		#this_TMP_1724629946208, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1724629946208_0, 1
mov rbx, r8		#Address_85, this_TMP_1724629946208
mov rbx, rcx		#Address_85, this
mov rcx, rbx		#REG_Address_85_Parameter29168, Address_85
mov edx, 8		#REG_8_Parameter900, 8
call _V19internal_deallocatePhx
Return_Here_115:
mov rcx, rbx		#REG_Address_85_Parameter32591, Address_85
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
mov r8, rcx		#this_TMP_1724629953984, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1724629953984_0, 1
mov rbx, r8		#Address_86, this_TMP_1724629953984
mov rbx, rcx		#Address_86, this
mov rcx, rbx		#REG_Address_86_Parameter18762, Address_86
mov edx, 8		#REG_8_Parameter1655, 8
call _V19internal_deallocatePhx
Return_Here_116:
mov rcx, rbx		#REG_Address_86_Parameter17410, Address_86
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
