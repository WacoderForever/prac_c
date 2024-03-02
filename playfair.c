#include "allheaders.h"

#define MATRIX_ROW 5
#define MATRIX_COLUMN 5

int get_row(char matrix[MATRIX_ROW][MATRIX_COLUMN],char c){

    int row;

    for(int i=0; i<MATRIX_ROW;i++){

        for(int j=0;j<MATRIX_COLUMN;j++){

            if(matrix[i][j]==c){

                row=i;
                break;

            }
            
            
        }

    }

    return row;

}

int get_column(char matrix[MATRIX_ROW][MATRIX_COLUMN],char c){

    int column;

    for(int i=0; i<MATRIX_ROW;i++){

        for(int j=0;j<MATRIX_COLUMN;j++){

            if(matrix[i][j]==c){

                column=j;
                break;

            }
            
            
        }

    }

    return column;

}

int same_row(char matrix[MATRIX_ROW][MATRIX_COLUMN],char fchar,char schar){

    int row;
    int ans=0;

    for(int i=0; i<MATRIX_ROW;i++){

        for(int j=0;j<MATRIX_COLUMN;j++){

            if(fchar=='j'){

                fchar=='i';
            }

            if(matrix[i][j]==fchar){

                row=i;
                break;

            }
            
            
        }

    }

    for(int j=0 ; j < MATRIX_COLUMN ; j++){

        if(matrix[row][j]==schar){
            ans=1;
            break;
        }
    }

    return ans;

}

char same_row_encoding(char matrix[MATRIX_ROW][MATRIX_COLUMN],char c){

    int row=get_row(matrix,c);
    char result;
    int column=get_column(matrix,c);

    column=(int)((column+1)%5);
    result=matrix[row][column];

    return result;

}

char same_row_decoding(char matrix[MATRIX_ROW][MATRIX_COLUMN],char c){

    int row=get_row(matrix,c);
    char result;
    int column=get_column(matrix,c);

    column=(int)((column+4)%5);
    result=matrix[row][column];

    return result;
}

int same_column(char matrix[MATRIX_ROW][MATRIX_COLUMN],char fchar,char schar){

    int column;
    int ans=0;

    for(int j=0;j<MATRIX_COLUMN;j++){

        for(int i=0;i<MATRIX_ROW;i++){

            if(fchar=='j'){

                fchar='i';

            }
            
            if(matrix[i][j]==fchar){

                column=j;
                break;

            }
        }
    }

    for(int i=0;i<MATRIX_ROW;i++){

        if(matrix[i][column]==schar){

            ans=1;
            break;
        }
    }

    return ans;

}

char same_column_encoding(char matrix[MATRIX_ROW][MATRIX_COLUMN], char c){

    char result;
    int column=get_column(matrix,c);
    int row=get_row(matrix,c);

    row=(int)(row+1)%5;
    result=matrix[row][column];

    return result;

}

char same_column_decoding(char matrix[MATRIX_ROW][MATRIX_COLUMN], char c){

    char result;
    int column=get_column(matrix,c);
    int row=get_row(matrix,c);

    row=(int)(row+4)%5;
    result=matrix[row][column];

    return result;

}

char rectangular_encoding(char matrix[MATRIX_ROW][MATRIX_COLUMN],char fchar,char schar){

    int column1,column2,row1,row2;
    char result;

    row1=get_row(matrix,fchar);
    row2=get_row(matrix,schar);
    column1=get_column(matrix,fchar);
    column2=get_column(matrix,schar);
    result=matrix[row1][column2];

    return result;

}

int search(char *key,char letter){

    int ret=0;

    for(int i=0;key[i] != '\0';i++){

        if(key[i]==letter){

            ret=1;
            break;
        }
    }

    return ret;
}

char *make_key(char *key){

    char *final_key;
    int i=0;
    int size=1;
    final_key=(char*)calloc(size,sizeof(char));

    if(final_key==NULL){

        perror("Memory not allocated for key");
        exit(1);
    }

    if(key[i]=='j'){

        key[i]='i';

    }

    final_key[0]=key[0];
    i++;

    while(key[i] != '\0'){

        if(key[i]=='j'){
        
            key[i]='i';

        }

        int present=search(final_key,key[i]);

        if(present==0){

            size++;
            char *new=(char*)realloc(final_key,size*sizeof(char));

            if(new==NULL){

                free(final_key);
                perror("Memory not allocated for new text");
                exit(1);
            }

            final_key[size-1]=key[i];
            
        }

        i++;

    }

    final_key[size]='\0';

    return final_key;
}

char *matrix_elements(char *key){

    char *matrix_ele=(char*)malloc(26);
    int i=0;
    
    for(;key[i] != '\0';i++){

        matrix_ele[i]=key[i];
    }
    
    int temp=i-1;
    char start='a';

    while(i<(26 - strlen(key)) + temp){

        int present=search(key,start);

        if(present==0){

            matrix_ele[i]=start;
           
        }

        else{

            i--;
        }

         start++;
         if(start=='j'){
            start++;
         }
         i++;
         
    }
    matrix_ele[i]='\0';

    return matrix_ele;
}

char *encode(char matrix[MATRIX_ROW][MATRIX_COLUMN],char *text){

    int i=0;
    int k=0;
    long int length=strlen(text+1);
    char *ciphertext=(char*)calloc(length+1,sizeof(char));

    if(ciphertext==NULL){

        perror("no room for cipher");
        exit(1);
    }

    while(text[i] != '\0'){

        int incr=2;
        char fchar=text[i];
        char schar=text[i+1];

        if(schar=='\0'){

            schar='x';
        }
        

        if(schar==fchar){

            schar='x';
            ++length;

            char *new=(char*)realloc(ciphertext,length*sizeof(char));

            if(new==NULL){

                free(ciphertext);
                perror("Memory allocation failed");
                exit(1);

            }

            incr=1;

        }

        if((same_row(matrix,fchar,schar))==1){

            ciphertext[k]=same_row_encoding(matrix,fchar);
            ciphertext[k+1]=same_row_encoding(matrix,schar);

        }

        else{

            if((same_column(matrix,fchar,schar))==1){

                ciphertext[k]=same_column_encoding(matrix,fchar);
                ciphertext[k+1]=same_column_encoding(matrix,schar);

            }

             else{

                ciphertext[k]=rectangular_encoding(matrix,fchar,schar);
                ciphertext[k+1]=rectangular_encoding(matrix,schar,fchar);

            }

        }

        k+=2;
        i+=incr;
    }

    ciphertext[k-1]=='\0';

    return ciphertext;

}

char *decode(char matrix[MATRIX_ROW][MATRIX_COLUMN],char *text){

    char *plaintext=(char*)malloc((strlen(text)+1)*sizeof(char));
    int i=0;
    int incr=2;

    if(plaintext==NULL){

        perror("Plaintext not assigned memory.");
        exit(1);
    }

    while(text[i] != '\0'){

        char fchar=text[i];
        char schar=text[i+1];

        if((same_row(matrix,fchar,schar))==1){

            plaintext[i]=same_row_decoding(matrix,fchar);
            plaintext[i+1]=same_row_decoding(matrix,schar);

        }

        else{

            if((same_column(matrix,fchar,schar))==1){

                plaintext[i]=same_column_decoding(matrix,fchar);
                plaintext[i+1]=same_column_decoding(matrix,schar);

            }

            else{

                plaintext[i]=rectangular_encoding(matrix,fchar,schar);
                plaintext[i+1]=rectangular_encoding(matrix,schar,fchar);

            }
        }

        i+=incr;
    }

    plaintext[i]='\0';

    return plaintext;
}

int main(){

    char *text=NULL;
    size_t size=0;
    printf("Enter text: ");
    getline(&text,&size,stdin);
    text[(strcspn(text,"\n"))]=0; //removing new line character in the string

    char *key=NULL;
    size=0;
    printf("Enter key: ");
    getline(&key,&size,stdin);
    key[(strcspn(key,"\n"))]=0;

    printf("The entered text is: %s\n",text);
    printf("The entered key is: %s\n",key);

    char *fkey=make_key(key);
    char *matrix_el=matrix_elements(fkey);
    char matrix[MATRIX_ROW][MATRIX_COLUMN];
    int pos=0;

    for(int i=0;i<MATRIX_ROW;i++){

        for(int j=0;j<MATRIX_COLUMN;j++){

            matrix [i][j]=matrix_el[pos];
            pos++;
        }
    }
    

    printf("The matrix is %s \n",matrix_el);
    printf("The matrix size is %ld\n",strlen(matrix_el));
    printf("The final_key is: %s\n",fkey);

    for(int i=0;i<MATRIX_ROW;i++){

        printf("\n");

        for(int j=0;j<MATRIX_COLUMN;j++){

            printf("%c,",matrix[i][j]);
        }
    }

    printf("\n");

    char *ciphertext=encode(matrix,text);
    char *plaintext=decode(matrix,ciphertext);

    printf("The ciphertext is : %s\n",ciphertext);
    printf("The plaintext is: %s\n",plaintext);

    free(ciphertext);
    free(plaintext);
    free(matrix_el);
    free(fkey);
    
    return 0;
}