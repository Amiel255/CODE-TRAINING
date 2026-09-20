#include <stdio.h>

int main()
{
    float annual, monthly, month, choice, monthn;
    char monthname;

    do
    {
        printf("\nThis Calculator aims to know your total refund.\nIf you don't wish to continue, type \"0\"\n");
        printf("If you want to continue with SET A, type \"1\"\n");
        printf("If you want to continue with SET B, type \"2\"\n");
        printf("Please enter the following: ");
        scanf("%f", &choice);
        if (choice == 1)
        {
            printf("\n---SET A---\n");
            printf("Enter your Annual subscription: ");
            scanf("%f", &annual);                                                    // knows what your annual is
            monthly = annual / 12;                                                   // calculates for monthly income
            printf("Your monthly payment for your subscription is %.2f\n", monthly); // dictates monthly income

            float totalpaid = 0;
            for (int i = 1; i <= 6; i++)
            {
                switch (i)
                {
                case 1:
                    printf("January");
                    break;
                case 2:
                    printf("February");
                    break;
                case 3:
                    printf("March");
                    break;
                case 4:
                    printf("April");
                    break;
                case 5:
                    printf("May");
                    break;
                case 6:
                    printf("June");
                    break;
                default:
                    break;
                }
                totalpaid += monthly;
                printf(" Subsription amout is %.2f\n", monthly);
            }

            float discounted = monthly * 0.95;
            for (int i = 7; i <= 12; i++)
            {
                switch (i)
                {
                case 7:
                    printf("July");
                    break;
                case 8:
                    printf("August");
                    break;
                case 9:
                    printf("September");
                    break;
                case 10:
                    printf("October");
                    break;
                case 11:
                    printf("November");
                    break;
                case 12:
                    printf("December");
                    break;

                default:
                    break;
                }
                printf(" Subscription amount is %.2f\n", discounted);
                totalpaid += discounted;
            }
            float refundamount = annual - totalpaid;
            printf("\nYour total refund from the subscription is: %.2f\n", refundamount);
        }
        else if (choice == 2)
        {
            printf("\n---SET B---\n");
            printf("Enter your Annual subscription: ");
            scanf("%f", &annual);                                                    // knows what your annual is
            monthly = annual / 12;                                                   // calculates for monthly income
            printf("Your monthly payment for your subscription is %.2f\n", monthly); // dictates monthly income

            float totalpaid = 0;
            for (int i = 1; i <= 6; i++)
            {
                switch (i)
                {
                case 1:
                    printf("January");
                    break;
                case 2:
                    printf("February");
                    break;
                case 3:
                    printf("March");
                    break;
                case 4:
                    printf("April");
                    break;
                case 5:
                    printf("May");
                    break;
                case 6:
                    printf("June");
                    break;
                default:
                    break;
                }
                totalpaid += monthly;
                printf(" Subsription amout is %.2f\n", monthly);
            }

            float discounted = monthly * 0.95;
            for (int i = 7; i <= 12; i++)
            {
                switch (i)
                {
                case 7:
                    printf("July");
                    break;
                case 8:
                    printf("August");
                    break;
                case 9:
                    printf("September");
                    break;
                case 10:
                    printf("October");
                    break;
                case 11:
                    printf("November");
                    break;
                case 12:
                    printf("December");
                    break;

                default:
                    break;
                }
                printf(" Subscription amount is %.2f\n", discounted);
                totalpaid += discounted;
            }
            float refundamount = annual - totalpaid;
            printf("\nYour total refund from the subscription is: %.2f\n", refundamount);
        }
        else if (choice != 0)
        {
            printf("\nPlease enter the following [0] to exit, [1] for SET A, and [2] for SET B\n\n");
        }

    } while (choice != 0);
    printf("THANK YOU FOR USING OUR SERVICES");

    system("pause");
    return 0;
}