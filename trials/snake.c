#include <stdio.h>
#include <stdlib.h>

#define COLS 60
#define ROWS 30

int main(){
    //hide cursor
    printf("\e[?25l");
    int quit=0;
    int x[1000],y[1000];
    while(!quit){
        //render table
        printf("+");
        for(int i=0;i<COLS;i++){
            printf("-");
        }
        printf("+\n");
        for(int j=0;j<ROWS;j++){
            printf("|");
            for(int i=0;i<COLS;i++){
                printf(".");
            }
            printf("|\n");
        }
        printf("+");
        for(int i=0;i<COLS;i++){
            printf("-");
        }
        printf("+\n");

        //move cursor to the top
        printf("\e[%iA",ROWS+2);

        int head,tail=0;
        x[head]=COLS/2;
        y[head]=ROWS/2;
        int gameover=0;
        int xdir=1,ydir=0;

        while((!quit) && (!gameover)){
            //clear tail
            printf("\e[%iB\e[%iC-");
        }
    }
    printf("\e[?25h");
    return 0;
}