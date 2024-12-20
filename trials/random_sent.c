#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#pragma pack(1)

int main(){
    srand(time(NULL));
    char *article[]={"the","a","one","some","any"};
    char *noun[]={"boy","girl","dog","town","car"};
    char *verb[]={"drove","jumped","ran","walked","skipped"};
    char *proposition[]={"to","from","over","under","on"};
    char *sentence[6];
    int i=1+rand()%5;
    sentence[0]=article[i];
      int j=1+rand()%5;
    sentence[1]=noun[j];
      int k=1+rand()%5;
    sentence[2]=verb[k];
      int l=1+rand()%5;
    sentence[3]=proposition[l];
      int m=1+rand()%5;
    sentence[4]=article[m];
      int n=1+rand()%5;
    sentence[5]=noun[n];
    int z=0;
    while(n<6){
        printf("%s ",sentence[z]);
        ++z;
    }
    printf(".\n");
    return 0;
}