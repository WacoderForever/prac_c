#include <unistd.h>

void _start(){
    const char messsage[]="Hello World!\n";
    write(1,messsage,sizeof(messsage)-1);
    _exit(0);
}