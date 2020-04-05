_banana: 
push ebp 
mov ebp , esp 
mov eax , dword [ebp  + 8]
; Boosted
add eax , eax 
leave 
ret
 
