#include <stdio.h>

#define MONTHS 12

// Function to process each set
void processSet(char setName) {
    printf("SET %c\n", setName);

    float annual, monthlyPayment, monthlyPayments[MONTHS], refund = 0.0;
    const float discount = 0.95;

    // Input annual and monthly payment
    printf("Enter Amount for Annual Subscription: ");
    scanf("%f", &annual);
    printf("Enter Monthly Payment: ");
    scanf("%f", &monthlyPayment);

    float amountPerMonth = annual / MONTHS;
    printf("Amount per month to pay: %.2f\n", amountPerMonth);

    // Calculate monthly payments (discounted from July to December)
    for (int i = 0; i < MONTHS; i++) {
        if (i >= 6)  // July to December (months 6 to 11)
            monthlyPayments[i] = monthlyPayment * discount;
        else
            monthlyPayments[i] = monthlyPayment;
    }

    // Print monthly payments
    const char *monthNames[MONTHS] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("\nMONTHLY PAYMENTS:\n");
    for (int i = 0; i < MONTHS; i++) {
        printf("%s Subscription = %.2f\n", monthNames[i], monthlyPayments[i]);
    }

    // Print extra balance to be returned
    printf("\nEXTRA BALANCE TO BE RETURNED PER MONTH:\n");
    for (int i = 0; i < MONTHS; i++) {
        float extra = monthlyPayment - monthlyPayments[i];
        printf("%s = %.2f\n", monthNames[i], extra);
        if (i >= 5)  // From June onwards (i=5 is June)
            refund += extra;
    }

    // Print total refund
    printf("\nAmount of Internet Subscription Refund = %.2f\n\n", refund);
}

int main() {
    processSet('A');
    processSet('B');

    return 0;
}
