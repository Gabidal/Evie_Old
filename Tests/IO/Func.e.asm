.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
call Start_Test
mov eax, 1
ret 
ret 


foo:
mov eax, 5
ret 
ret 


Start_Test:
lea rcx, qword ptr [rip + foo ]
mov rcx, rcx
call rcx
mov eax, eax
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


.section .data
