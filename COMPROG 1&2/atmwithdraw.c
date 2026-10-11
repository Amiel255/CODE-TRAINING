#include <stdio.h>
#include <stdlib.h>

int main()
{
    float balance, amount;

    printf("PLEASE ENTER YOUR CURRENT BALANCE: ");
    scanf("%f", &balance);

    printf("PLEASE ENTER THE AMOUNT TO WITHDRAW: ");
    scanf("%f", &amount);

    while ((int)amount % 100 != 0)
    {
        printf("INVALID AMOUNT! WITHDRAWALS ARE ONLY IN MULTIPLES OF 100.\n");
        printf("PLEASE ENTER THE AMOUNT TO WITHDRAW: ");
        scanf("%f", &amount);
    }

    if (amount > balance)
    {
        printf("INSUFFICIENT BALANCE! PLEASE TRY AGAIN.\n");
    }
    else
    {
        balance = balance - amount;
        printf("WITHDRAWAL SUCCESSFUL!\n");
        printf("AMOUNT WITHDRAWN: %.2f\n", amount);
        printf("YOUR REMAINING BALANCE IS: %.2f\n", balance);
    }

    system("pause");
    return 0;
}