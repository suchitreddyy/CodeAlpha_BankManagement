#include <stdio.h>
#include <stdlib.h>

struct BankAccount
{
    int accountNumber;
    char name[50];
    float balance;
};
void createAccount();
void deposit();
void withdraw();
void checkBalance();

int main()
{
    int ch;

do
    {
        printf("\n---- BANK MANAGEMENT SYSTEM ----\nEnter your choice: \n1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Balance Enquiry\n5. Exit\n");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1: createAccount();
                break;
            case 2: deposit();
                break;
            case 3: withdraw();
                break;
            case 4: checkBalance();
                break;

            case 5:
                printf("Thank you for using the banking system!\n");
                break;
        }
    }while(ch!=5);

    return 0;
}
void createAccount()
{
    struct BankAccount acc;

    FILE *fp = fopen("bank.dat", "ab");

    if (fp == NULL)
    {
        printf("File could not be opened!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNumber);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);

    printf("Account created successfully!\n");

    fclose(fp);
}
void deposit()
{
    int accNo, found = 0;
    float amount;

    struct BankAccount acc;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accountNumber == accNo)
        {
            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("Amount deposited successfully!\n");
            printf("Updated Balance: %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account not found!\n");
    }

    fclose(fp);
}
void withdraw()
{
    int accNo, found = 0;
    float amount;

    struct BankAccount acc;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accountNumber == accNo)
        {
            if (amount > acc.balance)
            {
                printf("Insufficient Balance!\n");
            }
            else
            {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("Withdrawal successful!\n");
                printf("Remaining Balance: %.2f\n", acc.balance);
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account not found!\n");
    }

    fclose(fp);
}
void checkBalance()
{
    int accNo, found = 0;

    struct BankAccount acc;

    FILE *fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accountNumber == accNo)
        {
            printf("\n ACCOUNT DETAILS \n");
            printf("Account Number : %d\n", acc.accountNumber);
            printf("Account Holder : %s\n", acc.name);
            printf("Balance         : %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Account not found!\n");
    }

    fclose(fp);
}