.intel_syntax noprefix
.file 1 "Tests/IO/Template.e"
.file 2 "Tests/IO/../../IO/cstd.e"
.file 3 "Tests/IO/../../IO/sys.e"
.file 4 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm.obj"
.file 5 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/console.asm"
.file 6 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm.obj"
.file 7 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/math.asm"
.file 8 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm.obj"
.file 9 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/memory.asm"
.file 10 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm.obj"
.file 11 "C:/Users/GabenRTX/.Repos/vivid/Vivid/libv/windows_x64/system.asm"
.file 12 "Tests/IO/../../IO/STD.e"
.file 13 "Tests/IO/../../IO/Memory.e"
.file 14 "Tests/IO/../../IO/List.e"
Code_Start:
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv_START:
.loc 1 3 1
_Z10Start_Testv:
.cfi_startproc 
.cfi_def_cfa_offset 16
.loc 1 8 11
push r12
push rbp
push rsi
push rdi
push rbx
sub rsp, 412
.loc 1 4 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 4 2
mov qword ptr [rsp + 24 ], rcx
mov rcx, qword ptr [rsp + 24 ]
.loc 14 2 15
mov dword ptr [rcx + 8 ], 1
mov rcx, qword ptr [rsp + 24 ]
.loc 14 3 11
mov dword ptr [rcx + 12 ], 0
mov rcx, qword ptr [rsp + 24 ]
.loc 14 2 2
mov ecx, dword ptr [rcx + 8 ]
mov dword ptr [rsp + 40 ], ecx
.loc 13 5 31
mov ecx, dword ptr [rsp + 40 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, dword ptr [rsp + 40 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov qword ptr [rsp + 32 ], rax
jmp Return_Here_5
.loc 14 4 16
Return_Here_5:
mov rcx, qword ptr [rsp + 24 ]
mov r8, qword ptr [rsp + 32 ]
mov qword ptr [rcx + 16 ], r8
jmp Return_Here_4
Return_Here_4:
.loc 1 5 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 5 2
mov qword ptr [rsp + 44 ], rcx
.loc 14 8 2
if_0:
mov rcx, qword ptr [rsp + 44 ]
.loc 14 3 2
mov ecx, dword ptr [rcx + 12 ]
mov r8, qword ptr [rsp + 44 ]
.loc 14 2 2
mov r8d, dword ptr [r8 + 8 ]
.loc 14 8 10
cmp ecx, r8d
jl if_0_END
mov rcx, qword ptr [rsp + 44 ]
mov r8, qword ptr [rsp + 44 ]
.loc 14 3 2
mov r8d, dword ptr [r8 + 12 ]
mov r9, rdx
mov eax, 2
mul r8d
mov r8d, eax
mov rdx, r9
.loc 14 10 18
mov dword ptr [rcx + 8 ], r8d
mov rcx, qword ptr [rsp + 44 ]
.loc 14 2 2
mov ecx, dword ptr [rcx + 8 ]
mov dword ptr [rsp ], ecx
.loc 13 5 31
mov ecx, dword ptr [rsp ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, dword ptr [rsp ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rbx, rax
jmp Return_Here_7
.loc 14 11 21
Return_Here_7:
mov rdi, rbx
mov rcx, qword ptr [rsp + 44 ]
.loc 14 3 2
mov ecx, dword ptr [rcx + 12 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
.loc 14 13 37
mov dword ptr [rsp + 20 ], ecx
mov rcx, qword ptr [rsp + 44 ]
.loc 14 4 2
mov rcx, qword ptr [rcx + 16 ]
mov qword ptr [rsp + 12 ], rcx
.loc 14 13 20
mov qword ptr [rsp + 4 ], rdi
.loc 2 38 17
mov esi, 0
cmp esi, dword ptr [rsp + 20 ]
jge while_1_END
while_1:
mov rbp, qword ptr [rsp + 4 ]
.loc 2 39 9
lea rcx, qword ptr [rbp + rsi * 4 ]
mov r12, qword ptr [rsp + 12 ]
mov r8d, dword ptr [r12 + rsi * 4 ]
mov dword ptr [rcx ], r8d
.loc 2 38 33
add esi, 1
cmp esi, dword ptr [rsp + 20 ]
jge while_1_END
jmp while_1
while_1_END:
jmp Return_Here_8
.loc 14 13 9
Return_Here_8:
mov rcx, qword ptr [rsp + 44 ]
.loc 14 17 15
mov qword ptr [rcx + 16 ], rdi
.loc 14 8 2
if_0_END:
mov rcx, qword ptr [rsp + 44 ]
.loc 14 4 2
mov rcx, qword ptr [rcx + 16 ]
mov r8, qword ptr [rsp + 44 ]
.loc 14 3 2
mov r8d, dword ptr [r8 + 12 ]
.loc 14 19 2
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 5
mov rcx, qword ptr [rsp + 44 ]
.loc 14 20 6
add dword ptr [rcx + 12 ], 1
.loc 1 5 4
Return_Here_6:
.loc 1 6 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 6 2
mov qword ptr [rsp + 52 ], rcx
.loc 14 8 2
if_2:
mov rcx, qword ptr [rsp + 52 ]
.loc 14 3 2
mov ecx, dword ptr [rcx + 12 ]
mov r8, qword ptr [rsp + 52 ]
.loc 14 2 2
mov r8d, dword ptr [r8 + 8 ]
.loc 14 8 10
cmp ecx, r8d
jl if_2_END
mov rcx, qword ptr [rsp + 52 ]
mov r8, qword ptr [rsp + 52 ]
.loc 14 3 2
mov r8d, dword ptr [r8 + 12 ]
mov r9, rdx
mov eax, 2
mul r8d
mov r8d, eax
mov rdx, r9
.loc 14 10 18
mov dword ptr [rcx + 8 ], r8d
mov rcx, qword ptr [rsp + 52 ]
.loc 14 2 2
mov ecx, dword ptr [rcx + 8 ]
mov dword ptr [rsp ], ecx
.loc 13 5 31
mov ecx, dword ptr [rsp ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, dword ptr [rsp ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rbx, rax
jmp Return_Here_10
.loc 14 11 21
Return_Here_10:
mov rdi, rbx
mov rcx, qword ptr [rsp + 52 ]
.loc 14 3 2
mov ecx, dword ptr [rcx + 12 ]
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
.loc 14 13 37
mov dword ptr [rsp + 20 ], ecx
mov rcx, qword ptr [rsp + 52 ]
.loc 14 4 2
mov rcx, qword ptr [rcx + 16 ]
mov qword ptr [rsp + 12 ], rcx
.loc 14 13 20
mov qword ptr [rsp + 4 ], rdi
.loc 2 38 17
mov esi, 0
cmp esi, dword ptr [rsp + 20 ]
jge while_3_END
while_3:
mov rbp, qword ptr [rsp + 4 ]
.loc 2 39 9
lea rcx, qword ptr [rbp + rsi * 4 ]
mov r12, qword ptr [rsp + 12 ]
mov r8d, dword ptr [r12 + rsi * 4 ]
mov dword ptr [rcx ], r8d
.loc 2 38 33
add esi, 1
cmp esi, dword ptr [rsp + 20 ]
jge while_3_END
jmp while_3
while_3_END:
jmp Return_Here_11
.loc 14 13 9
Return_Here_11:
mov rcx, qword ptr [rsp + 52 ]
.loc 14 17 15
mov qword ptr [rcx + 16 ], rdi
.loc 14 8 2
if_2_END:
mov rcx, qword ptr [rsp + 52 ]
.loc 14 4 2
mov rcx, qword ptr [rcx + 16 ]
mov r8, qword ptr [rsp + 52 ]
.loc 14 3 2
mov r8d, dword ptr [r8 + 12 ]
.loc 14 19 2
lea rcx, qword ptr [rcx + r8 * 4 ]
mov dword ptr [rcx ], 2
mov rcx, qword ptr [rsp + 52 ]
.loc 14 20 6
add dword ptr [rcx + 12 ], 1
.loc 1 6 4
Return_Here_9:
.loc 1 7 2
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 7 2
mov qword ptr [rsp + 60 ], rcx
mov rcx, qword ptr [rsp + 60 ]
.loc 14 24 6
sub dword ptr [rcx + 12 ], 1
.loc 1 7 4
Return_Here_12:
.loc 1 8 13
mov dword ptr [rsp + 68 ], 0
lea rcx, qword ptr [rsp ]
mov rcx, rcx
.loc 14 2 40
add qword ptr [rcx + 0 ], 1
.loc 1 8 9
mov qword ptr [rsp + 72 ], rcx
.loc 14 28 2
if_4:
mov rcx, qword ptr [rsp + 72 ]
.loc 14 3 2
mov ecx, dword ptr [rcx + 12 ]
.loc 14 28 7
cmp dword ptr [rsp + 68 ], ecx
jle if_4_END
.loc 14 29 3
mov ecx, 0
jmp Return_Here_13
.loc 14 28 2
if_4_END:
mov r8, qword ptr [rsp + 72 ]
.loc 14 4 2
mov r8, qword ptr [r8 + 16 ]
.loc 14 31 9
mov r8d, dword ptr [r8 + 0 * 4 ]
mov ecx, r8d
jmp Return_Here_13
.loc 1 8 11
Return_Here_13:
mov eax, ecx
add rsp, 412
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
ret 
add rsp, 412
pop rbx
pop rdi
pop rsi
pop rbp
pop r12
ret 
_Z10Start_Testv_END:


.cfi_endproc 
_Z4mainv_START:
.loc 1 11 1
_Z4mainv:
.cfi_startproc 
.cfi_def_cfa_offset 16
jmp _Z10Start_Testv
.loc 1 13 2
mov eax, 1
ret 
ret 
_Z4mainv_END:


.cfi_endproc 
_ZN13____List_int_10DestructorEP13____List_int__START:
.loc 14 1 1
_ZN13____List_int_10DestructorEP13____List_int_:
.cfi_startproc 
.cfi_def_cfa_offset 16
sub rsp, 8
mov qword ptr [rsp + 0 ], rcx
if_5:
cmp qword ptr [rsp + 0 ], 0
je if_5_END
mov rcx, qword ptr [rsp + 0 ]
mov rcx, qword ptr [rcx + 0 ]
sub rcx, 1
cmp rcx, 1
jge if_5_END
.loc 14 2 26
mov rcx, qword ptr [rsp + 0 ]
add qword ptr [rcx + 0 ], 1
mov qword ptr [rsp ], rcx
mov rcx, qword ptr [rsp + 0 ]
mov qword ptr [rsp ], rcx
.loc 13 18 2
mov rcx, qword ptr [rsp ]
mov edx, 8
call _V19internal_deallocatePhx
.loc 14 2 1
Return_Here_3:
.loc 14 1 11
mov rcx, qword ptr [rsp ]
call _ZN13____List_int_10DestructorEP13____List_int_
if_5_END:
add rsp, 8
ret 
_ZN13____List_int_10DestructorEP13____List_int__END:


.cfi_endproc 
Code_End:
.section .data
.section .debug_abbrev
debug_abbrev:
.byte 1
.byte 17
.byte 1
.byte 37
.byte 14
.byte 19
.byte 5
.byte 3
.byte 14
.byte 16
.byte 23
.byte 27
.byte 14
.byte 17
.byte 1
.byte 18
.byte 6
.byte 0
.byte 0
.byte 2
.byte 36
.byte 0
.byte 3
.byte 8
.byte 62
.byte 11
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 56
.byte 5
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 4
.byte 2
.byte 0
.byte 54
.byte 11
.byte 3
.byte 8
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 5
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 8
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 6
.byte 52
.byte 0
.byte 2
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 7
.byte 46
.byte 0
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 8
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 63
.byte 25
.byte 0
.byte 0
.byte 8
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 9
.byte 5
.byte 0
.byte 2
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 10
.byte 2
.byte 1
.byte 54
.byte 11
.byte 3
.byte 8
.byte 11
.byte 11
.byte 58
.byte 11
.byte 59
.byte 11
.byte 0
.byte 0
.byte 11
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 8
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 0
.section .debug_info
Debug_Info_Start:
.long Debug_Info_End-Debug_Info
Debug_Info:
.word 4
.secrel32 debug_abbrev
.byte 8
.byte 1
.secrel32 .COMPILER_NAME
.word 0x29A
.secrel32 .FILE_NAME
.secrel32 .LINE_TABLE
.secrel32 .DIRECTORY
.quad Code_Start
.long Code_End
_int_START:
.byte 2
.asciz "int"
.byte 5
.byte 4
.byte 2
.byte 3
_short_START:
.byte 2
.asciz "short"
.byte 5
.byte 2
.byte 2
.byte 7
_char_START:
.byte 2
.asciz "char"
.byte 6
.byte 1
.byte 2
.byte 11
_float_START:
.byte 2
.asciz "float"
.byte 4
.byte 4
.byte 2
.byte 15
_double_START:
.byte 2
.asciz "double"
.byte 4
.byte 8
.byte 2
.byte 20
_long_START:
.byte 2
.asciz "long"
.byte 5
.byte 8
.byte 2
.byte 25
_string_START:
.byte 2
.asciz "string"
.byte 6
.byte 1
.byte 2
.byte 29
_12BYTE_POINTER_START:
.byte 4
.byte 1
.asciz "BYTE_POINTER"
.byte 8
.byte 13
.byte 1
.byte 5
.quad _Z10Start_Testv_START
.long _Z10Start_Testv_END
.byte 1
.byte 87
.asciz "_Z10Start_Testv"
.asciz "Start_Test"
.byte 1
.byte 3
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "a"
.byte 1
.byte 4
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 24
.asciz "this_4"
.byte 14
.byte 1
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 32
.asciz "Return_Value0_4"
.byte 14
.byte 4
.long _int_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 40
.asciz "Size_0_4"
.byte 13
.byte 3
.long _int_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "Return_Cast_Type_0_4"
.byte 13
.byte 4
.long _int_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 44
.asciz "this_5"
.byte 14
.byte 1
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 52
.asciz "this_6"
.byte 14
.byte 1
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 60
.asciz "this_7"
.byte 14
.byte 1
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "Return_Value8"
.byte 1
.byte 8
.long _int_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 68
.asciz "i_8"
.byte 14
.byte 27
.long _int_START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 72
.asciz "this_8"
.byte 14
.byte 1
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "_Reference2154126653488"
.byte 1
.byte 4
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "_Reference2154126670128"
.byte 1
.byte 5
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "_Reference2154126687600"
.byte 1
.byte 6
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "_Reference2154126706736"
.byte 1
.byte 7
.long _13____List_int__START-Debug_Info_Start
.byte 6
.byte 2
.byte 145
.byte 0
.asciz "_Reference2154126711728"
.byte 1
.byte 8
.long _13____List_int__START-Debug_Info_Start
.byte 0
.byte 7
.quad _Z4mainv_START
.long _Z4mainv_END
.byte 1
.byte 87
.asciz "_Z4mainv"
.asciz "main"
.byte 1
.byte 11
_13____List_int__START:
.byte 10
.byte 1
.asciz "____List_int_"
.byte 16
.byte 14
.byte 1
.byte 3
.word 0
.asciz "Reference_Count"
.byte 14
.byte 1
.long _long_START-Debug_Info_Start
.byte 3
.word 8
.asciz "Capacity"
.byte 14
.byte 2
.long _int_START-Debug_Info_Start
.byte 3
.word 12
.asciz "Size"
.byte 14
.byte 3
.long _int_START-Debug_Info_Start
.byte 3
.word 16
.asciz "Array"
.byte 14
.byte 4
.long _int_START-Debug_Info_Start
.byte 0
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Template.e"
.DIRECTORY:
.asciz "Tests/IO/"
.section .LINE_TABLE
.LINE_TABLE:
