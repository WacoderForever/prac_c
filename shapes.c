#include "allheaders.h"

char *ToLower(char *text){

    int stringlength=strlen(text);
    char *lower=(char*)malloc(sizeof(char)*stringlength);
    int i=0;

    while(i<stringlength){
        //checking if the character is an uppercase
        if((text[i]-'A')<=25){

            lower[i]=text[i]+32;
        }
        //if the character is lowercase
        else{

            lower[i]=text[i];
        }

        i++;
    }

    return lower;
}

void rec(int l,int w,char* sy){
    int p=w;
    int p1=l;
   for(w;w>=0;w--){
    for(l=p1;l>=0;l--){
        if((w==p)||(w==0)){
            printf("%s ",sy);
        }
        else{
            if((l==0)||(l==p1)){
            printf("%s ",sy);
        }
            else{
            printf("  ");
        }
        }
    }
    printf("\n");
   }
}

void square(int l,int w,char* sy){
    int p=w;
    int p1=l;
   for(w;w>=0;w--){
    for(l=p1;l>=0;l--){
        if((w==p)||(w==0)){
            printf("%s ",sy);
        }
        else{
            if((l==0)||(l==p1)){
            printf("%s ",sy);
        }
            else{
            printf("  ");
        }
        }
    }
    printf("\n");
   }
}

void triangle(int height,int base,char *type,char*sy){

    int h;
    int b;

    if(!strcmp(type,"right@angled")){

        h=1;
        b=1;

        while(h<=height){

            for(int i=b;i>0;i--){

                printf("*");
            }
            printf("\n");
            b++;
            h++;
        }
    }
}

int main(){
    int l;
    int w;
    char *r=NULL;
    size_t size1=0;
    char *shape=NULL;
    size_t size=0;

    printf("Enter character to use in drawing shape:");
    getline(&r, &size1, stdin);
    r[strcspn(r,"\n")]=0;
    printf("Which shape do you want to draw: ");
    getline(&shape, &size, stdin);
    shape[strcspn(shape,"\n")]=0;
    shape=ToLower(shape);

    if(!strcmp(shape,"rectangle")){
        printf("Enter length:");
        scanf("%d",&l);
        printf("Enter width:");
        scanf("%d",&w);
        w=w-1;
        l=l-1;
        rec(l,w,r);

    }

    if(!strcmp(shape,"square")){
        
        printf("Enter length:");
        scanf("%d",&l);
        l--;
        square(l,l,r);
    }

    if(!strcmp(shape,"triangle")){

        char *type=NULL;
        printf("Enter type of triangle: ");
        getline(&type,&size,stdin);
        type[strcspn(type,"\n")]=0;
        type=ToLower(type);
        printf("%s\n",type);
        printf("Enter height:");
        scanf("%d",&l);
        printf("Enter base:");
        scanf("%d",&w);
        triangle(l,w,type,r);
    }

    return 0;

}