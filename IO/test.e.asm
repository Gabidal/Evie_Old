linkage_1:
mov edx, ecx
mov ebp, dword 1
add ebp, edx
mov ecx, ebp
add edx, ecx
mov eax, edx
ret 
ret 


linkage_2:
mov edx, ecx
mov edx, dword 1
add ecx, edx
mov eax, ecx
ret 
ret 


main:
mov ecx, dword 1
call linkage_1
mov ecx, eax
mov eax, ecx
ret 
ret 


