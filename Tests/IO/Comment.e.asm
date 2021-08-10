.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
push rbx		#rbx
sub rsp, 32		#.STACK, 32
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_1724621245280, a_REG0
add qword ptr [rcx + 0 ], 1		#a_TMP_1724621245280_0, 1
mov rbx, rcx		#this_80, a_TMP_1724621245280
mov dword ptr [rbx + 8 ], 1		#this_80_8, 1
mov dword ptr [rbx + 12 ], 0		#this_80_12, 0
mov ecx, dword ptr [rbx + 8 ]		#this_80_8_REG1, this_80_8
mov ecx, ecx		#Size_76_80, this_80_8_REG1
mov r8d, ecx		#REG_Size_76_802, Size_76_80
mov r9, rdx		#REG_Size_76_802_REMAINDER9758, REMAINDER_24221
mov eax, 4		#4_QUOTIENT32209, 4
mul r8d		#REG_Size_76_802
mov r8d, eax		#REG_Size_76_802, 4_QUOTIENT32209
mov rdx, r9		#REMAINDER_24221, REG_Size_76_802_REMAINDER9758
mov ecx, ecx		#REG_Size_76_803, Size_76_80
mov r8, rdx		#REG_Size_76_803_REMAINDER6422, REMAINDER_24946
mov eax, 4		#4_QUOTIENT18588, 4
mul ecx		#REG_Size_76_803
mov ecx, eax		#REG_Size_76_803, 4_QUOTIENT18588
mov rdx, r8		#REMAINDER_24946, REG_Size_76_803_REMAINDER6422
mov ecx, ecx		#REG_REG_Size_76_803_Parameter27753, REG_Size_76_803
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 24 ], rax		#.STACK_24, RetREG_4
jmp Return_Here_110		#Return_Here_110
Return_Here_110:
mov rcx, qword ptr [rsp + 24 ]		#REG_Return_Value76_805, .STACK_24
mov qword ptr [rbx + 16 ], rcx		#this_80_16, REG_Return_Value76_805
jmp Return_Here_109		#Return_Here_109
Return_Here_109:
mov ecx, 1		#Return_Value81, 1
jmp Return_Here_111		#Return_Here_111
Return_Here_111:
mov eax, ecx		#Returning_REG6, Return_Value81
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
if_31:
cmp rcx, 0		#this, 0
je if_31_END		#if_31_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_31_END		#if_31_END
mov r8, rcx		#this_TMP_1724621246144, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1724621246144_0, 1
mov rbx, r8		#Address_79, this_TMP_1724621246144
mov rbx, rcx		#Address_79, this
mov rcx, rbx		#REG_Address_79_Parameter10383, Address_79
mov edx, 8		#REG_8_Parameter14945, 8
call _V19internal_deallocatePhx
Return_Here_108:
mov rcx, rbx		#REG_Address_79_Parameter8909, Address_79
call _ZN13____List_int_10DestructorEP13____List_int_
if_31_END:
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
