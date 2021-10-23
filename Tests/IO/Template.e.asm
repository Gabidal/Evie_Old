.intel_syntax noprefix
.file 1 "Tests/IO/Template.e"		#1 "Tests/IO/Template.e"
.file 2 "Tests/IO/../../STD/STD.e"		#2 "Tests/IO/../../STD/STD.e"
.file 3 "Tests/IO/../../STD/Types.e"		#3 "Tests/IO/../../STD/Types.e"
.file 4 "Tests/IO/../../STD/Memory.e"		#4 "Tests/IO/../../STD/Memory.e"
.file 5 "Tests/IO/../../STD/List.e"		#5 "Tests/IO/../../STD/List.e"
.file 6 "Tests/IO/../../STD/String.e"		#6 "Tests/IO/../../STD/String.e"
.file 7 "Tests/IO/../../STD/Console.e"		#7 "Tests/IO/../../STD/Console.e"
.file 8 "Tests/IO/../../STD/sys.e"		#8 "Tests/IO/../../STD/sys.e"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"		#9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"		#10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"		#11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 12 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"		#12 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 13 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"		#13 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 14 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"		#14 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 15 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"		#15 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 16 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"		#16 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 17 "Tests/IO/../../STD/Win/File.e"		#17 "Tests/IO/../../STD/Win/File.e"
Code_Start:
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv_START:
.loc 1 5 1		#1 5 1
_Z10Start_Testv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
.loc 1 10 11		#1 10 11
push r12		#r12
push rbp		#rbp
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 124		#.STACK, 124
.loc 1 6 2		#1 6 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_2242140518592, a_REG0
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2242140518592_0, 1
.loc 1 6 2		#1 6 2
mov qword ptr [rsp + 20 ], rcx		#.STACK_20, a_TMP_2242140518592
mov rcx, qword ptr [rsp + 20 ]		#this_143_REG1, .STACK_20
.loc 5 3 16		#5 3 16
mov dword ptr [rcx + 8 ], 1		#this_143_REG1_8, 1
mov rcx, qword ptr [rsp + 20 ]		#this_143_REG2, .STACK_20
.loc 5 4 12		#5 4 12
mov dword ptr [rcx + 12 ], 0		#this_143_REG2_12, 0
mov rcx, qword ptr [rsp + 20 ]		#this_143_REG3, .STACK_20
.loc 5 3 3		#5 3 3
mov ecx, dword ptr [rcx + 8 ]		#this_143_REG3_8_REG4, this_143_REG3_8
mov dword ptr [rsp + 36 ], ecx		#.STACK_36, this_143_REG3_8_REG4
.loc 4 2 34		#4 2 34
mov ecx, dword ptr [rsp + 36 ]		#REG_Size_110_1435, .STACK_36
mov r8, rdx		#REG_Size_110_1435_REMAINDER24393, REMAINDER_3548
mov eax, 4		#4_QUOTIENT31101, 4
mul ecx		#REG_Size_110_1435
mov ecx, eax		#REG_Size_110_1435, 4_QUOTIENT31101
mov rdx, r8		#REMAINDER_3548, REG_Size_110_1435_REMAINDER24393
mov ecx, dword ptr [rsp + 36 ]		#REG_Size_110_1436, .STACK_36
mov r8, rdx		#REG_Size_110_1436_REMAINDER12623, REMAINDER_24084
mov eax, 4		#4_QUOTIENT19629, 4
mul ecx		#REG_Size_110_1436
mov ecx, eax		#REG_Size_110_1436, 4_QUOTIENT19629
mov rdx, r8		#REMAINDER_24084, REG_Size_110_1436_REMAINDER12623
mov ecx, ecx		#REG_REG_Size_110_1436_Parameter24370, REG_Size_110_1436
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 28 ], rax		#.STACK_28, RetREG_7
jmp Return_Here_189		#Return_Here_189
.loc 5 5 17		#5 5 17
Return_Here_189:
mov rcx, qword ptr [rsp + 20 ]		#this_143_REG8, .STACK_20
mov r8, qword ptr [rsp + 28 ]		#REG_Return_Value110_1439, .STACK_28
mov qword ptr [rcx + 16 ], r8		#this_143_REG8_16, REG_Return_Value110_1439
jmp Return_Here_188		#Return_Here_188
.loc 1 6 14		#1 6 14
Return_Here_188:
.loc 1 7 2		#1 7 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG10, .STACK_0
mov rcx, rcx		#a_TMP_2242140558912, a_REG10
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2242140558912_0, 1
.loc 1 7 2		#1 7 2
mov qword ptr [rsp + 40 ], rcx		#.STACK_40, a_TMP_2242140558912
.loc 5 9 3		#5 9 3
if_17:
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG11, .STACK_40
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_144_REG11_12_REG12, this_144_REG11_12
mov r8, qword ptr [rsp + 40 ]		#this_144_REG13, .STACK_40
.loc 5 3 3		#5 3 3
mov r8d, dword ptr [r8 + 8 ]		#this_144_REG13_8_REG14, this_144_REG13_8
.loc 5 9 12		#5 9 12
cmp ecx, r8d		#this_144_REG11_12_REG12, this_144_REG13_8_REG14
jl if_17_END		#if_17_END
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG15, .STACK_40
mov r8, qword ptr [rsp + 40 ]		#this_144_REG16, .STACK_40
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_144_REG16_12_REG17, this_144_REG16_12
mov r9, rdx		#this_144_REG16_12_REG17_REMAINDER18756, REMAINDER_11840
mov eax, 2		#2_QUOTIENT19954, 2
mul r8d		#this_144_REG16_12_REG17
mov r8d, eax		#this_144_REG16_12_REG17, 2_QUOTIENT19954
mov rdx, r9		#REMAINDER_11840, this_144_REG16_12_REG17_REMAINDER18756
.loc 5 11 13		#5 11 13
mov dword ptr [rcx + 8 ], r8d		#this_144_REG15_8, this_144_REG16_12_REG17
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG18, .STACK_40
.loc 5 3 3		#5 3 3
mov ecx, dword ptr [rcx + 8 ]		#this_144_REG18_8_REG19, this_144_REG18_8
mov dword ptr [rsp + 76 ], ecx		#.STACK_76, this_144_REG18_8_REG19
.loc 4 2 34		#4 2 34
mov ecx, dword ptr [rsp + 76 ]		#REG_Size_11120, .STACK_76
mov r8, rdx		#REG_Size_11120_REMAINDER7376, REMAINDER_13931
mov eax, 4		#4_QUOTIENT4966, 4
mul ecx		#REG_Size_11120
mov ecx, eax		#REG_Size_11120, 4_QUOTIENT4966
mov rdx, r8		#REMAINDER_13931, REG_Size_11120_REMAINDER7376
mov ecx, dword ptr [rsp + 76 ]		#REG_Size_11121, .STACK_76
mov r8, rdx		#REG_Size_11121_REMAINDER16944, REMAINDER_32439
mov eax, 4		#4_QUOTIENT26308, 4
mul ecx		#REG_Size_11121
mov ecx, eax		#REG_Size_11121, 4_QUOTIENT26308
mov rdx, r8		#REMAINDER_32439, REG_Size_11121_REMAINDER16944
mov ecx, ecx		#REG_REG_Size_11121_Parameter15350, REG_Size_11121
call _V17internal_allocatex_rPh
mov rbx, rax		#Return_Value111, RetREG_22
jmp Return_Here_191		#Return_Here_191
.loc 5 12 16		#5 12 16
Return_Here_191:
mov rdi, rbx		#tmp, Return_Value111
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG23, .STACK_40
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_144_REG23_12_REG24, this_144_REG23_12
mov dword ptr [rsp + 96 ], ecx		#.STACK_96, this_144_REG23_12_REG24
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG25, .STACK_40
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_144_REG25_16_REG26, this_144_REG25_16
mov qword ptr [rsp + 88 ], rcx		#.STACK_88, this_144_REG25_16_REG26
.loc 5 14 14		#5 14 14
mov qword ptr [rsp + 80 ], rdi		#.STACK_80, tmp
.loc 4 26 18		#4 26 18
mov esi, 0		#i, 0
cmp esi, dword ptr [rsp + 96 ]		#i, .STACK_96
jge while_18_END		#while_18_END
while_18:
mov rbp, qword ptr [rsp + 80 ]		#dest_112_UnLoaded, .STACK_80
.loc 4 27 9		#4 27 9
lea rcx, qword ptr [rbp + rsi * 4 ]		#dest_112_UnLoaded_REG27, *
mov r12, qword ptr [rsp + 88 ]		#source_112_UnLoaded, .STACK_88
mov r8d, dword ptr [r12 + rsi * 4 ]		#source_112_UnLoaded_REG28, *
mov dword ptr [rcx ], r8d		#dest_112_UnLoaded_REG27, source_112_UnLoaded_REG28
.loc 4 26 34		#4 26 34
add esi, 1		#i, 1
cmp esi, dword ptr [rsp + 96 ]		#i, .STACK_96
jge while_18_END		#while_18_END
jmp while_18		#while_18
while_18_END:
jmp Return_Here_192		#Return_Here_192
.loc 5 14 4		#5 14 4
Return_Here_192:
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG29, .STACK_40
.loc 5 18 10		#5 18 10
mov qword ptr [rcx + 16 ], rdi		#this_144_REG29_16, tmp
.loc 5 9 3		#5 9 3
if_17_END:
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG30, .STACK_40
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_144_REG30_16_REG31, this_144_REG30_16
mov r8, qword ptr [rsp + 40 ]		#this_144_REG33, .STACK_40
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_144_REG33_12_REG34, this_144_REG33_12
.loc 5 20 3		#5 20 3
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_144_REG30_16_REG31_REG32, *
mov dword ptr [rcx ], 5		#this_144_REG30_16_REG31_REG32, 5
mov rcx, qword ptr [rsp + 40 ]		#this_144_REG35, .STACK_40
.loc 5 21 7		#5 21 7
add dword ptr [rcx + 12 ], 1		#this_144_REG35_12, 1
.loc 1 7 4		#1 7 4
Return_Here_190:
.loc 1 8 2		#1 8 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_2242140569664, a_REG36
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2242140569664_0, 1
.loc 1 8 2		#1 8 2
mov qword ptr [rsp + 48 ], rcx		#.STACK_48, a_TMP_2242140569664
.loc 5 9 3		#5 9 3
if_19:
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG37, .STACK_48
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_145_REG37_12_REG38, this_145_REG37_12
mov r8, qword ptr [rsp + 48 ]		#this_145_REG39, .STACK_48
.loc 5 3 3		#5 3 3
mov r8d, dword ptr [r8 + 8 ]		#this_145_REG39_8_REG40, this_145_REG39_8
.loc 5 9 12		#5 9 12
cmp ecx, r8d		#this_145_REG37_12_REG38, this_145_REG39_8_REG40
jl if_19_END		#if_19_END
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG41, .STACK_48
mov r8, qword ptr [rsp + 48 ]		#this_145_REG42, .STACK_48
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_145_REG42_12_REG43, this_145_REG42_12
mov r9, rdx		#this_145_REG42_12_REG43_REMAINDER11323, REMAINDER_5537
mov eax, 2		#2_QUOTIENT24626, 2
mul r8d		#this_145_REG42_12_REG43
mov r8d, eax		#this_145_REG42_12_REG43, 2_QUOTIENT24626
mov rdx, r9		#REMAINDER_5537, this_145_REG42_12_REG43_REMAINDER11323
.loc 5 11 13		#5 11 13
mov dword ptr [rcx + 8 ], r8d		#this_145_REG41_8, this_145_REG42_12_REG43
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG44, .STACK_48
.loc 5 3 3		#5 3 3
mov ecx, dword ptr [rcx + 8 ]		#this_145_REG44_8_REG45, this_145_REG44_8
mov dword ptr [rsp + 100 ], ecx		#.STACK_100, this_145_REG44_8_REG45
.loc 4 2 34		#4 2 34
mov ecx, dword ptr [rsp + 100 ]		#REG_Size_11146, .STACK_100
mov r8, rdx		#REG_Size_11146_REMAINDER16118, REMAINDER_2082
mov eax, 4		#4_QUOTIENT21538, 4
mul ecx		#REG_Size_11146
mov ecx, eax		#REG_Size_11146, 4_QUOTIENT21538
mov rdx, r8		#REMAINDER_2082, REG_Size_11146_REMAINDER16118
mov ecx, dword ptr [rsp + 100 ]		#REG_Size_11147, .STACK_100
mov r8, rdx		#REG_Size_11147_REMAINDER16541, REMAINDER_4833
mov eax, 4		#4_QUOTIENT22929, 4
mul ecx		#REG_Size_11147
mov ecx, eax		#REG_Size_11147, 4_QUOTIENT22929
mov rdx, r8		#REMAINDER_4833, REG_Size_11147_REMAINDER16541
mov ecx, ecx		#REG_REG_Size_11147_Parameter15006, REG_Size_11147
call _V17internal_allocatex_rPh
mov rbx, rax		#Return_Value111, RetREG_48
jmp Return_Here_194		#Return_Here_194
.loc 5 12 16		#5 12 16
Return_Here_194:
mov rdi, rbx		#tmp, Return_Value111
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG49, .STACK_48
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_145_REG49_12_REG50, this_145_REG49_12
mov dword ptr [rsp + 120 ], ecx		#.STACK_120, this_145_REG49_12_REG50
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG51, .STACK_48
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_145_REG51_16_REG52, this_145_REG51_16
mov qword ptr [rsp + 112 ], rcx		#.STACK_112, this_145_REG51_16_REG52
.loc 5 14 14		#5 14 14
mov qword ptr [rsp + 104 ], rdi		#.STACK_104, tmp
.loc 4 26 18		#4 26 18
mov esi, 0		#i, 0
cmp esi, dword ptr [rsp + 120 ]		#i, .STACK_120
jge while_20_END		#while_20_END
while_20:
mov rbp, qword ptr [rsp + 104 ]		#dest_112_UnLoaded, .STACK_104
.loc 4 27 9		#4 27 9
lea rcx, qword ptr [rbp + rsi * 4 ]		#dest_112_UnLoaded_REG53, *
mov r12, qword ptr [rsp + 112 ]		#source_112_UnLoaded, .STACK_112
mov r8d, dword ptr [r12 + rsi * 4 ]		#source_112_UnLoaded_REG54, *
mov dword ptr [rcx ], r8d		#dest_112_UnLoaded_REG53, source_112_UnLoaded_REG54
.loc 4 26 34		#4 26 34
add esi, 1		#i, 1
cmp esi, dword ptr [rsp + 120 ]		#i, .STACK_120
jge while_20_END		#while_20_END
jmp while_20		#while_20
while_20_END:
jmp Return_Here_195		#Return_Here_195
.loc 5 14 4		#5 14 4
Return_Here_195:
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG55, .STACK_48
.loc 5 18 10		#5 18 10
mov qword ptr [rcx + 16 ], rdi		#this_145_REG55_16, tmp
.loc 5 9 3		#5 9 3
if_19_END:
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG56, .STACK_48
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_145_REG56_16_REG57, this_145_REG56_16
mov r8, qword ptr [rsp + 48 ]		#this_145_REG59, .STACK_48
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_145_REG59_12_REG60, this_145_REG59_12
.loc 5 20 3		#5 20 3
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_145_REG56_16_REG57_REG58, *
mov dword ptr [rcx ], 2		#this_145_REG56_16_REG57_REG58, 2
mov rcx, qword ptr [rsp + 48 ]		#this_145_REG61, .STACK_48
.loc 5 21 7		#5 21 7
add dword ptr [rcx + 12 ], 1		#this_145_REG61_12, 1
.loc 1 8 4		#1 8 4
Return_Here_193:
.loc 1 9 2		#1 9 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG62, .STACK_0
mov rcx, rcx		#a_TMP_2242140581312, a_REG62
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2242140581312_0, 1
.loc 1 9 2		#1 9 2
mov qword ptr [rsp + 56 ], rcx		#.STACK_56, a_TMP_2242140581312
mov rcx, qword ptr [rsp + 56 ]		#this_146_REG63, .STACK_56
.loc 5 25 7		#5 25 7
sub dword ptr [rcx + 12 ], 1		#this_146_REG63_12, 1
.loc 1 9 4		#1 9 4
Return_Here_196:
.loc 1 10 14		#1 10 14
mov dword ptr [rsp + 64 ], 0		#.STACK_64, 0
lea rcx, qword ptr [rsp + 0 ]		#a_REG64, .STACK_0
mov rcx, rcx		#a_TMP_2242140603712, a_REG64
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2242140603712_0, 1
.loc 1 10 9		#1 10 9
mov qword ptr [rsp + 68 ], rcx		#.STACK_68, a_TMP_2242140603712
.loc 5 29 3		#5 29 3
if_21:
mov rcx, qword ptr [rsp + 68 ]		#this_147_REG65, .STACK_68
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_147_REG65_12_REG66, this_147_REG65_12
.loc 5 29 9		#5 29 9
cmp dword ptr [rsp + 64 ], ecx		#.STACK_64, this_147_REG65_12_REG66
jle if_21_END		#if_21_END
.loc 5 30 4		#5 30 4
mov ecx, 0		#Return_Value147, 0
jmp Return_Here_197		#Return_Here_197
.loc 5 29 3		#5 29 3
if_21_END:
mov r8, qword ptr [rsp + 68 ]		#this_147_REG67, .STACK_68
.loc 5 5 3		#5 5 3
mov r8, qword ptr [r8 + 16 ]		#this_147_REG67_16_REG68, this_147_REG67_16
.loc 5 32 10		#5 32 10
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_147_REG67_16_REG68_REG69, *
mov ecx, r8d		#Return_Value147, this_147_REG67_16_REG68_REG69
jmp Return_Here_197		#Return_Here_197
.loc 1 10 11		#1 10 11
Return_Here_197:
mov eax, ecx		#Returning_REG70, Return_Value147
add rsp, 124		#.STACK, 124
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
ret 		#
add rsp, 124		#.STACK, 124
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
ret 		#
_Z10Start_Testv_END:


.cfi_endproc 		#
_Z4mainv_START:
.loc 1 13 1		#1 13 1
_Z4mainv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
jmp _Z10Start_Testv		#_Z10Start_Testv
.loc 1 15 2		#1 15 2
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#
_Z4mainv_END:


.cfi_endproc 		#
Code_End:
.section .data		#.data
std_MAX_CONSOLE_BUFFER_LENGHT:
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
.section .debug_abbrev		#.debug_abbrev
debug_abbrev:
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 37		#37
.byte 14		#14
.byte 19		#19
.byte 5		#5
.byte 3		#3
.byte 14		#14
.byte 16		#16
.byte 23		#23
.byte 27		#27
.byte 14		#14
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 0		#0
.byte 0		#0
.byte 2		#2
.byte 36		#36
.byte 0		#0
.byte 3		#3
.byte 8		#8
.byte 62		#62
.byte 11		#11
.byte 11		#11
.byte 7		#7
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 3		#3
.byte 52		#52
.byte 0		#0
.byte 56		#56
.byte 5		#5
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 4		#4
.byte 2		#2
.byte 1		#1
.byte 54		#54
.byte 11		#11
.byte 3		#3
.byte 8		#8
.byte 11		#11
.byte 7		#7
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 5		#5
.byte 46		#46
.byte 0		#0
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 6		#6
.byte 46		#46
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 7		#7
.byte 46		#46
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 8		#8
.byte 46		#46
.byte 1		#1
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 110		#110
.byte 8		#8
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 63		#63
.byte 25		#25
.byte 0		#0
.byte 0		#0
.byte 9		#9
.byte 52		#52
.byte 0		#0
.byte 2		#2
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 10		#10
.byte 46		#46
.byte 0		#0
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 110		#110
.byte 8		#8
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 63		#63
.byte 25		#25
.byte 0		#0
.byte 0		#0
.byte 11		#11
.byte 5		#5
.byte 0		#0
.byte 2		#2
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 12		#12
.byte 2		#2
.byte 0		#0
.byte 54		#54
.byte 11		#11
.byte 3		#3
.byte 8		#8
.byte 11		#11
.byte 7		#7
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 0		#0
.byte 0		#0
.byte 13		#13
.byte 46		#46
.byte 0		#0
.byte 17		#17
.byte 1		#1
.byte 18		#18
.byte 6		#6
.byte 64		#64
.byte 24		#24
.byte 3		#3
.byte 8		#8
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
.byte 73		#73
.byte 19		#19
.byte 0		#0
.byte 0		#0
.byte 0		#0
.section .debug_info		#.debug_info
Debug_Info_Start:
.long Debug_Info_End-Debug_Info		#Debug_Info_End-Debug_Info
Debug_Info:
.word 4		#4
.secrel32 debug_abbrev		#debug_abbrev
.byte 8		#8
.byte 1		#1
.secrel32 .COMPILER_NAME		#.COMPILER_NAME
.word 0x29A		#0x29A
.secrel32 .FILE_NAME		#.FILE_NAME
.secrel32 .LINE_TABLE		#.LINE_TABLE
.secrel32 .DIRECTORY		#.DIRECTORY
.quad Code_Start		#Code_Start
.quad Code_End		#Code_End
_char_START:
.byte 2		#2
.asciz "char"		#char
.byte 6		#6
.quad 0		#0
.byte 3		#3
.byte 1		#1
_bool_START:
.byte 2		#2
.asciz "bool"		#bool
.byte 6		#6
.quad 0		#0
.byte 3		#3
.byte 5		#5
_short_START:
.byte 2		#2
.asciz "short"		#short
.byte 5		#5
.quad 0		#0
.byte 3		#3
.byte 9		#9
_int_START:
.byte 2		#2
.asciz "int"		#int
.byte 5		#5
.quad 0		#0
.byte 3		#3
.byte 13		#13
_long_START:
.byte 2		#2
.asciz "long"		#long
.byte 5		#5
.quad 0		#0
.byte 3		#3
.byte 17		#17
_float_START:
.byte 2		#2
.asciz "float"		#float
.byte 4		#4
.quad 0		#0
.byte 3		#3
.byte 21		#21
_double_START:
.byte 2		#2
.asciz "double"		#double
.byte 4		#4
.quad 0		#0
.byte 3		#3
.byte 26		#26
_3std_START:
.byte 4		#4
.byte 1		#1
.asciz "std"		#std
.quad 0		#0
.byte 5		#5
.byte 1		#1
_6string_START:
.byte 4		#4
.byte 1		#1
.asciz "string"		#string
.quad 0		#0
.byte 6		#6
.byte 2		#2
.byte 3		#3
.word 0		#0
.asciz "Characters"		#Characters
.byte 6		#6
.byte 3		#3
.long _14____List_char__START-Debug_Info_Start		#_14____List_char__START-Debug_Info_Start
.byte 0		#0
_14____List_char__START:
.byte 4		#4
.byte 1		#1
.asciz "____List_char_"		#____List_char_
.quad 0		#0
.byte 5		#5
.byte 2		#2
.byte 3		#3
.word 0		#0
.asciz "Capacity"		#Capacity
.byte 5		#5
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Size"		#Size
.byte 5		#5
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "Array"		#Array
.byte 5		#5
.byte 5		#5
.long _char_START-Debug_Info_Start		#_char_START-Debug_Info_Start
.byte 0		#0
.byte 3		#3
.word 0		#0
.asciz "MAX_CONSOLE_BUFFER_LENGHT"		#MAX_CONSOLE_BUFFER_LENGHT
.byte 7		#7
.byte 3		#3
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "GENERIC_WRITE"		#GENERIC_WRITE
.byte 17		#17
.byte 2		#2
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "GENERIC_READ"		#GENERIC_READ
.byte 17		#17
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_NONE"		#FILE_SHARE_NONE
.byte 17		#17
.byte 5		#5
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_READ"		#FILE_SHARE_READ
.byte 17		#17
.byte 6		#6
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_WRITE"		#FILE_SHARE_WRITE
.byte 17		#17
.byte 7		#7
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_SHARE_DELETE"		#FILE_SHARE_DELETE
.byte 17		#17
.byte 8		#8
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "CREATE_NEW"		#CREATE_NEW
.byte 17		#17
.byte 10		#10
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "CREATE_ALWAYS"		#CREATE_ALWAYS
.byte 17		#17
.byte 11		#11
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "OPEN_EXISTING"		#OPEN_EXISTING
.byte 17		#17
.byte 12		#12
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "OPEN_ALWAYS"		#OPEN_ALWAYS
.byte 17		#17
.byte 13		#13
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "TRUNCATE_EXISTING"		#TRUNCATE_EXISTING
.byte 17		#17
.byte 14		#14
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_ATTRIBUTE_NORMAL"		#FILE_ATTRIBUTE_NORMAL
.byte 17		#17
.byte 16		#16
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "FILE_ATTRIBUTE_FOLDER"		#FILE_ATTRIBUTE_FOLDER
.byte 17		#17
.byte 17		#17
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "MAXIMUM_PATH_LENGTH"		#MAXIMUM_PATH_LENGTH
.byte 17		#17
.byte 19		#19
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "ERROR_INSUFFICIENT_BUFFER"		#ERROR_INSUFFICIENT_BUFFER
.byte 17		#17
.byte 21		#21
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "MINIMUM_PROCESS_FILENAME_LENGTH"		#MINIMUM_PROCESS_FILENAME_LENGTH
.byte 17		#17
.byte 22		#22
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
_Char_260_START:
.byte 2		#2
.asciz "Char_260"		#Char_260
.byte 5		#5
.quad 0		#0
.byte 17		#17
.byte 41		#41
_Char_14_START:
.byte 2		#2
.asciz "Char_14"		#Char_14
.byte 5		#5
.quad 0		#0
.byte 17		#17
.byte 45		#45
_12FileIterator_START:
.byte 4		#4
.byte 1		#1
.asciz "FileIterator"		#FileIterator
.quad 0		#0
.byte 17		#17
.byte 49		#49
.byte 3		#3
.word 0		#0
.asciz "attributes"		#attributes
.byte 17		#17
.byte 50		#50
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "creation_time"		#creation_time
.byte 17		#17
.byte 51		#51
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "last_access_time"		#last_access_time
.byte 17		#17
.byte 52		#52
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "last_write_time"		#last_write_time
.byte 17		#17
.byte 53		#53
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "file_size"		#file_size
.byte 17		#17
.byte 54		#54
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "reserved"		#reserved
.byte 17		#17
.byte 55		#55
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "filename"		#filename
.byte 17		#17
.byte 56		#56
.long _Char_260_START-Debug_Info_Start		#_Char_260_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "alternate_filename"		#alternate_filename
.byte 17		#17
.byte 57		#57
.long _Char_14_START-Debug_Info_Start		#_Char_14_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "file_type"		#file_type
.byte 17		#17
.byte 58		#58
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "creator_type"		#creator_type
.byte 17		#17
.byte 59		#59
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 0		#0
.asciz "finder_flags"		#finder_flags
.byte 17		#17
.byte 60		#60
.long _short_START-Debug_Info_Start		#_short_START-Debug_Info_Start
.byte 0		#0
.byte 0		#0
.byte 8		#8
.quad _Z10Start_Testv_START		#_Z10Start_Testv_START
.quad _Z10Start_Testv_END		#_Z10Start_Testv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z10Start_Testv"		#_Z10Start_Testv
.asciz "Start_Test"		#Start_Test
.byte 1		#1
.byte 5		#5
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a"		#a
.byte 1		#1
.byte 6		#6
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 20		#20
.asciz "this_143"		#this_143
.byte 5		#5
.byte 2		#2
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 28		#28
.asciz "Return_Value110_143"		#Return_Value110_143
.byte 5		#5
.byte 5		#5
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 36		#36
.asciz "Size_110_143"		#Size_110_143
.byte 4		#4
.byte 1		#1
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "this_144"		#this_144
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 48		#48
.asciz "this_145"		#this_145
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 56		#56
.asciz "this_146"		#this_146
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value147"		#Return_Value147
.byte 1		#1
.byte 10		#10
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 64		#64
.asciz "i_147"		#i_147
.byte 5		#5
.byte 28		#28
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 68		#68
.asciz "this_147"		#this_147
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2242140518592"		#a_TMP_2242140518592
.byte 1		#1
.byte 6		#6
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2242140558912"		#a_TMP_2242140558912
.byte 1		#1
.byte 7		#7
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2242140569664"		#a_TMP_2242140569664
.byte 1		#1
.byte 8		#8
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2242140581312"		#a_TMP_2242140581312
.byte 1		#1
.byte 9		#9
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2242140603712"		#a_TMP_2242140603712
.byte 1		#1
.byte 10		#10
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 0		#0
.byte 10		#10
.quad _Z4mainv_START		#_Z4mainv_START
.quad _Z4mainv_END		#_Z4mainv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z4mainv"		#_Z4mainv
.asciz "main"		#main
.byte 1		#1
.byte 13		#13
_13____List_int__START:
.byte 4		#4
.byte 1		#1
.asciz "____List_int_"		#____List_int_
.quad 0		#0
.byte 5		#5
.byte 2		#2
.byte 3		#3
.word 0		#0
.asciz "Reference_Count"		#Reference_Count
.byte 5		#5
.byte 2		#2
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 8		#8
.asciz "Capacity"		#Capacity
.byte 5		#5
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 12		#12
.asciz "Size"		#Size
.byte 5		#5
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 12		#12
.asciz "Array"		#Array
.byte 5		#5
.byte 5		#5
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
_26____VIRTUAL_CLASS_char_ptr_START:
.byte 12		#12
.byte 1		#1
.asciz "____VIRTUAL_CLASS_char_ptr"		#____VIRTUAL_CLASS_char_ptr
.quad 0		#0
.byte 4		#4
.byte 2		#2
_25____VIRTUAL_CLASS_int_ptr_START:
.byte 12		#12
.byte 1		#1
.asciz "____VIRTUAL_CLASS_int_ptr"		#____VIRTUAL_CLASS_int_ptr
.quad 0		#0
.byte 4		#4
.byte 2		#2
_func_START:
.byte 2		#2
.asciz "func"		#func
.byte 5		#5
.quad 0		#0
.byte 1		#1
.byte 1		#1
.byte 0		#0
Debug_Info_End:
.section .debug_str		#.debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"		#Evie engine 3.0.0 https://github.com/Gabidal/Evie
.FILE_NAME:
.asciz "Tests/IO/Template.e"		#Tests/IO/Template.e
.DIRECTORY:
.asciz "Tests/IO/"		#Tests/IO/
.section .LINE_TABLE		#.LINE_TABLE
.LINE_TABLE:
