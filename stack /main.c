#include <stdio.h>
#include <stdlib.h>

struct stackNode {
int data; 
struct stackNode *nextPtr; 
};

typedef struct stackNode StackNode; 
typedef StackNode *StackNodePtr;

void instructions(void);
int isEmpty(StackNodePtr topPtr);
void push(StackNodePtr *topPtr, int info);
int pop(StackNodePtr *topPtr);
void printStack(StackNodePtr currentPtr);


int main(void) {
    StackNodePtr stackPtr = NULL; 
    int value = 0; 
    instructions();
    printf("%s", "? ");
    int choice = 0; 
    scanf("%d", &choice);

    while (choice != 3) {
        switch (choice) {
         case 1: // push value onto stack
            printf("%s", "Enter an integer: ");
            scanf("%d", &value);
            push(&stackPtr, value);
            printStack(stackPtr);
            break;

         case 2: // pop value off stack

            if (!isEmpty(stackPtr)) {
                    printf("The popped value is %d.\n", pop(&stackPtr));
                    }
            printStack(stackPtr);
            break;
         default:
            puts("Invalid choice.\n");
            instructions();
            break;
    }
    printf("%s", "? ");
    scanf("%d", &choice);
    }
    puts("End of run.");
}

void instructions(void) {
puts("Enter choice:\n"
"1 to push a value on the stack\n"
"2 to pop a value off the stack\n"
"3 to end program");
}

int isEmpty(StackNodePtr topPtr) {
return topPtr == NULL;
}


void push(StackNodePtr *topPtr, int info){
    StackNodePtr newNode = malloc(sizeof(StackNode));

    if(newNode != NULL){
        newNode->data = info;
        newNode->nextPtr = *topPtr;
        *topPtr = newNode;
        
    }
    else
        printf("%d not inserted. No memory available.\n", info);
}
int pop(StackNodePtr *topPtr){
    StackNodePtr tempNode = *topPtr;
        int value = tempNode->data;
        *topPtr=(*topPtr)->nextPtr;
        free(tempNode);
        return value;

}
void printStack(StackNodePtr currentPtr){

    while(currentPtr !=NULL){
        printf("%d -->",currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }
    puts("NULL");
}