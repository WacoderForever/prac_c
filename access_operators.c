#include <stdio.h>


typedef struct MyStruct{
    int x;
    int y;
}MyStruct;

int main(){
    MyStruct MyObject;
    MyStruct *p=&MyObject;
    
    p->x=42;
    p->y=90;

    printf("->x = %i and ->y=%i\n",p->x,p->y);
    printf(".x = %i and .y=%i\n",MyObject.x,MyObject.y);

    return 0; 
}