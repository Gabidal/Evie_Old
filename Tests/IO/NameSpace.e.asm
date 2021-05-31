.intel_syntax noprefix
.global main
.global Start_Test
.section .text
Start_Test:
push rbx
sub rsp, 16
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Banana
lea rcx, qword ptr [rsp ]
mov rcx, rcx
call Get
mov ebx, eax
lea rcx, qword ptr [rsp ]
mov rcx, rcx
mov edx, 1
call Set
add ebx, eax
mov ecx, ebx
mov r8d, dword ptr [rip + Banana_Y ]
mov r9d, dword ptr [rip + Apple_Y ]
add r8d, r9d
sub r8d, ecx
mov eax, r8d
add rsp, 16
pop rbx
ret 
add rsp, 16
pop rbx
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


Get:
mov ecx, dword ptr [rip + Banana_Y ]
add ecx, 1
mov eax, ecx
ret 
ret 


char:
mov rax, rcx
ret 
ret 


____Deallocate_BYTE_POINTER_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


Banana:
mov rax, rcx
ret 
ret 


____Deallocate_Banana_:
mov rcx, rcx
mov edx, 8
call _V19internal_deallocatePhx
ret 


Set:
add edx, 1
mov eax, edx
ret 
ret 


.section .data
Banana_Y:
.long 2
Apple_X:
.long 2
Apple_Y:
.long 3
