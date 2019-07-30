

[section .text]
global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

[section .code]
test:
mov eax , dword [a]
mov ebx , dword [b]
cmp eax , ebx 
 je else11
 mov [a] , ebx 
 jmp end11
 else11: 
 mov edx , dword [c]
 mov eax , dword [a]
 cmp edx , eax 
  jge else22
  mov [c] , eax 
  jmp end22
  else22: 
  cmp edx , eax 
   jge else33
   cmp edx , eax 
    jge else44
    mov [c] , eax 
    jmp end44
    else44: 
    mov [c] , ebx 
    end44: 
   jmp end34
   else34: 
   mov [c] , ebx 
   end34: 
  end22: 
 cmp edx , eax 
  je else25
  mov [c] , edx 
  jmp end25
  else25: 
  mov [c] , edx 
  add edx , edx 
  mov [c], edx 
  end25: 
 end11: 
ret

main:
call test
ret



[section .data]
a dd 23
b dd 25
c dd 1
