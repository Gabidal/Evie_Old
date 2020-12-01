;analyze
section .text

extern GetStdHandle
extern WriteFile
extern ReadConsoleA

; rcx: Address
; rdx: Length
global _Z14internal_printPci
global _import_func_cpp_internal_print__char__int
_import_func_cpp_internal_print__char__int:
_Z14internal_printPci:
push rbx
push rsi

; Required spill area, 1 x 64 bit parameter and lpNumberOfCharsWritten for WriteFile (aligned)
sub rsp, 56

mov rbx, rcx ; Address
mov rsi, rdx ; Length

mov rcx, -11 ; STD_OUTPUT_HANDLE
call GetStdHandle

mov rcx, rax ; hConsoleOutput
mov rdx, rbx ; lpBuffer
mov r8, rsi ; nNumberOfCharsToWrite
lea r9, [rsp+40] ; lpNumberOfCharsWritten
mov qword [rsp+32], 0 ; lpReserved (Stack memory should be zeroes?)

call WriteFile

; Required spill area, 1 x 64 bit parameter and lpNumberOfCharsWritten for WriteFile (aligned)
add rsp, 56

pop rsi
pop rbx
ret

; rcx: Buffer
; rdx: Length
global _Z13internal_readPci
_Z13internal_readPci:
push rbx
push rsi

; Required spill area and 2 x 64 bit parameters for ReadConsole (aligned)
sub rsp, 56

mov rbx, rcx ; Buffer
mov rsi, rdx ; Length

mov rcx, -10 ; STD_INPUT_HANDLE

call GetStdHandle

mov rcx, rax ; hConsoleOutput
mov rdx, rbx ; lpBuffer
mov r8, rsi ; nNumberOfCharsToRead
lea r9, [rsp+32] ; lpNumberOfCharsRead
mov qword [rsp+40], 0 ; pInputControl (Stack memory should be zeroes?)

call ReadConsoleA

; Remove spill area and 2 x 64 bit parameters for ReadConsole
add rsp, 56

pop rsi
pop rbx
ret

;int ptr banana(int, apple ptr)
;_E stands for Evie
;P stands for ptr
;number stands for the length of the class name
;first type is the returning type
;second is the func name
;rest are the parameters
_EP3int6banana3intP5appleF3int4pear3int5floatE: