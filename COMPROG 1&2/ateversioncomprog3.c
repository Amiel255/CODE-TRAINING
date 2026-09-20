#include <stdio.h>

int main() {
    float annual, monthly;
    float refund = 0.0;

    // ---------- SET A ----------
    printf("SET A\n");
    printf("Enter Amount for Annual Subscription: ");
    scanf("%f", &annual);

    monthly = annual / 12; // monthly payment
    printf("Amount per month to pay: %.2f\n", monthly);

    float totalNew = 0.0;

    // First 6 months (no discount)
    for (int i = 1; i <= 6; i++) {
        totalNew += monthly;
    }

    // Next 6 months (flat 5% discount each month)
    float reduced = monthly * 0.95;
    for (int i = 7; i <= 12; i++) {
        printf("Month %d Subscription = %.2f\n", i, reduced);
        totalNew += reduced;
    }

    refund = annual - totalNew;
    printf("Amount of Internet Subscription Refund = %.2f\n\n", refund);

    // ---------- SET B ----------
    printf("SET B\n");
    printf("Enter Amount for Annual Subscription: ");
    scanf("%f", &annual);

    monthly = annual / 12; 
    printf("Amount per month to pay: %.2f\n", monthly);

    totalNew = 0.0;

    // First 6 months
    for (int i = 1; i <= 6; i++) {
        totalNew += monthly;
    }

    // Next 6 months (flat 5% discount)
    reduced = monthly * 0.95;
    for (int i = 7; i <= 12; i++) {
        printf("Month %d Subscription = %.2f\n", i, reduced);
        totalNew += reduced;
    } 


    refund = annual - totalNew;
    printf("Amount of Internet Subscription Refund = %.2f\n", refund);

    system("pause");
    return 0;
}