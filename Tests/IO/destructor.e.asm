.intel_syntax noprefix
.global Start_Test
.global main
.section .text
main:
mov eax, 1
ret 
ret 


Start_Test:
push rbx
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
mov ebx, r8d
mov rcx, rcx
call Destructor
mov eax, ebx
add rsp, 16
pop rbx
ret 
add rsp, 16
pop rbx
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
if34:
cmp rcx, 0
je if34_END
sub r8, 1
cmp r8, 1
jge if34_END
mov rcx, rcx
call ____Deallocate_foo_
if34_END:
ret 


.section .data
