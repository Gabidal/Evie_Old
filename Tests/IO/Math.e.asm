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
mov eax, -2
mul r8d
mov r8d, eax
add r8d, 6
mov eax, r8d
ret 
mov ecx, ecx
mov eax, -2
mul ecx
mov ecx, eax
add ecx, 6
mov eax, ecx
ret 
ret 


main:
call Start_Test
mov eax, 1
ret 
ret 


