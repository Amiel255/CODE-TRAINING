#include <stdio.h>
#include <stdlib.h>

int main () {
    int n, i;
    int t1 = 0, t2 = 1, tn;

    printf("Enter the number of terms you want in the Fibonacci sequence: ");
    scanf("%d", &n);

    printf("Fibonacci Sequence:\n");

    for (i = 1; i <= n; ++i) {
        if (i == 1) {
            printf("%d", t1);
            continue;
        }
        if (i == 2) {
            printf(", %d", t2);
            continue;
        }
        tn = t1 + t2;
        t1 = t2;
        t2 = tn;
        printf(",%5d", tn);
    }
    printf("\n");

    system("pause");
    return 0;
}