#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    char st[100];
    int i=0;
    printf("Enter string:");
    fgets(st,100,stdin);
    printf("\nThe string is:%s",st);
    while(st[i] !='\0'){
        if(i%2==0){
            st[i]=toupper(st[i]);
            ++i;
        }
        if(i%2 != 0){
            st[i]=tolower(st[i]);
            ++i;
        }
    }
    puts("");
    printf("Modified string is:%s",st);
 return 0;
}