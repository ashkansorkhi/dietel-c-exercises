#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//structs 

struct binaryTree {
    
    struct binaryTree *leftSubTree;
    int data;
    struct binaryTree *rightSubTree;
    
};

//typedefs
typedef struct binaryTree binaryTree ;
typedef struct binaryTree *binaryTreePtr ;

//prototypes
void insertNode(int value , binaryTreePtr * parentNode); 


int main(void){

int number = 0;
binaryTreePtr parent = NULL;
srand(time(NULL));

puts("the numbers are:");

for(int i =1 ; i<=10; i++){
    number = rand() % 15;
    printf("%d ",number);
    insertNode(number,&parent);
}
    

}


// functions 


void insertNode(int value , binaryTreePtr * parentNode)
{

    if(*parentNode == NULL)
    {
        binaryTreePtr newPtr = malloc(sizeof(binaryTree));
        if(newPtr != NULL)
        {
          newPtr->data = value;
          newPtr->leftSubTree = NULL;
          newPtr->rightSubTree = NULL;
          * parentNode = newPtr;
        }
        else
        {
            puts("not enough space");
        }

    }
    else if(value < (*parentNode)->data)
    {
        insertNode(value, &(*parentNode)->leftSubTree);
    }


    else if(value > (*parentNode)->data)
    {
        insertNode(value, &(*parentNode)->rightSubTree);
    }
    else
    {
        printf("%s","dub");
    }



}
