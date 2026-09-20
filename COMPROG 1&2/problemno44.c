#include <stdio.h>
#include <stdlib.h>

void measurements(int *length, int *width, float *discountpc, float *cost);

int main()
{
    int length, width;
    float discount, cost;
    printf("THIS IS A CHARGE CALCULATOR FOR CARPET MEASUREMENTS\n");
    printf("Enter Length of desired carpet:\n");
    scanf("%d", &length);
    printf("Enter Width of desired carpet:\n");
    scanf("%d", &width);
    printf("Enter value of Customer Discount:\n");
    scanf("%f", &discount);
    printf("Enter the Cost of Carpet per square foot:\n");
    scanf("%f", &cost);

    measurements(&length, &width, &discount, &cost);
    system("pause");
    return 0;
}

void measurements(int *length, int *width, float *discountpc, float *cost)
{
    int area = *length * *width;

    printf("\t\tMEASUREMENTS\t\t\n");
    printf("Length\t\t\t\t%d ft\n", *length);
    printf("Width\t\t\t\t%d ft\n", *width);
    printf("Area\t\t\t\t%d square ft\n\n", area);
    float costpsqf = area * *cost ;
    float tax = 8.5/100;
    float laborcost = area * 0.35;
    float installedprice = laborcost + costpsqf;
    float costaftercustomerdiscount =  (*discountpc/100) * installedprice;
    float subtotal = installedprice - costaftercustomerdiscount;
    float chargeaftertax = subtotal * tax;
    float total = chargeaftertax + subtotal;
    printf("\t\tCHARGES\t\t\t\t\t\n");
    printf("DESCRIPTION\tCOST/SQ.FT.\tCHARGE\n");
    printf("-----------\t-----------\t-----------\n");
    printf("CARPET\t\t%f\t$%f\n", *cost, costpsqf);
    printf("LABOR\t\t0.35\t\t%f\n", laborcost);
    printf("-------------------------------------------\n");
    printf("INSTALLED PRICE\t\t\t$%f\n", installedprice);
    printf("DISCOUNT\t\t\t%f\n", costaftercustomerdiscount);
    printf("-------------------------------------------\n");
    printf("SUBTOTAL\t\t\t%f\n", subtotal);
    printf("TAX\t\t%f\t$%f\n", tax, chargeaftertax);
    printf("TOTAL\t\t\t\t$%f\n", total);
}
