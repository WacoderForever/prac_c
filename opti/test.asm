section .text
    global _start

_start:
    mov eax, 60      ; syscall: exit
    xor edi, edi     ; status: 0
    syscall
