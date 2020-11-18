main:
mov ecx, 2
call apple
mov eax, eax
ret 
ret 


apple:
add ecx, 1
mov eax, ecx
ret 
ret 


