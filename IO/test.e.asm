.intel_syntax noprefix
.global apple
.global main
banana:
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 2
mov dword ptr [rcx + 8 ], 3
mov rax, rcx
ret 
ret 


main:
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call banana
mov rax, rax
add rsp, 24
ret 
add rsp, 24
ret 


apple:
mov rcx, rcx
call banana
mov rcx, rax
call banana
mov eax, dword ptr [rax + 0 ]
ret 
ret 


