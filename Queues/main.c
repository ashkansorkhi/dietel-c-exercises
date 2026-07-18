#include <stdio.h>
#include <stdlib.h>

//structures 
struct queueNode {
char data; // define data as a char
struct queueNode *nextPtr; // queueNode pointer
};

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;





//prototypes
void printQueue(QueueNodePtr currentPtr);
int isEmpty(QueueNodePtr headPtr);
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value);
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
void instructions(void);





int main(void) {
QueueNodePtr headPtr = NULL; 
QueueNodePtr tailPtr = NULL; 
char item = '\0'; 
instructions(); 
printf("%s", "? ");
int choice = 0; 
scanf("%d", &choice);

while (choice != 3) {
switch(choice) {
case 1: // enqueue value
printf("%s", "Enter a character: ");
scanf("\n%c", &item);
enqueue(&headPtr, &tailPtr, item);
printQueue(headPtr);
break;
case 2: 

if (!isEmpty(headPtr)) {
item = dequeue(&headPtr, &tailPtr);
printf("%c has been dequeued.\n", item);
}
printQueue(headPtr);
break;
default:
puts("Invalid choice.\n");
instructions();
break;
}
printf("%s", "? ");
scanf("%d", &choice);
}
puts("End of run");



}


void instructions(void) {
puts("Enter your choice:\n1 to add an item to the queue\n2 to remove an item from the queue\n3 to end\n");
}



int isEmpty(QueueNodePtr headPtr){

    return headPtr == NULL;
}


void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value){
    QueueNodePtr newNode = malloc(sizeof(QueueNode));
    newNode->data = value;
    newNode->nextPtr = NULL;
    if(newNode != NULL ){

        if(isEmpty(*headPtr))
        {
            *headPtr = newNode;
        }

        else
        {
            (*tailPtr)->nextPtr = newNode;
        }
        *tailPtr = newNode;
    }
    
    else
    {
        puts("not enough storage");
    }


}



char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr){

    if(!isEmpty(*headPtr))
    {
        QueueNodePtr tempNode = *headPtr;
        char value = (*headPtr)->data;
        *headPtr = (*headPtr)->nextPtr;
        free(tempNode);
        return  value;
    }
    else
    {
        puts("the queue is empty");
    }


}


void printQueue(QueueNodePtr currentPtr){
    while (currentPtr != NULL )
    {
        printf("%c -->",currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }

    puts("NULL");


}
