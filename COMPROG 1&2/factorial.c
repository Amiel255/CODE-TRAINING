#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int n, i;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("Error! Enter a positive integer.");
    }
    else
    {
        long long unsigned int factorial = 1;
        for (i = 1; i <= n; ++i)
        {
            factorial *= i; // factorial = factorial*i;
        }
        printf("Factorial of %d = %llu", n, factorial);
    }

    system("pause");
    return 0;
}