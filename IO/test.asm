global main
 ; Function main
main: 
 ; Making stack frame 
push r8
mov r8, r7

   ; Giving a, 1
  mov [r7 - 4], dword 1
   ; Giving b, 2
  mov [r7 - 8], dword 2
   ; Giving c, 3
  mov [r7 - 12], dword 3
   ; Giving d, 4
  mov [r7 - 16], dword 4
   ; Giving e, 5
  mov [r7 - 20], dword 5
   ; Giving f, 6
  mov [r7 - 24], dword 6
   ; Multiplying d into c
   ; Just directly get address
   ; Giving c, r1
   ; Initializing new register for private  variable c
  mov r1, [r7 - 12]
  imul r1, [r7 - 16]
   ; Adding c into b
   ; There is already register for it, use it
   ; Giving b, r4
   ; Initializing new register for private  variable b
  mov r4, [r7 - 8]
  add r4, r1
   ; Dividing f into e
   ; Giving e, r1
   ; Initializing new register for private  variable e
  mov r1, [r7 - 20]
   ; Just directly get address
  cdq 
  idiv dword [r7 - 24]
   ; Substracting e into b
   ; There is already register for it, use it
   ; b has already a register to it
  sub r4, r1
    mov [r7 - 4], r4
     ; Return a
    mov r1, r4
    mov r7, r8
    pop r8
    ret 

 ; Ending stack frame 
mov r7, r8
pop r8
 ; Returning 
ret

section .bss
section .data
