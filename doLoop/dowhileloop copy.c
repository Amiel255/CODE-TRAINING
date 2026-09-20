#include <stdio.h>
#include <stdlib.h>

int main()
{

    int num, sum;
    float ave, num2;
    num2 = 0;
    sum = 0;
    printf("PLEASE ENTER A NUMBER: ");
    scanf("%d", &num);

    while (num < 0)
        
    {
        sum = sum + num;
        num2++;
        printf("ENTER ANOTHER NUMBER: ");
        scanf("%d", &num);
    } 
    ave = sum / num2;
    printf("THE AVERAGE IS %f", ave);
    system("pause");
    return 0;
}