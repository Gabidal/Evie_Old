.intel_syntax noprefix
.global main
.global Start_Test
Banana:
mov dword ptr [rcx + 4 ], 3
mov dword ptr [rcx + 8 ], 4
mov dword ptr [rcx + 12 ], 7
mov dword ptr [rcx + 0 ], 1
mov rax, rcx
ret 
ret 


Start_Test:
sub rsp, 16
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
mov eax, dword ptr [rsp + 4 ]
add rsp, 16
ret 
add rsp, 16
ret 


main:
mov eax, 1
ret 
ret 


