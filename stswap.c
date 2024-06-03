#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Solution(char *str1,char *str2){

    if(!strcmp(str1,str2)){

        return 1;
    }

    for(int i=0; i<strlen(str1); i++){

        for(int j=0 ; j<strlen(str1) ; j++){

            char *temp=(char*)malloc(strlen(str1));
            
            for(int k=0; k<strlen(str1);k++){

                if(k==i || k==j){

                    temp[k] = str2[j];
                    temp[j] = str2[i];
                }

                else{

                    temp[k]=str2[k];
                }
            }

            if(!strcmp(str1,temp)){

                return 1;
            }

            temp=NULL;
        }
    }

    return 0;
}

int main(){

    char *str1="Seth";
    char *str2="Seht";

    bool a=Solution(str1,str2);
    printf("%d\n",a);


}