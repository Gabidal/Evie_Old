extern _Z14internal_printPci
a:
dd 12
S0:
dq "Hello World!"
main:
mov r8, S0
mov rcx, r8
mov edx, dword[a]
call _Z14internal_printPci
mov eax, dword 0
ret 
ret 


