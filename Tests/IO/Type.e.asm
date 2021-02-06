.intel_syntax noprefix
.global main
.global Start_Test
Fruit:
mov dword ptr [rcx + 0 ], 5
mov rax, rcx
ret 
ret 


Banana:
push rbx
mov dword ptr [rcx + 4 ], 1
mov dword ptr [rcx + 8 ], 2
mov dword ptr [rcx + 12 ], 6
mov rbx, rcx
mov rcx, rbx
call Fruit
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


Start_Test:
sub rsp, 16
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
mov eax, dword ptr [rsp + 0 ]
add rsp, 16
ret 
add rsp, 16
ret 


main:
mov eax, 1
ret 
ret 


