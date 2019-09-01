

section .text

global _start
_start:
call main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

 gout:
  ;making a function stack frame
  push ebp
  mov ebp, esp
  sub esp, 8
  
  ;name is now an Variable.
  mov eax , [ebp+8]
  mov [ gout.name], eax 
  
  ;size is now an Variable.
  mov ebx , [ebp+12]
  mov [ gout.size], ebx 

  push eax
  mov eax, 4
  mov ebx, 1
  mov ecx, dword [gout.name]
  mov edx, dword [gout.size]
  int 80h
  mov [carry], eax
  pop eax


  ;making a stack frame end
  mov esp, ebp
  pop ebp

 gin:
   ;making a function stack frame
   push ebp
   mov ebp, esp
   sub esp, 8
   
   ;name is now an Variable.
   mov ecx , [ebp+8]
   mov [ gin.name], ecx 
   
   ;size is now an Variable.
   mov edx , [ebp+12]
   mov [ gin.size], edx 

   push eax
   mov eax, 3
   mov ebx, 2
   mov ecx, dword [gin.name]
   mov edx, dword [gin.size]
   int 80h
   mov [carry], eax
   pop eax


   ;making a stack frame end
   mov esp, ebp
   pop ebp

 file.open:
    ;making a function stack frame
    push ebp
    mov ebp, esp
    sub esp, 4
    
    ;name is now an Variable.
    mov eax , [ebp+8]
    mov [ file.open.name], eax 

    push eax
    mov eax, 5
    mov ebx, dword [file.open.name]
    mov ecx, 0
    mov edx, 0777
    int 80h
    mov [header], eax
    pop eax


    ;making a stack frame end
    mov esp, ebp
    pop ebp

 file.make:
     ;making a function stack frame
     push ebp
     mov ebp, esp
     sub esp, 4
     
     ;name is now an Variable.
     mov ebx , [ebp+8]
     mov [ file.make.name], ebx 

     push eax
     mov eax, 8
     mov ebx, dword [file.make.name]
     mov ecx, 0777
     mov edx, 0
     int 80h
     mov [header], eax
     pop eax


     ;making a stack frame end
     mov esp, ebp
     pop ebp

 file.close:
      ;making a function stack frame
      push ebp
      mov ebp, esp

      push eax
      mov eax, 6
      mov ebx, dword [header]
      mov ecx, 0
      mov edx, 0
      int 80h
      mov [header], eax
      pop eax


      ;making a stack frame end
      mov esp, ebp
      pop ebp

 file.write:
       ;making a function stack frame
       push ebp
       mov ebp, esp
       sub esp, 8
       
       ;text is now an Variable.
       mov ecx , [ebp+8]
       mov [ file.write.text], ecx 
       
       ;size is now an Variable.
       mov edx , [ebp+12]
       mov [ file.write.size], edx 

       push eax
       mov eax, 4
       mov ebx, 1
       mov ecx, dword [file.write.text]
       mov edx, dword [file.write.size]
       int 80h
       mov [carry], eax
       pop eax


       ;making a stack frame end
       mov esp, ebp
       pop ebp

 file.read:
        ;making a function stack frame
        push ebp
        mov ebp, esp
        sub esp, 8
        
        ;name is now an Variable.
        mov eax , [ebp+8]
        mov [ file.read.name], eax 
        
        ;size is now an Variable.
        mov ebx , [ebp+12]
        mov [ file.read.size], ebx 

        push eax
        mov eax, 3
        mov ebx, dword [header]
        mov ecx, dword [file.read.name]
        mov edx, dword [file.read.size]
        int 80h
        mov [carry], eax
        pop eax


        ;making a stack frame end
        mov esp, ebp
        pop ebp

 main:
         ;making a function stack frame
         push ebp
         mov ebp, esp
         cmp , 
         jmp else11
          ;Functions Parameters
          push  .nullnullTokennullnull
          
          ;Call the function
          call gout

          ;making a stack frame end
          mov esp, ebp
          pop ebp

         
jmp end11
         
else11: 
          ;making a stack frame start          
push ebp
          mov ebp, esp

          ;Functions Parameters
          push  .nullnullTokennullnull
          
          ;Call the function
          call gout
         
end11: 

          ;making a stack frame end
          mov esp, ebp
          pop ebp


         ;making a stack frame end
         mov esp, ebp
         pop ebp



section .data

return dd 0
header dd 0
carry dd 0
true dd 1
false dd 0
 gout.name dd 0
 gout.size dd 0
 gin.name dd 0
 gin.size dd 0
 file.open.name dd 0
 file.make.name dd 0
 file.write.text dd 0
 file.write.size dd 0
 file.read.name dd 0
 file.read.size dd 0
file.read.msg db "hello world!"
file.read.msg.size dd 12
file.read.msg2 db "bananas!"
file.read.msg2.size dd 8
a.size dd 256
file.read.b dd 2
file.read.c dd 3


section .bss

file.read.a resd 256
