

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
testFalse:
ret

testTrue:
mov eax , dword [a]
mov [a] , eax 
mov ebx , dword [c]
add eax , ebx 
mov [a], eax 
mov ecx , dword [b]
cmp eax , ecx 
jge else0
call testFalse
jmp end0
else0: 
call testTrue
end0: 
ret

main:
call testTrue
call testFalse
ret



[section .data]
a dd 23
b dd 25
c dd 1
