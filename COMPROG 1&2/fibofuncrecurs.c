#include <stdio.h>
#include <stdlib.h>

int fibonacci (int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main () {
    int termnumber;
    printf("Enter how many numbers you want in FibonacSci sequence: ");
    scanf("%d", &termnumber);   
    
    printf("Fibonacci Sequence:\n");
    for (int i = 1; i <= termnumber; i++) {
        printf("%d ", fibonacci(i));
    }
    for (int i = fibonacci(i); i < termnumber; i++) {
        printf("%d ", fibonacci(i));
    }
    
    system("pause");
    return 0;
}