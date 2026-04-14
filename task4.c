#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

// Function Prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();

int main() {
    int choice;

    while (1) {
        printf("\n--- WELCOME TO MINI BANK ---");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Balance Enquiry");
        printf("\n5. Exit");
        printf("\nSelect Option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: exit(0);
            default: printf("\nInvalid Choice!");
        }
    }
    return 0;
}

void createAccount() {
    FILE *fp = fopen("bank.dat", "ab");
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("\nAccount created successfully!");
}

void depositMoney() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account acc;
    int accNum, found = 0;
    float amount;

    if (fp == NULL) return;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNo == accNum) {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);
            acc.balance += amount;

            // Move file pointer back to update the specific record
            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            
            printf("\nSuccessfully Deposited. New Balance: %.2f", acc.balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nAccount not found.");
    fclose(fp);
}

void withdrawMoney() {
    FILE *fp = fopen("bank.dat", "rb+");
    struct Account acc;
    int accNum, found = 0;
    float amount;

    if (fp == NULL) return;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNo == accNum) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount <= acc.balance) {
                acc.balance -= amount;
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("\nWithdrawal Successful. New Balance: %.2f", acc.balance);
            } else {
                printf("\nInsufficient Funds!");
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("\nAccount not found.");
    fclose(fp);
}

void checkBalance() {
    FILE *fp = fopen("bank.dat", "rb");
    struct Account acc;
    int accNum, found = 0;

    if (fp == NULL) return;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNo == accNum) {
            printf("\nAccount Holder: %s", acc.name);
            printf("\nCurrent Balance: %.2f", acc.balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nAccount not found.");
    fclose(fp);
}