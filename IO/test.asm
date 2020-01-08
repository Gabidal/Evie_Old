global main
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
 ; Adding the offset of y by 0
lea esi, [(ebp + 12) + 0 * 4]
 ; From x added address by value of 0
 ; Adding the offset of x by 0
lea edi, [(ebp + 8) + 0 * 4]
 ; Saving the value from y offsetted by 0
mov ecx, [ebp + 16]
repz movsd
 ; Ending stack frame 
mov esp, ebp
pop ebp
 ; Returning 
ret

 ; Function banana
banana: 
 ; Making stack frame 
push ebp
mov ebp, esp

 ; Adding y into x
 ; Just directly get address
 ; Giving x, eax
 ; Initializing new register for private  variable x
mov eax, [ebp + 8]
add eax, [ebp + 12]
 ; Saving x into z
 ; x has already a register to it
mov [ebp - 4], dword eax
 ; Return z
mov esp, ebp
pop ebp
ret 

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
if1: 
 ; Comparing a and b
 ; Just directly get address of b
 ; Giving a, edx
mov edx, [ebp - 4]
cmp edx, [ebp - 8]
 ; Jumping source: '<'
jge if1END
 ; Calling banana
 ; Pushing Variable 
push dword [ebp - 8]
 ; Pushing Variable 
push dword [ebp - 4]
call banana

 ; Clearing the parameters
add esp, 8
 ; Giving a the return value
 ; Giving banana, eax
mov [ebp - 4], eax

if1END: 
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
