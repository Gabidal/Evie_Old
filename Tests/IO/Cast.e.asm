.intel_syntax noprefix
.global main
.global Start_Test
Base:
mov dword ptr [rcx + 0 ], 0
mov rax, rcx
ret 
ret 


Mid:
push rbx
mov rbx, rcx
mov rcx, rbx
call Base
mov dword ptr [rbx + 0 ], 1
mov ecx, 1074261268
mov dword ptr [rbx + 4 ], ecx
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


test_all_format_casts:
mov ecx, 1
cvtsi2ss xmm0, ecx
movss xmm0, xmm0
cvtsi2sd xmm1, ecx
movsd xmm1, xmm1
cvttss2si r8d, xmm0
mov ecx, r8d
cvttsd2si r8d, xmm1
mov ecx, r8d
cvtsd2ss xmm1, xmm1
movss xmm0, xmm1
cvtss2sd xmm0, xmm0
movsd xmm1, xmm0
ret 


Start_Test:
sub rsp, 8
call test_all_format_casts
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Mid
movss xmm0, dword ptr [rsp + 4 ]
cvttss2si ecx, xmm0
mov eax, ecx
add rsp, 8
ret 
add rsp, 8
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.byte 1 "Tests/IO/Cast.e"
.byte 2 "../../IO/cstd.e"
.byte 3 "sys.e"
.byte 4 "win32.asm.obj"
.byte 5 "asm.h"
.byte 6 "win32.asm"
.section .debug_abbrev,"",@progbits
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
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 63
.byte 25
.byte 0
.byte 0
.byte 3
.byte 52
.byte 0
.byte 2
.byte 24
.byte 3
.byte 14
.byte 58
.byte 11
.byte 59
.byte 11
.byte 73
.byte 19
.byte 0
.byte 0
.byte 4
.byte 36
.byte 0
.byte 3
.byte 14
.byte 62
.byte 11
.byte 11
.byte 11
.byte 0
.byte 0
.byte 0
.section .debug_info,"",@progbits
:
.long .Ldebug_info_end0-.Ldebug_info_start0
:
.word 4
.long .debug_abbrev
.byte 8
.byte 1
.byte 1
.word 0x666
.long .FILE_NAME
.long .LINE_TABLE
.long .DIRECTORY
.quad .Code_Start
.long .Code_End-.Code_Start
.byte 4
.quad .memcpy_START
.long .memcpy_END-.memcpy_START
.byte 1
.byte 87
.long .memcpy_NAME
.byte 0
.byte 36
.long ._func_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .dest_NAME
.byte 2
.byte 36
.quad ._dest_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .source_NAME
.byte 2
.byte 36
.quad ._source_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .Size_NAME
.byte 2
.byte 36
.quad ._int_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .test_all_format_casts_START
.long .test_all_format_casts_END-.test_all_format_casts_START
.byte 1
.byte 87
.long .test_all_format_casts_NAME
.byte 1
.byte 17
.long ._func_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .i_NAME
.byte 1
.byte 18
.quad ._int_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .a_NAME
.byte 1
.byte 20
.quad ._float_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .b_NAME
.byte 1
.byte 21
.quad ._double_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .Start_Test_START
.long .Start_Test_END-.Start_Test_START
.byte 1
.byte 87
.long .Start_Test_NAME
.byte 2
.byte 30
.long ._export_int_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .m_NAME
.byte 1
.byte 32
.quad ._Mid_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .main_START
.long .main_END-.main_START
.byte 1
.byte 87
.long .main_NAME
.byte 3
.byte 36
.long ._export_int_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .int_START
.long .int_END-.int_START
.byte 1
.byte 87
.long .int_NAME
.byte 4
.byte 3
.long ._int_cpp_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 3
.quad ._int_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .short_START
.long .short_END-.short_START
.byte 1
.byte 87
.long .short_NAME
.byte 5
.byte 7
.long ._short_cpp_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 7
.quad ._short_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .char_START
.long .char_END-.char_START
.byte 1
.byte 87
.long .char_NAME
.byte 6
.byte 11
.long ._char_cpp_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 11
.quad ._char_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .float_START
.long .float_END-.float_START
.byte 1
.byte 87
.long .float_NAME
.byte 7
.byte 15
.long ._float_cpp_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 15
.quad ._float_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .double_START
.long .double_END-.double_START
.byte 1
.byte 87
.long .double_NAME
.byte 8
.byte 20
.long ._double_cpp_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 20
.quad ._double_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .long_START
.long .long_END-.long_START
.byte 1
.byte 87
.long .long_NAME
.byte 9
.byte 25
.long ._long_cpp_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 25
.quad ._long_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .string_START
.long .string_END-.string_START
.byte 1
.byte 87
.long .string_NAME
.byte 10
.byte 29
.long ._string_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 2
.byte 29
.quad ._string_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .Base_START
.long .Base_END-.Base_START
.byte 1
.byte 87
.long .Base_NAME
.byte 11
.byte 3
.long ._Base_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 1
.byte 3
.quad ._Base_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .Mid_START
.long .Mid_END-.Mid_START
.byte 1
.byte 87
.long .Mid_NAME
.byte 12
.byte 7
.long ._Mid_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 1
.byte 7
.quad ._Mid_START-.Debug_Info_Start
.byte 0
.byte 4
.quad .Top_START
.long .Top_END-.Top_START
.byte 1
.byte 87
.long .Top_NAME
.byte 13
.byte 12
.long ._Top_START-.Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long .this_NAME
.byte 1
.byte 12
.quad ._Top_START-.Debug_Info_Start
.byte 0
.byte 0
.section .debug_str,"MS",@progbits,1
:
.ascii Evie engine 3.0.0 https://github.com/Gabidal/Evie
:
.ascii Tests/IO/Cast.e
:
.ascii Tests/IO/
:
.ascii int
:
.ascii size
:
.ascii short
:
.ascii size
:
.ascii char
:
.ascii size
:
.ascii float
:
.ascii size
:
.ascii format
:
.ascii double
:
.ascii size
:
.ascii format
:
.ascii long
:
.ascii size
:
.ascii string
:
.ascii size
:
.ascii memcpy
:
.ascii dest
:
.ascii source
:
.ascii Size
:
.ascii Base
:
.ascii Type
:
.ascii Mid
:
.ascii Type
:
.ascii feature
:
.ascii Top
:
.ascii Type
:
.ascii feature
:
.ascii feature
:
.ascii test_all_format_casts
:
.ascii i
:
.ascii a
:
.ascii b
:
.ascii Start_Test
:
.ascii m
:
.ascii main
:
.ascii int
:
.ascii this
:
.ascii short
:
.ascii this
:
.ascii char
:
.ascii this
:
.ascii float
:
.ascii this
:
.ascii double
:
.ascii this
:
.ascii long
:
.ascii this
:
.ascii string
:
.ascii this
:
.ascii Base
:
.ascii this
:
.ascii Mid
:
.ascii this
:
.ascii Top
:
.ascii this
