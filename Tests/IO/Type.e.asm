.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Fruit:
mov dword ptr [rcx + 8 ], 4
ret 


Get_Sugar:
mov eax, dword ptr [rcx + 12 ]
ret 
ret 


is_Banana:
mov rcx, rcx
call Get_Sugar
mov eax, eax
ret 
ret 


Start_Test:
sub rsp, 24
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call is_Banana
mov eax, eax
add rsp, 24
ret 
add rsp, 24
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


char:
mov rax, rcx
ret 
ret 


Banana:
push rbx
mov rbx, rcx
mov rcx, rbx
call Fruit
mov dword ptr [rbx + 12 ], 1
mov dword ptr [rbx + 16 ], 2
mov dword ptr [rbx + 20 ], 6
mov dword ptr [rbx + 8 ], 5
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


.section .data
