#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
void showInventory(HardWares*, FILE * );
void deleteTool(HardWares * ,FILE * );
void editTool(HardWares * ,FILE * );


int main(void){

    int choice =0;
    HardWares hardware = {0,"",0,0.0};
    FILE *filePtr = 0;


    if((filePtr = fopen("hardware.dat","rb+") ) == 0){
       filePtr = initializeFile(&hardware,filePtr);
    }

    
    
    puts("*****WELCOME*****");

    while(choice !=-1){
     printMenu();
     scanf("%2d",&choice);

    switch (choice)
    {
    case 1 :
        addTool(&hardware,filePtr);
        break;
        
     case 2 :
     editTool(&hardware,filePtr);
        break;
        
    case 3:
        deleteTool(&hardware,filePtr);
        break;
    case 4:
        showInventory(&hardware,filePtr);
        break;
    default:
        puts("invalid choice!");
        break;
    }//end switch   
}//end while
fclose(filePtr);
puts("end of program.");
}




 FILE * initializeFile(HardWares *hardware,FILE * filePtr){


 if ((filePtr = fopen("hardware.dat","wb+") )==0)
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
 puts("Please Enter:");
 puts("1.For adding new tool.");
 puts("2.For edit a tool");
 puts ("3.For delete a tool");
puts ("4.To show inventory");
 }




 void addTool(HardWares* tool,FILE * filePtr){

     puts("Please Enter the Tool number:");
    scanf("%d",&tool->recordNumber);
     puts("Please Enter the Tool name:");
    scanf(" %14s",tool->toolName);
     puts("Please Enter the Tool quantity:");
    scanf("%d",&tool->quantity);
     puts("Please Enter the Tool price:");
    scanf("%lf",&tool->price);

    fseek(filePtr, (tool->recordNumber - 1) * sizeof(HardWares),SEEK_SET);
    
    fwrite(tool,sizeof(HardWares),1,filePtr);

 }



 void showInventory(HardWares * tool, FILE * filePtr){
   
    rewind(filePtr);

    printf("%-12s%-12s%-12s%s\n","#RECORD","Tool Name","Quantity","Cost");

    while((fread(tool,sizeof(HardWares),1,filePtr) )!= 0){
        if(tool->quantity !=0)
          printf("%-12d%-12s%-12d%.2lf\n",tool->recordNumber,tool->toolName,tool->quantity,tool->price);

    }


 }

  void deleteTool(HardWares * tool,FILE * filePtr){
    int toolNumber = 0 ;

    puts("Please Enter the Tool number:");

        scanf("%d",&toolNumber);
    
    fseek(filePtr, (toolNumber - 1) * sizeof(HardWares),SEEK_SET);
        *tool = (HardWares){0,"",0,0.0};
        fwrite(tool,sizeof(HardWares),1,filePtr);

  }

  void editTool(HardWares* tool,FILE * filePtr){
    int toolNumber =0;
    int choice = 0;
    puts("please Enter the tool number to edit");
    scanf("%d",&toolNumber);
    fseek(filePtr, (toolNumber - 1) * sizeof(HardWares),SEEK_SET);
    fread(tool,sizeof(HardWares),1,filePtr);
    puts("please Enter:\n 1.to edit tool number\n2.to edit tool name\n3.to edit tool quantity.\n4.to edit tool price.");
     scanf("%d",&choice);
    switch (choice)
    {
    case 1:
    int toolNewNumber = 0;
    bool isItDublicated = false;
     rewind(filePtr);
     puts("Please Enter the Tool new number:");
     scanf("%d",&toolNewNumber);
     while(fread(tool,sizeof(HardWares),1,filePtr) !=0){
        if(tool->recordNumber == toolNewNumber)
            isItDublicated = true;
     }
     if(!isItDublicated){
         fseek(filePtr,(toolNumber -1) *sizeof(HardWares),SEEK_SET);
        fread(tool,sizeof(HardWares),1,filePtr);
        tool->recordNumber = toolNewNumber;
        fseek(filePtr,(tool->recordNumber -1) *sizeof(HardWares),SEEK_SET);
        fwrite(tool,sizeof(HardWares),1,filePtr);
        *tool = (HardWares) {0,"",0,0.0};
     }
     else
     puts("this number was assigned to another tool please try another number");
        break;
    case 2:

     puts("Please Enter the Tool new name:");
     scanf(" %14s",tool->toolName);
        break;

    case 3:

     puts("Please Enter the Tool new quantity:");
     scanf("%d",&tool->quantity);
        break;

    case 4:
     puts("Please Enter the Tool new price:");
     scanf("%lf",&tool->price);
        break;
    
    default:
    puts("invalid choice");
        break;
    }
    fseek(filePtr, (toolNumber - 1) * sizeof(HardWares),SEEK_SET);
    fwrite(tool,sizeof(HardWares),1,filePtr);
  }
