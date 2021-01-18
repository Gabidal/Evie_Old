.intel_syntax noprefix
.global main
.global Start_Test
Start_Test:
mov ecx, 40
call _Z8allocatei
mov rcx, rax
lea rdx, qword ptr [rcx + 1 * 4 ]
mov dword ptr [rdx ], 1
lea rdx, qword ptr [rcx + 1 * 4 ]
mov eax, dword ptr [rdx ]
ret 
ret 


main:
mov eax, 1
ret 
ret 


