extern _Z14internal_printPci
main:
sub rsp, dword 1
mov r8d, dword 1
mov byte [rsp ], byte 2
lea r9, qword [rsp ]
mov rcx, r9
mov edx, r8d
call _Z14internal_printPci
mov eax, dword 0
add rsp, dword 1
ret 
add rsp, dword 1
ret 


