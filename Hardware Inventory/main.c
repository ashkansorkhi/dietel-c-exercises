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
void showInventory(HardWares*,FILE *);
void deleteTool(HardWares * tool,FILE * filePtr);



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
      //  editTool();
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



 void showInventory(HardWares * tool,FILE * filePtr){
   
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