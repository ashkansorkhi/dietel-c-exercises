#include <stdio.h>
#include "greet.c"

#define POW_2(x) ((x) * ( x))

#if defined(POW_2)  
    #define MODE "square mode"

#elif defined(POW_3)
#define MODE "cubed mode"

#else 
    #define MODE  "no mode"
#endif




int main(void){
    char name[10] =" ";
    scanf("%s",name);
   greet();
    printf("%s\n",name);
    puts("here's the pow of 4 :");
    printf("%d\n",POW_2(2+2));

}