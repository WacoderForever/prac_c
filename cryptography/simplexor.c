#include "/prac_c/allheaders.h"

int main(int argc,char **argv){
    FILE *fi,*fo;
    char *ch;
    char c;

    if((ch=argv[1])&&(*ch != '\0')){
        if((fi=fopen(argv[2],"rb")) != NULL){
            if((fo=fopen(argv[3],"wb")) != NULL){
                while((c=getc(fi)) != EOF){
                    if(!*ch) ch=argv[1];
                    c^=*(ch++);
                    putc(c,fo);
                }
                fclose(fo);
            }
            fclose(fi); 
        }
     
    }
    return 0;
}