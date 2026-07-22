#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10


void insertionSort(int arr[],size_t length);
void printfPass(size_t index,int arr[],size_t length);
int main(void)
{
    int array[SIZE] = {0};
    srand(time(NULL));

    for(size_t i = 0; i <SIZE ; i++)
    {
        array[i] = rand() %100;
    }
    puts("Unsorted array:");

    for(size_t i = 0; i <SIZE ; i++)
    {
        printf("%d ",array[i]);
    }
    puts("");
    insertionSort(array,SIZE);

    puts("Sorted array:");
    for(size_t i = 0; i <SIZE ; i++)
    {
        printf("%d ",array[i]);
    }

}



void insertionSort(int arr[],size_t length)
{
    
    for(size_t i = 1 ; i< length  ; i++)
    {
        int key = arr[i]; 
        int counter = i;
        while(counter != 0 && arr[counter -1] > key)
        {
              arr[counter] =  arr[counter -1 ];
            counter--;
        }
        arr[counter] = key;
        printfPass(i, arr,length);
    }

}


void printfPass(size_t index,int arr[],size_t length)
{
    printf("after pass %d: ",(int)index);
    for(size_t i = 0 ; i <length;i++)
        arr[index] == arr[i] ? printf("%d* ",arr[i]): printf("%d  ",arr[i]);
    puts("");
    printf("%s","              ");
    for(int i = 0 ; i<=index;i++)
        printf("%s","--  ");
    puts("");
    
}