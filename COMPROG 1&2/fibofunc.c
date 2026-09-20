#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;

    int t1 = 0, t2 = 1, tn;
    for (int i = 3; i <= n; i++) {
        tn = t1 + t2;
        t1 = t2;
        t2 = tn;
    }
    return tn;
}

int main() {
    int termnumber;
    printf("Enter how many numbers you want in Fibonacci sequence: ");
    scanf("%d", &termnumber);

    printf("Fibonacci Sequence:\n");
    for (int i = 1; i <= termnumber; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");

    system("pause");
    return 0;
}
