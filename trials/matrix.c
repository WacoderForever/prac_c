#include <stdio.h>
#include <stdlib.h>

int main(){
    int r1,r2,c1,c2;
    printf("Enter number of row(s) for matrix 1:");
    scanf("%d",&r1);
    printf("Enter number of column(s) for matrix 1:");
    scanf("%d",&c1);
    printf("Enter number of row(s) for matrix 2:");
    scanf("%d",&r2);
    printf("Enter number of column(s) for matrix 2:");
    scanf("%d",&c2);
    int M1[r1][c1]={0};
    int M2[r2][c2]={0};
    if(c1 != r2){
        printf("The matrix cannot multiply.\n");
        exit(0);
    }
    int Ans[r1][c2]={0};
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            printf("Enter M[%d][%d]",i,j);
            scanf("%d",M1[i][j]);
        }
    }
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            printf("Enter M[%d][%d]",i,j);
            scanf("%d",M1[i][j]);
        }
    }

    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            int k=0;
            while(k<c1){
                Ans[i][j] += (M1[i][k] * M2[k][j]);
                k++;
            }
        }
    }
    printMatrix(M1[r1][c1]);
    printMatrix(M2[r2][c2]);
    printMatrix(A[r1][c2]);
    return EXIT_SUCCESS;
}