#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union numbers{
    int x;
    double y;
};
int main(){
    union numbers self;
    self.x=100;
    printf("Printing values after asigning x\nx:%d \ny:%g\n",self.x,self.y);
    self.y=14.789;
    printf("Printing values after asigning y\ny:%g \nx:%d",self.y,self.x);
}