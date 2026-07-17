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
char delete(listNodePtr *startPtr,char value);
 int main(void){
    listNodePtr startPtr = NULL;
    char character = ' ';
    int choice = 0 ;
    puts("please Enter:\n1.to add new character and\n2.to delete a character");
    switch (choice)
    {
    case 1:
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
        break;
    case 2:
        puts("Enter the character you want to delete:");
        scanf(" %c",&character);
        char deletedChar = delete(&startPtr,character);
        printf("char %c deleted\n",deletedChar);
        puts("new linked list table:");
        printNode(&startPtr);
        break;
    default:
    puts("invalid code");
        break;
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


 char delete(listNodePtr *startPtr,char value){

    if(value = (*startPtr)->value){
        listNodePtr tempNode = *startPtr;
        *startPtr = (*startPtr)->nextPtr;
        free(tempNode);
        return value;
    }

    else{
        listNodePtr previousNode = *startPtr;
        listNodePtr currentNode = (*startPtr)->nextPtr;
        if(currentNode != NULL && currentNode->value != value){
            previousNode = currentNode;
            currentNode = currentNode->nextPtr;
        }

        if(currentNode !=NULL){
            listNodePtr tempNode = currentNode;
            currentNode = currentNode->nextPtr;
            free(tempNode);
            return value;
        }

    }
    return '\0';

 }