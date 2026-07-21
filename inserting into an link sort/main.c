#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structs

struct numbers
{
    int value;
    struct numbers * nextNumber;
};


typedef struct numbers numbers;

typedef numbers *numberPtr;


//prototypes
void insertingNumbers(int value ,numberPtr * startNode,numberPtr * tailNode);
void printLinkedList(numberPtr headNode);
void freeLinkList(numberPtr  startNode);
int main(void)
{

   numberPtr startPtr = NULL;
   numberPtr tailNode = NULL;
    srand(time(NULL));
    
    for(int i = 1; i <= 25; i++)
        insertingNumbers(rand()%100,&startPtr,&tailNode);
    printLinkedList(startPtr);
    freeLinkList(startPtr);
    startPtr = NULL;
    tailNode = NULL;
}



void insertingNumbers(int value ,numberPtr * startNode,numberPtr * tailNode)
{

    numberPtr newNode = malloc(sizeof(numbers));

    if(newNode !=NULL)
    {

    newNode->value = value;
    newNode->nextNumber = NULL;

    if( *startNode  == NULL)
    {
        *startNode = newNode;
        *tailNode = newNode;
    }

    else
    {
        (*tailNode)->nextNumber = newNode;
        *tailNode = newNode;
    }
    
  

    }
    else
    {
        puts("not enough storage.");
    }
        
}

void printLinkedList(numberPtr headNode)
{
    while(headNode != NULL)
    {
        printf("%d ",headNode->value);
        headNode= headNode->nextNumber;
    }
    puts("");
}



void freeLinkList(numberPtr  startNode){
    numberPtr temp = NULL;
    while(*startNode !=NULL)
    {
        temp = startNode;
        free(temp);
        startNode = startNode->nextNumber;
    }
}