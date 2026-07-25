#include <stdio.h>
#include <assert.h>
#include "greet.c"
#define POW_2(x) ((x) * ( x))
#define NAME(x) puts("hello " #x)
#if defined(POW_2)  
    #define MODE "square mode"

#elif defined(POW_3)
#define MODE "cubed mode"

#else 
    #define MODE  "no mode"
#endif




int main(void){
    int number[10] ={0};
    //scanf("%s",name);
  // greet();
  for(size_t i = 0 ; i <=11 ; i++)
  {
      assert(i <= 10);
      number[i] = i + 1;
      printf("%d \n", number[i]);
  }
    NAME(ahkan);
    puts("here's the pow of 4 :");
    printf("%d\n",POW_2(2+2));

}