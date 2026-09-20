#include <stdio.h>

float computeCharge(char vType, int hr);

int main()
{
    char vehicleType;
    int hours;
    float charge;
    char choice;   // For Y/N input

    do
    {
        printf("Enter vehicle type (C=Car, B=Bus, T=Truck): ");
        scanf(" %c", &vehicleType); 

        printf("Enter hours spent: ");
        scanf("%d", &hours);

        charge = computeCharge(vehicleType, hours);

        printf("Your bill is %.2f\n", charge);

        printf("Do you want to continue? (Y/N): ");
        scanf(" %c", &choice);   
    }
    while (choice == 'Y' || choice == 'y');

    system("pause");
    return 0;
}

float computeCharge(char vType, int hr)
{
    float ch;  

    if (vType == 'c' || vType == 'C')
    {
        ch = 2 * hr;
    }
    else if (vType == 'b' || vType == 'B')
    {
        ch = 3 * hr;
    }
    else if (vType == 't' || vType == 'T')
    {
        ch = 4 * hr;
    }
    else
    {
        ch = 0 * hr;
    }

    return ch;
}
