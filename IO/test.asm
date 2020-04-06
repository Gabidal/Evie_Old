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
_glClear: 
push ebp 
mov ebp , esp 
push dword [ebp  + 8]
call _glClear@4
xor al , al 
leave 
ret
 
_glClearColor: 
push ebp 
mov ebp , esp 
push dword [ebp  + 20]
push dword [ebp  + 16]
push dword [ebp  + 12]
push dword [ebp  + 8]
call _glClearColor@16
xor al , al 
leave 
ret
 
_glVertex2f: 
push ebp 
mov ebp , esp 
push dword [ebp  + 12]
push dword [ebp  + 8]
call _glVertex2f@8
xor al , al 
leave 
ret
 
_glBegin: 
push ebp 
mov ebp , esp 
push dword [ebp  + 8]
call _glBegin@4
xor al , al 
leave 
ret
 
_glEnd: 
call _glEnd@0
xor al , al 
ret
 
_glFlush: 
call _glFlush@0
xor al , al 
ret
 
_glColor3f: 
push ebp 
mov ebp , esp 
push dword [ebp  + 16]
push dword [ebp  + 12]
push dword [ebp  + 8]
call _glColor3f@12
xor al , al 
leave 
ret
 
export main
global main
main: 
_main: 
push ebp 
mov ebp , esp 
sub esp , dword 22
mov dword [ebp  - 4], dword 16384
mov dword [ebp  - 8], dword 7
mov dword [ebp  - 12], dword 0
mov dword [ebp  - 16], dword 0
mov word [ebp  - 20], word 0
_if29: 
call _glfwInit
mov esi , dword 1
cmp eax , esi 
je _if29END
mov al , byte -1
leave 
ret
 
_if29END: 
push dword 0
push dword 0
lea edi , dword [ebp  - 16]
push edi 
push dword 480
push dword 640
call _glfwCreateWindow
add esp , dword 20
mov dword [ebp  - 12], eax 
_if30: 
mov eax , dword [ebp  - 12]
xor ebx , ebx 
cmp eax , ebx 
jne _if30END
call _glfwTerminate
mov al , byte -1
leave 
ret
 
_if30END: 
push dword [ebp  - 12]
call _glfwMakeContextCurrent
add esp , dword 4
mov dword [ebp  - 22], dword 0
_while31: 
mov ecx , dword [ebp  - 22]
xor edx , edx 
cmp ecx , edx 
jne _while31END
push dword [ebp  - 4]
call _glClear
add esp , dword 4
push dword [ebp  - 8]
call _glBegin
add esp , dword 4
push dword 0.0
push dword 0.0
push dword 1.0
call _glColor3f
add esp , dword 12
push dword -0.5
push dword -0.5
call _glVertex2f
push dword -0.5
push dword 0.5
call _glVertex2f
add esp , dword 4
push dword 0.5
push dword 0.5
call _glVertex2f
add esp , dword 8
push dword 0.5
push dword -0.5
call _glVertex2f
add esp , dword 4
call _glEnd
call _glFlush
push dword [ebp  - 12]
call _glfwSwapBuffers
add esp , dword 4
call _glfwPollEvents
push dword [ebp  - 12]
call _glfwWindowShouldClose
add esp , dword 4
mov dword [ebp  - 22], eax 
jmp _while31
_while31END: 
call _glfwTerminate
xor al , al 
leave 
ret
 
