#include <stdio.h>
#include <stdlib.h>
int main()
{
    int num, total = 0, countn = 0, countp = 0;
    printf("Enter number (Ctrl+Z to stop):\n");
    scanf ("%d", &num);
    while (num != EOF)
    {
        total = total + num;
        printf("Total: %d\n", total);
        if (num < 0)
            countn++;
        else
            countp++;
        scanf ("%d", &num);
    }
    printf("Negative numbers: %d\n", countn);
    printf("Positive numbers: %d\n", countp);
    system("pause");
    return 0;
}