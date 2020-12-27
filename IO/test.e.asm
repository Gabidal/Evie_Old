.intel_syntax noprefix
.global main
banana:
mov dword ptr [rcx + 0 ], dword ptr 1
mov dword ptr [rcx + 4 ], dword ptr 2
mov dword ptr [rcx + 8 ], dword ptr 3
mov rax, rcx
ret 
ret 


main:
ret 


