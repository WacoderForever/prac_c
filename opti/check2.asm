
section .text
    global Checksum

Checksum:
    ; Save base pointer
    push rbp
    mov rbp, rsp

    ; Extract arguments
    mov rdi, [rbp+16]  ; First argument: Handle (file descriptor)
    mov rsi, [rbp+24]  ; Second argument: Checksum pointer
    mov rdx, [rbp+32]  ; Third argument: Byte buffer (passed from C)

    ; Initialize checksum to 0
    xor eax, eax
    xor rcx,rcx

read_loop:
    ; System call: read(Handle, &Byte, 1)
    mov eax, 0
    mov rdi, [rbp+16]
    mov rsi, [rbp+32]
    mov rdx, 1
    syscall

    ; Check if we successfully read a byte
    test rax, rax
    jle end_loop

    ; Add the byte to the checksum (modulo 256)
    add eax, [rsi]
    adc eax, 0   ; Handle potential carry-over

    inc rcx
    ; Continue reading next byte
    jmp read_loop

end_loop:
    ; Store the checksum in the provided memory location
    mov [rsi], al

    ; Return the number of bytes read (stored in RCX)
    mov rax, rcx
    leave
    ret