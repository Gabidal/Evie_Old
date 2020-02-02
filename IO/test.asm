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
   ; Giving f, 6
  mov [ebp - 24], dword 6
   ; Multiplying d into c
   ; Just directly get address
   ; Giving c, eax
   ; Initializing new register for private  variable c
  mov eax, [ebp - 12]
  imul eax, [ebp - 16]
   ; Adding d into b
   ; Just directly get address
   ; Giving b, edx
   ; Initializing new register for private  variable b
  mov edx, [ebp - 8]
  add edx, [ebp - 16]
   ; Dividing f into e
   ; Giving e, eax
   ; Initializing new register for private  variable e
  mov eax, [ebp - 20]
  xchg eax, eax
   ; Just directly get address
  cdq 
  idiv dword [ebp - 24]
   ; Substracting f into b
   ; Just directly get address
   ; b has already a register to it
  sub edx, [ebp - 24]
    mov [ebp - 4], edx
     ; Return a
    mov eax, edx
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
