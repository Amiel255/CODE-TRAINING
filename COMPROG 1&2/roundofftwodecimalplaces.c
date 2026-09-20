#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

void convertToTwoDecimalPlaces(float num);

int main()
{
    float number;

    printf("Enter a floating-point number: ");
    scanf("%f", &number);

    convertToTwoDecimalPlaces(number);

    system("pause");
    return 0;
}

void convertToTwoDecimalPlaces(float num)
{
    float roundedNum = ceil(num * 100) / 100; // Round to two decimal places
    printf("Number rounded to two decimal places: %.2f\n", roundedNum);
}
