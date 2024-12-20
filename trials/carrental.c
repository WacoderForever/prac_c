#include "allheaders.h"

void welcome(){

    printf("===================================================\n");
    printf("========Welcome to Car Rental Services=============\n");
    printf("===================================================\n");
}

int GetHours(int carNo){

    int hours;
    printf("Enter hours rented for car%d:",carNo);
    scanf("%d",&hours);

    return hours;
}

float CalculateCost(int hours){

    

    if(hours<=24){

        float cost;
        int G8=hours-8;

        if(G8>=0){

            cost=25+(hours-8)*5;
        }
        else{

            cost=25;
        }

        if(cost<=50){

            return cost+(0.5*hours);
        }

        else{

            return 50+(0.5*hours);
        }

    }

    else{

        int days=hours/24;
        int rem=hours%24;

        if(rem==0){

            return days*50+((0.5*24)*days);
        }
        else{

            return days*50+CalculateCost(rem)+(0.5*24*days);
        }
    }
}

int main(){

    welcome();
    int car1=GetHours(1);
    int car2=GetHours(2);
    int car3=GetHours(3);

    printf("%s%13s%18s\n","Car","Hours","Charge");
    printf("%2d%13d%18.2f\n",1,car1,CalculateCost(car1));
    printf("%2d%13d%18.2f\n",2,car2,CalculateCost(car2));
    printf("%2d%13d%18.2f\n",3,car3,CalculateCost(car3));
    printf("TOTAL %9d%18.2f\n",car1 + car2 + car3,CalculateCost(car1)+CalculateCost(car2)+CalculateCost(car3));

    return 0;
}