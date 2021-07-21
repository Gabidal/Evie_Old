.intel_syntax noprefix
.file 1 "Tests/IO/Template.e"		#1 "Tests/IO/Template.e"
.file 2 "Tests/IO/../../IO/cstd.e"		#2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"		#3 "Tests/IO/../../IO/sys.e"
.file 4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"		#4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"		#5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"		#6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"		#7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"		#8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"		#9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"		#10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"		#11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 12 "Tests/IO/../../IO/STD.e"		#12 "Tests/IO/../../IO/STD.e"
.file 13 "Tests/IO/../../IO/Memory.e"		#13 "Tests/IO/../../IO/Memory.e"
.file 14 "Tests/IO/../../IO/List.e"		#14 "Tests/IO/../../IO/List.e"
Code_Start:
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv_START:
.loc 1 3 1		#1 3 1
_Z10Start_Testv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
.loc 1 8 11		#1 8 11
push r12		#r12
push rbp		#rbp
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
sub rsp, 112		#.STACK, 112
.loc 1 4 2		#1 4 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#a_TMP_2116495274048, a_REG0
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2116495274048_0, 1
.loc 1 4 2		#1 4 2
mov qword ptr [rsp + 24 ], rcx		#.STACK_24, a_TMP_2116495274048
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG1, .STACK_24
.loc 14 2 15		#14 2 15
mov dword ptr [rcx + 8 ], 1		#this_4_REG1_8, 1
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG2, .STACK_24
.loc 14 3 11		#14 3 11
mov dword ptr [rcx + 12 ], 0		#this_4_REG2_12, 0
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG3, .STACK_24
.loc 14 2 2		#14 2 2
mov ecx, dword ptr [rcx + 8 ]		#this_4_REG3_8_REG4, this_4_REG3_8
mov dword ptr [rsp + 40 ], ecx		#.STACK_40, this_4_REG3_8_REG4
.loc 13 5 31		#13 5 31
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
.loc 14 4 16		#14 4 16
Return_Here_5:
mov rcx, qword ptr [rsp + 24 ]		#this_4_REG8, .STACK_24
mov r8, qword ptr [rsp + 32 ]		#REG_Return_Value0_49, .STACK_32
mov qword ptr [rcx + 16 ], r8		#this_4_REG8_16, REG_Return_Value0_49
jmp Return_Here_4		#Return_Here_4
Return_Here_4:
.loc 1 5 2		#1 5 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG10, .STACK_0
mov rcx, rcx		#a_TMP_2116495842160, a_REG10
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2116495842160_0, 1
.loc 1 5 2		#1 5 2
mov qword ptr [rsp + 44 ], rcx		#.STACK_44, a_TMP_2116495842160
.loc 14 8 2		#14 8 2
if_0:
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG11, .STACK_44
.loc 14 3 2		#14 3 2
mov ecx, dword ptr [rcx + 12 ]		#this_5_REG11_12_REG12, this_5_REG11_12
mov r8, qword ptr [rsp + 44 ]		#this_5_REG13, .STACK_44
.loc 14 2 2		#14 2 2
mov r8d, dword ptr [r8 + 8 ]		#this_5_REG13_8_REG14, this_5_REG13_8
.loc 14 8 10		#14 8 10
cmp ecx, r8d		#this_5_REG11_12_REG12, this_5_REG13_8_REG14
jl if_0_END		#if_0_END
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG15, .STACK_44
mov r8, qword ptr [rsp + 44 ]		#this_5_REG16, .STACK_44
.loc 14 3 2		#14 3 2
mov r8d, dword ptr [r8 + 12 ]		#this_5_REG16_12_REG17, this_5_REG16_12
mov r9, rdx		#this_5_REG16_12_REG17_REMAINDER16827, REMAINDER_9961
mov eax, 2		#2_QUOTIENT23281, 2
mul r8d		#this_5_REG16_12_REG17
mov r8d, eax		#this_5_REG16_12_REG17, 2_QUOTIENT23281
mov rdx, r9		#REMAINDER_9961, this_5_REG16_12_REG17_REMAINDER16827
.loc 14 10 18		#14 10 18
mov dword ptr [rcx + 8 ], r8d		#this_5_REG15_8, this_5_REG16_12_REG17
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG18, .STACK_44
.loc 14 2 2		#14 2 2
mov ecx, dword ptr [rcx + 8 ]		#this_5_REG18_8_REG19, this_5_REG18_8
mov dword ptr [rsp + 0 ], ecx		#.STACK_0, this_5_REG18_8_REG19
.loc 13 5 31		#13 5 31
mov ecx, dword ptr [rsp + 0 ]		#REG_Size_120, .STACK_0
mov r8, rdx		#REG_Size_120_REMAINDER2995, REMAINDER_11942
mov eax, 4		#4_QUOTIENT491, 4
mul ecx		#REG_Size_120
mov ecx, eax		#REG_Size_120, 4_QUOTIENT491
mov rdx, r8		#REMAINDER_11942, REG_Size_120_REMAINDER2995
mov ecx, dword ptr [rsp + 0 ]		#REG_Size_121, .STACK_0
mov r8, rdx		#REG_Size_121_REMAINDER5436, REMAINDER_32391
mov eax, 4		#4_QUOTIENT4827, 4
mul ecx		#REG_Size_121
mov ecx, eax		#REG_Size_121, 4_QUOTIENT4827
mov rdx, r8		#REMAINDER_32391, REG_Size_121_REMAINDER5436
mov ecx, ecx		#REG_REG_Size_121_Parameter18467, REG_Size_121
call _V17internal_allocatex_rPh
mov rbx, rax		#Return_Value1, RetREG_22
jmp Return_Here_7		#Return_Here_7
.loc 14 11 21		#14 11 21
Return_Here_7:
mov rdi, rbx		#tmp, Return_Value1
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG23, .STACK_44
.loc 14 3 2		#14 3 2
mov ecx, dword ptr [rcx + 12 ]		#this_5_REG23_12_REG24, this_5_REG23_12
mov r8, rdx		#this_5_REG23_12_REG24_REMAINDER3902, REMAINDER_153
mov eax, 4		#4_QUOTIENT14604, 4
mul ecx		#this_5_REG23_12_REG24
mov ecx, eax		#this_5_REG23_12_REG24, 4_QUOTIENT14604
mov rdx, r8		#REMAINDER_153, this_5_REG23_12_REG24_REMAINDER3902
.loc 14 13 37		#14 13 37
mov dword ptr [rsp + 20 ], ecx		#.STACK_20, this_5_REG23_12_REG24
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG25, .STACK_44
.loc 14 4 2		#14 4 2
mov rcx, qword ptr [rcx + 16 ]		#this_5_REG25_16_REG26, this_5_REG25_16
mov qword ptr [rsp + 12 ], rcx		#.STACK_12, this_5_REG25_16_REG26
.loc 14 13 20		#14 13 20
mov qword ptr [rsp + 4 ], rdi		#.STACK_4, tmp
.loc 2 38 17		#2 38 17
mov esi, 0		#i, 0
cmp esi, dword ptr [rsp + 20 ]		#i, .STACK_20
jge while_1_END		#while_1_END
while_1:
mov rbp, qword ptr [rsp + 4 ]		#dest_2_UnLoaded, .STACK_4
.loc 2 39 9		#2 39 9
lea rcx, qword ptr [rbp + rsi * 4 ]		#dest_2_UnLoaded_REG27, *
mov r12, qword ptr [rsp + 12 ]		#source_2_UnLoaded, .STACK_12
mov r8d, dword ptr [r12 + rsi * 4 ]		#source_2_UnLoaded_REG28, *
mov dword ptr [rcx ], r8d		#dest_2_UnLoaded_REG27, source_2_UnLoaded_REG28
.loc 2 38 33		#2 38 33
add esi, 1		#i, 1
cmp esi, dword ptr [rsp + 20 ]		#i, .STACK_20
jge while_1_END		#while_1_END
jmp while_1		#while_1
while_1_END:
jmp Return_Here_8		#Return_Here_8
.loc 14 13 9		#14 13 9
Return_Here_8:
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG29, .STACK_44
.loc 14 17 15		#14 17 15
mov qword ptr [rcx + 16 ], rdi		#this_5_REG29_16, tmp
.loc 14 8 2		#14 8 2
if_0_END:
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG30, .STACK_44
.loc 14 4 2		#14 4 2
mov rcx, qword ptr [rcx + 16 ]		#this_5_REG30_16_REG31, this_5_REG30_16
mov r8, qword ptr [rsp + 44 ]		#this_5_REG33, .STACK_44
.loc 14 3 2		#14 3 2
mov r8d, dword ptr [r8 + 12 ]		#this_5_REG33_12_REG34, this_5_REG33_12
.loc 14 19 2		#14 19 2
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_5_REG30_16_REG31_REG32, *
mov dword ptr [rcx ], 5		#this_5_REG30_16_REG31_REG32, 5
mov rcx, qword ptr [rsp + 44 ]		#this_5_REG35, .STACK_44
.loc 14 20 6		#14 20 6
add dword ptr [rcx + 12 ], 1		#this_5_REG35_12, 1
.loc 1 5 4		#1 5 4
Return_Here_6:
.loc 1 6 2		#1 6 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG36, .STACK_0
mov rcx, rcx		#a_TMP_2116495823856, a_REG36
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2116495823856_0, 1
.loc 1 6 2		#1 6 2
mov qword ptr [rsp + 52 ], rcx		#.STACK_52, a_TMP_2116495823856
.loc 14 8 2		#14 8 2
if_2:
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG37, .STACK_52
.loc 14 3 2		#14 3 2
mov ecx, dword ptr [rcx + 12 ]		#this_6_REG37_12_REG38, this_6_REG37_12
mov r8, qword ptr [rsp + 52 ]		#this_6_REG39, .STACK_52
.loc 14 2 2		#14 2 2
mov r8d, dword ptr [r8 + 8 ]		#this_6_REG39_8_REG40, this_6_REG39_8
.loc 14 8 10		#14 8 10
cmp ecx, r8d		#this_6_REG37_12_REG38, this_6_REG39_8_REG40
jl if_2_END		#if_2_END
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG41, .STACK_52
mov r8, qword ptr [rsp + 52 ]		#this_6_REG42, .STACK_52
.loc 14 3 2		#14 3 2
mov r8d, dword ptr [r8 + 12 ]		#this_6_REG42_12_REG43, this_6_REG42_12
mov r9, rdx		#this_6_REG42_12_REG43_REMAINDER12382, REMAINDER_17421
mov eax, 2		#2_QUOTIENT292, 2
mul r8d		#this_6_REG42_12_REG43
mov r8d, eax		#this_6_REG42_12_REG43, 2_QUOTIENT292
mov rdx, r9		#REMAINDER_17421, this_6_REG42_12_REG43_REMAINDER12382
.loc 14 10 18		#14 10 18
mov dword ptr [rcx + 8 ], r8d		#this_6_REG41_8, this_6_REG42_12_REG43
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG44, .STACK_52
.loc 14 2 2		#14 2 2
mov ecx, dword ptr [rcx + 8 ]		#this_6_REG44_8_REG45, this_6_REG44_8
mov dword ptr [rsp + 0 ], ecx		#.STACK_0, this_6_REG44_8_REG45
.loc 13 5 31		#13 5 31
mov ecx, dword ptr [rsp + 0 ]		#REG_Size_146, .STACK_0
mov r8, rdx		#REG_Size_146_REMAINDER19718, REMAINDER_19895
mov eax, 4		#4_QUOTIENT18716, 4
mul ecx		#REG_Size_146
mov ecx, eax		#REG_Size_146, 4_QUOTIENT18716
mov rdx, r8		#REMAINDER_19895, REG_Size_146_REMAINDER19718
mov ecx, dword ptr [rsp + 0 ]		#REG_Size_147, .STACK_0
mov r8, rdx		#REG_Size_147_REMAINDER21726, REMAINDER_14771
mov eax, 4		#4_QUOTIENT5447, 4
mul ecx		#REG_Size_147
mov ecx, eax		#REG_Size_147, 4_QUOTIENT5447
mov rdx, r8		#REMAINDER_14771, REG_Size_147_REMAINDER21726
mov ecx, ecx		#REG_REG_Size_147_Parameter6334, REG_Size_147
call _V17internal_allocatex_rPh
mov rbx, rax		#Return_Value1, RetREG_48
jmp Return_Here_10		#Return_Here_10
.loc 14 11 21		#14 11 21
Return_Here_10:
mov rdi, rbx		#tmp, Return_Value1
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG49, .STACK_52
.loc 14 3 2		#14 3 2
mov ecx, dword ptr [rcx + 12 ]		#this_6_REG49_12_REG50, this_6_REG49_12
mov r8, rdx		#this_6_REG49_12_REG50_REMAINDER1869, REMAINDER_19912
mov eax, 4		#4_QUOTIENT11538, 4
mul ecx		#this_6_REG49_12_REG50
mov ecx, eax		#this_6_REG49_12_REG50, 4_QUOTIENT11538
mov rdx, r8		#REMAINDER_19912, this_6_REG49_12_REG50_REMAINDER1869
.loc 14 13 37		#14 13 37
mov dword ptr [rsp + 20 ], ecx		#.STACK_20, this_6_REG49_12_REG50
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG51, .STACK_52
.loc 14 4 2		#14 4 2
mov rcx, qword ptr [rcx + 16 ]		#this_6_REG51_16_REG52, this_6_REG51_16
mov qword ptr [rsp + 12 ], rcx		#.STACK_12, this_6_REG51_16_REG52
.loc 14 13 20		#14 13 20
mov qword ptr [rsp + 4 ], rdi		#.STACK_4, tmp
.loc 2 38 17		#2 38 17
mov esi, 0		#i, 0
cmp esi, dword ptr [rsp + 20 ]		#i, .STACK_20
jge while_3_END		#while_3_END
while_3:
mov rbp, qword ptr [rsp + 4 ]		#dest_2_UnLoaded, .STACK_4
.loc 2 39 9		#2 39 9
lea rcx, qword ptr [rbp + rsi * 4 ]		#dest_2_UnLoaded_REG53, *
mov r12, qword ptr [rsp + 12 ]		#source_2_UnLoaded, .STACK_12
mov r8d, dword ptr [r12 + rsi * 4 ]		#source_2_UnLoaded_REG54, *
mov dword ptr [rcx ], r8d		#dest_2_UnLoaded_REG53, source_2_UnLoaded_REG54
.loc 2 38 33		#2 38 33
add esi, 1		#i, 1
cmp esi, dword ptr [rsp + 20 ]		#i, .STACK_20
jge while_3_END		#while_3_END
jmp while_3		#while_3
while_3_END:
jmp Return_Here_11		#Return_Here_11
.loc 14 13 9		#14 13 9
Return_Here_11:
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG55, .STACK_52
.loc 14 17 15		#14 17 15
mov qword ptr [rcx + 16 ], rdi		#this_6_REG55_16, tmp
.loc 14 8 2		#14 8 2
if_2_END:
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG56, .STACK_52
.loc 14 4 2		#14 4 2
mov rcx, qword ptr [rcx + 16 ]		#this_6_REG56_16_REG57, this_6_REG56_16
mov r8, qword ptr [rsp + 52 ]		#this_6_REG59, .STACK_52
.loc 14 3 2		#14 3 2
mov r8d, dword ptr [r8 + 12 ]		#this_6_REG59_12_REG60, this_6_REG59_12
.loc 14 19 2		#14 19 2
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_6_REG56_16_REG57_REG58, *
mov dword ptr [rcx ], 2		#this_6_REG56_16_REG57_REG58, 2
mov rcx, qword ptr [rsp + 52 ]		#this_6_REG61, .STACK_52
.loc 14 20 6		#14 20 6
add dword ptr [rcx + 12 ], 1		#this_6_REG61_12, 1
.loc 1 6 4		#1 6 4
Return_Here_9:
.loc 1 7 2		#1 7 2
lea rcx, qword ptr [rsp + 0 ]		#a_REG62, .STACK_0
mov rcx, rcx		#a_TMP_2116495862960, a_REG62
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2116495862960_0, 1
.loc 1 7 2		#1 7 2
mov qword ptr [rsp + 60 ], rcx		#.STACK_60, a_TMP_2116495862960
mov rcx, qword ptr [rsp + 60 ]		#this_7_REG63, .STACK_60
.loc 14 24 6		#14 24 6
sub dword ptr [rcx + 12 ], 1		#this_7_REG63_12, 1
.loc 1 7 4		#1 7 4
Return_Here_12:
.loc 1 8 13		#1 8 13
mov dword ptr [rsp + 68 ], 0		#.STACK_68, 0
lea rcx, qword ptr [rsp + 0 ]		#a_REG64, .STACK_0
mov rcx, rcx		#a_TMP_2116495872944, a_REG64
.loc 14 2 36		#14 2 36
add qword ptr [rcx + 0 ], 1		#a_TMP_2116495872944_0, 1
.loc 1 8 9		#1 8 9
mov qword ptr [rsp + 72 ], rcx		#.STACK_72, a_TMP_2116495872944
.loc 14 28 2		#14 28 2
if_4:
mov rcx, qword ptr [rsp + 72 ]		#this_8_REG65, .STACK_72
.loc 14 3 2		#14 3 2
mov ecx, dword ptr [rcx + 12 ]		#this_8_REG65_12_REG66, this_8_REG65_12
.loc 14 28 7		#14 28 7
cmp dword ptr [rsp + 68 ], ecx		#.STACK_68, this_8_REG65_12_REG66
jle if_4_END		#if_4_END
.loc 14 29 3		#14 29 3
mov ecx, 0		#Return_Value8, 0
jmp Return_Here_13		#Return_Here_13
.loc 14 28 2		#14 28 2
if_4_END:
mov r8, qword ptr [rsp + 72 ]		#this_8_REG67, .STACK_72
.loc 14 4 2		#14 4 2
mov r8, qword ptr [r8 + 16 ]		#this_8_REG67_16_REG68, this_8_REG67_16
.loc 14 31 9		#14 31 9
mov r8d, dword ptr [r8 + 0 * 4 ]		#this_8_REG67_16_REG68_REG69, *
mov ecx, r8d		#Return_Value8, this_8_REG67_16_REG68_REG69
jmp Return_Here_13		#Return_Here_13
.loc 1 8 11		#1 8 11
Return_Here_13:
mov eax, ecx		#Returning_REG70, Return_Value8
add rsp, 112		#.STACK, 112
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
ret 		#
add rsp, 112		#.STACK, 112
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
pop r12		#r12
ret 		#
_Z10Start_Testv_END:


.cfi_endproc 		#
_Z4mainv_START:
.loc 1 11 1		#1 11 1
_Z4mainv:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
jmp _Z10Start_Testv		#_Z10Start_Testv
.loc 1 13 2		#1 13 2
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#
_Z4mainv_END:


.cfi_endproc 		#
_ZN13____List_int_10DestructorEP13____List_int__START:
.loc 14 1 1		#14 1 1
_ZN13____List_int_10DestructorEP13____List_int_:
.cfi_startproc 		#
.cfi_def_cfa_offset 16		#16
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this
if_5:
cmp qword ptr [rsp + 0 ], 0		#.STACK_0, 0
je if_5_END		#if_5_END
mov rcx, qword ptr [rsp + 0 ]		#this_REG0, .STACK_0
mov rcx, qword ptr [rcx + 0 ]		#this_REG0_0_REG1, this_REG0_0
sub rcx, 1		#this_REG0_0_REG1, 1
cmp rcx, 1		#this_REG0_0_REG1, 1
jge if_5_END		#if_5_END
.loc 14 2 26		#14 2 26
mov rcx, qword ptr [rsp + 0 ]		#this_TMP_2116495868784, .STACK_0
add qword ptr [rcx + 0 ], 1		#this_TMP_2116495868784_0, 1
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, this_TMP_2116495868784
mov rcx, qword ptr [rsp + 0 ]		#REG_this2, .STACK_0
mov qword ptr [rsp + 0 ], rcx		#.STACK_0, REG_this2
.loc 13 18 2		#13 18 2
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_3_Parameter26500, .STACK_0
mov edx, 8		#REG_8_Parameter19169, 8
call _V19internal_deallocatePhx
.loc 14 2 1		#14 2 1
Return_Here_3:
.loc 14 1 11		#14 1 11
mov rcx, qword ptr [rsp + 0 ]		#REG_Address_3_Parameter15724, .STACK_0
call _ZN13____List_int_10DestructorEP13____List_int_
if_5_END:
ret 		#
_ZN13____List_int_10DestructorEP13____List_int__END:


.cfi_endproc 		#
Code_End:
.section .data		#.data
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
.byte 5		#5
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
.byte 6		#6
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
.byte 7		#7
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
.byte 8		#8
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
.byte 9		#9
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
.byte 10		#10
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
.byte 11		#11
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
_int_START:
.byte 2		#2
.asciz "int"		#int
.byte 5		#5
.byte 4		#4
.byte 2		#2
.byte 3		#3
_short_START:
.byte 2		#2
.asciz "short"		#short
.byte 5		#5
.byte 2		#2
.byte 2		#2
.byte 7		#7
_char_START:
.byte 2		#2
.asciz "char"		#char
.byte 6		#6
.byte 1		#1
.byte 2		#2
.byte 11		#11
_float_START:
.byte 2		#2
.asciz "float"		#float
.byte 4		#4
.byte 4		#4
.byte 2		#2
.byte 15		#15
_double_START:
.byte 2		#2
.asciz "double"		#double
.byte 4		#4
.byte 8		#8
.byte 2		#2
.byte 20		#20
_long_START:
.byte 2		#2
.asciz "long"		#long
.byte 5		#5
.byte 8		#8
.byte 2		#2
.byte 25		#25
_string_START:
.byte 2		#2
.asciz "string"		#string
.byte 6		#6
.byte 1		#1
.byte 2		#2
.byte 29		#29
_12BYTE_POINTER_START:
.byte 4		#4
.byte 1		#1
.asciz "BYTE_POINTER"		#BYTE_POINTER
.byte 8		#8
.byte 13		#13
.byte 1		#1
.byte 5		#5
.quad _Z10Start_Testv_START		#_Z10Start_Testv_START
.long _Z10Start_Testv_END		#_Z10Start_Testv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z10Start_Testv"		#_Z10Start_Testv
.asciz "Start_Test"		#Start_Test
.byte 1		#1
.byte 3		#3
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a"		#a
.byte 1		#1
.byte 4		#4
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 24		#24
.asciz "this_4"		#this_4
.byte 14		#14
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 32		#32
.asciz "Return_Value0_4"		#Return_Value0_4
.byte 14		#14
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 40		#40
.asciz "Size_0_4"		#Size_0_4
.byte 13		#13
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Cast_Type_0_4"		#Return_Cast_Type_0_4
.byte 13		#13
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 44		#44
.asciz "this_5"		#this_5
.byte 14		#14
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 52		#52
.asciz "this_6"		#this_6
.byte 14		#14
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 60		#60
.asciz "this_7"		#this_7
.byte 14		#14
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "Return_Value8"		#Return_Value8
.byte 1		#1
.byte 8		#8
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 68		#68
.asciz "i_8"		#i_8
.byte 14		#14
.byte 27		#27
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 72		#72
.asciz "this_8"		#this_8
.byte 14		#14
.byte 1		#1
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2116495274048"		#a_TMP_2116495274048
.byte 1		#1
.byte 4		#4
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2116495842160"		#a_TMP_2116495842160
.byte 1		#1
.byte 5		#5
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2116495823856"		#a_TMP_2116495823856
.byte 1		#1
.byte 6		#6
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2116495862960"		#a_TMP_2116495862960
.byte 1		#1
.byte 7		#7
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 6		#6
.byte 2		#2
.byte 145		#145
.byte 0		#0
.asciz "a_TMP_2116495872944"		#a_TMP_2116495872944
.byte 1		#1
.byte 8		#8
.long _13____List_int__START-Debug_Info_Start		#_13____List_int__START-Debug_Info_Start
.byte 0		#0
.byte 7		#7
.quad _Z4mainv_START		#_Z4mainv_START
.long _Z4mainv_END		#_Z4mainv_END
.byte 1		#1
.byte 87		#87
.asciz "_Z4mainv"		#_Z4mainv
.asciz "main"		#main
.byte 1		#1
.byte 11		#11
_13____List_int__START:
.byte 10		#10
.byte 1		#1
.asciz "____List_int_"		#____List_int_
.byte 16		#16
.byte 14		#14
.byte 1		#1
.byte 3		#3
.word 0		#0
.asciz "Reference_Count"		#Reference_Count
.byte 14		#14
.byte 1		#1
.long _long_START-Debug_Info_Start		#_long_START-Debug_Info_Start
.byte 3		#3
.word 8		#8
.asciz "Capacity"		#Capacity
.byte 14		#14
.byte 2		#2
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 12		#12
.asciz "Size"		#Size
.byte 14		#14
.byte 3		#3
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 3		#3
.word 16		#16
.asciz "Array"		#Array
.byte 14		#14
.byte 4		#4
.long _int_START-Debug_Info_Start		#_int_START-Debug_Info_Start
.byte 0		#0
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
