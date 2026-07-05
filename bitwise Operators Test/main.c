#include <stdio.h>
#include <stdlib.h>
#define CARDS 52


struct bitCard{
    unsigned int face :4;
    unsigned int suit :2;
};
typedef struct bitCard Card;

void deckFill(CARDS deck[]);
void deal(CARDS deck[]);

int main()
{

card Deck[CARDS] = {0};
deckFill(Deck);



}

void deckFill(CARDS deck[]){

    for(size_t i = 0 ; i < CARDS ; i++){


    }

}
