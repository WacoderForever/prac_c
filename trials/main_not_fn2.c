// file: main.c
int main(void) {
    asm volatile(
        // write(1, message, 14)
        "mov   $1, %%rax\n"               // syscall: sys_write
        "mov   $1, %%rdi\n"               // fd = stdout
        "lea   message(%%rip), %%rsi\n"   // buf = &message
        "mov   $14, %%rdx\n"              // count = 14 (including newline)
        "syscall\n"

        // exit(0)
        "mov   $60, %%rax\n"              // syscall: sys_exit
        "xor   %%rdi, %%rdi\n"            // status = 0
        "syscall\n"

        // data
        "message:\n"
        "   .ascii \"Hello World!\\n\"\n"
        :
        :   /* no inputs */
        :   "rax", "rdi", "rsi", "rdx"
    );
    return 0;
}
