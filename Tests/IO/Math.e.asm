.intel_syntax noprefix
.global main
.global Start_Test
sum:
add ecx, 3
mov eax, ecx
ret 
ret 


Start_Test:
push rbx
mov ecx, 1
add ecx, 2
mov ebx, ecx
mov ecx, ebx
call sum
mov ecx, eax
mov r8d, ecx
mov eax, r8d
mul ebx
mov r8d, eax
mov r8d, r8d
mov r9d, r8d
xor edx, edx
mov eax, r9d
div ecx
mov r9d, eax
mov r9d, r9d
add r9d, ebx
add r9d, ecx
sub r9d, r8d
mov eax, r9d
pop rbx
ret 
pop rbx
ret 


main:
mov eax, 1
ret 
ret 


