#include <stdio.h>
#include <stdlib.h>

void bitDisplay(unsigned int num);

int main()
{
unsigned int number1 = 5324;
unsigned int mask = 1;
bitDisplay(number1);
bitDisplay(~number1);
bitDisplay(mask);
bitDisplay(~mask);
bitDisplay(mask & number1);
bitDisplay(mask | number1);
bitDisplay(mask ^ number1);
}


void bitDisplay(unsigned int num){

    unsigned int displayMask =1<< 31;
    for(int i =1 ; i<=32; i++){
        putchar( num & displayMask?'1':'0');
        num <<=1;
        if(i %8 == 0)
            putchar(' ');
    }
    putchar('\n');
}
