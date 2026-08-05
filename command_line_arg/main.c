#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        puts("not enough arguments to run");
        exit(1);
    }

    FILE * inputFilePtr = NULL;

    if((inputFilePtr = fopen(argv[1],"r")) != NULL)
    {
        int c = 0;
        FILE * outPutFilePtr = NULL;

        if((outPutFilePtr = fopen(argv[2],"w")) != 0)
        {
            while((c = fgetc(inputFilePtr) )!= EOF)
            {
                fputc(c,outPutFilePtr);
            }
            fclose(outPutFilePtr);
        }
        else
        {
            puts("could't open the output file");
        }
        fclose(inputFilePtr);
    }
    else{
        puts("couldn't find the input file to copy");
    }

}