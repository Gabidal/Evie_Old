global main
main: 
mov eax , dword [ebp  + 12]
cvttss2si eax ,  [ebp  + 24]
_=[ebp  + 24], eax 
mov eax , dword [ebp  + 12]
mov [ebp  - 4], eax 
mov eax , dword [ebp  - 4]
ret
 
