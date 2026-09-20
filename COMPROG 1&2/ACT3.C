#include <stdio.h>
int main()
{
    float monthly;
    float minuspercent = 0.95;
    printf("EnterMonthl payment:");
    scanf("%f", &monthly);

    float month7 = monthly * minuspercent;
    float month8 = month7 * minuspercent;
    float month9 = month8 * minuspercent;
    float month10 = month9 * minuspercent;
    float month11 = month10 * minuspercent;
    float month12 = month11 * minuspercent;
    printf("Month 6 = %f\n", monthly);
    printf("July Subscription = %f\n", month7);
    printf("August Subscription = %f\n", month8);
    printf("September Subscription = %f\n", month9);
    printf("October Subscription = %f\n", month10);
    printf("November Subscription = %f\n", month11);
    printf("December Subscription = %f\n", month12);
    system("pause");

    return 0;
}