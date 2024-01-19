#include <stdio.h>

int main(){
    int day;
    int month;
    int year;
    printf("Enter date format in dd-mm-yyyy:");
    scanf("%d%*c%d%*c%d",&day,&month,&year);
    printf("day=%-5d\nmonth=%-5d\nyear=%-5d\n",day,month,year);
}