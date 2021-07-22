.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 16		#.STACK, 16
mov ecx, 10		#Size_86, 10
mov r8d, ecx		#REG_Size_860, Size_86
mov r9, rdx		#REG_Size_860_REMAINDER24946, REMAINDER_27506
mov eax, 4		#4_QUOTIENT6422, 4
mul r8d		#REG_Size_860
mov r8d, eax		#REG_Size_860, 4_QUOTIENT6422
mov rdx, r9		#REMAINDER_27506, REG_Size_860_REMAINDER24946
mov ecx, ecx		#REG_Size_861, Size_86
mov r8, rdx		#REG_Size_861_REMAINDER16413, REMAINDER_29168
mov eax, 4		#4_QUOTIENT13030, 4
mul ecx		#REG_Size_861
mov ecx, eax		#REG_Size_861, 4_QUOTIENT13030
mov rdx, r8		#REMAINDER_29168, REG_Size_861_REMAINDER16413
mov ecx, ecx		#REG_REG_Size_861_Parameter18588, REG_Size_861
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 8 ], rax		#.STACK_8, RetREG_2
jmp Return_Here_120		#Return_Here_120
Return_Here_120:
mov rcx, qword ptr [rsp + 8 ]		#REG_Return_Value863, .STACK_8
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_Return_Value863
lea rcx, qword ptr [rsp + 0 ]		#a_REG4, .STACK_0
mov rcx, rcx		#b, a_REG4
mov r8, qword ptr [rcx + 0 * 8 ]		#b_REG5, *
lea r8, qword ptr [r8 + 1 * 4 ]		#b_REG5_REG6, *
mov dword ptr [r8 ], 1		#b_REG5_REG6, 1
mov rcx, qword ptr [rcx + 0 * 8 ]		#b_REG7, *
mov ecx, dword ptr [rcx + 1 * 4 ]		#b_REG7_REG8, *
mov ecx, ecx		#c, b_REG7_REG8
mov eax, ecx		#Returning_REG9, c
add rsp, 16		#.STACK, 16
ret 		#
add rsp, 16		#.STACK, 16
ret 		#


_Z4mainv:
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


.section .data		#.data
