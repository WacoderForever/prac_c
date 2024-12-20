section .data
    message db "Debug: Reached point X", 10 ; Newline at the end (10 = ASCII newline)

section .text
    global Checksum

Checksum:
    ; Save base pointer
    push rbp
    mov rbp, rsp

    ; Extract arguments
    mov rdi, [rbp + 16]  ; First argument: Handle (file descriptor)
    mov rsi, [rbp + 24]  ; Second argument: Checksum pointer (unused)
    mov rdx, [rbp + 32]  ; Third argument: Byte buffer (passed from C)

    ; Debug: Print the file descriptor
    ; ... (Optional: Uncomment to print the file descriptor)
    ; mov eax, 1
    ; mov edi, 1
    ; mov rsi, rdi
    ; mov rdx, 1
    ; syscall

    ; Check for invalid arguments
    test rdi, rdi
    jz error_handle
    test rdx, rdx
    jz error_byte

    ; Initialize byte count to 0
    xor ecx, ecx

read_loop:
    ; Debug: Print message before reading
    ; ... (Optional: Uncomment to print the message)
    ; mov eax, 1
    ; mov edi, 1
    ; lea rsi, [rel message]
    ; mov rdx, 24
    ; syscall

    ; System call: read(Handle, &Byte, 1)
    mov eax, 0
    mov rdi, [rbp + 16]
    mov rsi, [rbp + 32]
    mov rdx, 1
    syscall

    ; Check if we successfully read a byte
    test rax, rax
    jle end_loop
    mov
    ; Increment byte count
    inc ecx

    ; Continue reading next byte
    jmp read_loop

end_loop:
    ; Return the number of bytes read (stored in ecx)
    mov eax, ecx
    leave
    ret

error_handle:
    ; Handle invalid file descriptor
    mov eax, 0
    leave
    ret

error_byte:
    ; Handle invalid byte buffer
    mov eax, 0
    leave
    ret