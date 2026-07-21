#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10


//prototype 
void selectionSort(int array[],int length);

void swap(int array[],size_t first,size_t second);

void printPass(const int array[],size_t first,size_t second,int length);



int main(void)
{
    int arr[SIZE]={0};

    srand(time(NULL));

    for(size_t i =0 ; i < SIZE ; i++)
    {
        arr[i] = rand() % 90 +10;
    }

    puts("unsorted Array:");

    for(size_t i =0 ; i < SIZE ; i++)
    {
        printf("%d ",arr[i]);
    }
    puts(" ");
    selectionSort(arr,SIZE);
    puts(" ");
    puts("sorted array:");


    for(size_t i =0 ; i < SIZE ; i++)
    {
        printf("%d ",arr[i]);
    }



}



void selectionSort(int array[],int length)
{
    for(size_t j = 0 ; j < length - 1; j++)
    {
        int smallest = j;
        for(size_t i = j + 1 ; i < length ;i++)
        {
            if(array[i] < array[smallest])
                smallest = i;
        }
             swap(array,smallest,j);
             printPass(array,smallest,j,SIZE);
    }
    
}

void swap(int array[],size_t first,size_t second)
{
    int temp = array[second];
    array[second] = array[first];
    array[first] = temp;
}



void printPass(const int array[],size_t first,size_t second,int length)
{
    printf("%s  %d :","after pass ",(int)second +1);

    for(size_t i =0 ; i < length ; i++)
    {
        if(i == first)
            printf("%d* ",array[first]);
        else
            printf("%d ",array[i]);


    }
    puts(" ");

    printf("%s","                ");
    for(int i = 0; i <=second; i++)
         printf("%s", "-- ");
    puts(" ");
}