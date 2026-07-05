#include <stdio.h> 
#define MAX_NAME_STRING 30

/*  
sudocode 



main func 
for other functions
 fopen("account.txt","rb+");

delete account function

access to file and delete a record from the list 

add account function
    access to file and add a new account to the list 
*/


//Structs 

typedef struct {
    int accountNumber ;
    char firstName[MAX_NAME_STRING];
    char lastName[MAX_NAME_STRING];
    double balance ;

} clientStruct ;



//function prototypes
void createListOfAccounts(clientStruct *);

void printListOfAccounts(clientStruct *,FILE *);

void updateAccount(clientStruct *,FILE *);

void createNewAccount(clientStruct *,FILE *);

void deleteAccount(clientStruct *,FILE *);


//main function

int main(void){
    clientStruct client = {0,"","",0.0};
    FILE *cltPtr = 0;
    
    createListOfAccounts(&client); //initialize the file and list 
    
    if((cltPtr = fopen("accounts.txt","rb+")) == 0)
        puts("cannot find the file");

    else {
        printListOfAccounts(&client,cltPtr);
        puts("Welcome\n    please Enter: 1 to make the list of clients\n   please Enter: 2 edit client informations\n   please Enter: 3 to delete a client \n please  Enter: 4 to add a client  ");
        updateAccount(&client,cltPtr);
         printListOfAccounts(&client,cltPtr);

    }
fclose(cltPtr);
}     





void createListOfAccounts(clientStruct * client){

    FILE * listOfAccountsPtr = 0;

    if((listOfAccountsPtr = fopen("accounts.txt","wb")) == 0)
        puts("cannot open the file ");

    else{
        puts("Please Enter account number, first name ,last name,balance and -1 to end the procces");
         scanf("%d%29s%29s%lf",&client->accountNumber,client->firstName,client->lastName,&client->balance);
        while(client->accountNumber != -1){
            fwrite(client,sizeof(clientStruct),1,listOfAccountsPtr);
            puts("please Enter the next client: ");
            scanf("%d%29s%29s%lf",&client->accountNumber,client->firstName,client->lastName,&client->balance);
        }
        
    }
    fclose(listOfAccountsPtr);

}   


void updateAccount(clientStruct *client ,FILE * filePtr){

    int accountNumber = 0;
    int option =0;

        puts("please Enter The Account Number:");
         scanf("%d",&accountNumber);

        puts("1.Edit First Name.\n 2.Edit Last Name.\n3.Edit Balance.");
         scanf("%d",&option);

    switch (option) {

    case 1:
        
        fseek(filePtr,(accountNumber-1) * sizeof(clientStruct),SEEK_SET);
        fread(client,sizeof(clientStruct),1,filePtr);
        puts("Please Enter The New First Name:");
        scanf("%29s",client->firstName);
        fseek(filePtr,(accountNumber-1) * sizeof(clientStruct),SEEK_SET);
        fwrite(client,sizeof(clientStruct),1,filePtr);
        break;

    case 2:

        fseek(filePtr,(accountNumber-1) * sizeof(clientStruct),SEEK_SET);
        fread(client,sizeof(clientStruct),1,filePtr);
        fseek(filePtr,(accountNumber-1) * sizeof(clientStruct),SEEK_SET);
        puts("Please Enter The New Last Name:");
        scanf("%29s",client->lastName);
        fwrite(client,sizeof(clientStruct),1,filePtr);
        break;

    case 3:
        fseek(filePtr,(accountNumber-1) * sizeof(clientStruct),SEEK_SET);
        fread(client,sizeof(clientStruct),1,filePtr);
        fseek(filePtr,(accountNumber-1) * sizeof(clientStruct),SEEK_SET);
        puts("Please Enter The New Balance:");
        scanf("%lf",&client->balance);
        fwrite(client,sizeof(clientStruct),1,filePtr);
        break;

    default:
    puts("Please Enter a valid choice");
        break;
    }

}





void printListOfAccounts(clientStruct * client,FILE * filePtr){
    rewind(filePtr);
        puts("account number  first name  last name  balance");
        while(fread(client,sizeof(clientStruct),1,filePtr)!=0){
            printf("%d %12s %12s %lf\n",client->accountNumber,client->firstName,client->lastName,client->balance);
   
        }

}