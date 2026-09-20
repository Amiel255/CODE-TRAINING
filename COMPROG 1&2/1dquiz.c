#include <stdio.h>
#include <stdlib.h>
int main()
{

    int bal, rembal, withdAmount, multiple = 100;
    char yesorno;
    printf("Enter desired balance: ");
    scanf("%d", &bal);
    do
    {
        if (bal != bal % 50)
        {
            printf("Enter amount to withdraw: ");
            scanf("%d", &withdAmount);
            rembal = bal - withdAmount;
            if (multiple = rembal % 100)
            {
                if (multiple = 50)
                {
                    printf("THIS IS NOT A MULTIPLE OF 100");
                }
                else
                    ;
            }
            else if (rembal <= 499)

            {
                printf("Insufficient Balance\n");
            }
            else if (rembal >= 500)
            {
                printf("\nAmount withdrawn: %d\n", withdAmount);
                printf("Remaining Balance: %d", rembal);
            }
            else
                printf("Invalid Input");
        }
        else
            printf("Invalid Input");

        printf("\nDO YOU WANT TO MAKE ANOTHER TRANSACTION [y/n]: ");
        scanf(" %c", &yesorno);
    } while (yesorno == 'y' && yesorno == 'Y');

    system("pause");
    return 0;
}