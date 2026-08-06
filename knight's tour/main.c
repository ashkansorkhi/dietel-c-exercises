#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MOVES_COUNT 8
//#define DEBUG

void moveKnight(int vericalMove, int horizontalMove,int chessBoard[][8],int * moveCounter);
bool isMoveValid(const int  horizontal,const int vertical, const int chessBoard[][8]);


int main(void)
{
const  int horizontal[MOVES_COUNT] = {2,1,-1,-2,-2,-1,1,2};
const  int  vertical [MOVES_COUNT] = {-1,-2,-2,-1,1,2,2,1};
       int chessBoard[8][8] = {0};
       int moveCounter = 0;
       srand(time(NULL));

    for(int i = 1 ; i <= 64 ; i++)
    {
        int choice = rand() % 8 ;
        #ifdef DEBUG
            printf("choice : %d\n", choice);
        #endif
        moveKnight(vertical[choice],horizontal[choice],chessBoard,&moveCounter);

    }
        



}





void moveKnight(int vericalMove, int horizontalMove,int chessBoard[][8],int * moveCounter)
{  
 static int currentRow = 5;
 static int currentColumn = 3;
 chessBoard[5][3] = 1;
 currentRow += horizontalMove;
 currentColumn += vericalMove;
        #ifdef DEBUG
            printf("Row: %d\n", currentRow);
            printf("column: %d\n", currentColumn);
        #endif
 if(isMoveValid(currentRow,currentColumn, chessBoard))
 {
        #ifdef DEBUG
            puts("Done");
        #endif
    chessBoard[currentRow][currentColumn] = 1;
    *moveCounter = *moveCounter + 1;
     printf("knight moved %d times\n", *moveCounter);
 }


 else 
 {
 currentRow -= horizontalMove;
 currentColumn -= vericalMove;
 }

 
}


bool isMoveValid(const int  horizontal,const int vertical, const int chessBoard[][8])
{
    if(   horizontal >=0 && vertical >=0 && horizontal <=7 && vertical <=7 &&chessBoard[horizontal][vertical] ==0)
        return true;
    else
        return false;
}