section .text
    global Checksum_Chunk

Checksum_Chunk:
    push rbp
    mov rbp, rsp

    mov rdi, [rbp+16]  ; 1st argument (WorkBuffer)
    mov rsi, [rbp+24]  ; 2nd argument (WorkingLength)
    mov rdx, [rbp+32]  ; 3rd argument (checksum)

    cmp rdi,0
    je error

    cmp rsi,0
    je error

    cmp rdx,0
    jne error

    xor eax,eax

loop_start:
    cmp rsi, 0  ; Compare WorkingLength with 0
    je loop_end  ; Jump to the end if WorkingLength is 0

    movzx eax, BYTE [rdi]  ; Load a byte from WorkBuffer, zero-extend
    add [rdx], eax  ; Add the byte to the checksum
    inc rdi  ; Increment WorkBuffer pointer
    dec rsi  ; Decrement WorkingLength

    jmp loop_start

loop_end:
    pop rbp
    ret

error:
    mov rax,-1
    pop rbp
    ret