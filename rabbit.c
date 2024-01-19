#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define FINISH 70

// function calls for pointer to hare and tortiose and positioning

void position1 ( int* tPtr );
void position2 ( int* hPtr );
void printPositions ( int* tPtr , int* hPtr );


int main (void)
{

    int turtle = 1, hare = 1, movement1 = 1, movement2 = 1, timer = 0, start = 0; // variables
    int choice; // Exit choice
    int *tPtr = &turtle; // tort pointer
    int *hPtr = &hare; // hare pointer

    printf ( "To have the tortiose and the hare race, press 1 [Any other character to exit]: " );
    scanf ( "%d", &start ); // input to start

    while ( start == 1 )
    {

        puts ( "BANG!!!!!!" );
        puts ( "AND THEY'RE OFF!!!!!" );
        puts ( "HT" );
        // for loop to activate this function call to 70.
//        printf ( "%d %d ", *tPtr, *hPtr);
        for ( turtle != FINISH, hare != FINISH; turtle <= 70 || hare <= 70; timer++ )
        {
            sleep(1);
            position1 ( &turtle );     //function call tort
            position2 ( &hare );    // fucntion call hare
            printPositions ( &turtle, &hare ); // function call print result
//            printf ( "%d %d", *tPtr, *hPtr);
        }

        if ( hare >= FINISH || turtle >= FINISH ) // results
        {
            if ( turtle > hare )
            {
                printf ( "THE TORTIOSE WINS!!!!\n" );
                printf ( "The race took: %ds\n", timer );
            }

            else if ( hare > turtle )
            {
                printf ( "The hare wins. Yuch\n" );
                printf ( "The race took: %ds\n", timer );
            }

            else
            {
                printf ( "Tie race!\n" );
                printf ( "The race took: %ds\n", timer );
            }

        }// end results

    break; // stops while loop (No exit condition)
    } // end main while loop


} // end main

void position1 ( int *tPtr ) // function call for tortoise
{

    int turtle;

        srand( time ( 0 ));
        turtle = 1 + ( rand() % 10 ) ;
    //    printf ( "%d ", turtle );
    //    printf( "%d", *tPtr );

        if ( turtle >= 1 || turtle <= 5 )// movement1 <=5
        {
            *tPtr += 3;
        //    printf ( "m3t ");
        }
        else if ( turtle == 6 || turtle == 7 ) // movement1 = 6 && movement1 = 7
        {
            *tPtr -= 6;
        //    printf ( " m-6t ");
        }
        else if ( turtle >= 8 ) // movement1 >=8
        {
            *tPtr += 1;
        //    printf ( "m1t ");
        }

        else // (movement1 < 1 )
        {
            *tPtr == 1;
        //    printf ( "m0t ");
        }
}// end of turtle fucntion
void position2 ( int *hPtr ) // function call for hare
{

    int hare;

        srand (time ( 0 ));
        hare = 1 + ( rand() % 10 );
    //    printf ( "%d ", *hPtr);

        if ( hare <= 2)// movement2 <=2
        {
            *hPtr += 1;
        //    printf ( "m1h ");
        }

        else if ( hare == 3 || hare == 4 ) // movement2 = 6 && movement2 = 7
        {
            *hPtr = *hPtr;
        //    printf ( "m0h ");
        }

        else if ( hare >= 5 || hare <= 7 ) // movement2 >=8
        {
            *hPtr += 9;
        //    printf ( "m9h ");
        }

        else if ( hare >= 8 || hare <= 9 )
        {
            *hPtr -= 2;
        //    printf ( "m-2h ");
        }

        else if ( hare == 10 )// (movement2 < 1 )
        {
            *hPtr -= 12;
        //    printf ( "m-12h  " );
        }
        else
        {
            *hPtr = 1;
                   }
}// end of turtle fucntion

void printPositions ( int *tPtr, int *hPtr ) // Race Print function start
{
    int movement;
    int turtle;
    int hare;

    if ( &turtle == &hare ) // We are only getting in here, why?
    {
    //    printf ( " *tPtr == *hPtr ");
        for ( movement = 0; movement < *tPtr; movement++ )
            {
                printf ( " " );
            }
        printf ( "OUCH!" );
    }
    else if ( *tPtr < *hPtr )
    {
        //printf( "*tPtr < *hPtr " );
        for ( movement = 0; movement < *tPtr; movement++ )
            printf ( " " );

        printf ( "T" );


        for ( movement = 0; movement < (*hPtr - *tPtr); movement++ )
            printf ( " " );

        printf ( "H" );
    }

    else  {
        //printf ( " *hptr < *tptr " );
        for ( movement = 0; movement < *hPtr; movement++)
        {
            printf ( " " );
        }
        printf ( "H" );
        for (movement = 0; movement < ( *tPtr - *hPtr ); movement++ )
        {
            printf ( " " );
        }
        printf ( "T" );
    }
    printf ( "\n" );


} // race print function, end.