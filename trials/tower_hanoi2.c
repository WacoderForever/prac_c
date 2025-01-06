#include <stdio.h>
/*
This is a variation of the towers of Hanoi whereby there 
is no direct exchange between the source and destination pins
i.e no movement from A to B and vice versa
*/
void tower(int n,char a,char b,char c){
    if(n == 0) return;
    tower(n-1,a,b,c);
    printf("Move disk %d from %c to %c\n",n,a,c);
    tower(n-1,b,a,c);
    printf("Move disk %d from %c to %c\n",n,c,b);
    tower(n-1,a,b,c);
}

int main(){
    int n;
    printf("Enter number of disks:");
    scanf("%d",&n);

    tower(n,'A','B','C');

    return 0;
}