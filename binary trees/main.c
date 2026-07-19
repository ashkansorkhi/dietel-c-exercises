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
void inOrder(binaryTreePtr treePtr);
void preOrder(binaryTreePtr treePtr);
void postOrder(binaryTreePtr treePtr);


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

puts("\n\nThe preOrder traversal is:");
preOrder(parent);
// traverse the tree inOrder
puts("\n\nThe inOrder traversal is:");
inOrder(parent);
// traverse the tree postOrder
puts("\n\nThe postOrder traversal is:");
postOrder(parent);

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



void inOrder(binaryTreePtr treePtr)
{
    if (treePtr != NULL) {
    inOrder(treePtr->leftSubTree);
    printf("%d ",treePtr->data);
    inOrder(treePtr->rightSubTree);
    }
}

void preOrder(binaryTreePtr treePtr)
{
    if (treePtr != NULL) {
    printf("%d ",treePtr->data);
    preOrder(treePtr->leftSubTree);
    preOrder(treePtr->rightSubTree);
    }
}

void postOrder(binaryTreePtr treePtr){
    if (treePtr != NULL) {
    postOrder(treePtr->leftSubTree);
    postOrder(treePtr->rightSubTree);
    printf("%d ",treePtr->data);
    }
}