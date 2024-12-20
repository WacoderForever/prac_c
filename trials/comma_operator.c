#include <stdio.h>

int main(){
    int x=42;
    int y=42;

    printf("%i\n",(x*=2,y));
    printf("x=%i\n",x);

    for(int k=1;printf("k=%i\n",k),k<10;k++){
        //
    }
    return 0;
}