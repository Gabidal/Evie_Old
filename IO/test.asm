global main
 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

   ; Direct addition
   ; Giving 2, eax
   ; Initializing new register for number 2
  mov eax, 2
  add eax, dword 5
   ; Direct addition
   ; Giving a, edx
   ; Initializing new register for private  variable a
  mov edx, [ebp + 8]
  add edx, dword eax
   ; Direct addition
   ; 2 has already a register to it
  add edx, dword 3
    mov [ebp - 4], edx
     ; Return c
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
