.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_REG0, .STACK_0
mov rcx, rcx		#x_TMP_2097116288368, x_REG0
add qword ptr [rcx + 0 ], 1		#x_TMP_2097116288368_0, 1
mov rcx, rcx		#this_76, x_TMP_2097116288368
mov r8, rcx		#this_76_TMP_2097116302192, this_76
add qword ptr [r8 + 0 ], 1		#this_76_TMP_2097116302192_0, 1
mov r8, r8		#this_75_76, this_76_TMP_2097116302192
mov r8, rcx		#this_75_76, this_76
mov dword ptr [r8 + 8 ], 4		#this_75_76_8, 4
Return_Here_106:
mov dword ptr [rcx + 12 ], 1		#this_76_12, 1
mov dword ptr [rcx + 16 ], 2		#this_76_16, 2
mov dword ptr [rcx + 20 ], 6		#this_76_20, 6
mov dword ptr [rcx + 8 ], 5		#this_76_8, 5
jmp Return_Here_105		#Return_Here_105
Return_Here_105:
lea rcx, qword ptr [rsp + 0 ]		#x_REG1, .STACK_0
mov rcx, rcx		#x_TMP_2097116309968, x_REG1
add qword ptr [rcx + 0 ], 1		#x_TMP_2097116309968_0, 1
mov rcx, rcx		#f_77, x_TMP_2097116309968
mov r8, rcx		#f_77_TMP_2097116314288, f_77
add qword ptr [r8 + 0 ], 1		#f_77_TMP_2097116314288_0, 1
mov r8, r8		#b_74_77, f_77_TMP_2097116314288
mov r8, rcx		#b_74_77, f_77
jmp Return_Here_108		#Return_Here_108
Return_Here_108:
mov ecx, dword ptr [r8 + 12 ]		#b_74_77_12_REG2, b_74_77_12
mov ecx, ecx		#Return_Value77, b_74_77_12_REG2
jmp Return_Here_107		#Return_Here_107
Return_Here_107:
mov eax, ecx		#Returning_REG3, Return_Value77
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_Z4mainv:
sub rsp, 24		#.STACK, 24
lea rcx, qword ptr [rsp + 0 ]		#x_78_REG0, .STACK_0
mov rcx, rcx		#x_78_TMP_2097116359216, x_78_REG0
add qword ptr [rcx + 0 ], 1		#x_78_TMP_2097116359216_0, 1
mov rcx, rcx		#this_76_78, x_78_TMP_2097116359216
mov r8, rcx		#this_76_78_TMP_2097116336752, this_76_78
add qword ptr [r8 + 0 ], 1		#this_76_78_TMP_2097116336752_0, 1
mov r8, r8		#this_75_76_78, this_76_78_TMP_2097116336752
mov r8, rcx		#this_75_76_78, this_76_78
mov dword ptr [r8 + 8 ], 4		#this_75_76_78_8, 4
Return_Here_110:
mov dword ptr [rcx + 12 ], 1		#this_76_78_12, 1
mov dword ptr [rcx + 16 ], 2		#this_76_78_16, 2
mov dword ptr [rcx + 20 ], 6		#this_76_78_20, 6
mov dword ptr [rcx + 8 ], 5		#this_76_78_8, 5
jmp Return_Here_111		#Return_Here_111
Return_Here_111:
lea rcx, qword ptr [rsp + 0 ]		#x_78_REG1, .STACK_0
mov rcx, rcx		#x_78_TMP_2097116329840, x_78_REG1
add qword ptr [rcx + 0 ], 1		#x_78_TMP_2097116329840_0, 1
mov rcx, rcx		#f_77_78, x_78_TMP_2097116329840
mov r8, rcx		#f_77_78_TMP_2097116364400, f_77_78
add qword ptr [r8 + 0 ], 1		#f_77_78_TMP_2097116364400_0, 1
mov r8, r8		#b_74_77_78, f_77_78_TMP_2097116364400
mov r8, rcx		#b_74_77_78, f_77_78
jmp Return_Here_112		#Return_Here_112
Return_Here_112:
mov ecx, dword ptr [r8 + 12 ]		#b_74_77_78_12_REG2, b_74_77_78_12
mov ecx, ecx		#Return_Value77_78, b_74_77_78_12_REG2
jmp Return_Here_113		#Return_Here_113
Return_Here_113:
jmp Return_Here_109		#Return_Here_109
Return_Here_109:
mov eax, 1		#Returning_REG3, 1
add rsp, 24		#.STACK, 24
ret 		#
add rsp, 24		#.STACK, 24
ret 		#


_ZN6Banana10DestructorEP6Banana:
push rbx		#rbx
if_30:
cmp rcx, 0		#this, 0
je if_30_END		#if_30_END
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
sub r8, 1		#this_0_REG0, 1
cmp r8, 1		#this_0_REG0, 1
jge if_30_END		#if_30_END
mov r8, rcx		#this_TMP_2097116370448, this
add qword ptr [r8 + 0 ], 1		#this_TMP_2097116370448_0, 1
mov rbx, r8		#Address_73, this_TMP_2097116370448
mov rbx, rcx		#Address_73, this
mov rcx, rbx		#REG_Address_73_Parameter10383, Address_73
mov edx, r8d		#REG_size_Parameter14945, size
call _V19internal_deallocatePhx
Return_Here_102:
mov rcx, rbx		#REG_Address_73_Parameter8909, Address_73
call _ZN6Banana10DestructorEP6Banana
if_30_END:
pop rbx		#rbx
ret 		#


.section .data		#.data
