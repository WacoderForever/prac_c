section .bss
    Byte resb 1        ; Reserve 1 byte for the buffer

section .text
    global Checksum    ; Declare Checksum as external function

Checksum:
    ; Save base pointer
    push rbp
    mov rbp, rsp

    ; Extract arguments
    mov rdi, [rbp + 16] ; First argument: Handle (passed in rdi)
    mov rsi, [rbp + 24] ; Second argument: Checksum pointer (passed in rsi)

    ; Initialize Checksum to 0
    xor eax, eax        ; Clear eax (value 0)
    mov [rsi], eax      ; Store 0 at the address pointed to by rsi

read_loop:
    ; System call: read(Handle, &Byte, 1)
    mov eax, 0          ; syscall number for read
    lea rsi, [Byte]     ; Load address of Byte buffer
    mov rdx, 1          ; Number of bytes to read
    syscall

    ; Check for EOF or error
    test rax, rax       ; Was anything read?
    jle end_loop        ; If rax <= 0, exit loop

    ; Add the byte to the checksum
    movzx eax, byte [Byte] ; Zero-extend the byte to 32 bits
    add dword [rsi], eax   ; Add the value to Checksum

    jmp read_loop

end_loop:
    ; Return success
    mov eax, 1          ; return value (1 for success)
    leave
    ret
