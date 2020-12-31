.intel_syntax noprefix
.global apple
banana:
mov dword ptr [rcx + 0 ], 1
mov dword ptr [rcx + 4 ], 2
mov dword ptr [rcx + 8 ], 3
mov rax, rcx
ret 
ret 


apple:
mov rcx, rcx
call banana
mov rcx, rax
call banana
mov eax, dword ptr [rax + 8 ]
ret 
ret 


