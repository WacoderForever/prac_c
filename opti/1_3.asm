section .text
    global ChecksumFile

ChecksumFile:
    ; Arguments:
    ; rdi = file descriptor (Handle)
    ; rsi = pointer to store checksum (*Checksum)

    ; Save base pointer
    push rbp
    mov rbp, rsp

    ; Allocate space for local variables
    sub rsp, 528                ; 16 for checksum + buffer size (512 bytes)

    xor eax, eax                ; Clear eax
    mov dword [rbp-4], eax      ; checksum = 0

.read_loop:
    ; Prepare for sys_read (rax = 0, rdi = Handle, rsi = buffer, rdx = 512)
    mov eax, 0                  ; syscall number for sys_read
    mov rsi, rbp                ; Address of buffer (buffer starts at rbp)
    add rsi, -520               ; Offset to buffer location
    mov edx, 512                ; Buffer size
    syscall

    ; Check result of sys_read
    test rax, rax               ; Check if rax == 0 (EOF or no data)
    je .done                    ; If EOF, go to done
    js .error                   ; If error (rax < 0), go to error

    ; Add bytes to checksum
    mov ecx, eax                ; Number of bytes read (corrected: eax instead of rax)
    xor ebx, ebx                ; Clear index (ebx = 0)

.sum_loop:
    cmp ebx, ecx                ; Compare index to bytes_read
    jge .read_loop              ; If index >= bytes_read, read next chunk

    ; Add buffer[ebx] to checksum
    movzx eax, byte [rsi + rbx] ; Load byte from buffer
    add dword [rbp-4], eax      ; checksum += buffer[rbx]
    inc ebx                     ; Increment index
    jmp .sum_loop               ; Repeat

.done:
    ; Store checksum in *Checksum
    mov eax, dword [rbp-4]      ; Load checksum
    mov rdi, rsi                ; Pointer to *Checksum
    mov dword [rdi], eax        ; *Checksum = checksum

    ; Clean up and return success
    mov eax, 1                  ; Return 1 (success)
    add rsp, 528                ; Deallocate stack space
    pop rbp                     ; Restore base pointer
    ret

.error:
    ; Clean up and return failure
    mov eax, 0                  ; Return 0 (failure)
    add rsp, 528                ; Deallocate stack space
    pop rbp                     ; Restore base pointer
    ret
