#include "allheaders.h"

typedef struct Person{
 char name[50];
 char password[50];
 char email[100];
}Person;

int main(){
    FILE *fp;
    Person guy;
    printf("Enter name:");
    scanf("%s",guy.name);
    printf("Enter password:");
    scanf("%s",guy.password);
    printf("Enter email:");
    scanf("%s",guy.email);
    char fname[10]="user1";
    fp=fopen(strcat(fname,".json"),"w");
    fwrite(&guy,sizeof(Person),1,fp);
    if(fwrite){
        puts("Success");
    }
    else{
        puts("Failed");
    }
    fclose(fp);
}