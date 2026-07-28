#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#define DEBUG
#define F_NAME_SIZE 26


//prototype
void getFileName(char arr[],size_t size);
void deleteDigit(FILE * filePtr);


int main(void)
{

    char filename[F_NAME_SIZE] = {};
    FILE * headerPtr = NULL;
    getFileName(filename,F_NAME_SIZE);
    #ifdef DEBUG
    printf("getFileName-output= %s",filename);
    #endif
    if((headerPtr = fopen(filename,"r+"))!=0)
    {
        deleteDigit(headerPtr);
    }
    else
    {
        puts("could not open the file or invalid file name");
    }
    
    fclose(headerPtr);
}


void getFileName(char arr[],size_t size)
{

    puts("***welcome to the line number remover***");
    printf("%s","please Enter the file name you need to edit:");
    scanf("%25s",arr);

}



void deleteDigit(FILE * filePtr)
{
    char character;
        while(fscanf(filePtr,"%c",&character)== 1)
        {
            ;
            if(isdigit(character)) 
           {    
               fseek(filePtr,-1,SEEK_CUR);
               character =' ';
                fprintf(filePtr,"%c",character);
                fseek(filePtr,-1,SEEK_CUR);
           }
        }
}
