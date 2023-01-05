.intel_syntax noprefix
.extern ReadConsoleA
.extern WriteFile
.extern GetStdHandle
.extern VirtualFree
.extern VirtualAlloc
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
sub rsp, 20		#.STACK, 20
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#REG_a_REG0_Parameter19169, a_REG0
call _Z13____List_int_P13____List_int_
lea rcx, qword ptr [rsp + 0 ]		#a_REG2, .STACK_0
mov rcx, rcx		#REG_a_REG2_Parameter15724, a_REG2
mov edx, 5		#REG_5_Parameter11478, 5
call _ZN13____List_int_12____Add_int_EP13____List_int_i
lea rcx, qword ptr [rsp + 0 ]		#a_REG4, .STACK_0
mov rcx, rcx		#REG_a_REG4_Parameter29358, a_REG4
mov edx, 2		#REG_2_Parameter26962, 2
call _ZN13____List_int_12____Add_int_EP13____List_int_i
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#REG_a_REG6_Parameter24464, a_REG6
call _ZN13____List_int_8Pop_BackEP13____List_int_
lea rcx, qword ptr [rsp + 0 ]		#a_REG8, .STACK_0
mov rcx, rcx		#REG_a_REG8_Parameter5705, a_REG8
mov edx, 0		#REG_0_Parameter28145, 0
call _ZN13____List_int_11____At_int_EP13____List_int_i
mov eax, eax		#Returning_REG10, RetREG_9
add rsp, 20		#.STACK, 20
ret 		#
add rsp, 20		#.STACK, 20
ret 		#


_Z4mainv:
push rbp		#Reg_rbp
push rsi		#Reg_rsi
push rdi		#Reg_rdi
push rbx		#Reg_rbx
mov dword ptr [rip + std_ALLOCATION_SIZE ], 700000		#.RIP_std_ALLOCATION_SIZE, 700000
mov dword ptr [rip + std_BUCKET_COUNT ], 100000		#.RIP_std_BUCKET_COUNT, 100000
mov ebx, dword ptr [rip + std_BUCKET_COUNT ]		#std_BUCKET_COUNT_REGISTER, .RIP_std_BUCKET_COUNT
mov ecx, ebx		#REG_std_BUCKET_COUNT_REGISTER_Parameter23281, std_BUCKET_COUNT_REGISTER
call _ZN8Internal18____Allocate_char_El
mov qword ptr [rip + std_BUCKET_BUFFER ], rax		#.RIP_std_BUCKET_BUFFER, RetREG_0
mov rdi, qword ptr [rip + std_BUCKET_BUFFER ]		#std_BUCKET_BUFFER_REGISTER, .RIP_std_BUCKET_BUFFER
mov rcx, rdi		#REG_std_BUCKET_BUFFER_REGISTER_Parameter16827, std_BUCKET_BUFFER_REGISTER
call _ZN6Bucket3std6BucketEP6Bucket
mov qword ptr [rip + std_Bucket_Start ], rax		#.RIP_std_Bucket_Start, RetREG_1
mov rsi, qword ptr [rip + std_Bucket_Start ]		#std_Bucket_Start_REGISTER, .RIP_std_Bucket_Start
mov qword ptr [rip + std_Bucket_Cache ], rsi		#.RIP_std_Bucket_Cache, std_Bucket_Start_REGISTER
mov rcx, 4886408106085781771		#REG_4886408106085813093, 4886408106085781771
mov qword ptr [rip + std_Pi ], rcx		#.RIP_std_Pi, REG_4886408106085813093
mov rcx, 4886407175215432982		#REG_4886407175215463315, 4886407175215432982
mov qword ptr [rip + std_E ], rcx		#.RIP_std_E, REG_4886407175215463315
mov qword ptr [rip + std_Eps ], 0		#.RIP_std_Eps, 0
mov qword ptr [rip + std_Inf ], -9223372036854775808		#.RIP_std_Inf, -9223372036854775808
mov rbp, qword ptr [rip + std_Inf ]		#std_Inf_REGISTER, .RIP_std_Inf
mov rbp, qword ptr [rip + std_Inf ]		#std_Inf_REGISTER, .RIP_std_Inf
sub rbp, rbp		#std_Inf_REGISTER, std_Inf_REGISTER
mov qword ptr [rip + std_Nan ], rbp		#.RIP_std_Nan, std_Inf_REGISTER
mov dword ptr [rip + Internal_MEMORY_COMMIT ], 4096		#.RIP_Internal_MEMORY_COMMIT, 4096
mov dword ptr [rip + Internal_MEMORY_RESERVE ], 8192		#.RIP_Internal_MEMORY_RESERVE, 8192
mov dword ptr [rip + Internal_MEMORY_RELEASE ], 32768		#.RIP_Internal_MEMORY_RELEASE, 32768
mov dword ptr [rip + Internal_PAGE_READWRITE ], 4		#.RIP_Internal_PAGE_READWRITE, 4
mov dword ptr [rip + Internal_STANDARD_OUTPUT_HANDLE ], 11		#.RIP_Internal_STANDARD_OUTPUT_HANDLE, 11
mov dword ptr [rip + Internal_STANDARD_INPUT_HANDLE ], 10		#.RIP_Internal_STANDARD_INPUT_HANDLE, 10
mov dword ptr [rip + std_ALLOCATION_SIZE ], 700000		#.RIP_std_ALLOCATION_SIZE, 700000
mov dword ptr [rip + std_BUCKET_COUNT ], 100000		#.RIP_std_BUCKET_COUNT, 100000
mov ebx, dword ptr [rip + std_BUCKET_COUNT ]		#std_BUCKET_COUNT_REGISTER, .RIP_std_BUCKET_COUNT
mov ecx, ebx		#REG_std_BUCKET_COUNT_REGISTER_Parameter9961, std_BUCKET_COUNT_REGISTER
call _ZN8Internal18____Allocate_char_El
mov qword ptr [rip + std_BUCKET_BUFFER ], rax		#.RIP_std_BUCKET_BUFFER, RetREG_2
mov rdi, qword ptr [rip + std_BUCKET_BUFFER ]		#std_BUCKET_BUFFER_REGISTER, .RIP_std_BUCKET_BUFFER
mov rcx, rdi		#REG_std_BUCKET_BUFFER_REGISTER_Parameter491, std_BUCKET_BUFFER_REGISTER
call _ZN6Bucket3std6BucketEP6Bucket
mov qword ptr [rip + std_Bucket_Start ], rax		#.RIP_std_Bucket_Start, RetREG_3
mov rsi, qword ptr [rip + std_Bucket_Start ]		#std_Bucket_Start_REGISTER, .RIP_std_Bucket_Start
mov qword ptr [rip + std_Bucket_Cache ], rsi		#.RIP_std_Bucket_Cache, std_Bucket_Start_REGISTER
mov rcx, 4886408106085781771		#REG_4886408106085799444, 4886408106085781771
mov qword ptr [rip + std_Pi ], rcx		#.RIP_std_Pi, REG_4886408106085799444
mov rcx, 4886407175215432982		#REG_4886407175215437646, 4886407175215432982
mov qword ptr [rip + std_E ], rcx		#.RIP_std_E, REG_4886407175215437646
mov qword ptr [rip + std_Eps ], 0		#.RIP_std_Eps, 0
mov qword ptr [rip + std_Inf ], -9223372036854775808		#.RIP_std_Inf, -9223372036854775808
mov rbp, qword ptr [rip + std_Inf ]		#std_Inf_REGISTER, .RIP_std_Inf
mov rbp, qword ptr [rip + std_Inf ]		#std_Inf_REGISTER, .RIP_std_Inf
sub rbp, rbp		#std_Inf_REGISTER, std_Inf_REGISTER
mov qword ptr [rip + std_Nan ], rbp		#.RIP_std_Nan, std_Inf_REGISTER
jmp _Z10Start_Testv		#_Z10Start_Testv
mov eax, 1		#Returning_REG4, 1
pop Reg_rbx		#Reg_Reg_rbx
pop Reg_rdi		#Reg_Reg_rdi
pop Reg_rsi		#Reg_Reg_rsi
pop Reg_rbp		#Reg_Reg_rbp
ret 		#
pop Reg_rbx		#Reg_Reg_rbx
pop Reg_rdi		#Reg_Reg_rdi
pop Reg_rsi		#Reg_Reg_rsi
pop Reg_rbp		#Reg_Reg_rbp
ret 		#


_Z15____Memcpy_int_PiPii:
mov r9d, 0		#i, 0
cmp r9d, r8d		#i, Size
jge while_3_END		#while_3_END
while_3:
lea r10, qword ptr [rcx + r9 * 4 ]		#dest_REG0, *
mov r11d, dword ptr [rdx + r9 * 4 ]		#source_REG1, *
mov dword ptr [r10 ], r11d		#dest_REG0, source_REG1
add r9d, 1		#i, 1
cmp r9d, r8d		#i, Size
jge while_3_END		#while_3_END
jmp while_3		#while_3
while_3_END:
ret 		#
ret 		#


_ZN3std13Get_Free_PageEv:
mov rcx, qword ptr [rip + Get_Free_Page_Bucket_Cache ]		#Get_Free_Page_Bucket_Cache_REG0, .RIP_Get_Free_Page_Bucket_Cache
mov rcx, qword ptr [rcx + 0 ]		#Get_Free_Page_Bucket_Cache_REG0_0_REG1, Get_Free_Page_Bucket_Cache_REG0_0
mov rcx, rcx		#Current, Get_Free_Page_Bucket_Cache_REG0_0_REG1
mov r8, rcx		#Last, Current
cmp rcx, 0		#Current, 0
je while_4_END		#while_4_END
while_4:
mov r8, rcx		#Last, Current
if_5:
mov r9b, byte ptr [rcx + 0 ]		#Current_0_REG2, Current_0
cmp r9b, 1		#Current_0_REG2, 1
jne else_6		#else_6
mov r9, qword ptr [rcx + 0 ]		#Current_0_REG3, Current_0
mov rcx, r9		#Current, Current_0_REG3
jmp else_6_END		#else_6_END
if_5_END:
else_6:
mov r9, qword ptr [rip + else_6_Bucket_Cache ]		#else_6_Bucket_Cache_REG4, .RIP_else_6_Bucket_Cache
mov qword ptr [r9 + 0 ], rcx		#else_6_Bucket_Cache_REG4_0, Current
mov rax, rcx		#Returning_REG5, Current
ret 		#
else_6_END:
cmp rcx, 0		#Current, 0
je while_4_END		#while_4_END
jmp while_4		#while_4
while_4_END:
if_7:
mov rcx, qword ptr [r8 + 0 ]		#Last_0_REG6, Last_0
mov r9, qword ptr [r8 + 0 ]		#+_0_REG7, Last_0
lea r10, qword ptr [rip + std_ALLOCATION_SIZE ]		#std_ALLOCATION_SIZE_REG8, .RIP_std_ALLOCATION_SIZE
add r9, r10		#+_0_REG7, std_ALLOCATION_SIZE_REG8
cmp rcx, r9		#Last_0_REG6, +_0_REG7
jl if_7_END		#if_7_END
mov byte ptr [r8 + 0 ], 1		#Last_0, 1
mov rax, 0		#Returning_REG9, 0
ret 		#
if_7_END:
mov rcx, qword ptr [r8 + 0 ]		#Last_0_REG10, Last_0
mov rcx, rcx		#REG_Last_0_REG10_Parameter2995, Last_0_REG10
mov rdx, r8		#REG_Last_Parameter11942, Last
call _ZN4Page3std4PageEP4PageP4Page
mov rcx, rax		#Result, RetREG_11
mov rax, rcx		#Returning_REG12, Result
ret 		#
ret 		#


_ZN3std15Get_Free_BucketEv:
mov rcx, qword ptr [rip + std_Bucket_Cache ]		#Current, .RIP_std_Bucket_Cache
mov r8, rcx		#Last, Current
cmp rcx, 0		#Current, 0
je while_8_END		#while_8_END
while_8:
mov r8, rcx		#Last, Current
if_9:
mov r9, qword ptr [rcx + 0 ]		#Current_0_REG0, Current_0
mov rcx, r9		#Current, Current_0_REG0
jmp else_10_END		#else_10_END
if_9_END:
else_10:
mov qword ptr [rip + std_Bucket_Cache ], rcx		#.RIP_std_Bucket_Cache, Current
mov rax, rcx		#Returning_REG1, Current
ret 		#
else_10_END:
cmp rcx, 0		#Current, 0
je while_8_END		#while_8_END
jmp while_8		#while_8
while_8_END:
mov rcx, qword ptr [r8 + 0 ]		#Last_0_REG2, Last_0
mov rcx, rcx		#REG_Last_0_REG2_Parameter4827, Last_0_REG2
mov rdx, r8		#REG_Last_Parameter5436, Last
call _ZN6Bucket3std6BucketEP6BucketP6Bucket
mov rcx, rax		#Result, RetREG_3
mov qword ptr [rip + std_Bucket_Cache ], rcx		#.RIP_std_Bucket_Cache, Result
mov rax, rcx		#Returning_REG4, Result
ret 		#
ret 		#


_ZN3std8AllocateEi:
push rsi		#Reg_rsi
push rdi		#Reg_rdi
push rbx		#Reg_rbx
mov ebx, ecx		#Size, Size
if_11:
cmp ebx, dword ptr [rip + std_ALLOCATION_SIZE ]		#Size, .RIP_std_ALLOCATION_SIZE
jle if_11_END		#if_11_END
add ebx, 37		#Size, 37
mov ecx, ebx		#REG_Size_Parameter32391, Size
call _ZN8Internal27____Allocate_____char_ptr__El
mov qword ptr [rsp + 0 ], rax		#.STACK_0, RetREG_0
mov rcx, qword ptr [rsp + 0 ]		#REG_Result_Parameter14604, .STACK_0
mov r8, qword ptr [rip + if_11_Bucket_Cache ]		#if_11_Bucket_Cache_REG1, .RIP_if_11_Bucket_Cache
mov r8, qword ptr [r8 + 0 ]		#if_11_Bucket_Cache_REG1_0_REG2, if_11_Bucket_Cache_REG1_0
mov rdx, r8		#REG_if_11_Bucket_Cache_REG1_0_REG2_Parameter3902, if_11_Bucket_Cache_REG1_0_REG2
call _ZN4Page3std4PageEP4PageP4Page
mov rcx, qword ptr [rsp + 0 ]		#Result_REG4, .STACK_0
mov rax, qword ptr [rcx + 0 ]		#Returning_REG5, Result_REG4_0
add rsp, 8		#.STACK, 8
pop Reg_rbx		#Reg_Reg_rbx
pop Reg_rdi		#Reg_Reg_rdi
pop Reg_rsi		#Reg_Reg_rsi
ret 		#
if_11_END:
call _ZN3std13Get_Free_PageEv
mov rdi, rax		#New_Page, RetREG_6
call _ZN3std15Get_Free_BucketEv
mov rsi, rax		#New_Bucket, RetREG_7
if_12:
cmp rdi, 0		#New_Page, 0
jne if_12_END		#if_12_END
call _ZN3std13Get_Free_PageEv
mov rdi, rax		#New_Page, RetREG_8
if_12_END:
mov rcx, rdi		#REG_New_Page_Parameter153, New_Page
mov edx, ebx		#REG_Size_Parameter292, Size
call _ZN4Page3std11Update_PageEP4Pagei
mov byte ptr [rdi + 0 ], 1		#New_Page_0, 1
mov qword ptr [rip + std_Bucket_Cache ], rsi		#.RIP_std_Bucket_Cache, New_Bucket
mov rcx, qword ptr [rip + Allocate_Bucket_Cache ]		#Allocate_Bucket_Cache_REG10, .RIP_Allocate_Bucket_Cache
mov qword ptr [rcx + 0 ], rdi		#Allocate_Bucket_Cache_REG10_0, New_Page
mov rcx, qword ptr [rip + Allocate_Bucket_Cache ]		#Allocate_Bucket_Cache_REG11, .RIP_Allocate_Bucket_Cache
add dword ptr [rcx + 0 ], 1		#Allocate_Bucket_Cache_REG11_0, 1
mov rax, qword ptr [rdi + 0 ]		#Returning_REG12, New_Page_0
add rsp, 8		#.STACK, 8
pop Reg_rbx		#Reg_Reg_rbx
pop Reg_rdi		#Reg_Reg_rdi
pop Reg_rsi		#Reg_Reg_rsi
ret 		#
add rsp, 8		#.STACK, 8
pop Reg_rbx		#Reg_Reg_rbx
pop Reg_rdi		#Reg_Reg_rdi
pop Reg_rsi		#Reg_Reg_rsi
ret 		#


_ZN8Internal8AllocateEl:
push rbx		#Reg_rbx
mov rcx, 0		#REG_0_Parameter12382, 0
mov Non-Volatile15141, rcx		#Non-Volatile15141, Current_Volatile7711
mov rdx, rbx		#REG_Size_Parameter17421, Size
mov ecx, dword ptr [rip + Internal_MEMORY_COMMIT ]		#REG_Internal_MEMORY_COMMIT0, .RIP_Internal_MEMORY_COMMIT
or ecx, dword ptr [rip + Internal_MEMORY_RESERVE ]		#REG_Internal_MEMORY_COMMIT0, .RIP_Internal_MEMORY_RESERVE
mov r8d, ecx		#REG_REG_Internal_MEMORY_COMMIT0_Parameter18716, REG_Internal_MEMORY_COMMIT0
mov r9d, dword ptr [rip + Internal_PAGE_READWRITE ]		#REG_Internal_PAGE_READWRITE_Parameter19718, .RIP_Internal_PAGE_READWRITE
call VirtualAlloc
mov rax, rax		#Returning_REG2, RetREG_1
pop Reg_rbx		#Reg_Reg_rbx
ret 		#
pop Reg_rbx		#Reg_Reg_rbx
ret 		#


_ZN8Internal18____Allocate_char_El:
imul rcx, rcx, 1		#Size, Size, 1
mov rcx, rcx		#REG_Size_Parameter19895, Size
call _ZN8Internal8AllocateEl
mov rax, rax		#Returning_REG1, RetREG_0
ret 		#
ret 		#


_ZN8Internal27____Allocate_____char_ptr__El:
imul rcx, rcx, 8		#Size, Size, 8
mov rcx, rcx		#REG_Size_Parameter5447, Size
call _ZN8Internal8AllocateEl
mov rax, rax		#Returning_REG1, RetREG_0
ret 		#
ret 		#


_ZN4Page3std4PageEP4PageP4Page:
mov byte ptr [rcx + 0 ], 0		#this_0, 0
mov qword ptr [rdx + 0 ], rcx		#previus_0, this
mov r8, qword ptr [rdx + 0 ]		#previus_0_REG0, previus_0
mov qword ptr [rcx + 0 ], r8		#this_0, previus_0_REG0
add rcx, 37		#this, 37
mov qword ptr [rcx + 0 ], rcx		#this_0, this
mov r8, qword ptr [rcx + 0 ]		#this_0_REG1, this_0
lea r9, qword ptr [r9d ]		#Size_REG2, Size
add r8, r9		#this_0_REG1, Size_REG2
mov qword ptr [rcx + 0 ], r8		#this_0, this_0_REG1
ret 		#


_ZN4Page3std4PageEP4PageP6Bucket:
mov dword ptr [rcx + 0 ], 0		#this_0, 0
mov byte ptr [rcx + 0 ], 0		#this_0, 0
mov qword ptr [rcx + 0 ], 0		#this_0, 0
mov qword ptr [rcx + 0 ], rdx		#this_0, parent
add rcx, 37		#this, 37
mov qword ptr [rcx + 0 ], rcx		#this_0, this
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
lea r9, qword ptr [r9d ]		#Size_REG1, Size
add r8, r9		#this_0_REG0, Size_REG1
mov qword ptr [rcx + 0 ], r8		#this_0, this_0_REG0
ret 		#


_ZN4Page3std11Update_PageEP4Pagei:
mov dword ptr [rcx + 0 ], edx		#this_0, size
mov r8, qword ptr [rcx + 0 ]		#this_0_REG0, this_0
lea r9, qword ptr [r9d ]		#Size_REG1, Size
add r8, r9		#this_0_REG0, Size_REG1
mov qword ptr [rcx + 0 ], r8		#this_0, this_0_REG0
ret 		#


_ZN6Bucket3std6BucketEP6BucketP6Bucket:
push rdi		#Reg_rdi
push rbx		#Reg_rbx
mov rdi, rdx		#previus, previus
mov rbx, rcx		#this, this
mov ecx, dword ptr [rip + std_ALLOCATION_SIZE ]		#REG_std_ALLOCATION_SIZE_Parameter21726, .RIP_std_ALLOCATION_SIZE
call _ZN8Internal18____Allocate_char_El
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_0
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG1, this_0
mov rcx, rcx		#REG_this_0_REG1_Parameter14771, this_0_REG1
mov rdx, rbx		#REG_this_Parameter11538, this
call _ZN4Page3std4PageEP4PageP6Bucket
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_2
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG3, this_0
mov qword ptr [rbx + 0 ], rcx		#this_0, this_0_REG3
mov byte ptr [rbx + 0 ], 0		#this_0, 0
mov rcx, qword ptr [rdi + 0 ]		#previus_0_REG4, previus_0
mov qword ptr [rbx + 0 ], rcx		#this_0, previus_0_REG4
mov qword ptr [rdi + 0 ], rbx		#previus_0, this
mov qword ptr [rbx + 0 ], rdi		#this_0, previus
mov cl, byte ptr [rbx ]		#this_REG5, this
add cl, 53		#this_REG5, 53
mov qword ptr [rbx + 0 ], cl		#this_0, this_REG5
pop Reg_rbx		#Reg_Reg_rbx
pop Reg_rdi		#Reg_Reg_rdi
ret 		#


_ZN6Bucket3std6BucketEP6Bucket:
push rbx		#Reg_rbx
mov rbx, rcx		#this, this
mov ecx, dword ptr [rip + std_ALLOCATION_SIZE ]		#REG_std_ALLOCATION_SIZE_Parameter1869, .RIP_std_ALLOCATION_SIZE
call _ZN8Internal27____Allocate_____char_ptr__El
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_0
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG1, this_0
mov rcx, rcx		#REG_this_0_REG1_Parameter19912, this_0_REG1
mov rdx, rbx		#REG_this_Parameter25667, this
call _ZN4Page3std4PageEP4PageP6Bucket
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_2
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG3, this_0
mov qword ptr [rbx + 0 ], rcx		#this_0, this_0_REG3
mov byte ptr [rbx + 0 ], 0		#this_0, 0
mov qword ptr [rbx + 0 ], 0		#this_0, 0
mov qword ptr [rbx + 0 ], 0		#this_0, 0
mov cl, byte ptr [rbx ]		#this_REG4, this
add cl, 53		#this_REG4, 53
mov qword ptr [rbx + 0 ], cl		#this_0, this_REG4
pop Reg_rbx		#Reg_Reg_rbx
ret 		#


_ZN13____List_int_12____Add_int_EP13____List_int_i:
push rbx		#Reg_rbx
mov rbx, rcx		#this, this
if_13:
mov ecx, dword ptr [rbx + 0 ]		#this_0_REG0, this_0
mov r8d, dword ptr [rbx + 0 ]		#this_0_REG1, this_0
cmp ecx, r8d		#this_0_REG0, this_0_REG1
jl if_13_END		#if_13_END
mov ecx, dword ptr [rbx + 0 ]		#this_0_REG2, this_0
imul ecx, ecx, 2		#this_0_REG2, this_0_REG2, 2
mov dword ptr [rbx + 0 ], ecx		#this_0, this_0_REG2
mov ecx, dword ptr [rbx + 0 ]		#this_0_REG3, this_0
mov ecx, ecx		#REG_this_0_REG3_Parameter26299, this_0_REG3
call _ZN3std8AllocateEi
mov qword ptr [rsp + 4 ], rax		#.STACK_4, RetREG_4
mov rcx, qword ptr [rsp + 4 ]		#REG_tmp_Parameter17035, .STACK_4
mov r8, qword ptr [rbx + 0 ]		#this_0_REG5, this_0
mov rdx, r8		#REG_this_0_REG5_Parameter9894, this_0_REG5
mov r8d, dword ptr [rbx + 0 ]		#this_0_REG6, this_0
mov r8d, r8d		#REG_this_0_REG6_Parameter28703, this_0_REG6
call _Z15____Memcpy_int_PiPii
mov rcx, qword ptr [rsp + 4 ]		#REG_tmp8, .STACK_4
mov qword ptr [rbx + 0 ], rcx		#this_0, REG_tmp8
if_13_END:
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG9, this_0
mov r8d, dword ptr [rbx + 0 ]		#this_0_REG11, this_0
lea rcx, qword ptr [rcx + r8 * 4 ]		#this_0_REG9_REG10, *
mov r8d, dword ptr [rsp + 0 ]		#REG_Element12, .STACK_0
mov dword ptr [rcx ], r8d		#this_0_REG9_REG10, REG_Element12
add dword ptr [rbx + 0 ], 1		#this_0, 1
add rsp, 12		#.STACK, 12
pop Reg_rbx		#Reg_Reg_rbx
ret 		#


_ZN13____List_int_8Pop_BackEP13____List_int_:
sub dword ptr [rcx + 0 ], 1		#this_0, 1
ret 		#


_ZN13____List_int_11____At_int_EP13____List_int_i:
if_14:
mov r8d, dword ptr [rcx + 0 ]		#this_0_REG0, this_0
cmp edx, r8d		#i, this_0_REG0
jle if_14_END		#if_14_END
mov eax, 0		#Returning_REG1, 0
ret 		#
if_14_END:
mov rcx, qword ptr [rcx + 0 ]		#this_0_REG2, this_0
lea rcx, qword ptr [rcx + rdx * 4 ]		#this_0_REG2_REG3, *
mov eax, dword ptr [rcx ]		#Returning_REG4, this_0_REG2_REG3
ret 		#
ret 		#


_Z13____List_int_P13____List_int_:
push rbx		#Reg_rbx
mov rbx, rcx		#this, this
mov dword ptr [rbx + 0 ], 1		#this_0, 1
mov dword ptr [rbx + 0 ], 0		#this_0, 0
mov ecx, dword ptr [rbx + 0 ]		#this_0_REG0, this_0
mov ecx, ecx		#REG_this_0_REG0_Parameter23811, this_0_REG0
call _ZN3std8AllocateEi
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_1
mov rax, rbx		#Returning_REG2, this
pop Reg_rbx		#Reg_Reg_rbx
ret 		#
pop Reg_rbx		#Reg_Reg_rbx
ret 		#


.section .data		#.data
Internal_MEMORY_COMMIT:
.word 4096		#4096
Internal_MEMORY_RESERVE:
.word 8192		#8192
Internal_MEMORY_RELEASE:
.word 32768		#32768
Internal_PAGE_READWRITE:
.word 4		#4
Internal_STANDARD_OUTPUT_HANDLE:
.word 11		#11
Internal_STANDARD_INPUT_HANDLE:
.word 10		#10
