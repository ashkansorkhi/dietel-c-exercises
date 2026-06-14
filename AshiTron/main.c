#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define WORD_SIZE 100
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
#define STR_IN 50
#define STR_OUT 51
/*
1090
1091
2091
2196
1092
2092
3093
2193
2091
3190
2191
4213
4004
2093
3296
2195
1195
4300


1.get the statement
operation code 50 operand x
2. first 2 digits as readChar statement last two as first memory element
3. read every char and convert it to ascii and store it in memory
while(c = getch() != '\n' && i < MAX_STRING_LIMITATION)
    int c1 =
4 first memory elementr stores size of the string
*/
void dump(int,int,int,int,int,const int[]);

int main(void){

int accumulator = 0000;
int instructionCounter = 00;
int instructionRegister = 0000;
int operationCode = 00;
int operandCode =00;
int memory[WORD_SIZE] = {0};

   printf("*** Welcome to AshiTron! ***\n");
    printf("*** Please enter your program one instruction ***\n");
    printf("*** (or data word) at a time. I will type the ***\n");
    printf("*** location number and a question mark (?). ***\n");
    printf("*** You then type the word for that location. ***\n");
    printf("*** Type -99999 to stop entering your program. ***\n\n");

    for(size_t i =0 ; i < WORD_SIZE ; i++){
        int input = 0 ;
        printf("%02d ? ",i);
        scanf("%d",&input);
        if(input <=9999 && input >=1000 || input == -99999){
                    if(input == -99999)
                        break;

                    memory[i]=input;
    }//end if
        else{
                puts("Please Enter a Valid instruction");
                i--;
    }//end else
}//end for loop
puts("Program Loading Completed");
while(1){
    instructionRegister = memory[instructionCounter];
    operationCode = instructionRegister / 100;
    operandCode = instructionRegister %100;

    switch(operationCode){
    case READ:
        scanf(" %d",&memory[operandCode]);
        instructionCounter++;
        break;
    case WRITE:
        printf("%d \n",memory[operandCode]);
          instructionCounter++;
        break;
    case LOAD:
        accumulator = memory[operandCode];
          instructionCounter++;
        break;
    case STORE:
            memory[operandCode] = accumulator;
              instructionCounter++;
            break;
    case ADD:
            accumulator+=memory[operandCode];
              instructionCounter++;
            break;
    case SUBTRACT:
            accumulator-=memory[operandCode];
              instructionCounter++;
            break;
    case MULTIPLY:
            accumulator*=memory[operandCode];
              instructionCounter++;
            break;
    case DIVIDE:
        if(accumulator ==0 || memory[operandCode] == 0)
            puts("fatal error = trying to divide to zero!");
        else {  accumulator/=memory[operandCode];
              instructionCounter++;}
            break;
    case HALT:
            printf("*** AshiTron execution terminated ***");
            dump(accumulator,instructionCounter,instructionRegister,operationCode,operandCode,memory);
              instructionCounter++;
           return 0;
            break;
    case BRANCH:
          instructionCounter =operandCode;
            break;
    case BRANCHNEG:
          if(accumulator < 0)
                instructionCounter =operandCode;
           else
                instructionCounter++;
          break;
    case BRANCHZERO:
          if(accumulator == 0)
                instructionCounter =operandCode;
           else
                instructionCounter++;
          break;
    case  STR_IN :
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

                puts("Please Enter your characters");
                size_t i = 1;
                int count = 0;
                char c1=0;
                while (1){
                    c1= getchar();
                        if(c1 == '\n')
                            break;
                        count++;
                    int ASC1 = (int)c1;
                        if( i > WORD_SIZE)
                            break;
                    memory[operandCode + i]= ASC1 ;
                    i++;
                }
                memory[operandCode]+=count;
                  instructionCounter++;
                break;
    case STR_OUT:

        char char1 = 0;
        int length = memory[operandCode];
        for(size_t i = 1 ; i<=length ; i++){
       int   charElement =  memory[operandCode+i];
          printf("%c",(char)charElement);
        }
        instructionCounter++;
        break;
    default:
         printf("Invalid Operation Code %d\n",operationCode);
       puts("*** AshiTron execution abnormally terminated ***\n");
       return 0;
}//end switch
}//end while
}

void dump(int acc,int instrCounter,int instrReg,int operationCode,int operandCode,const int memory[]){
puts("\n\nREGISTERS:");
printf("Accumulator %-1d\n",acc);
printf("InstructionCounter %-1d\n",instrCounter);
printf("InstructionRegister %-1d\n",instrReg);
printf("OperationCode %-1d\n",operationCode);
printf("OperandCode %-1d\n",operandCode);
puts("\n\n\nMEMORY:");
puts("          0       1       2       3       4       5       6       7       8       9");
    for(size_t j =0 ; j<100; j++){
        if(j% 10 == 0 || j == 0)
            printf("\n %02d",j);

        printf("   %+05d",memory[j]);

    }

}


