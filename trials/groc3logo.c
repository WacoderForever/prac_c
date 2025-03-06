#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 30
#define HEIGHT 30

int main(){

    float w=WIDTH;
    float h=HEIGHT;
    for(int col=0;col<HEIGHT;++col){
        for(int row=0;row<WIDTH;++row){
            float x=col;
            float y=row;

            float cx=(2*x-w)/h;
            float cy=(2*y-h)/h;

            float d=sqrtf((cx*cx)-(cy*cy));
            d-=0.5;
            d+=((0.01*h)/(2*(x-y)+h-w));
            d=fabsf(d);
            if (d == 0.0f) d = 1e-6f;
            d=0.1/d;
            int index=(int)fminf(floorf(d/(1+d)*7),5);
            char c = "-+=<@#"[index];
            printf("%c%c",c,c);
        }
        printf("\n");
    }
}