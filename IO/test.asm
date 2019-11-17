main: 
push ebp
mov ebp, esp

mov dword [ebp - 4], 2
mov dword [ebp - 8], 3
if0: 
mov eax, [ebp - 4]
sub eax, [ebp - 8]
cmp eax, ebp - 4
jg if0END
add eax, 1
mov [ebp - 4], eax

if1: 
sub eax, eax
mov [ebp - 4], eax

else2: 
mov ebx, [ebp - 8]
add ebx, 1
mov [ebp - 8], ebx

else2END: 
if1END: 
if0END: 
if1: 
cmp eax, ebx

jne if1END
sub ebx, 1
mov [ebp - 8], ebx

if1END: 
else2: 
mov [ebp - 4], ebx
else2END: 
mov esp, ebp
pop ebp
ret

