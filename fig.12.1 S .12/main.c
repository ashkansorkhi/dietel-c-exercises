 #include <stdio.h>
#include <stdlib.h>

typedef struct listNode 
{
    char value; 
    struct listNode *nextPtr;
}listNode;

typedef listNode *listNodePtr;
void insert(listNodePtr *,char );
void printNode(const listNodePtr *);

 int main(void){
    listNodePtr startPtr = NULL;
    char character = ' ';

    puts("enter the character");
    scanf(" %c",&character);
    puts("");
    while (character != '0')
    {
     insert(&startPtr,character);
     printNode(&startPtr);
     scanf(" %c",&character);
     puts("");
    }
    
    
 }





 void insert(listNodePtr *startPtr,char value){

    listNodePtr newNode = malloc(sizeof(listNode));
    if(newNode !=NULL){
        newNode->value = value;
        newNode->nextPtr = NULL; 
  

    listNodePtr previousNode = NULL;
    listNodePtr currentNode = *startPtr;

    while(currentNode !=0 && value > currentNode->value)
    {
        previousNode = currentNode;
        currentNode = currentNode->nextPtr;
    }

    if(previousNode == NULL){
        newNode->nextPtr = *startPtr;
        *startPtr = newNode;
    }
    else{
        previousNode->nextPtr = newNode;
        newNode->nextPtr = currentNode;
    }  }
    else{
        puts("not inserted, memory unavailable");
    }
 }


 void printNode(const listNodePtr * node){
    listNodePtr currentPtr =    *node;

    while(currentPtr->nextPtr != NULL){
        printf("%c --> ", currentPtr->value);
        currentPtr = currentPtr->nextPtr;
    }
 }