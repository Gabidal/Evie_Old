.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
mov ecx, 6		#Return_Value94, 6
jmp Return_Here_131		#Return_Here_131
Return_Here_131:
mov r8d, ecx		#REG_Return_Value940, Return_Value94
mov r9, rdx		#REG_Return_Value940_REMAINDER21548, REMAINDER_6483
mov eax, 3		#3_QUOTIENT20537, 3
mul r8d		#REG_Return_Value940
mov r8d, eax		#REG_Return_Value940, 3_QUOTIENT20537
mov rdx, r9		#REMAINDER_6483, REG_Return_Value940_REMAINDER21548
mov r8d, r8d		#c, REG_Return_Value940
mov r9d, r8d		#REG_c1, c
xor edx, edx		#REG_c1_REMAINDER4041, REG_c1_REMAINDER4041
mov eax, r9d		#REG_c1_QUOTIENT27595, REG_c1
div ecx		#Return_Value94
mov r9d, eax		#REG_c1, REG_c1_QUOTIENT27595
mov ecx, r9d		#d, REG_c1
add ecx, 3		#d, 3
add ecx, 6		#d, 6
sub ecx, r8d		#d, c
mov eax, ecx		#Returning_REG2, d
ret 		#
mov ecx, 1065353216		#REG_1065356818, 1065353216
movd xmm0, ecx		#MEDIA_1065377566, REG_1065356818
movss xmm0, xmm0		#Return_Value95, MEDIA_1065377566
jmp Return_Here_132		#Return_Here_132
Return_Here_132:
cvttss2si ecx, xmm0		#REG_Return_Value953, Return_Value95
mov eax, ecx		#Returning_REG4, REG_Return_Value953
ret 		#
mov eax, -6		#Returning_REG5, -6
ret 		#
ret 		#


_Z4mainv:
mov ecx, 6		#Return_Value94_96, 6
jmp Return_Here_134		#Return_Here_134
Return_Here_134:
mov r8d, ecx		#REG_Return_Value94_960, Return_Value94_96
mov r9, rdx		#REG_Return_Value94_960_REMAINDER30836, REMAINDER_9374
mov eax, 3		#3_QUOTIENT10291, 3
mul r8d		#REG_Return_Value94_960
mov r8d, eax		#REG_Return_Value94_960, 3_QUOTIENT10291
mov rdx, r9		#REMAINDER_9374, REG_Return_Value94_960_REMAINDER30836
mov r8d, r8d		#c_96, REG_Return_Value94_960
mov r8d, r8d		#REG_c_961, c_96
xor edx, edx		#REG_c_961_REMAINDER4596, REG_c_961_REMAINDER4596
mov eax, r8d		#REG_c_961_QUOTIENT11020, REG_c_961
div ecx		#Return_Value94_96
mov r8d, eax		#REG_c_961, REG_c_961_QUOTIENT11020
mov ecx, r8d		#d_96, REG_c_961
jmp Return_Here_133		#Return_Here_133
mov ecx, 1065353216		#REG_1065377237, 1065353216
movd xmm0, ecx		#MEDIA_1065380564, REG_1065377237
movss xmm0, xmm0		#Return_Value95_96, MEDIA_1065380564
jmp Return_Here_135		#Return_Here_135
Return_Here_135:
jmp Return_Here_133		#Return_Here_133
jmp Return_Here_133		#Return_Here_133
Return_Here_133:
mov eax, 1		#Returning_REG2, 1
ret 		#
ret 		#


.section .data		#.data
