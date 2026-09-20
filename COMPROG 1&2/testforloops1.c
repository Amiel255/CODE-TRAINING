#include <stdio.h>
#include <stdlib.h>
int main()
{
    int j;
    int i;
    int k = 2;
    int rows = 6;
    for (i = 1; i <= rows; i++)
    { 
        for (j = 1; j <= i * k - 1; j++)
        { 
            printf("*");
        } 
        printf("\n");
    }

    system("pause");
    return 0;
}