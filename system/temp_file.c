#include <stdio.h>
#include <unistd.h>

typedef int temp_file_handle;

temp_file_handle write_temp(char *buffer,size_t length){
    char temp_file_name = "/tmp/temp_file.XXXXXX";
    int fd = mkstemp(temp_file_name);
    // UNlink file so that it will be removed when fd is closed
    unlink(temp_file_name);
    // write number of bytes to the file first
    write(fd,&length,sizeof(length));
    // write the data itself
    write(fd,buffer,length);

    return fd;
}

char *read_temp(temp_file_handle temp_file,size_t *length){
    char *buffer;
    int fd = temp_file;
    // rewind to the beggining of file
    lseek(fd,0,SEEK_SET);
    // read size of file
    read(fd,length,sizeof(*length));
    buffer = (char *) malloc(*length);
    read(fd,buffer,*length);
    return buffer;
}