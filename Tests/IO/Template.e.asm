.intel_syntax noprefix
.global _Z6_INIT_v
.global _Z4mainv
.global _Z10Start_Testv
.section .text		#.text
_Z10Start_Testv:
lea rcx, qword ptr [rsp + 0 ]		#a_REG0, .STACK_0
mov rcx, rcx		#REG_a_REG0_Parameter41, a_REG0
call _Z13____List_int_P13____List_int_
lea rcx, qword ptr [rsp + 0 ]		#a_REG2, .STACK_0
mov rcx, rcx		#REG_a_REG2_Parameter18467, a_REG2
mov edx, 5		#REG_5_Parameter6334, 5
call _ZN13____List_int_12____Add_int_EP13____List_int_i
lea rcx, qword ptr [rsp + 0 ]		#a_REG4, .STACK_0
mov rcx, rcx		#REG_a_REG4_Parameter26500, a_REG4
mov edx, 2		#REG_2_Parameter19169, 2
call _ZN13____List_int_12____Add_int_EP13____List_int_i
lea rcx, qword ptr [rsp + 0 ]		#a_REG6, .STACK_0
mov rcx, rcx		#REG_a_REG6_Parameter15724, a_REG6
call _ZN13____List_int_8Pop_BackEP13____List_int_
lea rcx, qword ptr [rsp + 0 ]		#a_REG8, .STACK_0
mov rcx, rcx		#REG_a_REG8_Parameter11478, a_REG8
mov edx, 0		#REG_0_Parameter29358, 0
call _ZN13____List_int_11____At_int_EP13____List_int_i
mov eax, eax		#Returning_REG10, RetREG_9
ret 		#
ret 		#


_Z4mainv:
jmp _Z10Start_Testv		#_Z10Start_Testv
mov eax, 1		#Returning_REG0, 1
ret 		#
ret 		#


_Z15____Memcpy_int_PiPii:
mov r9d, 0		#i, 0
cmp r9d, r8d		#i, Size
jge while_0_END		#while_0_END
while_0:
lea r10, qword ptr [rcx + r9 * 4 ]		#dest_REG0, *
mov r11d, dword ptr [rdx + r9 * 4 ]		#source_REG1, *
mov dword ptr [r10 ], r11d		#dest_REG0, source_REG1
add r9d, 1		#i, 1
cmp r9d, r8d		#i, Size
jge while_0_END		#while_0_END
jmp while_0		#while_0
while_0_END:
ret 		#
ret 		#


_Z27____Internal_Allocate_char_i:
mov r8, rdx		#Size_REMAINDER18716, REMAINDER_19718
mov eax, 1		#1_QUOTIENT17421, 1
mul ecx		#Size
mov ecx, eax		#Size, 1_QUOTIENT17421
mov rdx, r8		#REMAINDER_19718, Size_REMAINDER18716
mov r8, rdx		#Size_REMAINDER5447, REMAINDER_21726
mov eax, 1		#1_QUOTIENT19895, 1
mul ecx		#Size
mov ecx, eax		#Size, 1_QUOTIENT19895
mov rdx, r8		#REMAINDER_21726, Size_REMAINDER5447
mov ecx, ecx		#REG_Size_Parameter26962, Size
call _V17internal_allocatel_rPh
mov rax, rax		#Returning_REG1, RetREG_0
ret 		#
ret 		#


_Z36____Internal_Allocate_____char_ptr__i:
mov r8, rdx		#Size_REMAINDER11538, REMAINDER_1869
mov eax, 8		#8_QUOTIENT14771, 8
mul ecx		#Size
mov ecx, eax		#Size, 8_QUOTIENT14771
mov rdx, r8		#REMAINDER_1869, Size_REMAINDER11538
mov r8, rdx		#Size_REMAINDER25667, REMAINDER_26299
mov eax, 8		#8_QUOTIENT19912, 8
mul ecx		#Size
mov ecx, eax		#Size, 8_QUOTIENT19912
mov rdx, r8		#REMAINDER_26299, Size_REMAINDER25667
mov ecx, ecx		#REG_Size_Parameter24464, Size
call _V17internal_allocatel_rPh
mov rax, rax		#Returning_REG1, RetREG_0
ret 		#
ret 		#


_Z6_INIT_v:
mov dword ptr [rip + std_ALLOCATION_SIZE ], 700000		#.RIP_std_ALLOCATION_SIZE, 700000
mov dword ptr [rip + std_BUCKET_COUNT ], 100000		#.RIP_std_BUCKET_COUNT, 100000
mov ecx, dword ptr [rip + std_BUCKET_COUNT ]		#REG_std_BUCKET_COUNT_Parameter5705, .RIP_std_BUCKET_COUNT
call _Z27____Internal_Allocate_char_i
mov qword ptr [rip + std_BUCKET_BUFFER ], rax		#.RIP_std_BUCKET_BUFFER, RetREG_0
mov rcx, qword ptr [rip + std_BUCKET_BUFFER ]		#REG_std_BUCKET_BUFFER_Parameter28145, .RIP_std_BUCKET_BUFFER
call _ZN6Bucket3std6BucketEP6Bucket
mov qword ptr [rip + std_Bucket_Start ], rax		#.RIP_std_Bucket_Start, RetREG_1
mov rcx, qword ptr [rip + std_Bucket_Start ]		#REG_std_Bucket_Start2, .RIP_std_Bucket_Start
mov qword ptr [rip + std_Bucket_Cache ], rcx		#.RIP_std_Bucket_Cache, REG_std_Bucket_Start2
mov rcx, 4886408106085781771		#REG_4886408106085798806, 4886408106085781771
movsd qword ptr [rip + std_Pi ], rcx		#.RIP_std_Pi, REG_4886408106085798806
mov rcx, 4886407175215432982		#REG_4886407175215442876, 4886407175215432982
movsd qword ptr [rip + std_E ], rcx		#.RIP_std_E, REG_4886407175215442876
mov rcx, 0		#REG_28703, 0
movsd qword ptr [rip + std_Eps ], rcx		#.RIP_std_Eps, REG_28703
mov rcx, -4332462841530417152		#REG_-4332462841530393341, -4332462841530417152
movsd qword ptr [rip + std_Inf ], rcx		#.RIP_std_Inf, REG_-4332462841530393341
movsd xmm0, qword ptr [rip + std_Inf ]		#REG_std_Inf3, .RIP_std_Inf
subsd xmm0, qword ptr [rip + std_Inf ]		#REG_std_Inf3, .RIP_std_Inf
movsd qword ptr [rip + std_Nan ], xmm0		#.RIP_std_Nan, REG_std_Inf3
mov qword ptr [rip + std_MAX_CONSOLE_BUFFER_LENGHT ], 4096		#.RIP_std_MAX_CONSOLE_BUFFER_LENGHT, 4096
mov dword ptr [rip + std_GENERIC_WRITE ], 1073741824		#.RIP_std_GENERIC_WRITE, 1073741824
mov dword ptr [rip + std_GENERIC_READ ], 2147483648		#.RIP_std_GENERIC_READ, 2147483648
mov dword ptr [rip + std_FILE_SHARE_NONE ], 0		#.RIP_std_FILE_SHARE_NONE, 0
mov dword ptr [rip + std_FILE_SHARE_READ ], 1		#.RIP_std_FILE_SHARE_READ, 1
mov dword ptr [rip + std_FILE_SHARE_WRITE ], 2		#.RIP_std_FILE_SHARE_WRITE, 2
mov dword ptr [rip + std_FILE_SHARE_DELETE ], 4		#.RIP_std_FILE_SHARE_DELETE, 4
mov dword ptr [rip + std_CREATE_NEW ], 1		#.RIP_std_CREATE_NEW, 1
mov dword ptr [rip + std_CREATE_ALWAYS ], 2		#.RIP_std_CREATE_ALWAYS, 2
mov dword ptr [rip + std_OPEN_EXISTING ], 3		#.RIP_std_OPEN_EXISTING, 3
mov dword ptr [rip + std_OPEN_ALWAYS ], 4		#.RIP_std_OPEN_ALWAYS, 4
mov dword ptr [rip + std_TRUNCATE_EXISTING ], 4		#.RIP_std_TRUNCATE_EXISTING, 4
mov dword ptr [rip + std_FILE_ATTRIBUTE_NORMAL ], 128		#.RIP_std_FILE_ATTRIBUTE_NORMAL, 128
mov dword ptr [rip + std_FILE_ATTRIBUTE_FOLDER ], 16		#.RIP_std_FILE_ATTRIBUTE_FOLDER, 16
mov dword ptr [rip + std_MAXIMUM_PATH_LENGTH ], 260		#.RIP_std_MAXIMUM_PATH_LENGTH, 260
mov dword ptr [rip + std_ERROR_INSUFFICIENT_BUFFER ], 122		#.RIP_std_ERROR_INSUFFICIENT_BUFFER, 122
mov dword ptr [rip + std_MINIMUM_PROCESS_FILENAME_LENGTH ], 50		#.RIP_std_MINIMUM_PROCESS_FILENAME_LENGTH, 50
ret 		#


_ZN3std13Get_Free_PageEv:
mov rcx, qword ptr [rip + Get_Free_Page_Bucket_Cache ]		#Get_Free_Page_Bucket_Cache_REG0, .RIP_Get_Free_Page_Bucket_Cache
mov rcx, qword ptr [rcx + 0 ]		#Get_Free_Page_Bucket_Cache_REG0_0_REG1, Get_Free_Page_Bucket_Cache_REG0_0
mov rcx, rcx		#Current, Get_Free_Page_Bucket_Cache_REG0_0_REG1
mov r8, rcx		#Last, Current
cmp rcx, 0		#Current, 0
je while_1_END		#while_1_END
while_1:
mov r8, rcx		#Last, Current
if_2:
mov r9b, byte ptr [rcx + 0 ]		#Current_0_REG2, Current_0
cmp r9b, 1		#Current_0_REG2, 1
jne else_3		#else_3
mov r9, qword ptr [rcx + 0 ]		#Current_0_REG3, Current_0
mov rcx, r9		#Current, Current_0_REG3
jmp else_3_END		#else_3_END
if_2_END:
else_3:
mov r9, qword ptr [rip + else_3_Bucket_Cache ]		#else_3_Bucket_Cache_REG4, .RIP_else_3_Bucket_Cache
mov qword ptr [r9 + 0 ], rcx		#else_3_Bucket_Cache_REG4_0, Current
mov rax, rcx		#Returning_REG5, Current
ret 		#
else_3_END:
cmp rcx, 0		#Current, 0
je while_1_END		#while_1_END
jmp while_1		#while_1
while_1_END:
if_4:
mov rcx, qword ptr [r8 + 0 ]		#Last_0_REG6, Last_0
mov r9, qword ptr [r8 + 0 + 0 ]		#+_0_REG7, +_0
mov r9, r9		#REG_Initial_Heap8, Initial_Heap
add r9, qword ptr [rip + std_ALLOCATION_SIZE ]		#REG_Initial_Heap8, .RIP_std_ALLOCATION_SIZE
cmp rcx, r9		#Last_0_REG6, REG_Initial_Heap8
jl if_4_END		#if_4_END
mov byte ptr [r8 + 0 + 0 ], 1		#+_0, 1
mov rax, 0		#Returning_REG9, 0
ret 		#
if_4_END:
mov rcx, qword ptr [r8 + 0 ]		#Last_0_REG10, Last_0
mov rcx, rcx		#REG_Last_0_REG10_Parameter23281, Last_0_REG10
call _Z4PageP4Page
mov rcx, rax		#Result, RetREG_11
mov rax, rcx		#Returning_REG12, Result
ret 		#
ret 		#


_ZN3std15Get_Free_BucketEv:
mov rcx, qword ptr [rip + std_Bucket_Cache ]		#Current, .RIP_std_Bucket_Cache
mov r8, rcx		#Last, Current
cmp rcx, 0		#Current, 0
je while_5_END		#while_5_END
while_5:
mov r8, rcx		#Last, Current
if_6:
mov r9, qword ptr [rcx + 0 ]		#Current_0_REG0, Current_0
mov rcx, r9		#Current, Current_0_REG0
jmp else_7_END		#else_7_END
if_6_END:
else_7:
mov qword ptr [rip + std_Bucket_Cache ], rcx		#.RIP_std_Bucket_Cache, Current
mov rax, rcx		#Returning_REG1, Current
ret 		#
else_7_END:
cmp rcx, 0		#Current, 0
je while_5_END		#while_5_END
jmp while_5		#while_5
while_5_END:
mov rcx, qword ptr [r8 + 0 ]		#Last_0_REG2, Last_0
mov rcx, rcx		#REG_Last_0_REG2_Parameter16827, Last_0_REG2
call _ZN6Bucket3std6BucketEP6Bucket
mov rcx, rax		#Result, RetREG_3
mov qword ptr [rip + std_Bucket_Cache ], rcx		#.RIP_std_Bucket_Cache, Result
mov rax, rcx		#Returning_REG4, Result
ret 		#
ret 		#


_ZN3std8AllocateEi:
push rbp		#rbp
push rsi		#rsi
push rdi		#rdi
push rbx		#rbx
mov ebx, ecx		#Size, Size
if_8:
cmp ebx, dword ptr [rip + std_ALLOCATION_SIZE ]		#Size, .RIP_std_ALLOCATION_SIZE
jle if_8_END		#if_8_END
add ebx, 37		#Size, 37
mov ecx, ebx		#REG_Size_Parameter9961, Size
call _Z36____Internal_Allocate_____char_ptr__i
mov rcx, rax		#Result, RetREG_0
mov rcx, rcx		#REG_Result_Parameter491, Result
mov r8, qword ptr [rip + if_8_Bucket_Cache ]		#if_8_Bucket_Cache_REG1, .RIP_if_8_Bucket_Cache
mov r8, qword ptr [r8 + 0 ]		#if_8_Bucket_Cache_REG1_0_REG2, if_8_Bucket_Cache_REG1_0
mov rdx, r8		#REG_if_8_Bucket_Cache_REG1_0_REG2_Parameter2995, if_8_Bucket_Cache_REG1_0_REG2
call _ZN4Page3std4PageEP4PageP4Page
mov rax, rdi		#Returning_REG4, Buffer
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
ret 		#
if_8_END:
call _ZN3std13Get_Free_PageEv
mov rsi, rax		#New_Page, RetREG_5
call _ZN3std15Get_Free_BucketEv
mov rbp, rax		#New_Bucket, RetREG_6
if_9:
cmp rsi, 0		#New_Page, 0
jne if_9_END		#if_9_END
call _ZN3std13Get_Free_PageEv
mov rsi, rax		#New_Page, RetREG_7
if_9_END:
mov rcx, rsi		#REG_New_Page_Parameter11942, New_Page
mov edx, ebx		#REG_Size_Parameter4827, Size
call _ZN4Page3std11Update_PageEP4Pagei
mov byte ptr [rsi + 0 ], 1		#New_Page_0, 1
mov qword ptr [rip + std_Bucket_Cache ], rbp		#.RIP_std_Bucket_Cache, New_Bucket
mov rcx, qword ptr [rip + Allocate_Bucket_Cache ]		#Allocate_Bucket_Cache_REG9, .RIP_Allocate_Bucket_Cache
mov qword ptr [rcx + 0 ], rsi		#Allocate_Bucket_Cache_REG9_0, New_Page
mov rcx, qword ptr [rip + Allocate_Bucket_Cache ]		#Allocate_Bucket_Cache_REG10, .RIP_Allocate_Bucket_Cache
add dword ptr [rcx + 0 ], 1		#Allocate_Bucket_Cache_REG10_0, 1
mov rax, rdi		#Returning_REG11, Buffer
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
ret 		#
pop rbx		#rbx
pop rdi		#rdi
pop rsi		#rsi
pop rbp		#rbp
ret 		#


_Z13____List_int_P13____List_int_:
push rbx		#rbx
mov rbx, rcx		#this, this
mov dword ptr [rbx + 0 ], 1		#this_0, 1
mov dword ptr [rbx + 0 ], 0		#this_0, 0
mov ecx, dword ptr [rbx + 0 ]		#this_0_REG0, this_0
mov ecx, ecx		#REG_this_0_REG0_Parameter5436, this_0_REG0
call _ZN3std8AllocateEi
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_1
mov rax, rbx		#Returning_REG2, this
pop rbx		#rbx
ret 		#
pop rbx		#rbx
ret 		#


_ZN4Page3std4PageEP4PageP4Page:
mov byte ptr [rcx + 0 ], 0		#this_0, 0
mov qword ptr [rdx + 0 ], rcx		#previus_0, this
mov r8, qword ptr [rdx + 0 ]		#previus_0_REG0, previus_0
mov qword ptr [rcx + 0 ], r8		#this_0, previus_0_REG0
add rcx, 8		#this, 8
add rcx, 8		#this, 8
mov qword ptr [rcx + 0 ], rcx		#this_0, this
mov r8d, dword ptr [rcx + 0 ]		#this_0_REG1, this_0
mov r8, qword ptr [rcx + 0 ]		#this_0_REG2, this_0
mov r9, r8		#REG_Buffer3, Buffer
cvtsi2sd r11, r10d		#Size_converted, Size
add r9, r11		#REG_Buffer3, Size_converted
mov r8, r8		#REG_Buffer4, Buffer
cvtsi2sd r11, r10d		#Size_converted, Size
add r8, r11		#REG_Buffer4, Size_converted
mov qword ptr [rcx + 0 ], r8		#this_0, REG_Buffer4
ret 		#


_ZN4Page3std4PageEP4PageP6Bucket:
mov dword ptr [rcx + 0 ], 0		#this_0, 0
mov byte ptr [rcx + 0 ], 0		#this_0, 0
mov qword ptr [rcx + 0 ], 0		#this_0, 0
mov qword ptr [rcx + 0 ], rdx		#this_0, parent
add rcx, 8		#this, 8
add rcx, 8		#this, 8
mov qword ptr [rcx + 0 ], rcx		#this_0, this
mov r8d, dword ptr [rcx + 0 ]		#this_0_REG0, this_0
mov r8, qword ptr [rcx + 0 ]		#this_0_REG1, this_0
mov r9, r8		#REG_Buffer2, Buffer
cvtsi2sd r11, r10d		#Size_converted, Size
add r9, r11		#REG_Buffer2, Size_converted
mov r8, r8		#REG_Buffer3, Buffer
cvtsi2sd r11, r10d		#Size_converted, Size
add r8, r11		#REG_Buffer3, Size_converted
mov qword ptr [rcx + 0 ], r8		#this_0, REG_Buffer3
ret 		#


_ZN4Page3std11Update_PageEP4Pagei:
mov dword ptr [rcx + 0 ], edx		#this_0, size
mov r8d, dword ptr [rcx + 0 ]		#this_0_REG0, this_0
mov r8, qword ptr [rcx + 0 ]		#this_0_REG1, this_0
mov r9, r8		#REG_Buffer2, Buffer
cvtsi2sd r11, r10d		#Size_converted, Size
add r9, r11		#REG_Buffer2, Size_converted
mov r8, r8		#REG_Buffer3, Buffer
cvtsi2sd r11, r10d		#Size_converted, Size
add r8, r11		#REG_Buffer3, Size_converted
mov qword ptr [rcx + 0 ], r8		#this_0, REG_Buffer3
ret 		#


_Z4PageP4Page:
mov rax, rcx		#Returning_REG0, this
ret 		#
ret 		#


_ZN6Bucket3std6BucketEP6BucketP6Bucket:
push rdi		#rdi
push rbx		#rbx
mov rdi, rdx		#previus, previus
mov rbx, rcx		#this, this
mov ecx, dword ptr [rip + std_ALLOCATION_SIZE ]		#REG_std_ALLOCATION_SIZE_Parameter32391, .RIP_std_ALLOCATION_SIZE
call _Z27____Internal_Allocate_char_i
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_0
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG1, this_0
mov rcx, rcx		#REG_this_0_REG1_Parameter14604, this_0_REG1
mov rdx, rbx		#REG_this_Parameter3902, this
call _ZN4Page3std4PageEP4PageP6Bucket
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_2
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG3, this_0
mov qword ptr [rbx + 0 ], rcx		#this_0, this_0_REG3
mov byte ptr [rbx + 0 ], 0		#this_0, 0
mov rcx, qword ptr [rdi + 0 ]		#previus_0_REG4, previus_0
mov qword ptr [rbx + 0 ], rcx		#this_0, previus_0_REG4
mov qword ptr [rdi + 0 ], rbx		#previus_0, this
mov qword ptr [rbx + 0 ], rdi		#this_0, previus
add rbx, 8		#this, 8
add rbx, 8		#this, 8
mov qword ptr [rbx + 0 ], rbx		#this_0, this
pop rbx		#rbx
pop rdi		#rdi
ret 		#


_ZN6Bucket3std6BucketEP6Bucket:
push rbx		#rbx
mov rbx, rcx		#this, this
mov ecx, dword ptr [rip + std_ALLOCATION_SIZE ]		#REG_std_ALLOCATION_SIZE_Parameter153, .RIP_std_ALLOCATION_SIZE
call _Z36____Internal_Allocate_____char_ptr__i
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_0
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG1, this_0
mov rcx, rcx		#REG_this_0_REG1_Parameter292, this_0_REG1
mov rdx, rbx		#REG_this_Parameter12382, this
call _ZN4Page3std4PageEP4PageP6Bucket
mov qword ptr [rbx + 0 ], rax		#this_0, RetREG_2
mov rcx, qword ptr [rbx + 0 ]		#this_0_REG3, this_0
mov qword ptr [rbx + 0 ], rcx		#this_0, this_0_REG3
mov byte ptr [rbx + 0 ], 0		#this_0, 0
mov qword ptr [rbx + 0 ], 0		#this_0, 0
mov qword ptr [rbx + 0 ], 0		#this_0, 0
add rbx, 8		#this, 8
add rbx, 8		#this, 8
mov qword ptr [rbx + 0 ], rbx		#this_0, this
pop rbx		#rbx
ret 		#


.section .data		#.data
