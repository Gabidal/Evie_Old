.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Banana:
push rbx
mov rbx, rcx
mov rcx, rbx
call Fruit
mov dword ptr [rbx + 4 ], 1
mov dword ptr [rbx + 8 ], 2
mov dword ptr [rbx + 12 ], 6
mov dword ptr [rbx + 0 ], 5
mov rax, rbx
pop rbx
ret 
pop rbx
ret 


Fruit:
mov dword ptr [rcx + 0 ], 4
ret 


Get_Sugar:
mov eax, dword ptr [rcx + 4 ]
ret 
ret 


is_Banana:
mov rcx, rcx
call Get_Sugar
mov eax, eax
ret 
ret 


Start_Test:
sub rsp, 16
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call is_Banana
mov eax, eax
add rsp, 16
ret 
add rsp, 16
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


.section .data
