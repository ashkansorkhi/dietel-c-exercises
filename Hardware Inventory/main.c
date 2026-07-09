#include <stdio.h>

//structs
typedef struct {
        int recordNumber;
        char toolName[15];
        int quantity ;
        double price;
}HardWares;

//prototypes

void initializeFile(HardWares*);
void printMenu(void);





int main(void){

    int choice =0;
    HardWares hardware = {0,"",0,0.0};

    initializeFile(&hardware);
    printMenu();

    while(choice !=-1){
    switch (choice)
    {
    case 1 
        addTool() 
        break;
        
     case 2 
        editTool() 
        break;
        
    case 3
        deleteTool() 
        break;
    default:
        puts("invalid choice!");
        break;
    }//end switch   
}//end while
puts("end of program.");
}




 void initializeFile(HardWares *hardware){
    FILE * filePtr = 0;

 if (filePtr = fopen("hardware.dat","wd") ==0)
 {
    puts("cannot open the file in initializeFile");
 }
 else{
    for( int i =1 ; i <=100 ; i++)
        fwrite(hardware,sizeof(HardWares),1,filePtr);

 }
fclose(filePtr);


 }