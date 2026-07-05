#include <stdio.h>

 struct clientData {
   int account;
   char lastName[15];
   char firstName[10];
   double balance;
 };

 int main(void) {
   FILE *cfPtr = NULL;
    int accountNumb = 0;
   if ((cfPtr = fopen("accounts.dat", "rb+")) == NULL) {
      puts("File could not be opened.");
  }
   else {

      struct clientData client = {0, "", "", 0.0};

      puts("plese Enter the account number between 1-100 and 0 to end:");
        scanf("%2d",&accountNumb);
        while(accountNumb !=0){
            fseek(cfPtr,(accountNumb-1)*sizeof(struct clientData),SEEK_SET);
            puts("here is the account information:");
            fread(&client,sizeof(struct clientData),1,cfPtr);
            printf("FirstName:%s LastName:%s Balance:%f\n",client.lastName,client.firstName,&client.balance);

            puts("Enter the next account number:");
            scanf("%2d",&accountNumb);

        }
        fclose(cfPtr);
   }
 }
