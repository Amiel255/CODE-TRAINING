#include <stdio.h>
#include <stdlib.h>
int main()
{
    int num;
    int i;
    for (num = 9; num >= 1; num--)
    { // count down from 9 to 1 then list down from 9 to 1
        for (i = 1; i <= num; i++)
        {    // then it prints out in the outer loop from 1-9 decrementing starting from top to bottom
            printf("%d ", i); // prints i
        } // space for readability
        printf("\n");
    }

    system("pause");
    return 0;
}