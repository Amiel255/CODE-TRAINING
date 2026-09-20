#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n, i, primecheck = 1;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    for (i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            primecheck = 0;
            break;
        } 
    }

    if (primecheck == 1) {
        printf("Prime Number");
    }
    else printf("Not a Prime Number");

    system("pause");
    return 0;
}
