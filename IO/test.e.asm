extern _Z10deallocatePti
extern _Z8allocatei
main:
mov edx, dword 4
call _Z8allocatei
mov r8, rax
mov rcx, r8
mov edx, dword 4
call _Z10deallocatePti
mov eax, dword 0
ret 
ret 


