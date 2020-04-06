extern _glClear@4
__glClear@4: 
extern _glClearColor@16
__glClearColor@16: 
extern _glVertex2f@8
__glVertex2f@8: 
extern _glBegin@4
__glBegin@4: 
extern _glEnd@0
__glEnd@0: 
extern _glFlush@0
__glFlush@0: 
extern _glColor3f@12
__glColor3f@12: 
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
sub esp , dword 22
mov dword [ebp  - 4], dword 0
mov dword [ebp  - 8], dword 0
mov word [ebp  - 12], word 0
_if29: 
call _glfwInit
mov edi , dword 1
cmp eax , edi 
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
mov esi , dword [ebp  - 4]
xor eax , eax 
cmp esi , eax 
jne _if30END
call _glfwTerminate
mov al , byte -1
leave 
ret
 
_if30END: 
push dword [ebp  - 4]
call _glfwMakeContextCurrent
add esp , dword 4
mov dword [ebp  - 14], dword 0
mov dword [ebp  - 18], dword 16384
mov dword [ebp  - 22], dword 7
_while31: 
mov ebx , dword [ebp  - 14]
xor ecx , ecx 
cmp ebx , ecx 
jne _while31END
push dword [ebp  - 18]
call _glClear@4
push dword [ebp  - 22]
call _glBegin@4
push dword 1.0
push dword 0.0
push dword 0.0
call _glColor3f@12
push dword -0.5
push dword -0.5
call _glVertex2f@8
push dword 0.5
push dword -0.5
call _glVertex2f@8
push dword 0.5
push dword 0.5
call _glVertex2f@8
push dword -0.5
push dword 0.5
call _glVertex2f@8
call _glEnd@0
push dword [ebp  - 4]
call _glfwSwapBuffers
add esp , dword 4
call _glfwPollEvents
push dword [ebp  - 4]
call _glfwWindowShouldClose
add esp , dword 4
mov dword [ebp  - 14], eax 
jmp _while31
_while31END: 
call _glfwTerminate
xor al , al 
leave 
ret
 
