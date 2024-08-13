#include "allheaders.h"

int main() {
    long long int a[] = {27, 56, 12, 98, 45667, 6776};
    int size = sizeof(a) / sizeof(a[0]);
    long long int b[size];
    b[0] = a[0];
    int count = 1;

    while (count < size) {
        if (a[count] < b[0]) {
            long long int c[count];
            for (int i = 0; i < count; i++) {
                c[i] = b[i];
            }
            b[0] = a[count];
            for (int i = 1; i <= count; i++) {
                b[i] = c[i - 1];
            }
        } else if (a[count] >= b[count - 1]) {
            b[count] = a[count];
        } else {
            for (int i = 1; i < count; i++) {
                if (a[count] < b[i]) {
                    int csize = count - i;
                    int k = i;
                    long long int c[csize];
                    for (int j = 0; j < csize; j++) {
                        c[j] = b[k];
                        k++;
                    }
                    b[i] = a[count];
                    k = 0;
                    for (int j = i + 1; j < count; j++) {
                        b[j] = c[k];
                        k++;
                    }
                }
            }
        }
        count++;
    }

    for (int i = 0; i < size; i++) {
        printf("%lld, ", b[i]);
    }
    printf("\n");

    return 0;
}
