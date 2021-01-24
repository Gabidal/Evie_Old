.intel_syntax noprefix
.global main
.global Start_Test
sum:
add ecx, 3
mov eax, ecx
ret 
ret 


Start_Test:
mov ecx, 3
call sum
mov ecx, eax
mov r8d, ecx
mov eax, 3
mul r8d
mov r8d, eax
xor edx, edx
mov eax, r8d
div ecx
mov r8d, eax
add r8d, 3
add r8d, ecx
mov ecx, ecx
mov eax, -3
mul ecx
mov ecx, eax
add r8d, ecx
mov eax, r8d
ret 
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


