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
mov ecx, ecx
mov eax, -2
mul ecx
mov ecx, eax
add ecx, 6
mov eax, ecx
ret 
ret 


main:
mov eax, 1
ret 
ret 


