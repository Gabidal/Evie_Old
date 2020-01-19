global main
 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

    if0: 
   ; Comparing a and 10
   ; Just directly get name of the number
   ; Giving 10, eax
  mov eax, 10
  cmp [ebp + 8], eax
    jne  else1
       ; Return 4
      mov eax, 4
      mov esp, ebp
      pop ebp
      ret 

    jmp else1END
    if0END: 
    jmp else1END
    else1: 
       ; Return 3
      mov eax, 3
      mov esp, ebp
      pop ebp
      ret 

    else1END: 
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function apple
apple: 
 ; Making stack frame 
push ebp
mov ebp, esp

     ; Return 4
    mov eax, 4
    mov esp, ebp
    pop ebp
    ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function main
main: 
  mov eax, 4
  ret 
section .bss
section .data
