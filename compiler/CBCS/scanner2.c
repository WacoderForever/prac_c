#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_special(char ch,char *spec_list){
    char sp = spec_list[0];
    int i = 1;
    while(sp != '\0'){
        if(ch == sp) return true;
        sp = spec_list[i];
        i++;
    }
    return false;
}

int main(){
    FILE *input,*output;
    input = fopen("input.txt","r");
    output = fopen("output.txt","w");
    int l = 1;
    int t = 1;
    int i,flag;
    char ch,str[30];
    char keyword[30] [30] = {"int","main","if","do","while","for","char","else","return","void","printf",
                            "return"};
    char special[30] = {'!','@','#','$','%','^','&','*','(',')','-','=','+','[',']','{','}',
                        '\"','\"','\'','\\','|',';',':',',','<','.','>'};
    fprintf(output,"Line no.\t Token no.\t Token\t\t\t Lexeme\n\n");
    while(!feof(input)){
        i=0;
        flag = 0;
        ch=fgetc(input);
        //digit
        if(isdigit(ch)){
            fprintf(output,"%7d\t%7d\t Digit\t\t\t %7c\n",l,t,ch);
            t++;
        }
        //preprocessor directive
        else if(ch == '#'){
            str[i] = ch;
            i++;
            ch = fgetc(input);
            while(ch != '\n'){
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            fprintf(output,"%7d\t%7d\t Preprocessor Directive\t\t\t %7s\n",l,t,str);
            t++;
            l++;
        }
        // newline
        else if(ch == '\n') l++;
        //special characters
        else if(is_special(ch,special)){
            fprintf(output,"%7d\t%7d\t Special character\t\t\t %7c\n",l,t,ch);
            t++;
        }
        else if(isalpha(ch)){
            str[i] = ch;
            i++;
            ch = fgetc(input);
            while((ch != ' ') && (ch != '\n') && (!is_special(ch,special))){
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            for(int j=0;j<30;j++){
                if(!strcmp(str,keyword[j])){
                    flag = 1;
                    break;
                }
            }
            if(flag){
                fprintf(output,"%7d\t%7d\t Keyword\t\t\t %7s\n",l,t,str);
                t++;
            }
            else{
                fprintf(output,"%7d\t%7d\t Identifier\t\t\t %7s\n",l,t,str);
                t++;
            }
            if(is_special(ch,special)){
                fprintf(output,"%7d\t%7d\t Special character\t\t\t %7c\n",l,t,ch);
                t++;
            }
        }
    }
    printf("Scanning done\n");
    return 0;    
}