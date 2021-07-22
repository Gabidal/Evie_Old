.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 6		#Return_Value88, 6
jmp Return_Here_122		#Return_Here_122
Return_Here_122:
mov r8d, ecx		#REG_Return_Value880, Return_Value88
mov r9, rdx		#REG_Return_Value880_REMAINDER32591, REMAINDER_18762
mov eax, 3		#3_QUOTIENT900, 3
mul r8d		#REG_Return_Value880
mov r8d, eax		#REG_Return_Value880, 3_QUOTIENT900
mov rdx, r9		#REMAINDER_18762, REG_Return_Value880_REMAINDER32591
mov r8d, r8d		#c, REG_Return_Value880
mov r9d, r8d		#REG_c1, c
xor edx, edx		#REG_c1_REMAINDER17410, REG_c1_REMAINDER17410
mov eax, r9d		#REG_c1_QUOTIENT1655, REG_c1
div ecx		#Return_Value88
mov r9d, eax		#REG_c1, REG_c1_QUOTIENT1655
mov ecx, r9d		#d, REG_c1
add ecx, 3		#d, 3
add ecx, 6		#d, 6
sub ecx, r8d		#d, c
mov eax, ecx		#Returning_REG2, d
ret 		#
mov ecx, 1065353216		#REG_1065359575, 1065353216
movd xmm0, ecx		#MEDIA_1065380840, REG_1065359575
movss xmm0, xmm0		#Return_Value89, MEDIA_1065380840
jmp Return_Here_123		#Return_Here_123
Return_Here_123:
cvttss2si ecx, xmm0		#REG_Return_Value893, Return_Value89
mov eax, ecx		#Returning_REG4, REG_Return_Value893
ret 		#
mov eax, -6		#Returning_REG5, -6
ret 		#
ret 		#


_Z4mainv:
mov ecx, 6		#Return_Value88_90, 6
jmp Return_Here_125		#Return_Here_125
Return_Here_125:
mov r8d, ecx		#REG_Return_Value88_900, Return_Value88_90
mov r9, rdx		#REG_Return_Value88_900_REMAINDER21548, REMAINDER_6483
mov eax, 3		#3_QUOTIENT20537, 3
mul r8d		#REG_Return_Value88_900
mov r8d, eax		#REG_Return_Value88_900, 3_QUOTIENT20537
mov rdx, r9		#REMAINDER_6483, REG_Return_Value88_900_REMAINDER21548
mov r8d, r8d		#c_90, REG_Return_Value88_900
mov r8d, r8d		#REG_c_901, c_90
xor edx, edx		#REG_c_901_REMAINDER4041, REG_c_901_REMAINDER4041
mov eax, r8d		#REG_c_901_QUOTIENT27595, REG_c_901
div ecx		#Return_Value88_90
mov r8d, eax		#REG_c_901, REG_c_901_QUOTIENT27595
mov ecx, r8d		#d_90, REG_c_901
jmp Return_Here_124		#Return_Here_124
mov ecx, 1065353216		#REG_1065356818, 1065353216
movd xmm0, ecx		#MEDIA_1065377566, REG_1065356818
movss xmm0, xmm0		#Return_Value89_90, MEDIA_1065377566
jmp Return_Here_126		#Return_Here_126
Return_Here_126:
jmp Return_Here_124		#Return_Here_124
jmp Return_Here_124		#Return_Here_124
Return_Here_124:
mov eax, 1		#Returning_REG2, 1
ret 		#
ret 		#


.section .data		#.data
