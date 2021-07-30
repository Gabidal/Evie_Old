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
sub rsp, 128		#.STACK, 128
.loc 1 6 2		#1 6 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_2130785468048, a_REG0
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2130785468048_0, 1
.loc 1 6 2		#1 6 2
mov qword ptr [rsp + 24 ], rcx		#.STACK_24, a_TMP_2130785468048
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG1, .STACK_24
.loc 5 3 16		#5 3 16
mov dword ptr [rcx + 8 ], 1		#this_4_REG1_8, 1
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG2, .STACK_24
.loc 5 4 12		#5 4 12
mov dword ptr [rcx + 12 ], 0		#this_4_REG2_12, 0
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG3, .STACK_24
.loc 5 3 3		#5 3 3
mov ecx, dword ptr [rcx + 8 ]		#this_4_REG3_8_REG4, this_4_REG3_8
mov dword ptr [rsp + 40 ], ecx		#.STACK_40, this_4_REG3_8_REG4
.loc 4 5 31		#4 5 31
mov ecx, dword ptr [rsp + 40 ]		#REG_Size_0_45, .STACK_40
mov r8, rdx		#REG_Size_0_45_REMAINDER29358, REMAINDER_26962
mov eax, 4		#4_QUOTIENT11478, 4
mul ecx		#REG_Size_0_45
mov ecx, eax		#REG_Size_0_45, 4_QUOTIENT11478
mov rdx, r8		#REMAINDER_26962, REG_Size_0_45_REMAINDER29358
mov ecx, dword ptr [rsp + 40 ]		#REG_Size_0_46, .STACK_40
mov r8, rdx		#REG_Size_0_46_REMAINDER5705, REMAINDER_28145
mov eax, 4		#4_QUOTIENT24464, 4
mul ecx		#REG_Size_0_46
mov ecx, eax		#REG_Size_0_46, 4_QUOTIENT24464
mov rdx, r8		#REMAINDER_28145, REG_Size_0_46_REMAINDER5705
mov ecx, ecx		#REG_REG_Size_0_46_Parameter41, REG_Size_0_46
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 32 ], rax		#.STACK_32, RetREG_7
jmp Return_Here_5		#Return_Here_5
Return_Here_5:
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG8, .STACK_24
mov r8, qword ptr [rsp + 32 ]		#REG_Return_Value0_49, .STACK_32
mov qword ptr [rcx + 16 ], r8		#this_4_REG8_16, REG_Return_Value0_49
jmp Return_Here_4		#Return_Here_4
.loc 1 6 14		#1 6 14
Return_Here_4:
.loc 1 7 2		#1 7 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG10, .STACK_0
mov rcx, rcx		#a_TMP_2130785482736, a_REG10
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2130785482736_0, 1
.loc 1 7 2		#1 7 2
mov qword ptr [rsp + 44 ], rcx		#.STACK_44, a_TMP_2130785482736
.loc 5 9 3		#5 9 3
if_0:
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG11, .STACK_44
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_5_REG11_12_REG12, this_5_REG11_12
mov r8, qword ptr [rsp + 44 ]		#this_5_REG13, .STACK_44
.loc 5 3 3		#5 3 3
mov r8d, dword ptr [r8 + 8 ]		#this_5_REG13_8_REG14, this_5_REG13_8
.loc 5 9 11		#5 9 11
cmp ecx, r8d		#this_5_REG11_12_REG12, this_5_REG13_8_REG14
jl if_0_END		#if_0_END
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG15, .STACK_44
mov r8, qword ptr [rsp + 44 ]		#this_5_REG16, .STACK_44
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_5_REG16_12_REG17, this_5_REG16_12
mov r9, rdx		#this_5_REG16_12_REG17_REMAINDER16827, REMAINDER_9961
mov eax, 2		#2_QUOTIENT23281, 2
mul r8d		#this_5_REG16_12_REG17
mov r8d, eax		#this_5_REG16_12_REG17, 2_QUOTIENT23281
mov rdx, r9		#REMAINDER_9961, this_5_REG16_12_REG17_REMAINDER16827
.loc 5 11 13		#5 11 13
mov dword ptr [rcx + 8 ], r8d		#this_5_REG15_8, this_5_REG16_12_REG17
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG18, .STACK_44
.loc 5 3 3		#5 3 3
mov ecx, dword ptr [rcx + 8 ]		#this_5_REG18_8_REG19, this_5_REG18_8
mov dword ptr [rsp + 80 ], ecx		#.STACK_80, this_5_REG18_8_REG19
.loc 4 5 31		#4 5 31
mov ecx, dword ptr [rsp + 80 ]		#REG_Size_120, .STACK_80
mov r8, rdx		#REG_Size_120_REMAINDER2995, REMAINDER_11942
mov eax, 4		#4_QUOTIENT491, 4
mul ecx		#REG_Size_120
mov ecx, eax		#REG_Size_120, 4_QUOTIENT491
mov rdx, r8		#REMAINDER_11942, REG_Size_120_REMAINDER2995
mov ecx, dword ptr [rsp + 80 ]		#REG_Size_121, .STACK_80
mov r8, rdx		#REG_Size_121_REMAINDER5436, REMAINDER_32391
mov eax, 4		#4_QUOTIENT4827, 4
mul ecx		#REG_Size_121
mov ecx, eax		#REG_Size_121, 4_QUOTIENT4827
mov rdx, r8		#REMAINDER_32391, REG_Size_121_REMAINDER5436
mov ecx, ecx		#REG_REG_Size_121_Parameter18467, REG_Size_121
call _V17internal_allocatex_rPh
mov rbx, rax		#Return_Value1, RetREG_22
jmp Return_Here_7		#Return_Here_7
.loc 5 12 16		#5 12 16
Return_Here_7:
mov rdi, rbx		#tmp, Return_Value1
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG23, .STACK_44
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_5_REG23_12_REG24, this_5_REG23_12
mov r8, rdx		#this_5_REG23_12_REG24_REMAINDER3902, REMAINDER_153
mov eax, 4		#4_QUOTIENT14604, 4
mul ecx		#this_5_REG23_12_REG24
mov ecx, eax		#this_5_REG23_12_REG24, 4_QUOTIENT14604
mov rdx, r8		#REMAINDER_153, this_5_REG23_12_REG24_REMAINDER3902
.loc 5 14 32		#5 14 32
mov dword ptr [rsp + 100 ], ecx		#.STACK_100, this_5_REG23_12_REG24
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG25, .STACK_44
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_5_REG25_16_REG26, this_5_REG25_16
mov qword ptr [rsp + 92 ], rcx		#.STACK_92, this_5_REG25_16_REG26
.loc 5 14 15		#5 14 15
mov qword ptr [rsp + 84 ], rdi		#.STACK_84, tmp
.loc 4 30 17		#4 30 17
mov esi, 0		#i, 0
cmp esi, dword ptr [rsp + 100 ]		#i, .STACK_100
jge while_1_END		#while_1_END
while_1:
mov rbp, qword ptr [rsp + 84 ]		#dest_2_UnLoaded, .STACK_84
.loc 4 31 9		#4 31 9
lea rcx, qword ptr [rbp + rsi * 4 ]		#dest_2_UnLoaded_REG27, *
mov r12, qword ptr [rsp + 92 ]		#source_2_UnLoaded, .STACK_92
mov r8d, dword ptr [r12 + rsi * 4 ]		#source_2_UnLoaded_REG28, *
mov dword ptr [rcx ], r8d		#dest_2_UnLoaded_REG27, source_2_UnLoaded_REG28
.loc 4 30 33		#4 30 33
add esi, 1		#i, 1
cmp esi, dword ptr [rsp + 100 ]		#i, .STACK_100
jge while_1_END		#while_1_END
jmp while_1		#while_1
while_1_END:
jmp Return_Here_8		#Return_Here_8
.loc 5 14 4		#5 14 4
Return_Here_8:
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG29, .STACK_44
.loc 5 18 10		#5 18 10
mov qword ptr [rcx + 16 ], rdi		#this_5_REG29_16, tmp
.loc 5 9 3		#5 9 3
if_0_END:
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG30, .STACK_44
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_5_REG30_16_REG31, this_5_REG30_16
mov r8, qword ptr [rsp + 44 ]		#this_5_REG33, .STACK_44
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_5_REG33_12_REG34, this_5_REG33_12
.loc 5 20 3		#5 20 3
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_5_REG30_16_REG31_REG32, *
mov dword ptr [rcx ], 5		#this_5_REG30_16_REG31_REG32, 5
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG35, .STACK_44
.loc 5 21 7		#5 21 7
add dword ptr [rcx + 12 ], 1		#this_5_REG35_12, 1
.loc 1 7 4		#1 7 4
Return_Here_6:
.loc 1 8 2		#1 8 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_2130785480144, a_REG36
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2130785480144_0, 1
.loc 1 8 2		#1 8 2
mov qword ptr [rsp + 52 ], rcx		#.STACK_52, a_TMP_2130785480144
.loc 5 9 3		#5 9 3
if_2:
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG37, .STACK_52
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_6_REG37_12_REG38, this_6_REG37_12
mov r8, qword ptr [rsp + 52 ]		#this_6_REG39, .STACK_52
.loc 5 3 3		#5 3 3
mov r8d, dword ptr [r8 + 8 ]		#this_6_REG39_8_REG40, this_6_REG39_8
.loc 5 9 11		#5 9 11
cmp ecx, r8d		#this_6_REG37_12_REG38, this_6_REG39_8_REG40
jl if_2_END		#if_2_END
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG41, .STACK_52
mov r8, qword ptr [rsp + 52 ]		#this_6_REG42, .STACK_52
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_6_REG42_12_REG43, this_6_REG42_12
mov r9, rdx		#this_6_REG42_12_REG43_REMAINDER12382, REMAINDER_17421
mov eax, 2		#2_QUOTIENT292, 2
mul r8d		#this_6_REG42_12_REG43
mov r8d, eax		#this_6_REG42_12_REG43, 2_QUOTIENT292
mov rdx, r9		#REMAINDER_17421, this_6_REG42_12_REG43_REMAINDER12382
.loc 5 11 13		#5 11 13
mov dword ptr [rcx + 8 ], r8d		#this_6_REG41_8, this_6_REG42_12_REG43
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG44, .STACK_52
.loc 5 3 3		#5 3 3
mov ecx, dword ptr [rcx + 8 ]		#this_6_REG44_8_REG45, this_6_REG44_8
mov dword ptr [rsp + 104 ], ecx		#.STACK_104, this_6_REG44_8_REG45
.loc 4 5 31		#4 5 31
mov ecx, dword ptr [rsp + 104 ]		#REG_Size_146, .STACK_104
mov r8, rdx		#REG_Size_146_REMAINDER19718, REMAINDER_19895
mov eax, 4		#4_QUOTIENT18716, 4
mul ecx		#REG_Size_146
mov ecx, eax		#REG_Size_146, 4_QUOTIENT18716
mov rdx, r8		#REMAINDER_19895, REG_Size_146_REMAINDER19718
mov ecx, dword ptr [rsp + 104 ]		#REG_Size_147, .STACK_104
mov r8, rdx		#REG_Size_147_REMAINDER21726, REMAINDER_14771
mov eax, 4		#4_QUOTIENT5447, 4
mul ecx		#REG_Size_147
mov ecx, eax		#REG_Size_147, 4_QUOTIENT5447
mov rdx, r8		#REMAINDER_14771, REG_Size_147_REMAINDER21726
mov ecx, ecx		#REG_REG_Size_147_Parameter6334, REG_Size_147
call _V17internal_allocatex_rPh
mov rbx, rax		#Return_Value1, RetREG_48
jmp Return_Here_10		#Return_Here_10
.loc 5 12 16		#5 12 16
Return_Here_10:
mov rdi, rbx		#tmp, Return_Value1
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG49, .STACK_52
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_6_REG49_12_REG50, this_6_REG49_12
mov r8, rdx		#this_6_REG49_12_REG50_REMAINDER1869, REMAINDER_19912
mov eax, 4		#4_QUOTIENT11538, 4
mul ecx		#this_6_REG49_12_REG50
mov ecx, eax		#this_6_REG49_12_REG50, 4_QUOTIENT11538
mov rdx, r8		#REMAINDER_19912, this_6_REG49_12_REG50_REMAINDER1869
.loc 5 14 32		#5 14 32
mov dword ptr [rsp + 124 ], ecx		#.STACK_124, this_6_REG49_12_REG50
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG51, .STACK_52
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_6_REG51_16_REG52, this_6_REG51_16
mov qword ptr [rsp + 116 ], rcx		#.STACK_116, this_6_REG51_16_REG52
.loc 5 14 15		#5 14 15
mov qword ptr [rsp + 108 ], rdi		#.STACK_108, tmp
.loc 4 30 17		#4 30 17
mov esi, 0		#i, 0
cmp esi, dword ptr [rsp + 124 ]		#i, .STACK_124
jge while_3_END		#while_3_END
while_3:
mov rbp, qword ptr [rsp + 108 ]		#dest_2_UnLoaded, .STACK_108
.loc 4 31 9		#4 31 9
lea rcx, qword ptr [rbp + rsi * 4 ]		#dest_2_UnLoaded_REG53, *
mov r12, qword ptr [rsp + 116 ]		#source_2_UnLoaded, .STACK_116
mov r8d, dword ptr [r12 + rsi * 4 ]		#source_2_UnLoaded_REG54, *
mov dword ptr [rcx ], r8d		#dest_2_UnLoaded_REG53, source_2_UnLoaded_REG54
.loc 4 30 33		#4 30 33
add esi, 1		#i, 1
cmp esi, dword ptr [rsp + 124 ]		#i, .STACK_124
jge while_3_END		#while_3_END
jmp while_3		#while_3
while_3_END:
jmp Return_Here_11		#Return_Here_11
.loc 5 14 4		#5 14 4
Return_Here_11:
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG55, .STACK_52
.loc 5 18 10		#5 18 10
mov qword ptr [rcx + 16 ], rdi		#this_6_REG55_16, tmp
.loc 5 9 3		#5 9 3
if_2_END:
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG56, .STACK_52
.loc 5 5 3		#5 5 3
mov rcx, qword ptr [rcx + 16 ]		#this_6_REG56_16_REG57, this_6_REG56_16
mov r8, qword ptr [rsp + 52 ]		#this_6_REG59, .STACK_52
.loc 5 4 3		#5 4 3
mov r8d, dword ptr [r8 + 12 ]		#this_6_REG59_12_REG60, this_6_REG59_12
.loc 5 20 3		#5 20 3
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_6_REG56_16_REG57_REG58, *
mov dword ptr [rcx ], 2		#this_6_REG56_16_REG57_REG58, 2
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG61, .STACK_52
.loc 5 21 7		#5 21 7
add dword ptr [rcx + 12 ], 1		#this_6_REG61_12, 1
.loc 1 8 4		#1 8 4
Return_Here_9:
.loc 1 9 2		#1 9 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG62, .STACK_0
mov rcx, rcx		#a_TMP_2130785478416, a_REG62
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2130785478416_0, 1
.loc 1 9 2		#1 9 2
mov qword ptr [rsp + 60 ], rcx		#.STACK_60, a_TMP_2130785478416
mov rcx, qword ptr [rsp + 60 ]		#this_7_REG63, .STACK_60
.loc 5 25 7		#5 25 7
sub dword ptr [rcx + 12 ], 1		#this_7_REG63_12, 1
.loc 1 9 4		#1 9 4
Return_Here_12:
.loc 1 10 13		#1 10 13
mov dword ptr [rsp + 68 ], 0		#.STACK_68, 0
lea rcx, qword ptr [rsp + 0 ]		#a_REG64, .STACK_0
mov rcx, rcx		#a_TMP_2130785513840, a_REG64
.loc 17 2 36		#17 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2130785513840_0, 1
.loc 1 10 9		#1 10 9
mov qword ptr [rsp + 72 ], rcx		#.STACK_72, a_TMP_2130785513840
.loc 5 29 3		#5 29 3
if_4:
mov rcx, qword ptr [rsp + 72 ]		#this_8_REG65, .STACK_72
.loc 5 4 3		#5 4 3
mov ecx, dword ptr [rcx + 12 ]		#this_8_REG65_12_REG66, this_8_REG65_12
.loc 5 29 8		#5 29 8
cmp dword ptr [rsp + 68 ], ecx		#.STACK_68, this_8_REG65_12_REG66
jle if_4_END		#if_4_END
.loc 5 30 4		#5 30 4
mov ecx, 0		#Return_Value8, 0
jmp Return_Here_13		#Return_Here_13
.loc 5 29 3		#5 29 3
if_4_END:
mov r8, qword ptr [rsp + 72 ]		#this_8_REG67, .STACK_72
.loc 5 5 3		#5 5 3
mov r8, qword ptr [r8 + 16 ]		#this_8_REG67_16_REG68, this_8_REG67_16
.loc 5 32 10		#5 32 10
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_8_REG67_16_REG68_REG69, *
mov ecx, r8d		#Return_Value8, this_8_REG67_16_REG68_REG69
jmp Return_Here_13		#Return_Here_13
.loc 1 10 11		#1 10 11
Return_Here_13:
mov eax, ecx		#Returning_REG70, Return_Value8
add rsp, 128		#.STACK, 128
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
ret 		#
add rsp, 128		#.STACK, 128
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
_ZN13____List_int_10DestructorEP13____List_int__START:
.loc 5 2 2		#5 2 2
_ZN13____List_int_10DestructorEP13____List_int_:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
sub rsp, 16		#.STACK, 16
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this
.loc 17 1 1		#17 1 1
if_5:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_5_END		#if_5_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
.loc 5 2 2		#5 2 2
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
.loc 17 1 26		#17 1 26
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_5_END		#if_5_END
.loc 17 2 26		#17 2 26
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_2130785544944, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_2130785544944_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_2130785544944
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 4 18 2		#4 18 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_3_Parameter26500, .STACK_0
mov edx, 8		#REG_8_Parameter19169, 8
call _V19internal_deallocatePhx
.loc 17 2 1		#17 2 1
Return_Here_3:
.loc 17 1 11		#17 1 11
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_3_Parameter15724, .STACK_0
call _ZN13____List_int_10DestructorEP13____List_int_
if_5_END:
add rsp, 16		#.STACK, 16
ret 		#
_ZN13____List_int_10DestructorEP13____List_int__END:


.cfi_endproc 		#
Code_End:
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
.byte 11		#11
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
.byte 11		#11
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
.byte 11		#11
.byte 58		#58
.byte 11		#11
.byte 59		#59
.byte 11		#11
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
.long Code_End		#Code_End
_char_START:
.byte 2		#2
.asciz "char"		#char
.byte 6		#6
.byte 1		#1
.byte 3		#3
.byte 1		#1
_bool_START:
.byte 2		#2
.asciz "bool"		#bool
.byte 6		#6
.byte 1		#1
.byte 3		#3
.byte 5		#5
_short_START:
.byte 2		#2
.asciz "short"		#short
.byte 5		#5
.byte 2		#2
.byte 3		#3
.byte 9		#9
_int_START:
.byte 2		#2
.asciz "int"		#int
.byte 5		#5
.byte 4		#4
.byte 3		#3
.byte 13		#13
_long_START:
.byte 2		#2
.asciz "long"		#long
.byte 5		#5
.byte 8		#8
.byte 3		#3
.byte 17		#17
_float_START:
.byte 2		#2
.asciz "float"		#float
.byte 4		#4
.byte 4		#4
.byte 3		#3
.byte 21		#21
_double_START:
.byte 2		#2
.asciz "double"		#double
.byte 4		#4
.byte 8		#8
.byte 3		#3
.byte 26		#26
_3std_START:
.byte 4		#4
.byte 1		#1
.asciz "std"		#std
.byte 698		#698
.byte 5		#5
.byte 1		#1
_6string_START:
.byte 4		#4
.byte 1		#1
.asciz "string"		#string
.byte 8		#8
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
.byte 16		#16
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
.asciz "MAX_CONCOLE_BUFFER_LENGHT"		#MAX_CONCOLE_BUFFER_LENGHT
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
.byte 260		#260
.byte 17		#17
.byte 41		#41
_Char_14_START:
.byte 2		#2
.asciz "Char_14"		#Char_14
.byte 5		#5
.byte 14		#14
.byte 17		#17
.byte 45		#45
_12FileIterator_START:
.byte 4		#4
.byte 1		#1
.asciz "FileIterator"		#FileIterator
.byte 328		#328
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
.long _Z10Start_Testv_END		#_Z10Start_Testv_END
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
.byte 24		#24
.asciz "this_4"		#this_4
.byte 5		#5
.byte 2		#2
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "Return_Value0_4"		#Return_Value0_4
.byte 5		#5
.byte 5		#5
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "Size_0_4"		#Size_0_4
.byte 4		#4
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 44		#44
.asciz "this_5"		#this_5
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 52		#52
.asciz "this_6"		#this_6
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 60		#60
.asciz "this_7"		#this_7
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value8"		#Return_Value8
.byte 1		#1
.byte 10		#10
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 68		#68
.asciz "i_8"		#i_8
.byte 5		#5
.byte 28		#28
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 72		#72
.asciz "this_8"		#this_8
.byte 17		#17
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2130785468048"		#a_TMP_2130785468048
.byte 1		#1
.byte 6		#6
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2130785482736"		#a_TMP_2130785482736
.byte 1		#1
.byte 7		#7
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2130785480144"		#a_TMP_2130785480144
.byte 1		#1
.byte 8		#8
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2130785478416"		#a_TMP_2130785478416
.byte 1		#1
.byte 9		#9
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 9		#9
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2130785513840"		#a_TMP_2130785513840
.byte 1		#1
.byte 10		#10
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 0		#0
.byte 10		#10
.quad _Z4mainv_START		#_Z4mainv_START
.long _Z4mainv_END		#_Z4mainv_END
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
.byte 16		#16
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
.word 16		#16
.asciz "Array"		#Array
.byte 5		#5
.byte 5		#5
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
_26____VIRTUAL_CLASS_char_ptr_START:
.byte 12		#12
.byte 1		#1
.asciz "____VIRTUAL_CLASS_char_ptr"		#____VIRTUAL_CLASS_char_ptr
.byte 8		#8
.byte 4		#4
.byte 5		#5
_25____VIRTUAL_CLASS_int_ptr_START:
.byte 12		#12
.byte 1		#1
.asciz "____VIRTUAL_CLASS_int_ptr"		#____VIRTUAL_CLASS_int_ptr
.byte 8		#8
.byte 4		#4
.byte 5		#5
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
