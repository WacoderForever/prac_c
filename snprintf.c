#include "allheaders.h"


int main(int argc,char **argv){

    char *a="Kokolechel";
    size_t size = strlen(a)*sizeof(char)+1;
    char b[size];

    snprintf(b,size,"%s",a);
    printf("b is %s\n",b);

}