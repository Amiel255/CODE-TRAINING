#include <stdio.h>
int main()
{
    int dividend, divisor;
    double qoutient;

    do
    {
        printf("PLEASE ENTER VALUE FOR DIVIDEND: ");
        scanf("%d", &dividend);

        if (dividend != 0)
        {
            printf("PLEASE ENTER VALUE FOR DIVISOR: ");
            scanf("%d", &divisor);
        }
        if (divisor == 0)
        {
            qoutient = (double)dividend / divisor;
            printf("THE QOUTIENT IS: %lf\n", qoutient);
        }
        else
        {
            printf("DO NOT DIVIDE BY ZERO\n");
        }
    } while (dividend = !0);
    {
        printf("THANKYOU FOR USING THIS");
    }

    system("pause");
    return 0;
}