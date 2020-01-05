global main
 ; Calling std_init
call std_init

 ; Function ntc
ntc: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Direct addition
add [ebp + 8], dword 48
 ; Saving c into c
 ; Giving c, eax
 ; Initializing new register for private  variable c
mov eax, [ebp + 8]
mov [ebp + 8], dword eax
 ; Return c
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function ctn
ctn: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Direct substraction
sub [ebp + 8], dword 48
 ; Saving i into i
 ; Giving i, edx
 ; Initializing new register for private  variable i
mov edx, [ebp + 8]
mov [ebp + 8], dword edx
 ; Return i
mov eax, edx
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function move
move: 
 ; Making stack frame 
push ebp
mov ebp, esp

while0: 
while0END: 
 ; Pointer to pointer directionation
 ; From y added address by value of 0
 ; Giving y, eax
mov eax, [ebp + 12]
 ; Adding the offset of y by 0
lea esi, [eax + 0 * 4]
 ; From x added address by value of 0
 ; Giving x, edx
mov edx, [ebp + 8]
 ; Adding the offset of x by 0
lea edi, [edx + 0 * 4]
 ; Saving the value from y offsetted by 0
mov ecx, [ebp + 16]
repz movsd
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function main
main: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Giving a, 1
mov [ebp - 4], dword 1
 ; Giving b, 2
mov [ebp - 8], dword 2
 ; Calling move
push dword 1
 ; Pushing pointter 
 ; Giving b, eax
 ; Adding the offset of b by 0
lea eax, [(ebp - 8) + 0 * 4]
push dword eax
 ; Pushing pointter 
 ; Giving a, edx
 ; Adding the offset of a by 0
lea edx, [(ebp - 4) + 0 * 4]
push dword edx
call move

 ; Return a
mov eax, edx
mov esp, ebp
pop ebp
ret 

 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

section .bss
section .data
