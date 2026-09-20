#include <stdio.h>
#include <stdlib.h>

int addition()
{
    int a, b, sum;
    printf("Enter two numbers to add: ");
    scanf("%d %d", &a, &b);
    sum = a + b;
    printf("Sum: %d\n\n", sum);
    return sum;
}


int subtraction()
{
    int a, b, diff;
    printf("Enter two numbers to subtract: ");
    scanf("%d %d", &a, &b);
    diff = a - b;
    printf("Difference: %d\n\n", diff);
    return diff;
}

int multiplication()
{
    int a, b, prod;
    printf("Enter two numbers to multiply: ");
    scanf("%d %d", &a, &b);
    prod = a * b;
    printf("Product: %d\n\n", prod);
    return prod;
}

int division()
{
    int a, b, modulus;
    float quot;
    printf("Enter two numbers to divide: ");
    scanf("%d %d", &a, &b);
    if (b != 0)
    {
        quot = (float)a / b;
        printf("Quotient: %.2f\n\n", quot);
        modulus = a % b;
        printf("Remainder: %d\n\n", modulus);
        return (int)quot, (int)modulus; // Return quotient as an integer
    }
    else
    {
        printf("Error: Division by zero is not allowed.\n\n");
        return 0; // Return 0 in case of error
    }
}

int main()
{
    int choice;

    do
    {
        printf("Calculator Menu:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addition();
                break;
            case 2:
                subtraction();
                break;
            case 3:
                multiplication();
                break;
            case 4:
                division();
                break;
            case 5:
                printf("Exiting the calculator. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n\n");
        }
    } while (choice != 5);

    return 0;
}
