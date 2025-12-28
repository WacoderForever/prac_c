#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    FILE *input,*output;
    int l=0;
    int t=0;
    int j=0;
    int i,flag;
    char ch,str[30];
    input = fopen("input.txt","r");
    output = fopen("output.txt","w");
    char keyword[30][30] = {"int","main","if","else","do","while"};
    char special[30] = {';','{','}','(',')','?','@','!','%'};
    fprintf(output,"Line no.\t Token no.\t Token\t Lexeme\n\n");
    while(!feof(input)){
        i=0;
        flag=0;
        ch = fgetc(input);
        if((ch == '+')||(ch == '-')||(ch == '/')||(ch =='*')){
            fprintf(output,"%7d\t%7d\t Operator %7c\n",l,t,ch);
            t++;
        }
        else if( ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')' || ch=='?' ||
                ch=='@' || ch=='!' ||ch=='%'){
            fprintf(output,"%7d\t%7d\t Special Symbol %7c\n",l,t,ch);
            t++;
        }
        else if(isdigit(ch)){
           fprintf(output,"%7d\t%7d\t Digit %7c\n",l,t,ch);
           t++; 
        }
        else if(isalpha(ch)){
            str[i] = ch;
            i++;
            ch = fgetc(input);
            while(isalpha(ch) && ch != ' '){
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            for(j=0;j<30;j++){
                if(!strcmp(str,keyword[j])){
                    flag = 1;
                    break;
                }
            }
            if(flag){
                fprintf(output,"%7d\t%7d\t Keyword %7s\n",l,t,str);
                t++;
            }
            else{
                fprintf(output,"%7d\t%7d\t Identifier %7s\n",l,t,str);
                t++;
            }
        }
        else if(ch == '\n'){
            l++;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}