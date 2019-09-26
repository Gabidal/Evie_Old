

section .text


function_size:
  pop ebx
  pop edx
  xor eax, eax
  jmp check
  top:
  inc edx
  inc eax
  check:
  cmp byte [edx], 0
  jnz top
  push eax
  push ebx
ret

function_malloc:
  push dword 0
  push dword -1
  push dword 0x22
  push dword 0x03
  push dword [esp+20]
  push dword 0
  mov eax, 0x5a
  mov ebx, esp
  int 0x80
  add esp, 24
  pop ebx
  push eax
jmp ebx

function_char:
  pop edi
  pop eax
  printRAX:
    lea ecx, [char.s]
    mov ebx, 10
    mov [ecx], ebx
    inc ecx
    mov [char.i], ecx
  charLoop:
    mov edx, 0
    mov ebx, 10
    div ebx
    push eax
    add edx, 48
    mov ecx, [char.i]
    mov [ecx], dl
    inc ecx
    mov [char.i], ecx
    pop eax
    cmp eax, 0
    jne charLoop
  push char.s
jmp edi

function_num:
  pop edx
  pop eax
  mov ecx, 48
  sub eax, ecx
  push eax
  jmp edx

function_reverse:
  push ebp
  mov ebp, esp
  mov esi, [ebp+8]
  push esi
  call function_size
  pop ecx
  mov eax, esi
  add eax, ecx
  mov edi, eax
  dec edi       ; edi points to end of string
  shr ecx, 1    ; ecx is count (length/2)
  jz reverse.done
  reverseLoop:
  mov al, [esi] ; load characters
  mov bl, [edi]
  mov [esi], bl ; and swap
  mov [edi], al
  inc esi       ; adjust pointers
  dec edi
  dec ecx       ; and loop
  jnz reverseLoop
  reverse.done:
  mov esp, ebp
  pop ebp
  ret

global _start
_start:
call function_main
mov eax, 1
mov ebx, 0
int 80h

GASCode:

function_apple:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;b is now an Variable.
 mov eax , [ebp+8]
 mov [apple.b], eax 
 ;returning from stack frame
 mov esp, ebp
 pop ebp

 ;returning a value from function
 pop eax
 push dword [apple.b]
jmp eax

function_banana:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;a is now an Variable.
 mov ebx , [ebp+8]
 mov [banana.a], ebx 
 ;returning from stack frame
 mov esp, ebp
 pop ebp

 ;returning a value from function
 pop eax
 push dword [banana.a]
jmp eax

function_vector:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 sub esp, 4
 
 ;a is now an Variable.
 mov ecx , [ebp+8]
 mov [vector.a], ecx 
 ;Set the value to local var
 mov dword [vector.b], 1
 cmp ecx , dword [vector.b]
 jne else11

  ;making a stack frame start
  push ebp
  mov ebp, esp


  ;The inital destination
  lea esi , vector.c[0 * 4]
  push esi 
  
  lea eax , [function_apple]

  ;Get the destination to: edi 
  pop edi 
  mov [edi ], eax 


  ;making a stack frame end
  mov esp, ebp
  pop ebp
 jmp end11
 else11:

  ;making a stack frame start
  push ebp
  mov ebp, esp


  ;The inital destination
  lea esi , vector.c[0 * 4]
  push esi 
  
  lea ebx , [function_banana]

  ;Get the destination to: edi 
  pop edi 
  mov [edi ], ebx 


  ;making a stack frame end
  mov esp, ebp
  pop ebp
 end11:

 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret

function_main:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 ;Set the value to local var
 mov dword [main.a], 1

 ;making a stack frame end
 mov esp, ebp
 pop ebp
ret



section .data

char.i dd 0
char.s times 20 db 1
 dd 0
reverse.s times 512 db 1
 dd 0

startOfLayerVariables_0:
apple.b dd 0
endOfLayerVariables_0:


startOfLayerVariables_1:
banana.a dd 0
endOfLayerVariables_1:


vector:

startOfLayerVariables_2:
vector.a dd 0
vector.b dd 0
vector.c times 2 dd 0
endOfLayerVariables_2:


startOfLayerVariables_3:
main.a dd 0
endOfLayerVariables_3:



section .bss

