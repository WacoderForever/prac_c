#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rec(int l,int w,char sy){
    int p=w;
    int p1=l;
   for(w;w>=0;w--){
    for(l=p1;l>=0;l--){
        if((w==p)||(w==0)){
            printf("%c",sy);
        }
        else{
            if((l==0)||(l==p1)){
            printf("%c",sy);
        }
            else{
            printf(" ");
        }
        }
    }
    printf("\n");
   }
}
int main(){
    int l;
    int w;
    char r;
    int shape;
    printf("Enter character to use in drawing shape:");
    scanf("%c",&r);
    printf("Which shape do you want to draw:");
    scanf("%d",&shape);
    if(!strcmp(shape,"rectangle")){
        printf("Enter length:");
        scanf("%d",&l);
        printf("Enter width:");
        scanf("%d",&w);
        w=w-1;
        l=l-1;
        rec(l,w,r);

    }

}