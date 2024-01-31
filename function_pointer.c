#include <stdio.h>

int MyFunction(int a, int b){
    return a*2+b;
}

int main(){
    int x=42;
    int y=210;
    int (*fnptr)(int,int)=&MyFunction;

    printf("(*fnptr)(%i,%i)=%i\n",x,y,(*fnptr)(x,y));
    printf("fnptr(%i,%i)=%i\n",x,y,fnptr(x,y));

}