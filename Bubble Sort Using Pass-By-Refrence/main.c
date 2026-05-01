#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void BubbleSorter(int * const, size_t);

void swap(int *, int *);

int main(void){

int a[SIZE] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };

puts("the original Array is :");

for(size_t i =0; i< SIZE ; i++)
    printf("%d ",a[i]);
BubbleSorter(a,SIZE);
puts("\nafter bubble sorting");
for(size_t i =0; i< SIZE ; i++)
    printf("%d ",a[i]);
}

void BubbleSorter(int * const arrPtr, size_t size){
        for(int pass = 0; pass <size -1 ;pass++){
            for(size_t i=0 ; i<size -1 ;i++){
                if(arrPtr[i]> arrPtr[i+1])
                    swap(&arrPtr[i],&arrPtr[i+1]);
                   }
            }
}

void swap(int *greater, int *smaller){
        int holder = *greater;
        *greater = *smaller ;
        *smaller = holder;
}

