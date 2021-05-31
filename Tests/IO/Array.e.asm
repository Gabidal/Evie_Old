.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
sub rsp, 8
mov ecx, 10
call ____Allocate_int_
mov qword ptr [rsp ], rax
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov r8, qword ptr [rcx + 0 * 8 ]
lea r8, qword ptr [r8 + 1 * 4 ]
mov dword ptr [r8 ], 1
mov rcx, qword ptr [rcx + 0 * 8 ]
mov ecx, dword ptr [rcx + 1 * 4 ]
mov ecx, ecx
mov eax, ecx
add rsp, 8
ret 
add rsp, 8
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


____Allocate_int_:
mov r8, rdx
mov eax, 4
mul ecx
mov ecx, eax
mov rdx, r8
mov ecx, ecx
call _V17internal_allocatex_rPh
mov rax, rax
ret 
ret 


.section .data
