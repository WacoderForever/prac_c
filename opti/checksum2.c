#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern int Checksum(int Handle, unsigned int *Checksum);

int main(int argc, char **argv) {
    int Handle;
    unsigned int ChecksumVal;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    if ((Handle = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    if (!Checksum(Handle, &ChecksumVal)) {
        perror("Checksum");
        exit(1);
    }

    printf("Checksum: %u\n", ChecksumVal);
    close(Handle);
    return 0;
}
