.intel_syntax noprefix
.global _Z4mainv
.global _Z10Start_Testv
.section .text
_Z10Start_Testv:
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
mov rcx, 1234
mov rcx, qword ptr [rcx ]
mov ecx, dword ptr [rcx ]
mov eax, ecx
add rsp, 44
ret 
add rsp, 44
ret 


_Z4mainv:
sub rsp, 88
mov dword ptr [rsp ], 10
lea rcx, qword ptr [rsp ]
mov qword ptr [rsp + 4 ], rcx
lea rcx, qword ptr [rsp + 4 ]
mov qword ptr [rsp + 12 ], rcx
jmp Return_Here_66
lea rcx, qword ptr [rsp + 12 ]
mov qword ptr [rsp + 20 ], rcx
lea rcx, qword ptr [rsp + 20 ]
mov qword ptr [rsp + 28 ], rcx
lea rcx, qword ptr [rsp + 28 ]
mov qword ptr [rsp + 36 ], rcx
lea rcx, qword ptr [rsp + 36 ]
mov rcx, rcx
jmp Return_Here_66
mov rcx, 123
jmp Return_Here_66
mov rcx, 1234
jmp Return_Here_66
Return_Here_66:
mov eax, 1
add rsp, 88
ret 
add rsp, 88
ret 


.section .data
