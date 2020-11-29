linkage_1:
mov edx, ecx
mov r8d, dword 1
add r8d, edx
mov ecx, r8d
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


linkage_3:
mov edx, ecx
mov edx, ecx
mov edx, dword 0
cmp edx, dword 3
jg while0_END
while0:
mov r8d, edx ;a = i
mov r9d, edx ;i = i
add r9d, dword 1 ;b = i + 1
mov ecx, r9d ; save b
add edx, dword 1 ;i++
cmp edx, dword 3 ;i < 3
jg while0_END
jmp while0
while0_END:
add r8d, ecx
mov eax, r8d
ret 
ret 


main:
mov ecx, dword 1
call linkage_1
mov ecx, eax
mov eax, ecx
ret 
ret 


