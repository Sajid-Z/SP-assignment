#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

struct Account {
    int accountNumber;
    char name[100];
    float balance;
    char email[50];
    char phone_number[11];
};

Account person;

vector<int> AC_NOs;

void createAccount();
void viewAccount();
void deposit();
void withdraw();
void listAccounts();
void deleteAccount();
void take_Existing_Accounts_From_File(vector<int> &AC_NOs);

//Admin user, that can check the list of accounts
char admin[10] = "Admin";
char pass[90] = "pass";

int main() {
    
    take_Existing_Accounts_From_File(AC_NOs);
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
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: listAccounts(); break;
            case 6: deleteAccount(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);

    return 0;
}

// Function Definitions 

void take_Existing_Accounts_From_File(vector<int>&AC_NOs){

    AC_NOs.clear();
    FILE *fptr = fopen("Accounts_info.txt", "r");

    if(!fptr){
        printf("An error occured to open the file!!");
        return;
    }

    int number;
    char characters[50];
    while(!feof(fptr)){
        if(fscanf(fptr, "%d", &number)){
            AC_NOs.push_back(number);
        }
        fgets(characters, sizeof(characters), fptr);
    }

    fclose(fptr);
}


void createAccount(){

    FILE *store = fopen("Accounts_info.txt", "a");

    printf("Creating Account\n");
    printf("\n");

    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);
    getchar();

    char AC_No[90];
    sprintf(AC_No, "%d", person.accountNumber);

    for(int i = 0; i<AC_NOs.size(); i++){
        if(person.accountNumber==AC_NOs[i]){
            printf("Sorry! This Account Number already exists!!");
            return;
        }
    }

    if(person.accountNumber>1000000000){
        printf("Account Number must be no more than 9 digits\n");
        return;
    }

    AC_NOs.push_back(person.accountNumber);

    printf("Enter Account Holder name: ");
    scanf("%[^\n]s", person.name);
    printf("Enter the amount you want to deposit: ");
    scanf("%f", &person.balance);
    printf("Enter your email address: ");
    scanf("%s", person.email);
    printf("Enter your phone number: ");
    scanf("%s", person.phone_number);

    char account[20] = "Account_";
    char balance[40] = "Account_Balance";
    char txt[5] = ".txt";
    char bintxt[5] = ".bin";

    strcat(account, AC_No);
    strcat(account, txt);

    strcat(balance, AC_No);
    strcat(balance, bintxt);

    FILE *fptr = fopen(account, "w");
    FILE *bptr = fopen(balance, "wb");

    fprintf(fptr, "Account Name: %s\n", person.name);
    fprintf(fptr, "Account Number: %s\n", AC_No);
    fprintf(fptr, "Email id: %s\n", person.email);
    fprintf(fptr, "Phone Number: %s\n", person.phone_number);
    fprintf(store, "%s ", AC_No);
    fprintf(store, "-- %s   \n", person.name);
    fwrite(&person.balance, sizeof(float), 1, bptr);

    fclose(fptr);
    fclose(bptr);
    fclose(store);
}

void viewAccount(){

    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);

    char AC_No[10];
    sprintf(AC_No, "%d", person.accountNumber);

    char account[20] = "Account_";
    char balance[40] = "Account_Balance";

    char txt[5] = ".txt";
    char bintxt[5] = ".bin";
    
    strcat(balance, AC_No);
    strcat(balance, bintxt);
    
    strcat(AC_No, txt);
    strcat(account, AC_No);

    FILE *fptr = fopen(account, "r");
    FILE *bptr = fopen(balance, "rb");

    if(fptr==NULL){
        printf("No account found!!\n");
        return;
    }

    printf("Account Found! Please Wait\n");
    printf("\n");

    char outs[50];

    while(fgets(outs, sizeof(outs), fptr) != NULL){
        printf("%s\n", outs);
    }

    if(bptr==NULL){
        printf("No deposits! Returning\n");
        return;
    }

    printf("\n");
    printf("Checking balance. \n");
    
    float balance_value;
    fread(&balance_value, sizeof(float), 1, bptr);
    printf("Account Balance: %.2f\n", balance_value);
    
    fclose(fptr);
    fclose(bptr);
}

void deposit(){

    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);

    char AC_No[10];
    sprintf(AC_No, "%d", person.accountNumber);

    char txt[5] = ".txt";
    char bintxt[5] = ".bin";

    char balance[40] = "Account_Balance";

    strcat(balance, AC_No);
    strcat(balance, bintxt);

    strcat(AC_No, txt);

    FILE *bptr = fopen(balance, "rb");

    if(bptr==NULL){
        printf("You Have no account!! Create Account First");
        return;
    }
    float Current_money = 0, Deposit_money = 0;
    fread(&Current_money, sizeof(float), 1, bptr);
    //fscanf(bptr, "Account Balance: %f\n", &Current_money);

    printf("Account Balance: %f\n", Current_money);
    fclose(bptr);

    char outs[50];
   
    printf("How Much you want To Deposit?: ");
    scanf("%f", &Deposit_money);

    Current_money+=Deposit_money;

    FILE *fptr = fopen(balance, "wb");

    fwrite(&Current_money, sizeof(float), 1, bptr);
    //fprintf(fptr, "Account Balance: %f\n", Current_money);
    fclose(fptr);

    bptr = fopen(balance, "rb");

    float display_money;
    fread(&display_money, sizeof(float), 1, bptr);
    printf("Account Balance: %f\n", display_money);

    /*while(fgets(outs, sizeof(outs), bptr)!=NULL){
        printf("%s\n", outs);
    }*/

    fclose(bptr);
}

void withdraw(){
    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);

    char AC_No[10];
    sprintf(AC_No, "%d", person.accountNumber);

    char balance[40] = "Account_Balance";
    strcat(balance, AC_No);

    char txt[5] = ".txt";
    char bintxt[5] = ".bin";

    strcat(balance, bintxt);
    strcat(AC_No, txt);

    FILE *bptr = fopen(balance, "rb");

    if(bptr==NULL){
        printf("You Have no account!! Create Account First");
        return;
    }
    float Current_money = 0, Deposit_money = 0;
    fread(&Current_money, sizeof(float), 1, bptr);

    //fscanf(bptr, "Account Balance: %f\n", &Current_money);

    printf("Account Balance: %f\n", Current_money);
    fclose(bptr);

    char outs[50];
   
    printf("How Much you want To Withdraw?: ");
    scanf("%f", &Deposit_money);

    if(Deposit_money>Current_money){
        printf("Insufficient balance\n");
        return;
    }

    Current_money-=Deposit_money;

    FILE *fptr = fopen(balance, "wb");

    fwrite(&Current_money, sizeof(float), 1, fptr);
    //fprintf(fptr, "Account Balance: %f\n", Current_money);
    fclose(fptr);

    bptr = fopen(balance, "rb");

    /*while(fgets(outs, sizeof(outs), bptr)!=NULL){
        printf("%s\n", outs);
    }*/

    float display_money;
    fread(&display_money, sizeof(float), 1, bptr);
    printf("Account Balance: %f", display_money);
    fclose(bptr);
}

void listAccounts(){
    
    char your_user[10], your_pass[90];
    printf("Enter your user: ");
    scanf("%s", your_user);

    if(strlen(your_user)!=strlen(admin)){
        printf("This Username does not exist\n");
        return;
    }
    else{
        for(int i = 0; i<strlen(admin); i++){
            if(your_user[i]!=admin[i]){
                printf("This Username does not exist\n");
                return;
            }
        }
    }

    printf("Enter your password: ");
    scanf("%s", your_pass);
    getchar();
    
    if(strlen(your_pass)!=strlen(pass)){
        printf("Wrong Password!! Try again\n");
        return;
    }
    else{
        for(int i = 0; i<strlen(pass); i++){
            if(your_pass[i]!=pass[i]){
                printf("Wrong Password!! Try again\n");
                return;
            }
        }
    }

    FILE *list = fopen("Accounts_info.txt", "r");
    if(list==NULL){
        printf("An Error Occured\n");
        return;
    }

    char outs[50];
    while(fgets(outs, sizeof(outs), list)!=NULL){
        printf("%s\n", outs);
    }
    fclose(list);
}

void deleteAccount(){

    printf("Enter Account Number: ");
    scanf("%d", &person.accountNumber);

    bool Is_Account_Number_Found = false;
    for(int i = 0; i<AC_NOs.size(); i++){
        if(person.accountNumber==AC_NOs[i]){
            Is_Account_Number_Found = true;
            break;
        }
    }

    if(!Is_Account_Number_Found){
        printf("Account Number Not Found!!\n");
        return;
    }

    char ch;
    printf("Are you sure, you want to delete this account?: y(yes) n(no) : ");
    scanf(" %c", &ch);

    if(ch=='y' || ch=='Y'){
        int number_to_delete;

        char AC_No[10];
        sprintf(AC_No, "%d", person.accountNumber);

        char account[20] = "Account_";
        char balance[40] = "Account_Balance";

        char txt[5] = ".txt";
        char bintxt[5] = ".bin";

        strcat(balance, AC_No);
        strcat(balance, bintxt);
        strcat(AC_No, txt);
        strcat(account, AC_No);

        remove(account);
        remove(balance);

        printf("Account deleted Succesfully\n");

        FILE *finding = fopen("Accounts_info.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        char buffer[50];

        if(finding==NULL){
            printf("There is an error!! Try again\n");
            return;
        }

        if(temp==NULL){
            fclose(finding);
            printf("Unable to open Temp file\n");
            return;
        }

        while(fgets(buffer, sizeof(buffer), finding)!=NULL){
            char *ptr = buffer;

            if(*ptr==' ') ptr++;
            int matched = sscanf(ptr, "%d", &number_to_delete);

            if(matched==1 && number_to_delete==person.accountNumber){
                continue;
            }

            fputs(buffer, temp);
        }

        auto it = find(AC_NOs.begin(), AC_NOs.end(), person.accountNumber);
        if(it!=AC_NOs.end()){
            AC_NOs.erase(it);
        }

        fclose(finding);
        fclose(temp);

        remove("Accounts_info.txt");
        rename("temp.txt", "Accounts_info.txt");
    }
    else if(ch=='n'||ch=='N'){
        return;
    }
    else{
        printf("Invalid input!! Try again.\n");
        return;
    }
    
}
