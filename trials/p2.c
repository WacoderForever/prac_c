#include <stdio.h>
#include <stdlib.h>

int main() {
    int num = 10;
    int *p = &num;

    printf("Address of num: %p\tValue of num: %d\n", &num, num); 
    printf("Address of p: %p\tValue of p: %p\n", &p, p);
    
    return EXIT_SUCCESS;
}