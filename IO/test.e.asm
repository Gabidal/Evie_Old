main:
mov ecx, 1
mov edx, 2
mov r8d, 3
mov r9d, 4
push 6
push 5
call apple
mov ecx, eax
mov eax, ecx
ret 
ret 


apple:
add ecx, edx
add ecx, r8d
add ecx, r9d
mov edx, [(rsp + 8) ]
add ecx, edx
mov edx, [(rsp + 12) ]
add ecx, edx
mov eax, ecx
ret 
ret 


