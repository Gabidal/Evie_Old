.intel_syntax noprefix
.global _Z4mainv
.section .text		#.text
_Z4mainv:
push rdi		#rdi
push rbx		#rbx
sub rsp, 8		#.STACK, 8
mov rcx, rbx		#Characters_TMP_1261249192384, Characters
add qword ptr [rcx + 0 ], 1		#Characters_TMP_1261249192384_0, 1
mov rdi, rcx		#this_34, Characters_TMP_1261249192384
mov rdi, rbx		#this_34, Characters
mov dword ptr [rdi + 8 ], 1		#this_34_8, 1
mov dword ptr [rdi + 12 ], 0		#this_34_12, 0
mov ecx, dword ptr [rdi + 8 ]		#this_34_8_REG0, this_34_8
mov ecx, ecx		#Size_0_34, this_34_8_REG0
mov r8d, ecx		#REG_Size_0_341, Size_0_34
mov r9, rdx		#REG_Size_0_341_REMAINDER29358, REMAINDER_26962
mov eax, 1		#1_QUOTIENT11478, 1
mul r8d		#REG_Size_0_341
mov r8d, eax		#REG_Size_0_341, 1_QUOTIENT11478
mov rdx, r9		#REMAINDER_26962, REG_Size_0_341_REMAINDER29358
mov ecx, ecx		#REG_Size_0_342, Size_0_34
mov r8, rdx		#REG_Size_0_342_REMAINDER5705, REMAINDER_28145
mov eax, 1		#1_QUOTIENT24464, 1
mul ecx		#REG_Size_0_342
mov ecx, eax		#REG_Size_0_342, 1_QUOTIENT24464
mov rdx, r8		#REMAINDER_28145, REG_Size_0_342_REMAINDER5705
mov ecx, ecx		#REG_REG_Size_0_342_Parameter41, REG_Size_0_342
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 0 ], rax		#.STACK_0, RetREG_3
jmp Return_Here_44		#Return_Here_44
Return_Here_44:
mov rcx, qword ptr [rsp + 0 ]		#REG_Return_Value0_344, .STACK_0
mov qword ptr [rdi + 16 ], rcx		#this_34_16, REG_Return_Value0_344
jmp Return_Here_43		#Return_Here_43
Return_Here_43:
mov ecx, 0		#i_33, 0
mov r8, rbx		#Characters_TMP_1261249229120, Characters
add qword ptr [r8 + 0 ], 1		#Characters_TMP_1261249229120_0, 1
mov rdi, r8		#this_33, Characters_TMP_1261249229120
mov rdi, rbx		#this_33, Characters
if_0:
mov r8d, dword ptr [rdi + 12 ]		#this_33_12_REG5, this_33_12
cmp ecx, r8d		#i_33, this_33_12_REG5
jle if_0_END		#if_0_END
mov ch, 0		#Return_Value33, 0
jmp Return_Here_42		#Return_Here_42
if_0_END:
mov rcx, qword ptr [rdi + 16 ]		#this_33_16_REG6, this_33_16
mov cl, byte ptr [rcx + 0 * 1 ]		#this_33_16_REG6_REG7, *
mov ch, cl		#Return_Value33, this_33_16_REG6_REG7
jmp Return_Here_42		#Return_Here_42
Return_Here_42:
mov ch, 1		#Return_Value33, 1
mov rcx, rbx		#REG_Characters_Parameter18467, Characters
call _ZN14____List_char_10DestructorEP14____List_char_
mov rcx, rdi		#REG_this_33_Parameter6334, this_33
call _ZN14____List_char_10DestructorEP14____List_char_
mov ecx, 0		#i_35, 0
mov r8, rbx		#Characters_TMP_1261249220160, Characters
add qword ptr [r8 + 0 ], 1		#Characters_TMP_1261249220160_0, 1
mov r8, r8		#this_35, Characters_TMP_1261249220160
mov r8, rbx		#this_35, Characters
if_1:
mov r9d, dword ptr [r8 + 12 ]		#this_35_12_REG10, this_35_12
cmp ecx, r9d		#i_35, this_35_12_REG10
jle if_1_END		#if_1_END
mov ch, 0		#Return_Value35, 0
jmp Return_Here_45		#Return_Here_45
if_1_END:
mov rcx, qword ptr [r8 + 16 ]		#this_35_16_REG11, this_35_16
mov cl, byte ptr [rcx + 0 * 1 ]		#this_35_16_REG11_REG12, *
mov ch, cl		#Return_Value35, this_35_16_REG11_REG12
jmp Return_Here_45		#Return_Here_45
Return_Here_45:
mov eax, ch		#Returning_REG13, Return_Value35
add rsp, 8		#.STACK, 8
pop rbx		#rbx
pop rdi		#rdi
ret 		#
add rsp, 8		#.STACK, 8
pop rbx		#rbx
pop rdi		#rdi
ret 		#


_ZN14____List_char_10DestructorEP14____List_char_:
push rbx		#rbx
if_2:
cmp rcx, 0		#this, 0
je if_2_END		#if_2_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_2_END		#if_2_END
mov r8, rcx		#this_TMP_1261248995264, this
add qword ptr [r8 + 0 ], 1		#this_TMP_1261248995264_0, 1
mov rbx, r8		#Address_11, this_TMP_1261248995264
mov rbx, rcx		#Address_11, this
mov rcx, rbx		#REG_Address_11_Parameter26500, Address_11
mov edx, 8		#REG_8_Parameter19169, 8
call _V19internal_deallocatePhx
Return_Here_14:
mov rcx, rbx		#REG_Address_11_Parameter15724, Address_11
call _ZN14____List_char_10DestructorEP14____List_char_
if_2_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
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
