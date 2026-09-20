#include <stdio.h>
#include <stdlib.h>

void addition()
{
    int a, b, sum;
    printf("Enter two numbers to add: ");
    scanf("%d %d", &a, &b);
    sum = a + b;
    printf("Sum: %d\n\n", sum);
}

void subtraction()
{
    int a, b, diff;
    printf("Enter two numbers to subtract: ");
    scanf("%d %d", &a, &b);
    diff = a - b;
    printf("Difference: %d\n\n", diff);
}

void multiplication()
{
    int a, b, prod;
    printf("Enter two numbers to multiply: ");
    scanf("%d %d", &a, &b);
    prod = a * b;
    printf("Product: %d\n\n", prod);
}

void division()
{
    int a, b;
    float quot;
    printf("Enter two numbers to divide: ");
    scanf("%d %d", &a, &b);
    if (b != 0)
    {
        quot = (float)a / b;
        printf("Quotient: %.2f\n\n", quot);
    }
    else
    {
        printf("Error: Division by zero is not allowed.\n\n");
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
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 5);
    system("pause");
    return 0;
}
