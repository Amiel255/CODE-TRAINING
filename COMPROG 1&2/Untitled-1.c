#include <stdio.h>

int main() {

    float number1;
    printf("Number=  ");
    scanf("%f", & number1);

    float number2;
    printf("Plus Number= ");
    scanf("%f", & number2);

    float sum = (float) number1 + number2;
    printf("Numerator divided by Denominator is= %f\n\n", sum);

    system("pause");
  return 0;
}