.intel_syntax noprefix
.global main
main:
sub rsp, 24
mov rcx, qword ptr [rsp + 0 ]
mov qword ptr [rsp + 12 + 0 ], rcx
mov ecx, dword ptr [rsp + 8 ]
mov dword ptr [rsp + 12 + 8 ], ecx
lea rcx, qword ptr [rsp + 12 ]
mov rax, rcx
add rsp, 24
ret 
add rsp, 24
ret 


