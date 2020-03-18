global _start
_start: 
__start: 
call main
mov eax , eax 
ret
 
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 16
mov eax , dword 0
mov dword [ebp  - 4], eax 
mov eax , dword 0
mov dword [ebp  - 8], eax 
mov eax , dword 0
mov dword [ebp  - 12], eax 
mov eax , dword 0
mov dword [ebp  - 16], eax 
_while4: 
mov ebx , dword [ebp  - 4]
mov ecx , dword 10
cmp ebx , ecx 
jnl _while4END
mov edx , dword [ebp  - 4]
mov edi , dword [ebp  - 16]
mov esi , dword [ebp  - 12]
mov eax , dword [(ebp  - 8) + esi  * 4]
mov ebx , dword [(ebp  - 12) + edi  * 4]
add eax , ebx 
mov ecx , dword [(ebp  - 16) + edx  * 4]
sub eax , ecx 
mov edx , dword [ebp  - 8]
mov dword [(ebp  - 4) + edx  * 4], eax 
jmp _while4
_while4END: 
