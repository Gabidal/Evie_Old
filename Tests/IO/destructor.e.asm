.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
mov eax, 1
ret 
ret 


Start_Test:
sub rsp, 16
call ____New_foo_
mov rcx, rax
call foo
mov rcx, qword ptr [rax + 0 ]
mov qword ptr [rsp + 0 ], rcx
mov rcx, qword ptr [rax + 8 ]
mov qword ptr [rsp + 8 ], rcx
lea rcx, qword ptr [rsp ]
mov rcx, rcx
add qword ptr [rcx + 0 ], 1
mov rcx, rcx
mov r8d, dword ptr [rcx + 12 ]
mov r8d, r8d
mov eax, r8d
add rsp, 16
ret 
mov rcx, rcx
call Destructor
add rsp, 16
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


foo:
mov dword ptr [rcx + 12 ], 1
mov dword ptr [rcx + 8 ], 2
mov rax, rcx
ret 
ret 


____Deallocate_foo_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


____New_foo_:
mov ecx, 8
call _V17internal_allocatex_rPh
lea rcx, qword ptr [rax ]
mov rax, rcx
ret 
ret 


Destructor:
if42:
mov rcx, rcx
call ____Deallocate_foo_
if42_END:
ret 


.section .data
