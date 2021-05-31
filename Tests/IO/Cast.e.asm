.intel_syntax noprefix
.global main
.global Start_Test
.section .text
test_all_format_casts:
ret 


Start_Test:
sub rsp, 16
call test_all_format_casts
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Mid
movss xmm0, dword ptr [rsp + 12 ]
cvttss2si ecx, xmm0
mov eax, ecx
add rsp, 16
ret 
add rsp, 16
ret 


main:
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


____Deallocate_BYTE_POINTER_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


Base:
mov dword ptr [rcx + 8 ], 0
mov rax, rcx
ret 
ret 


____Deallocate_Base_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


Mid:
push rbx
mov rbx, rcx
mov rcx, rbx
call Base
mov dword ptr [rbx + 8 ], 1
mov ecx, 1074261268
mov dword ptr [rbx + 12 ], ecx
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


____Deallocate_Mid_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


____Deallocate_Top_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


.section .data
