#include <stdio.h>

int main() {
    int choice, n, i, num;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Print numbers from 1 to N\n");
        printf("2. Check if a number is positive/negative/zero\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter N: ");
            scanf("%d", &n);

            printf("Numbers from 1 to %d:\n", n);
            for (i = 1; i <= n; i++) {   // <-- using for loop
                printf("%d ", i);
            }
            printf("\n");

        } else if (choice == 2) {   // <-- using else/if
            printf("Enter a number: ");
            scanf("%d", &num);

            if (num > 0) {
                printf("%d is Positive\n", num);
            } else if (num < 0) {
                printf("%d is Negative\n", num);
            } else {
                printf("Number is Zero\n");
            }

        } else if (choice != 3) {
            printf("Invalid choice, please try again.\n");
        }

    } while (choice != 3);   // <-- using do/while

    printf("Exiting program...\n");
    return 0;
}
