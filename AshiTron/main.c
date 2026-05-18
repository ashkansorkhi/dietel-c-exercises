#include <stdio.h>
#include <stdlib.h>
#define WORD_SIZE 100
#define WRITE 11
#define READ 10
#define LOAD 20
#define STORE 21
#define ADD 30
#define HALT 43
int main(void){

int accumulator = 0000;
int instructionCounter = 00;
int instructionRegister = 0000;
int operationCode = 00;
int operandCode =00;
int memory[WORD_SIZE] = {};

puts("Hi Im AshiTron Please Enter Your Command I will be happy to copy.");
while(operationCode != HALT){
    scanf("%d",&instructionRegister);
    instructionCounter++;
    operationCode = instructionRegister / 100;
    operandCode = instructionRegister %100;

    switch(operationCode){
    case READ:
        scanf(" %d",&memory[operandCode]);
        break;
    case WRITE:
        printf("%d \n",memory[operandCode]);
        break;
    case LOAD:
        accumulator = memory[operandCode];
        break;
    case STORE:
            memory[operandCode] = accumulator;
            break;
    case ADD:
            accumulator+=memory[operandCode];
            break;
    case HALT:
            printf("the program execution has completed");
            break;

}
}



}

