#include <stdio.h>
#include <stdlib.h>
#define SIZE 10



int main(void){

unsigned int sits[SIZE] = {0};
unsigned int customerChoice = 0;

while(sits[4]!=1 || sits[9]!=1 ){

    printf("%s\n%s","Please type 1 for \"first class\"","Please type 2 for \"economy\"\n");
    scanf("%ud",&customerChoice);
    if(customerChoice == 1 || customerChoice == 2){


        switch(customerChoice){

            case 1 :
                for(int i = 0 ; i<5; i++){
                    if(sits[i]==0){
                        sits[i] = 1;
                        break;
                        }
                    if(sits[4]==1){
                        puts("the first class section is full is it acceptable to be placed in the economy section?y/n");
                        char answer = 'p';
                           scanf(" %c",&answer);
                           answer == 'y'?customerChoice=2:puts("next flight leaves in 3 hours");
                            break;
                    }

                }//end for
                        break;

                 case 2 :
                    for(int i = 5 ; i<10; i++){
                        if(sits[i]==0){
                            sits[i] = 1;
                            break;
                        }
                        if(sits[9]==1){
                            puts("the economy section is full is it acceptable to be placed in the first class section?y/n");
                            char answer = 'p';
                            scanf(" %c",&answer);
                            answer == 'y'?customerChoice=1:puts("next flight leaves in 3 hours");
                            break;
                           }

                        }//end for
                        break;
        }//end switch
}//end if
else
    puts("Please Enter a valid Number.");

 }//end while

}//end main
