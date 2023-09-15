.intel_syntax noprefix
.extern ReadConsoleA
.extern WriteFile
.extern GetStdHandle
.extern VirtualFree
.extern VirtualAlloc
.global _Z4mainv
.global _Z10Start_Testv
.section .text                                              #.text
_Z10Start_Testv:
sub rsp, 20                                                 #.STACK, 20
lea rcx, qword ptr [rsp + 0 ]                               #a_REG0, .STACK_0
mov rcx, rcx                                                #REG_a_REG0_Parameter41, a_REG0
call _Z13____List_int_P13____List_int_
lea rcx, qword ptr [rsp + 0 ]                               #a_REG2, .STACK_0
mov rcx, rcx                                                #REG_a_REG2_Parameter18467, a_REG2
mov edx, 5                                                  #REG_5_Parameter6334, 5
call _ZN13____List_int_12____Add_int_EP13____List_int_i
lea rcx, qword ptr [rsp + 0 ]                               #a_REG4, .STACK_0
mov rcx, rcx                                                #REG_a_REG4_Parameter26500, a_REG4
mov edx, 2                                                  #REG_2_Parameter19169, 2
call _ZN13____List_int_12____Add_int_EP13____List_int_i
lea rcx, qword ptr [rsp + 0 ]                               #a_REG6, .STACK_0
mov rcx, rcx                                                #REG_a_REG6_Parameter15724, a_REG6
call _ZN13____List_int_8Pop_BackEP13____List_int_
lea rcx, qword ptr [rsp + 0 ]                               #a_REG8, .STACK_0
mov rcx, rcx                                                #REG_a_REG8_Parameter11478, a_REG8
mov edx, 0                                                  #REG_0_Parameter29358, 0
call _ZN13____List_int_11____At_int_EP13____List_int_i
mov eax, eax                                                #Returning_REG10, RetREG_9
add rsp, 20                                                 #.STACK, 20
ret                                                         #
add rsp, 20                                                 #.STACK, 20
ret                                                         #


_Z4mainv:
push rbp                                                    #Reg_rbp
push rsi                                                    #Reg_rsi
push rdi                                                    #Reg_rdi
push rbx                                                    #Reg_rbx
mov dword ptr [rip + _ZN3std15ALLOCATION_SIZEE ], 700000    #.RIP__ZN3std15ALLOCATION_SIZEE, 700000
mov dword ptr [rip + _ZN3std12BUCKET_COUNTE ], 100000       #.RIP__ZN3std12BUCKET_COUNTE, 100000
mov ebx, dword ptr [rip + _ZN3std12BUCKET_COUNTE ]          #std_BUCKET_COUNT_REGISTER, .RIP__ZN3std12BUCKET_COUNTE
mov ecx, ebx                                                #REG_std_BUCKET_COUNT_REGISTER_Parameter26962, std_BUCKET_COUNT_REGISTER
call _ZN8Internal18____Allocate_char_El
mov qword ptr [rip + _ZN3std13BUCKET_BUFFERE ], rax         #.RIP__ZN3std13BUCKET_BUFFERE, RetREG_0
mov rdi, qword ptr [rip + _ZN3std13BUCKET_BUFFERE ]         #std_BUCKET_BUFFER_REGISTER, .RIP__ZN3std13BUCKET_BUFFERE
mov rcx, rdi                                                #REG_std_BUCKET_BUFFER_REGISTER_Parameter24464, std_BUCKET_BUFFER_REGISTER
call _ZN6Bucket3std6BucketEP6Bucket
mov qword ptr [rip + _ZN3std12Bucket_StartE ], rax          #.RIP__ZN3std12Bucket_StartE, RetREG_1
mov rsi, qword ptr [rip + _ZN3std12Bucket_StartE ]          #std_Bucket_Start_REGISTER, .RIP__ZN3std12Bucket_StartE
mov qword ptr [rip + _ZN3std12Bucket_CacheE ], rsi          #.RIP__ZN3std12Bucket_CacheE, std_Bucket_Start_REGISTER
mov rcx, 4886408106085781771                                #REG_4886408106085798806, 4886408106085781771
mov qword ptr [rip + _ZN3std2PiE ], rcx                     #.RIP__ZN3std2PiE, REG_4886408106085798806
mov rcx, 4886407175215432982                                #REG_4886407175215442876, 4886407175215432982
mov qword ptr [rip + _ZN3std1EE ], rcx                      #.RIP__ZN3std1EE, REG_4886407175215442876
mov rcx, 0                                                  #REG_28703, 0
mov qword ptr [rip + _ZN3std3EpsE ], rcx                    #.RIP__ZN3std3EpsE, REG_28703
mov rcx, -4332462841530417152                               #REG_-4332462841530393341, -4332462841530417152
mov qword ptr [rip + _ZN3std3InfE ], rcx                    #.RIP__ZN3std3InfE, REG_-4332462841530393341
mov rbp, qword ptr [rip + _ZN3std3InfE ]                    #std_Inf_REGISTER, .RIP__ZN3std3InfE
mov rbp, qword ptr [rip + _ZN3std3InfE ]                    #std_Inf_REGISTER, .RIP__ZN3std3InfE
sub rbp, rbp                                                #std_Inf_REGISTER, std_Inf_REGISTER
mov qword ptr [rip + _ZN3std3NanE ], rbp                    #.RIP__ZN3std3NanE, std_Inf_REGISTER
mov dword ptr [rip + _ZN8Internal13MEMORY_COMMITE ], 4096   #.RIP__ZN8Internal13MEMORY_COMMITE, 4096
mov dword ptr [rip + _ZN8Internal14MEMORY_RESERVEE ], 8192  #.RIP__ZN8Internal14MEMORY_RESERVEE, 8192
mov dword ptr [rip + _ZN8Internal14MEMORY_RELEASEE ], 32768 #.RIP__ZN8Internal14MEMORY_RELEASEE, 32768
mov dword ptr [rip + _ZN8Internal14PAGE_READWRITEE ], 4     #.RIP__ZN8Internal14PAGE_READWRITEE, 4
mov dword ptr [rip + _ZN8Internal22STANDARD_OUTPUT_HANDLEE ], 11#.RIP__ZN8Internal22STANDARD_OUTPUT_HANDLEE, 11
mov dword ptr [rip + _ZN8Internal21STANDARD_INPUT_HANDLEE ], 10#.RIP__ZN8Internal21STANDARD_INPUT_HANDLEE, 10
mov dword ptr [rip + _ZN3std15ALLOCATION_SIZEE ], 700000    #.RIP__ZN3std15ALLOCATION_SIZEE, 700000
mov dword ptr [rip + _ZN3std12BUCKET_COUNTE ], 100000       #.RIP__ZN3std12BUCKET_COUNTE, 100000
mov ebx, dword ptr [rip + _ZN3std12BUCKET_COUNTE ]          #std_BUCKET_COUNT_REGISTER, .RIP__ZN3std12BUCKET_COUNTE
mov ecx, ebx                                                #REG_std_BUCKET_COUNT_REGISTER_Parameter5705, std_BUCKET_COUNT_REGISTER
call _ZN8Internal18____Allocate_char_El
mov qword ptr [rip + _ZN3std13BUCKET_BUFFERE ], rax         #.RIP__ZN3std13BUCKET_BUFFERE, RetREG_2
mov rdi, qword ptr [rip + _ZN3std13BUCKET_BUFFERE ]         #std_BUCKET_BUFFER_REGISTER, .RIP__ZN3std13BUCKET_BUFFERE
mov rcx, rdi                                                #REG_std_BUCKET_BUFFER_REGISTER_Parameter28145, std_BUCKET_BUFFER_REGISTER
call _ZN6Bucket3std6BucketEP6Bucket
mov qword ptr [rip + _ZN3std12Bucket_StartE ], rax          #.RIP__ZN3std12Bucket_StartE, RetREG_3
mov rsi, qword ptr [rip + _ZN3std12Bucket_StartE ]          #std_Bucket_Start_REGISTER, .RIP__ZN3std12Bucket_StartE
mov qword ptr [rip + _ZN3std12Bucket_CacheE ], rsi          #.RIP__ZN3std12Bucket_CacheE, std_Bucket_Start_REGISTER
mov rcx, 4886408106085781771                                #REG_4886408106085813093, 4886408106085781771
mov qword ptr [rip + _ZN3std2PiE ], rcx                     #.RIP__ZN3std2PiE, REG_4886408106085813093
mov rcx, 4886407175215432982                                #REG_4886407175215463315, 4886407175215432982
mov qword ptr [rip + _ZN3std1EE ], rcx                      #.RIP__ZN3std1EE, REG_4886407175215463315
mov rcx, 0                                                  #REG_17673, 0
mov qword ptr [rip + _ZN3std3EpsE ], rcx                    #.RIP__ZN3std3EpsE, REG_17673
mov rcx, -4332462841530417152                               #REG_-4332462841530412488, -4332462841530417152
mov qword ptr [rip + _ZN3std3InfE ], rcx                    #.RIP__ZN3std3InfE, REG_-4332462841530412488
mov rbp, qword ptr [rip + _ZN3std3InfE ]                    #std_Inf_REGISTER, .RIP__ZN3std3InfE
mov rbp, qword ptr [rip + _ZN3std3InfE ]                    #std_Inf_REGISTER, .RIP__ZN3std3InfE
sub rbp, rbp                                                #std_Inf_REGISTER, std_Inf_REGISTER
mov qword ptr [rip + _ZN3std3NanE ], rbp                    #.RIP__ZN3std3NanE, std_Inf_REGISTER
jmp _Z10Start_Testv                                         #_Z10Start_Testv
mov eax, 1                                                  #Returning_REG4, 1
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
pop Reg_rbp                                                 #Reg_Reg_rbp
ret                                                         #
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
pop Reg_rbp                                                 #Reg_Reg_rbp
ret                                                         #


_Z15____Memcpy_int_PiPii:
mov r9d, 0                                                  #i, 0
cmp r9d, r8d                                                #i, Size
jge while_0_END                                             #while_0_END
while_0:
lea r10, qword ptr [rcx + r9 * 4 ]                          #dest_REG0, *
mov r11d, dword ptr [rdx + r9 * 4 ]                         #source_REG1, *
mov dword ptr [r10 ], r11d                                  #dest_REG0, source_REG1
add r9d, 1                                                  #i, 1
cmp r9d, r8d                                                #i, Size
jge while_0_END                                             #while_0_END
jmp while_0                                                 #while_0
while_0_END:
ret                                                         #
ret                                                         #


_ZN3std13Get_Free_PageEv:
mov rcx, qword ptr [rip + _ZN3std12Bucket_CacheE ]          #_ZN3std12Bucket_CacheE_REG0, .RIP__ZN3std12Bucket_CacheE
mov rcx, qword ptr [rcx + 0 ]                               #_ZN3std12Bucket_CacheE_REG0_0_REG1, _ZN3std12Bucket_CacheE_REG0_0
mov rcx, rcx                                                #Current, _ZN3std12Bucket_CacheE_REG0_0_REG1
mov r8, rcx                                                 #Last, Current
cmp rcx, 0                                                  #Current, 0
je while_1_END                                              #while_1_END
while_1:
mov r8, rcx                                                 #Last, Current
if_2:
mov r9b, byte ptr [rcx + 12 ]                               #Current_12_REG2, Current_12
cmp r9b, 1                                                  #Current_12_REG2, 1
jne else_3                                                  #else_3
mov r9, qword ptr [rcx + 13 ]                               #Current_13_REG3, Current_13
mov rcx, r9                                                 #Current, Current_13_REG3
jmp else_3_END                                              #else_3_END
if_2_END:
else_3:
mov r9, qword ptr [rip + _ZN3std12Bucket_CacheE ]           #_ZN3std12Bucket_CacheE_REG4, .RIP__ZN3std12Bucket_CacheE
mov qword ptr [r9 + 0 ], rcx                                #_ZN3std12Bucket_CacheE_REG4_0, Current
mov rax, rcx                                                #Returning_REG5, Current
ret                                                         #
else_3_END:
cmp rcx, 0                                                  #Current, 0
je while_1_END                                              #while_1_END
jmp while_1                                                 #while_1
while_1_END:
if_4:
mov rcx, qword ptr [r8 + 29 ]                               #Last_29_REG6, Last_29
mov r9, qword ptr [r8 + 21 ]                                #+_0_REG7, Last_21
lea r10, qword ptr [rip + _Z15ALLOCATION_SIZE ]             #_Z15ALLOCATION_SIZE_REG8, .RIP__Z15ALLOCATION_SIZE
add r9, r10                                                 #+_0_REG7, _Z15ALLOCATION_SIZE_REG8
cmp rcx, r9                                                 #Last_29_REG6, +_0_REG7
jl if_4_END                                                 #if_4_END
mov byte ptr [r8 + 33 ], 1                                  #Last_33, 1
mov rax, 0                                                  #Returning_REG9, 0
ret                                                         #
if_4_END:
mov rcx, qword ptr [r8 + 29 ]                               #Last_29_REG10, Last_29
mov rcx, rcx                                                #REG_Last_29_REG10_Parameter23281, Last_29_REG10
mov rdx, r8                                                 #REG_Last_Parameter16827, Last
call _ZN4Page3std4PageEP4PageP4Page
mov rcx, rax                                                #Result, RetREG_11
mov rax, rcx                                                #Returning_REG12, Result
ret                                                         #
ret                                                         #


_ZN3std15Get_Free_BucketEv:
mov rcx, qword ptr [rip + _Z12Bucket_Cache ]                #Current, .RIP__Z12Bucket_Cache
mov r8, rcx                                                 #Last, Current
cmp rcx, 0                                                  #Current, 0
je while_5_END                                              #while_5_END
while_5:
mov r8, rcx                                                 #Last, Current
if_6:
mov r9, qword ptr [rcx + 29 ]                               #Current_29_REG0, Current_29
mov rcx, r9                                                 #Current, Current_29_REG0
jmp else_7_END                                              #else_7_END
if_6_END:
else_7:
mov qword ptr [rip + _Z12Bucket_Cache ], rcx                #.RIP__Z12Bucket_Cache, Current
mov rax, rcx                                                #Returning_REG1, Current
ret                                                         #
else_7_END:
cmp rcx, 0                                                  #Current, 0
je while_5_END                                              #while_5_END
jmp while_5                                                 #while_5
while_5_END:
mov rcx, qword ptr [r8 + 45 ]                               #Last_45_REG2, Last_45
mov rcx, rcx                                                #REG_Last_45_REG2_Parameter9961, Last_45_REG2
mov rdx, r8                                                 #REG_Last_Parameter491, Last
call _ZN6Bucket3std6BucketEP6BucketP6Bucket
mov rcx, rax                                                #Result, RetREG_3
mov qword ptr [rip + _Z12Bucket_Cache ], rcx                #.RIP__Z12Bucket_Cache, Result
mov rax, rcx                                                #Returning_REG4, Result
ret                                                         #
ret                                                         #


_ZN3std8AllocateEi:
push rsi                                                    #Reg_rsi
push rdi                                                    #Reg_rdi
push rbx                                                    #Reg_rbx
mov ebx, ecx                                                #Size, Size
if_8:
cmp ebx, dword ptr [rip + _Z15ALLOCATION_SIZE ]             #Size, .RIP__Z15ALLOCATION_SIZE
jle if_8_END                                                #if_8_END
add ebx, 37                                                 #Size, 37
mov ecx, ebx                                                #REG_Size_Parameter2995, Size
call _ZN8Internal27____Allocate_____char_ptr__El
mov qword ptr [rsp + 0 ], rax                               #.STACK_0, RetREG_0
mov rcx, qword ptr [rsp + 0 ]                               #REG_Result_Parameter11942, .STACK_0
mov r8, qword ptr [rip + _ZN3std12Bucket_CacheE ]           #_ZN3std12Bucket_CacheE_REG1, .RIP__ZN3std12Bucket_CacheE
mov r8, qword ptr [r8 + 0 ]                                 #_ZN3std12Bucket_CacheE_REG1_0_REG2, _ZN3std12Bucket_CacheE_REG1_0
mov rdx, r8                                                 #REG__ZN3std12Bucket_CacheE_REG1_0_REG2_Parameter4827, _ZN3std12Bucket_CacheE_REG1_0_REG2
call _ZN4Page3std4PageEP4PageP4Page
mov rcx, qword ptr [rsp + 0 ]                               #Result_REG4, .STACK_0
mov rax, qword ptr [rcx + 0 ]                               #Returning_REG5, Result_REG4_0
add rsp, 8                                                  #.STACK, 8
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #
if_8_END:
call _ZN3std13Get_Free_PageEv
mov rdi, rax                                                #New_Page, RetREG_6
call _ZN3std15Get_Free_BucketEv
mov rsi, rax                                                #New_Bucket, RetREG_7
if_9:
cmp rdi, 0                                                  #New_Page, 0
jne if_9_END                                                #if_9_END
call _ZN3std13Get_Free_PageEv
mov rdi, rax                                                #New_Page, RetREG_8
if_9_END:
mov rcx, rdi                                                #REG_New_Page_Parameter5436, New_Page
mov edx, ebx                                                #REG_Size_Parameter32391, Size
call _ZN4Page3std11Update_PageEP4Pagei
mov byte ptr [rdi + 12 ], 1                                 #New_Page_12, 1
mov qword ptr [rip + _Z12Bucket_Cache ], rsi                #.RIP__Z12Bucket_Cache, New_Bucket
mov rcx, qword ptr [rip + _ZN3std12Bucket_CacheE ]          #_ZN3std12Bucket_CacheE_REG10, .RIP__ZN3std12Bucket_CacheE
mov qword ptr [rcx + 0 ], rdi                               #_ZN3std12Bucket_CacheE_REG10_0, New_Page
mov rcx, qword ptr [rip + _ZN3std12Bucket_CacheE ]          #_ZN3std12Bucket_CacheE_REG11, .RIP__ZN3std12Bucket_CacheE
add dword ptr [rcx + 0 ], 1                                 #_ZN3std12Bucket_CacheE_REG11_0, 1
mov rax, qword ptr [rdi + 0 ]                               #Returning_REG12, New_Page_0
add rsp, 8                                                  #.STACK, 8
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #
add rsp, 8                                                  #.STACK, 8
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
pop Reg_rsi                                                 #Reg_Reg_rsi
ret                                                         #


_ZN8Internal8AllocateEl:
push rbx                                                    #Reg_rbx
mov rcx, 0                                                  #REG_0_Parameter14604, 0
mov Non-Volatile15141, rcx                                  #Non-Volatile15141, Current_Volatile7711
mov rdx, rbx                                                #REG_Size_Parameter3902, Size
mov ecx, dword ptr [rip + _ZN8Internal13MEMORY_COMMITE ]    #REG__ZN8Internal13MEMORY_COMMITE0, .RIP__ZN8Internal13MEMORY_COMMITE
or ecx, dword ptr [rip + _Z14MEMORY_RESERVE ]               #REG__ZN8Internal13MEMORY_COMMITE0, .RIP__Z14MEMORY_RESERVE
mov r8d, ecx                                                #REG_REG__ZN8Internal13MEMORY_COMMITE0_Parameter153, REG__ZN8Internal13MEMORY_COMMITE0
mov r9d, dword ptr [rip + _Z14PAGE_READWRITE ]              #REG__Z14PAGE_READWRITE_Parameter292, .RIP__Z14PAGE_READWRITE
call VirtualAlloc
mov rax, rax                                                #Returning_REG2, RetREG_1
pop Reg_rbx                                                 #Reg_Reg_rbx
ret                                                         #
pop Reg_rbx                                                 #Reg_Reg_rbx
ret                                                         #


_ZN8Internal18____Allocate_char_El:
imul rcx, rcx, 1                                            #Size, Size, 1
mov rcx, rcx                                                #REG_Size_Parameter12382, Size
call _ZN8Internal8AllocateEl
mov rax, rax                                                #Returning_REG1, RetREG_0
ret                                                         #
ret                                                         #


_ZN8Internal27____Allocate_____char_ptr__El:
imul rcx, rcx, 8                                            #Size, Size, 8
mov rcx, rcx                                                #REG_Size_Parameter17421, Size
call _ZN8Internal8AllocateEl
mov rax, rax                                                #Returning_REG1, RetREG_0
ret                                                         #
ret                                                         #


_ZN4Page3std4PageEP4PageP4Page:
mov byte ptr [rcx + 12 ], 0                                 #this_12, 0
mov qword ptr [rdx + 13 ], rcx                              #previus_13, this
mov r8, qword ptr [rdx + 21 ]                               #previus_21_REG0, previus_21
mov qword ptr [rcx + 21 ], r8                               #this_21, previus_21_REG0
add rcx, 37                                                 #this, 37
mov qword ptr [rcx + 0 ], rcx                               #this_0, this
mov r8, qword ptr [rcx + 0 ]                                #this_0_REG1, this_0
lea r9, qword ptr [rsp + 8 ]                                #Size_REG2, .STACK_8
add r8, r9                                                  #this_0_REG1, Size_REG2
mov qword ptr [rcx + 29 ], r8                               #this_29, this_0_REG1
ret                                                         #


_ZN4Page3std4PageEP4PageP6Bucket:
mov dword ptr [rcx + 8 ], 0                                 #this_8, 0
mov byte ptr [rcx + 12 ], 0                                 #this_12, 0
mov qword ptr [rcx + 13 ], 0                                #this_13, 0
mov qword ptr [rcx + 21 ], rdx                              #this_21, parent
add rcx, 37                                                 #this, 37
mov qword ptr [rcx + 0 ], rcx                               #this_0, this
mov r8, qword ptr [rcx + 0 ]                                #this_0_REG0, this_0
lea r9, qword ptr [rsp + 8 ]                                #Size_REG1, .STACK_8
add r8, r9                                                  #this_0_REG0, Size_REG1
mov qword ptr [rcx + 29 ], r8                               #this_29, this_0_REG0
ret                                                         #


_ZN4Page3std11Update_PageEP4Pagei:
mov dword ptr [rcx + 8 ], edx                               #this_8, size
mov r8, qword ptr [rcx + 0 ]                                #this_0_REG0, this_0
lea r9, qword ptr [rsp + 8 ]                                #Size_REG1, .STACK_8
add r8, r9                                                  #this_0_REG0, Size_REG1
mov qword ptr [rcx + 29 ], r8                               #this_29, this_0_REG0
ret                                                         #


_ZN6Bucket3std6BucketEP6BucketP6Bucket:
push rdi                                                    #Reg_rdi
push rbx                                                    #Reg_rbx
mov rdi, rdx                                                #previus, previus
mov rbx, rcx                                                #this, this
mov ecx, dword ptr [rip + _Z15ALLOCATION_SIZE ]             #REG__Z15ALLOCATION_SIZE_Parameter18716, .RIP__Z15ALLOCATION_SIZE
call _ZN8Internal18____Allocate_char_El
mov qword ptr [rbx + 0 ], rax                               #this_0, RetREG_0
mov rcx, qword ptr [rbx + 0 ]                               #this_0_REG1, this_0
mov rcx, rcx                                                #REG_this_0_REG1_Parameter19718, this_0_REG1
mov rdx, rbx                                                #REG_this_Parameter19895, this
call _ZN4Page3std4PageEP4PageP6Bucket
mov qword ptr [rbx + 13 ], rax                              #this_13, RetREG_2
mov rcx, qword ptr [rbx + 13 ]                              #this_13_REG3, this_13
mov qword ptr [rbx + 21 ], rcx                              #this_21, this_13_REG3
mov byte ptr [rbx + 12 ], 0                                 #this_12, 0
mov rcx, qword ptr [rdi + 29 ]                              #previus_29_REG4, previus_29
mov qword ptr [rbx + 29 ], rcx                              #this_29, previus_29_REG4
mov qword ptr [rdi + 29 ], rbx                              #previus_29, this
mov qword ptr [rbx + 37 ], rdi                              #this_37, previus
mov cl, byte ptr [rbx ]                                     #this_REG5, this
add cl, 53                                                  #this_REG5, 53
mov qword ptr [rbx + 45 ], cl                               #this_45, this_REG5
pop Reg_rbx                                                 #Reg_Reg_rbx
pop Reg_rdi                                                 #Reg_Reg_rdi
ret                                                         #


_ZN6Bucket3std6BucketEP6Bucket:
push rbx                                                    #Reg_rbx
mov rbx, rcx                                                #this, this
mov ecx, dword ptr [rip + _Z15ALLOCATION_SIZE ]             #REG__Z15ALLOCATION_SIZE_Parameter5447, .RIP__Z15ALLOCATION_SIZE
call _ZN8Internal27____Allocate_____char_ptr__El
mov qword ptr [rbx + 0 ], rax                               #this_0, RetREG_0
mov rcx, qword ptr [rbx + 0 ]                               #this_0_REG1, this_0
mov rcx, rcx                                                #REG_this_0_REG1_Parameter21726, this_0_REG1
mov rdx, rbx                                                #REG_this_Parameter14771, this
call _ZN4Page3std4PageEP4PageP6Bucket
mov qword ptr [rbx + 13 ], rax                              #this_13, RetREG_2
mov rcx, qword ptr [rbx + 13 ]                              #this_13_REG3, this_13
mov qword ptr [rbx + 21 ], rcx                              #this_21, this_13_REG3
mov byte ptr [rbx + 12 ], 0                                 #this_12, 0
mov qword ptr [rbx + 29 ], 0                                #this_29, 0
mov qword ptr [rbx + 37 ], 0                                #this_37, 0
mov cl, byte ptr [rbx ]                                     #this_REG4, this
add cl, 53                                                  #this_REG4, 53
mov qword ptr [rbx + 45 ], cl                               #this_45, this_REG4
pop Reg_rbx                                                 #Reg_Reg_rbx
ret                                                         #


_ZN13____List_int_12____Add_int_EP13____List_int_i:
push rbx                                                    #Reg_rbx
mov rbx, rcx                                                #this, this
if_10:
mov ecx, dword ptr [rbx + 0 ]                               #this_0_REG0, this_0
mov r8d, dword ptr [rbx + 0 ]                               #this_0_REG1, this_0
cmp ecx, r8d                                                #this_0_REG0, this_0_REG1
jl if_10_END                                                #if_10_END
mov ecx, dword ptr [rbx + 0 ]                               #this_0_REG2, this_0
imul ecx, ecx, 2                                            #this_0_REG2, this_0_REG2, 2
mov dword ptr [rbx + 0 ], ecx                               #this_0, this_0_REG2
mov ecx, dword ptr [rbx + 0 ]                               #this_0_REG3, this_0
mov ecx, ecx                                                #REG_this_0_REG3_Parameter11538, this_0_REG3
call _ZN3std8AllocateEi
mov qword ptr [rsp + 4 ], rax                               #.STACK_4, RetREG_4
mov rcx, qword ptr [rsp + 4 ]                               #REG_tmp_Parameter1869, .STACK_4
mov r8, qword ptr [rbx + 0 ]                                #this_0_REG5, this_0
mov rdx, r8                                                 #REG_this_0_REG5_Parameter19912, this_0_REG5
mov r8d, dword ptr [rbx + 0 ]                               #this_0_REG6, this_0
mov r8d, r8d                                                #REG_this_0_REG6_Parameter25667, this_0_REG6
call _Z15____Memcpy_int_PiPii
mov rcx, qword ptr [rsp + 4 ]                               #REG_tmp8, .STACK_4
mov qword ptr [rbx + 0 ], rcx                               #this_0, REG_tmp8
if_10_END:
mov rcx, qword ptr [rbx + 0 ]                               #this_0_REG9, this_0
mov r8d, dword ptr [rbx + 0 ]                               #this_0_REG11, this_0
lea rcx, qword ptr [rcx + r8 * 4 ]                          #this_0_REG9_REG10, *
mov r8d, dword ptr [rsp + 0 ]                               #REG_Element12, .STACK_0
mov dword ptr [rcx ], r8d                                   #this_0_REG9_REG10, REG_Element12
add dword ptr [rbx + 0 ], 1                                 #this_0, 1
add rsp, 12                                                 #.STACK, 12
pop Reg_rbx                                                 #Reg_Reg_rbx
ret                                                         #


_ZN13____List_int_8Pop_BackEP13____List_int_:
sub dword ptr [rcx + 0 ], 1                                 #this_0, 1
ret                                                         #


_ZN13____List_int_11____At_int_EP13____List_int_i:
if_11:
mov r8d, dword ptr [rcx + 0 ]                               #this_0_REG0, this_0
cmp edx, r8d                                                #i, this_0_REG0
jle if_11_END                                               #if_11_END
mov eax, 0                                                  #Returning_REG1, 0
ret                                                         #
if_11_END:
mov rcx, qword ptr [rcx + 0 ]                               #this_0_REG2, this_0
lea rcx, qword ptr [rcx + rdx * 4 ]                         #this_0_REG2_REG3, *
mov eax, dword ptr [rcx ]                                   #Returning_REG4, this_0_REG2_REG3
ret                                                         #
ret                                                         #


_Z13____List_int_P13____List_int_:
push rbx                                                    #Reg_rbx
mov rbx, rcx                                                #this, this
mov dword ptr [rbx + 0 ], 1                                 #this_0, 1
mov dword ptr [rbx + 0 ], 0                                 #this_0, 0
mov ecx, dword ptr [rbx + 0 ]                               #this_0_REG0, this_0
mov ecx, ecx                                                #REG_this_0_REG0_Parameter26299, this_0_REG0
call _ZN3std8AllocateEi
mov qword ptr [rbx + 0 ], rax                               #this_0, RetREG_1
mov rax, rbx                                                #Returning_REG2, this
pop Reg_rbx                                                 #Reg_Reg_rbx
ret                                                         #
pop Reg_rbx                                                 #Reg_Reg_rbx
ret                                                         #


.section .data                                              #.data
_ZN8Internal13MEMORY_COMMITE:
.long 0                                                     #0
_ZN8Internal14MEMORY_RESERVEE:
.long 0                                                     #0
_ZN8Internal14MEMORY_RELEASEE:
.long 0                                                     #0
_ZN8Internal14PAGE_READWRITEE:
.long 0                                                     #0
_ZN8Internal22STANDARD_OUTPUT_HANDLEE:
.long 0                                                     #0
_ZN8Internal21STANDARD_INPUT_HANDLEE:
.long 0                                                     #0
_ZN3std15ALLOCATION_SIZEE:
.long 0                                                     #0
_ZN3std12BUCKET_COUNTE:
.long 0                                                     #0
_ZN3std13BUCKET_BUFFERE:
.quad 0                                                     #0
_ZN3std12Bucket_StartE:
.quad 0                                                     #0
_ZN3std12Bucket_CacheE:
.quad 0                                                     #0
_ZN3std2PiE:
.quad 0                                                     #0
_ZN3std1EE:
.quad 0                                                     #0
_ZN3std3EpsE:
.quad 0                                                     #0
_ZN3std3InfE:
.quad 0                                                     #0
_ZN3std3NanE:
.quad 0                                                     #0
