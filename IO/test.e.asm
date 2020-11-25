linkage_1:
mov edx, dword 1
add edx, ecx
mov ecx, edx
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


