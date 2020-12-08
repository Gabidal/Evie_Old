;analyze
section .text

extern GetStdHandle
extern WriteFile
extern ReadConsoleA

; rcx: Address
; rdx: Length
global _Z14internal_printPci
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

extern VirtualAlloc
extern VirtualFree
extern Sleep

global _V5sleepx:function
_V5sleepx:
jmp Sleep

; rcx: Bytes
global _Z8allocatei:function
_Z8allocatei:

mov rdx, rcx ; Bytes
xor rcx, rcx ; lpAddress
mov r8, 0x00001000 | 0x00002000
mov r9, 0x04 ; PAGE_READWRITE

sub rsp, 40
call VirtualAlloc
add rsp, 40

ret

global _Z10deallocatePti:function
_Z10deallocatePti:

; rcx = lpAddress
xor rdx, rdx ; dwSize
mov r8, 0x00008000 ; MEM_RELEASE

sub rsp, 40
call VirtualFree
add rsp, 40

ret

; rcx: Source
; rdx: Count
; r8: Destination
global _V4copyPhxPS_:function
_V4copyPhxPS_:
push rdi
push rsi

mov rdi, r8 ; Destination
mov rsi, rcx ; Source
mov rcx, rdx ; Count

rep movsb

pop rsi
pop rdi
ret

; rcx: Source
; rdx: Count
; r8: Destination
; r9: Offset
global _V11offset_copyPhxPS_x:function
_V11offset_copyPhxPS_x:
push rdi
push rsi

mov rdi, r8 ; Destination
add rdi, r9 ; Apply offset
mov rsi, rcx ; Source
mov rcx, rdx ; Count

rep movsb

pop rsi
pop rdi
ret

; rcx: Destination
; rdx: Count
global _V4zeroPhx:function
_V4zeroPhx:
push rdi

mov rdi, rcx ; rdi = Destination
mov rcx, rdx ; rcx = Count
xor rax, rax ; Value used to fill the range

rep stosb

pop rdi
ret

; rcx: Destination
; rdx: Count
; r8: Value
global _V4fillPhxx:function
_V4fillPhxx:
push rdi

mov rdi, rcx ; rdi = Destination
mov rcx, rdx ; rcx = Count
mov rax, r8 ; rax = Value

rep stosb

pop rdi
ret