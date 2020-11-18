main:
mov ecx, 1
mov edx, 2
mov r8d, 3
mov r9d, 4
push 6
push 5
call apple
mov eax, eax
ret 
ret 


apple:
add ecx, edx
add ecx, r8d
add ecx, r9d
mov edx, [() ]
add ecx, edx
mov edx, [() ]
add ecx, edx
mov eax, ecx
ret 
ret 


