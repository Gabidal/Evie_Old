.intel_syntax noprefix
.global main
.global Start_Test
Banana:
mov dword ptr [rcx + 0 ], 3
mov dword ptr [rcx + 4 ], 4
mov rax, rcx
ret 
ret 


Start_Test:
sub rsp, 8
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
mov eax, dword ptr [rsp + 0 ]
add rsp, 8
ret 
add rsp, 8
ret 


main:
mov eax, 1
ret 
ret 


