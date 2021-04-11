.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
sub rsp, 8
mov ecx, 4
mov eax, 10
mul ecx
mov ecx, eax
mov ecx, ecx
call _Z8allocatei
mov qword ptr [rsp ], rax
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov r8, qword ptr [rcx + 0 * 8 ]
lea r8, qword ptr [r8 + 1 * 4 ]
mov dword ptr [r8 ], 1
mov rcx, qword ptr [rcx + 0 * 8 ]
mov ecx, dword ptr [rcx + 1 * 4 ]
mov ecx, ecx
mov eax, ecx
add rsp, 8
ret 
add rsp, 8
ret 


main:
mov eax, 1
ret 
ret 


.section .data
