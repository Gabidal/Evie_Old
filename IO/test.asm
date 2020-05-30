export main
global main
main: 
  _main: 
; ebp 
  push ebp 
; ebp esp 
  mov ebp , esp 
; reserve memory please! 20 
  sub esp, dword 20
; x_Giving_Address_regiser @x:10 
  lea ecx, dword [(ebp - 16) - 10 * 4]
; a gets value of x_Giving_Address_regiser x_Giving_Address_regiser 
  mov [ebp - 20], ecx 
; a_returning_register a 
  mov eax, dword [ebp - 20]
  leave 
  ret
 
_mainEND: 
_MAX_BUFFER_SIZE: 
; 123 
dd 123
