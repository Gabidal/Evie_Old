.intel_syntax noprefix
.section .text
Code_Start:
.global main
.global Start_Test
Base_START:
Base:
mov dword ptr [rcx + 0 ], 0
mov rax, rcx
ret 
ret 
Base_END:


Mid_START:
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
Mid_END:


test_all_format_casts_START:
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
test_all_format_casts_END:


Start_Test_START:
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
Start_Test_END:


main_START:
main:
mov eax, 1
ret 
ret 
main_END:


Code_End:
.file 1 "Tests/IO/Cast.e"
.file 2 "../../IO/cstd.e"
.file 3 "sys.e"
.file 4 "win32.asm.obj"
.file 5 "asm.h"
.file 6 "win32.asm"
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
.byte 46
.byte 1
.byte 17
.byte 1
.byte 18
.byte 6
.byte 64
.byte 24
.byte 110
.byte 14
.byte 3
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
.section .debug_info
.long Debug_Info_End-Debug_Info_Start
Debug_Info_Start:
.word 4
.long debug_abbrev
.byte 8
.byte 1
.long .COMPILER_NAME
.word 0x666
.long .FILE_NAME
.long .LINE_TABLE
.long .DIRECTORY
.quad Code_Start
.long Code_End-Code_Start
.byte 2
.quad test_all_format_casts_START
.long test_all_format_casts_END-test_all_format_casts_START
.byte 1
.byte 87
.long test_all_format_casts_NAME
.long test_all_format_casts_NAME
.byte 0
.byte 17
.long _func_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long i_NAME
.byte 1
.byte 18
.quad _int_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long a_NAME
.byte 1
.byte 20
.quad _float_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long b_NAME
.byte 1
.byte 21
.quad _double_START-Debug_Info_Start
.byte 0
.byte 2
.quad Base_START
.long Base_END-Base_START
.byte 1
.byte 87
.long Base_NAME
.long Base_NAME
.byte 1
.byte 3
.long _Base_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long this_NAME
.byte 1
.byte 3
.quad _Base_START-Debug_Info_Start
.byte 0
.byte 2
.quad Mid_START
.long Mid_END-Mid_START
.byte 1
.byte 87
.long Mid_NAME
.long Mid_NAME
.byte 2
.byte 7
.long _Mid_START-Debug_Info_Start
.byte 3
.byte 2
.byte 145
.byte 0
.long this_NAME
.byte 1
.byte 7
.quad _Mid_START-Debug_Info_Start
.byte 0
_int_START:
.byte 4
.quad int_NAME
.byte 62
.byte 4
_short_START:
.byte 4
.quad short_NAME
.byte 62
.byte 2
_char_START:
.byte 4
.quad char_NAME
.byte 62
.byte 1
_float_START:
.byte 4
.quad float_NAME
.byte 62
.byte 4
_double_START:
.byte 4
.quad double_NAME
.byte 62
.byte 8
_long_START:
.byte 4
.quad long_NAME
.byte 62
.byte 8
_string_START:
.byte 4
.quad string_NAME
.byte 62
.byte 1
_Base_START:
.byte 4
.byte 1
.long Base_NAME
.byte 4
.byte 1
.byte 3
.byte 5
.long Type_NAME
.quad _type_START-Debug_Info_Start
.byte 1
.byte 4
.byte 0
.byte 1
_Mid_START:
.byte 4
.byte 1
.long Mid_NAME
.byte 8
.byte 1
.byte 7
.byte 5
.long Type_NAME
.quad _Base_START-Debug_Info_Start
.byte 1
.byte 4
.byte 0
.byte 1
.byte 5
.long feature_NAME
.quad _Base_START-Debug_Info_Start
.byte 1
.byte 9
.byte 4
.byte 1
_Top_START:
.byte 4
.byte 1
.long Top_NAME
.byte 12
.byte 1
.byte 12
.byte 5
.long Type_NAME
.quad _Mid_START-Debug_Info_Start
.byte 1
.byte 4
.byte 0
.byte 1
.byte 5
.long feature_NAME
.quad _Mid_START-Debug_Info_Start
.byte 1
.byte 9
.byte 4
.byte 1
.byte 5
.long feature_NAME
.quad _Mid_START-Debug_Info_Start
.byte 1
.byte 14
.byte 8
.byte 1
_func_START:
.byte 4
.quad func_NAME
.byte 1
.byte 0
_type_START:
.byte 4
.quad type_NAME
.byte 1
.byte 0
.byte 0
Debug_Info_End:
.section .debug_str
.COMPILER_NAME:
.asciz "Evie engine 3.0.0 https://github.com/Gabidal/Evie"
.FILE_NAME:
.asciz "Tests/IO/Cast.e"
.DIRECTORY:
.asciz "Tests/IO/"
int_NAME:
.asciz "int"
size_NAME:
.asciz "size"
short_NAME:
.asciz "short"
char_NAME:
.asciz "char"
float_NAME:
.asciz "float"
format_NAME:
.asciz "format"
double_NAME:
.asciz "double"
long_NAME:
.asciz "long"
string_NAME:
.asciz "string"
Base_NAME:
.asciz "Base"
Type_NAME:
.asciz "Type"
Mid_NAME:
.asciz "Mid"
feature_NAME:
.asciz "feature"
Top_NAME:
.asciz "Top"
test_all_format_casts_NAME:
.asciz "test_all_format_casts"
i_NAME:
.asciz "i"
a_NAME:
.asciz "a"
b_NAME:
.asciz "b"
this_NAME:
.asciz "this"
func_NAME:
.asciz "func_NAME"
type_NAME:
.asciz "type_NAME"
.section .LINE_TABLE
.LINE_TABLE:
