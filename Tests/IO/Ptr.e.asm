.intel_syntax noprefix
.global main
.global Start_Test
Start_Test:
sub rsp, 44
mov dword ptr [rsp ], 10
lea rcx, qword ptr [rsp ]
mov qword ptr [rsp + 4 ], rcx
lea rcx, qword ptr [rsp + 4 ]
mov qword ptr [rsp + 12 ], rcx
mov rcx, qword ptr [rsp + 4 ]
mov ecx, dword ptr [rcx ]
mov eax, ecx
add rsp, 44
ret 
lea rcx, qword ptr [rsp + 12 ]
mov qword ptr [rsp + 20 ], rcx
lea rcx, qword ptr [rsp + 20 ]
mov qword ptr [rsp + 28 ], rcx
lea rcx, qword ptr [rsp + 28 ]
mov qword ptr [rsp + 36 ], rcx
lea rcx, qword ptr [rsp + 36 ]
mov rcx, rcx
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov rcx, qword ptr [rcx ]
mov ecx, dword ptr [rcx ]
mov eax, ecx
add rsp, 44
ret 
mov rcx, 123
mov ecx, dword ptr [rcx ]
mov eax, ecx
add rsp, 44
ret 
add rsp, 44
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


