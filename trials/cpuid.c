#include <stdio.h>
#include <cpuid.h>

int main() {
    unsigned int eax, ebx, ecx, edx;

    __cpuid(1, eax, ebx, ecx, edx);

    printf("ECX: 0x%x\n", ecx);
    printf("EDX: 0x%x\n", edx);

    if (ecx & bit_AVX) {
        printf("AVX supported\n");
    }

    if (ecx & bit_SSE3) {
        printf("SSE3 supported\n");
    }

    return 0;
}
