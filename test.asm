

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

type_vector:
 ;making a function stack frame
 push ebp
 mov ebp, esp

 ;Set the value to local var
 mov dword [vector.b], 1
function_c:
  ;making a function stack frame
  push ebp
  mov ebp, esp

  ;Set the value to local var
  mov dword [c.d], 0
  ;returning from stack frame
  mov esp, ebp
  pop ebp

  ;returning a value from function
  pop eax
  push dword [c.d]
 jmp eax


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
char.s dd 0
reverse.s dd 0

startVariables_apple:
apple.b dd 0
endVariables_apple:


startVariables_banana:
banana.a dd 0
endVariables_banana:


vector:
vector.b dd 0

startVariables_c:
c.d dd 0
endVariables_c:

vector_end:

startVariables_main:
main.a dd 0
endVariables_main:



section .bss

