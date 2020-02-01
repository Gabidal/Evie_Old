global main
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

   ; Giving a, 1
  mov [ebp - 4], dword 1
   ; Giving b, 2
  mov [ebp - 8], dword 2
   ; Giving c, 3
  mov [ebp - 12], dword 3
   ; Giving d, 4
  mov [ebp - 16], dword 4
   ; Giving e, 5
  mov [ebp - 20], dword 5
   ; Dividing f into e
   ; Giving e, eax
   ; Initializing new register for private  variable e
  mov eax, [ebp - 20]
  xchg eax, eax
   ; Just directly get address
  cdq 
  idiv dword [ebp + 8]
   ; Saving f into e
   ; Giving f, edx
   ; Initializing new register for private  variable f
  mov edx, [ebp + 8]
  mov [ebp - 20], dword edx
     ; Return a
    mov eax, dword [ebp - 4]
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
