#include "allheaders.h"

int main(){
    time_t larget=0x7fffffff;
    printf("Biggest=%s\n",asctime(gmtime(&larget)));
}