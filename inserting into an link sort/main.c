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
void insertingNumbers(int value ,numberPtr * startNode);
void printLinkedList(numberPtr headNode);

int main(void)
{

   numberPtr startPtr = NULL;
   
    srand(time(NULL));
    
    for(int i = 1; i <= 25; i++)
        insertingNumbers(rand()%100,&startPtr);
    printLinkedList(startPtr);
}



void insertingNumbers(int value ,numberPtr * startNode)
{

    numberPtr newNode = malloc(sizeof(numbers));

    if(newNode !=NULL)
    {

    newNode->value = value;
    newNode->nextNumber = NULL;
    
    numberPtr previusNode = NULL;
    numberPtr currentNode = *startNode;

    if(currentNode == NULL)
        *startNode = newNode;
    
    else{

         while(currentNode != NULL)
        {
            previusNode = currentNode;
            currentNode = currentNode->nextNumber;
        }

        currentNode = newNode;
        previusNode->nextNumber  = currentNode;
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
}