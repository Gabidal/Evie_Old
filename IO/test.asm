global main
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

   ; Direct addition
   ; Giving a, eax
   ; Initializing new register for private  variable a
  mov eax, [ebp + 8]
  add eax, dword 1
   ; Giving b, 1
  mov [ebp - 4], dword 1
   ; Direct addition
   ; Giving 2, edx
   ; Initializing new register for number 2
  mov edx, 2
  add edx, dword 5
   ; Direct addition
   ; Giving a, eax
   ; Initializing new register for private  variable a
  mov eax, [ebp + 8]
  add eax, dword 2
mov [ebp - 8], eax
     ; Return c
    mov eax, dword [ebp - 8]
    mov esp, ebp
    pop ebp
    ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
