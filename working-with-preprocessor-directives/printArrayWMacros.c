#include <stdio.h>

#define PRINTARRAY(x,length)  for(int i = 0 ; i <length ; i++)\
{\
    printf("%d ",x[i]);\
}


int main(void)
{
    int array[5] = {12,23,66,32,12};
    PRINTARRAY(array,5);
}