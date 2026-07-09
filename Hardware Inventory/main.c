#include <stdio.h>

//structs
typedef struct {
        int recordNumber;
        char toolName[15];
        int quantity ;
        double price;
}HardWares;

//prototypes

FILE * initializeFile(HardWares*,FILE *);
void printMenu(void);
void addTool(HardWares*,FILE *);




int main(void){

    int choice =0;
    HardWares hardware = {0,"",0,0.0};
    FILE *filePtr = 0;
    if((filePtr = fopen("hardware.dat","rb+") ) == 0){
       filePtr = initializeFile(&hardware,filePtr);
    }
    printMenu();

    while(choice !=-1){
    switch (choice)
    {
    case 1 :
        addTool(&hardware,filePtr);
        break;
        
     case 2 :
        editTool();
        break;
        
    case 3:
        deleteTool();
        break;
    default:
        puts("invalid choice!");
        break;
    }//end switch   
}//end while
puts("end of program.");
}




 FILE * initializeFile(HardWares *hardware,FILE * filePtr){


 if ((filePtr = fopen("hardware.dat","wb") )==0)
 {
    puts("cannot Create the file");
 }
 else{
    for( int i =1 ; i <=100 ; i++)
        fwrite(hardware,sizeof(HardWares),1,filePtr);

 }
return filePtr;


 }


 void printMenu(void){
 puts("*****WELCOME*****");
 puts("Please Enter:");
 puts("1.For adding new tool.");
 puts("2.For edit a tool");
 puts ("3.For delete a tool");

 }




 void addTool(HardWares*,FILE *){

    


 }