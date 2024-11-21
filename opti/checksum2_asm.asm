section data
    filename db "emojis.txt",0
    handle dd 0
section .bss
    checksum db 0
section .text
    global _start

_start: 
    ;open file
    mov eax,5           ;syscall to open file
    mov ebx,filename
    mov ecx,0           ;open in read mode
    int 0x80

    mov [handle],eax

    read_loop:
        mov eax,3           ;system call number for read
        mov ebx,[handle]    ;file handler
        mov ecx,[checksum]  ;buffer to store read byte
        mov edx,1           ;number of bytes to read
        int 0x80

        cmp eax,0           ;check if EOF is reached
        je end_loop

        add [checksum],byte[checksum]
        jmp read_loop
    
    end_loop:
    ;close file
    mov eax,6           ;syscall for close
    mov ebx,[handle] 
    int 0x80

    ;exit program
    mov eax,1   ;syscall for exit
    mov ebx,0   ;exit code
    int 0x80