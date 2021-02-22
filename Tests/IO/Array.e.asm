.intel_syntax noprefix
.global main
.global Start_Test
Start_Test:
mov ecx, 40
call _Z8allocatei
mov rcx, rax
lea r8, qword ptr [rcx + 1 * 4 ]
mov dword ptr [r8 ], 1
mov ecx, dword ptr [rcx + 1 * 4 ]
mov ecx, ecx
mov eax, ecx
ret 
ret 


main:
mov eax, 1
ret 
ret 


