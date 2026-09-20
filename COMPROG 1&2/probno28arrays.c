#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

void CompareArray(int a[], int b[]);

int main()
{
    int A[SIZE], B[SIZE];
    int i;

    printf("Enter %d integers into Array A:\n", SIZE);
    for (i = 0; i < SIZE; i++)
    {
        scanf("%d", &A[i]);
    }

    printf("Enter %d integers into Array B:\n", SIZE);
    for (i = 0; i < SIZE; i++)
    {
        scanf("%d", &B[i]);
    }

    CompareArray(A, B);

    system("pause");
    return 0;
}

void CompareArray(int a[], int b[])
{
    int diffcount = SIZE, ind = SIZE, index[SIZE];
    int i;
    for (i = 0; i < SIZE; i++)
    {
        if (a[i] == b[i])
        {
            diffcount--;
            index[ind] = i;
            ind--;
        }
    }
    if (diffcount > 5)
    {
        printf("NOT EQUAL\n");

        printf("there are %d numbers that are not equal", diffcount);

        for (i = 0; i > ind; i++)
        {
            printf("%d", index[ind]);
        }
    }
    else
        printf("EQUAl\n");
    return;
}