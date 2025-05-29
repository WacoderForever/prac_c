

const char main[] ={
    // Write syscall
    72, 199, 192, 1, 0, 0, 0,       // mov $1, %rax
    72, 199, 199, 1, 0, 0, 0,       // mov $1, %rdi
    72, 141, 53, 21, 0, 0, 0,       // lea message(%rip), %rsi
    72, 199, 194, 14, 0, 0, 0,      // mov $14, %rdx
    15, 5,                          // syscall
    
    // Exit syscall
    72, 199, 192, 60, 0, 0, 0,      // mov $60, %rax
    72, 49, 255,                    // xor %rdi, %rdi
    15, 5,                          // syscall
    
    // String data
    72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33, 10  // "Hello World!\n"
};