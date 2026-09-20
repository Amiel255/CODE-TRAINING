#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 6   // Number of lotto numbers
#define NUM 46    // Maximum number

int main() {
    int numbers[COUNT];   // Array to store lotto numbers
    srand(time(NULL));    // Seed random generator

    for (int i = 0; i < COUNT; ) {
        int n = rand() % NUM + 1; // Generate number 1..NUM
        int unique = 1;

        // Check for duplicates
        for (int j = 0; j < i; j++) {
            if (numbers[j] == n) {
                unique = 0;
                break;
            }
        }

        if (unique!=0) {
            numbers[i] = n;  // Store in array
            i++;
        }
    }

    // Print lotto numbers
    printf("Lotto Numbers: ");
    for (int i = 0; i < COUNT; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    system("pause");
    return 0;
}