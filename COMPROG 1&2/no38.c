#include <stdio.h>
int main()
{
    int num;
    int digit[5];
    printf("Please enter numbers between [0-32767]: ");
    scanf("%d", &num);

    digit[0] = num / 10000 % 10;
    digit[1] = num / 1000 % 10;
    digit[2] = num / 100 % 10;
    digit[3] = num / 10 % 10;
    digit[4] = num % 10;

    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            printf("%d", digit[j]);
            if (j < 4) { 
                printf("   ");
            }
        }
        printf("\n");
    }

    return 1;
} 