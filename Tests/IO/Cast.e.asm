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
ret 


Start_Test:
sub rsp, 8
call test_all_format_casts
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Mid
movd xmm0, dword ptr [rsp + 4 ]
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


