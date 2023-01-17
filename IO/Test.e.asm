.intel_syntax noprefix
.global _Z10Start_Testv
.global _Z4mainv
.section .text                                              #.text
_Z2Isv:
mov al, 1                                                   #Returning_REG0, 1
ret                                                         #
ret                                                         #


_Z5Innerl:
mov rax, rcx                                                #Returning_REG0, size
ret                                                         #
ret                                                         #


_Z4mainv:
push rsi                                                    #Reg_rsi
push rsi                                                    #Reg_rsi
push rdi                                                    #Reg_rdi
push rbx                                                    #Reg_rbx
sub rsp, 28                                                 #.STACK, 28
mov ecx, 123                                                #Num, 123
mov ecx, ecx                                                #REG_Num0, Num
sub ecx, 48                                                 #REG_Num0, 48
mov rbx, ecx                                                #r, REG_Num0
mov dword ptr [rsp + 0 ], 1                                 #.STACK_0, 1
lea rcx, qword ptr [rsp + 0 ]                               #a_REG1, .STACK_0
mov rdi, rcx                                                #b, a_REG1
if_0:
mov ecx, dword ptr [rdi ]                                   #b_REG2, b
cmp ecx, 2                                                  #b_REG2, 2
jne if_0_END                                                #if_0_END
lea rcx, qword ptr [rsp + 4 ]                               #maybe_REG3, .STACK_4
mov rcx, rcx                                                #REG_maybe_REG3_Parameter41, maybe_REG3
call _ZN11inheritable11inheritableEP11inheritable
lea rcx, qword ptr [rsp + 4 ]                               #maybe_REG5, .STACK_4
mov rcx, rcx                                                #REG_maybe_REG5_Parameter18467, maybe_REG5
call _ZN11inheritable2DoEP11inheritable
mov rcx, rax                                                #dont, RetREG_6
mov ecx, dword ptr [rsp + 0 ]                               #+_0_REG7, .STACK_0
mov rbx, ecx                                                #r, +_0_REG7
mov esi, 0                                                  #i, 0
if_1:
call _Z2Isv
cmp al, 1                                                   #RetREG_8, 1
jne if_1_END                                                #if_1_END
mov esi, 0                                                  #i, 0
if_1_END:
mov rcx, rbx                                                #REG_r_Parameter6334, r
call _Z15____Outer_char_l
mov rcx, rax                                                #c, RetREG_9
mov ecx, 1                                                  #1_TMP, 1
cmp ecx, 2                                                  #1_TMP, 2
jge while_2_END                                             #while_2_END
while_2:
mov r8d, dword ptr [rsp + 0 ]                               #REG_a11, .STACK_0
mov r9d, dword ptr [rdi + rsi * 4 ]                         #b_REG10, *
add r8d, r9d                                                #REG_a11, b_REG10
mov dword ptr [rsp + 0 ], r8d                               #.STACK_0, REG_a11
mov eax, dword ptr [rsp + 0 ]                               #Returning_REG12, .STACK_0
add rsp, 28                                                 #.STACK, 28
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #
cmp ecx, 2                                                  #1_TMP, 2
jge while_2_END                                             #while_2_END
jmp while_2                                                 #while_2
while_2_END:
mov eax, 1                                                  #Returning_REG13, 1
add rsp, 28                                                 #.STACK, 28
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #
if_0_END:
add dword ptr [rsp + 0 ], 1                                 #.STACK_0, 1
mov eax, dword ptr [rsp + 0 ]                               #Returning_REG14, .STACK_0
add rsp, 28                                                 #.STACK, 28
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #
add rsp, 28                                                 #.STACK, 28
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #


_Z10Start_Testv:
call _Z4mainv
mov eax, eax                                                #Returning_REG1, RetREG_0
ret                                                         #
ret                                                         #


_Z15____Outer_char_l:
imul rcx, rcx, 1                                            #Size, Size, 1
mov rcx, rcx                                                #REG_Size_Parameter26500, Size
call _Z5Innerl
mov rax, rax                                                #Returning_REG1, RetREG_0
ret                                                         #
ret                                                         #


_ZN11inheritable2DoEP11inheritable:
add rcx, 4                                                  #this, 4
mov rax, rcx                                                #Returning_REG0, this
ret                                                         #
ret                                                         #


_ZN11inheritable11inheritableEP11inheritable:
add rcx, 12                                                 #this, 12
mov rax, rcx                                                #Returning_REG0, this
ret                                                         #
ret                                                         #


.section .data                                              #.data
