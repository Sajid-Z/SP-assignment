#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[100];
    float balance;
};

void createAccount();
void viewAccount();
void deposit();
void withdraw();
void listAccounts();
void deleteAccount();

int main() {
    int choice;

    do {
        printf("\n=== Banking System Menu ===\n");
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. List All Accounts\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);

    return 0;
}

// Function Definitions 

void createAccount(){

    Account person;

    printf("Creating Account\n");
    printf("\n");

    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);
    getchar();

    printf("Enter Account Holder name: ");
    scanf("%[^\n]s", person.name);
    printf("Enter the amount you want to deposit: ");
    scanf("%f", &person.balance);

    char AC_No[100];
    sprintf(AC_No, "%d", person.accountNumber);

    char account[20] = "Account_";
    char txt[5] = ".txt";
    strcat(account, AC_No);
    strcat(account, txt);


    FILE *fptr = fopen(account, "w");

    if(fptr==NULL){
        printf("An error occured\n");
        return;
    }

    fprintf(fptr, "Account Name: %s\n", person.name);
    fprintf(fptr, "Account Number: %s\n", AC_No);
    fprintf(fptr, "Account Balance: %f\n", person.balance);

    fclose(fptr);
}

void viewAccount(){

    Account person;

    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);

    char AC_No[10];
    sprintf(AC_No, "%d", person.accountNumber);

    char account[20] = "Account_";
    char txt[5] = ".txt";
    strcat(AC_No, txt);
    strcat(account, AC_No);

    FILE *fptr = fopen(account, "r");

    if(fptr==NULL){
        printf("No account found!!");
        return;
    }

    printf("Account Found! Please Wait\n");
    printf("\n");

    char outs[50];

    while(!feof(fptr)){
        fgets(outs, sizeof(outs), fptr);
        printf("%s\n", outs);
    }
    
    fclose(fptr);
}