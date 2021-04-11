.intel_syntax noprefix
.global main
.global Start_Test
.section .text
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
mov eax, 1
ret 
ret 


.section .data
