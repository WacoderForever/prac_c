#include "allheaders.h"

int main(){
    time_t largest=0x7fffffff;
    printf("Biggest=%s\n",asctime(gmtime(&largest)));
    printf("Alert \a\n");
}