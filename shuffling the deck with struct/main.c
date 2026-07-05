#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define FACES 13

typedef struct{
    char * faces;
    char * suit;
}Card ;

void fillDeck(Card deck[],const char *const suit[], const char *const face[]);
void suffle(Card deck[]);
void deal(const Card deck[]);
int main(void){

    Card deck[CARDS];

    const char *faces[] = { "Ace", "Deuce", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    const char *suits[] = { "Hearts", "Diamonds", "Clubs", "Spades"};

    srand(time(NULL));

    fillDeck(deck,suits,faces);

    suffle(deck);

    deal(deck);
}

void fillDeck(Card deck[],const char *const suit[], const char *const face[]){

    for(size_t i =0; i< CARDS ; i++){
        deck[i].faces = face[i%FACES];
        deck[i].suit = suit[i/FACES];
    }

}


void suffle(Card deck[]){
    Card temp = {};
    for(size_t i = 0; i<CARDS ; i++){
        size_t j = rand() %CARDS;
        temp = deck[i];
        deck[i]= deck[j];
        deck[j] = temp;
    }

}


void deal(const Card deck[]){
    for(size_t i = 0; i<CARDS ; i++)
        printf("%5s of %-8s%c",deck[i].faces,deck[i].suit,(i +1)%4?' ':'\n');


}
