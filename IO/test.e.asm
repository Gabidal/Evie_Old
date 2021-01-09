.intel_syntax noprefix
.global main
main:
mov rcx, 4608083138725491507
movq xmm2, rcx
addsd xmm1, xmm2
mov rcx, -4616189618054758400
movq xmm2, rcx
mulsd xmm0, xmm2
subsd xmm1, xmm0
mov rcx, 4608533498688228557
movq xmm0, rcx
addsd xmm1, xmm0
movq xmm0, xmm1
ret 
ret 


