#include <stdio.h>

int main(){
    goto skip;
        printf("You should not see this.\n");
    skip:
        printf("Hello world.\n");
    return 0;
}