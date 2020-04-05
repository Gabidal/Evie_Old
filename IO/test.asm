extern __imp__glClear@4
___imp__glClear@4: 
extern __imp__glClearColor@16
___imp__glClearColor@16: 
extern _glfwInit
__glfwInit: 
extern _glfwTerminate
__glfwTerminate: 
extern _glfwCreateWindow
__glfwCreateWindow: 
extern _glfwWindowShouldClose
__glfwWindowShouldClose: 
extern _glfwPollEvents
__glfwPollEvents: 
extern _glfwMakeContextCurrent
__glfwMakeContextCurrent: 
extern _glfwSwapBuffers
__glfwSwapBuffers: 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 18
mov dword [ebp  - 4], dword 0
mov dword [ebp  - 8], dword 0
mov word [ebp  - 12], word 0
call _glfwInit
mov dword [ebp  - 14], eax 
_if29: 
mov ecx , dword [ebp  - 14]
mov edx , dword 1
cmp ecx , edx 
je _if29END
mov al , byte -1
leave 
ret
 
_if29END: 
push dword 0
push dword 0
lea ebx , dword [ebp  - 8]
push ebx 
push dword 480
push dword 640
call _glfwCreateWindow
add esp , dword 20
mov dword [ebp  - 4], eax 
_if30: 
mov edi , dword [ebp  - 4]
xor esi , esi 
cmp edi , esi 
jne _if30END
call _glfwTerminate
mov al , byte -1
leave 
ret
 
_if30END: 
push dword [ebp  - 4]
call _glfwMakeContextCurrent
add esp , dword 4
mov dword [ebp  - 18], dword 0
_while31: 
mov eax , dword [ebp  - 18]
mov ebx , dword 1
cmp eax , ebx 
jnl _while31END
push dword 16384
call __imp__glClear@4
add esp , dword 4
push dword [ebp  - 4]
call _glfwSwapBuffers
add esp , dword 4
call _glfwPollEvents
jmp _while31
_while31END: 
call _glfwTerminate
xor al , al 
leave 
ret
 
