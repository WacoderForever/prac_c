#include <stdio.h>

int main() {
    long long a = 1, b = 2, sum = 0;

    while (b <= 4000000) {
        if (b % 2 == 0) {
            sum += b;
        }

        // Compute the next Fibonacci number
        long long next = a + b;
        a = b;
        b = next;
    }

    printf("Sum of even Fibonacci numbers not exceeding 4,000,000: %lld\n", sum);
    return 0;
}
