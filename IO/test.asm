extern _glfwCreateWindow
__glfwCreateWindow: 
__glfwCreateWindowEND: 
extern _glfwPollEvents
__glfwPollEvents: 
__glfwPollEventsEND: 
extern _glfwWindowShouldClose
__glfwWindowShouldClose: 
__glfwWindowShouldCloseEND: 
extern _glfwInit
__glfwInit: 
__glfwInitEND: 
extern _glfwTerminate
__glfwTerminate: 
__glfwTerminateEND: 
extern _glfwMakeContextCurrent
__glfwMakeContextCurrent: 
__glfwMakeContextCurrentEND: 
extern _glfwSwapBuffers
__glfwSwapBuffers: 
__glfwSwapBuffersEND: 
export main
global main
main: 
  _main: 
  push ebp 
  mov ebp , esp 
  sub esp, dword 14
  mov [ebp - 4], dword 0
  mov [ebp - 8], dword 0
  mov [ebp - 12], word 0
   _if38: 
   call _glfwInit
   cmp eax, dword 1
   je _if38END
   mov eax, dword -1
   leave 
   ret
 
  _if38END: 
  push dword 0
  push dword 0
  lea ecx, dword [ebp - 8]
  push ecx 
  push dword 480
  push dword 640
  call _glfwCreateWindow
  mov [ebp - 4], eax
   _if39: 
   mov ecx, dword [ebp - 4]
   cmp ecx , dword 0
   jne _if39END
   call _glfwTerminate
   mov eax, dword -1
   leave 
   ret
 
  _if39END: 
  push dword [ebp - 4]
  call _glfwMakeContextCurrent
  mov [ebp - 14], dword 0
   _while40: 
   mov ecx, dword [ebp - 14]
   cmp ecx , dword 0
   jne _while40END
   push dword [ebp - 4]
   call _glfwSwapBuffers
   call _glfwPollEvents
   push dword [ebp - 4]
   call _glfwWindowShouldClose
   mov [ebp - 14], eax
   jmp _while40
  _while40END: 
  call _glfwTerminate
  xor eax, eax
  leave 
  ret
 
_mainEND: 
_GL_Color_Buffer_Bit: 
dd 16384
_GL_QUADS: 
dd 7
