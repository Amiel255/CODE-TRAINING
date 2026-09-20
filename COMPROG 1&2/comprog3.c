#include <stdio.h>
int main()
{
    printf("SET A\n");
    float annual;
    printf("Enter Amount for Annual Subscription: ");
    scanf("%f", & annual);
    float monthlypaymenttbp = annual / 12;
    printf("Amount per month to pay: %.2f\n", monthlypaymenttbp);
    float monthly;
    float minuspercent = 0.95;
    printf("Enter Monthly payment:");
    scanf("%f", &monthly);

    float month7 = monthly * minuspercent;
    float month8 = monthly * minuspercent;
    float month9 = monthly * minuspercent;
    float month10 = monthly * minuspercent;
    float month11 = monthly * minuspercent;
    float month12 = monthly * minuspercent;
    printf("Month 6 = %.2f\n", monthly);
    printf("July Subscription = %.2f\n", month7);
    printf("August Subscription = %.2f\n", month8);
    printf("September Subscription = %.2f\n", month9);
    printf("October Subscription = %.2f\n", month10);
    printf("November Subscription = %.2f\n", month11);
    printf("December Subscription = %.2f\n", month12);

    printf("Amount Paid = %.2f\n", annual);
    float monthlydue = monthly;
    printf("Amount to be paid per month: %.2f\n\n", monthlydue);

    float month1 = monthly;
    float month2 = monthly;
    float month3 = monthly;
    float month4 = monthly;
    float month5 = monthly;
    float month6 = monthly;
    float due1 = monthlydue - month1;
    float due2 = monthlydue - month2;
    float due3 = monthlydue - month3;
    float due4 = monthlydue - month4;
    float due5 = monthlydue - month5;
    float due6 = monthlydue - month6;
    float due7 = monthlydue - month7;
    float due8 = monthlydue - month8;
    float due9 = monthlydue - month9;
    float due10 = monthlydue - month10;
    float due11 = monthlydue - month11;
    float due12 = monthlydue - month12;

    printf("EXTRA BALANCED TO BE RETURNED\n");
    printf("January = %.2f\n", due1);
    printf("February = %.2f\n", due2);
    printf("March = %.2f\n", due3);
    printf("April = %.2f\n", due4);
    printf("May = %.2f\n", due5);
    printf("June = %.2f\n", due6);
    printf("July = %.2f\n", due7);
    printf("August = %.2f\n", due8);
    printf("September = %.2f\n", due9);
    printf("October = %.2f\n", due10);
    printf("November = %.2f\n", due11);
    printf("December = %.2f\n", due12);

    double refund = due6 + due7 + due8 + due9 + due10 + due11 + due12;
    printf("Amount of Internet Subscription Refund = %.2lf\n\n", refund);
    
    printf("SET B\n");
    float annuala;
    printf("Enter Amount for Annual Subscription: ");
    scanf("%f", & annuala);
    float monthlypaymenttbpa = annuala / 12;
    printf("Amount per month to pay: %.2f\n", monthlypaymenttbpa);
    float monthlya;
    printf("Enter Monthly payment:");
    scanf("%f", &monthlya);
    float minuspercenta = 0.95;

    float month7a = monthlya * minuspercenta;
    float month8a = monthlya * minuspercenta;
    float month9a = monthlya * minuspercenta;
    float month10a = monthlya * minuspercenta;
    float month11a = monthlya * minuspercenta;
    float month12a = monthlya * minuspercenta;
    printf("Month 6 = %.2f\n", monthlya);
    printf("July Subscription = %.2f\n", month7a);
    printf("August Subscription = %.2f\n", month8a);
    printf("September Subscription = %.2f\n", month9a);
    printf("October Subscription = %.2f\n", month10a);
    printf("November Subscription = %.2f\n", month11a);
    printf("December Subscription = %.2f\n", month12a);

    printf("Amount Paid = %.2f\n", annuala);
    float monthlyduea = monthlya;
    printf("Amount to be paid per month: %.2f\n\n", monthlyduea);

    float month1a = monthlya;
    float month2a = monthlya;
    float month3a = monthlya;
    float month4a = monthlya;
    float month5a = monthlya;
    float month6a = monthlya;
    float due11a = monthlyduea - month11a;
    float due2a = monthlyduea - month2a;
    float due3a = monthlyduea - month3a;
    float due4a = monthlyduea - month4a;
    float due5a = monthlyduea - month5a;
    float due6a = monthlyduea - month6a;
    float due7a = monthlyduea - month7a;
    float due8a = monthlyduea - month8a;
    float due9a = monthlyduea - month9a;
    float due10a = monthlyduea - month10a;
    float due11a = monthlyduea - month11a;
    float due12a = monthlyduea - month12a;

    printf("EXTRA BALANCED TO BE RETURNED\n");
    printf("January = %.2f\n", due11a);
    printf("February = %.2f\n", due2a);
    printf("March = %.2f\n", due3a);
    printf("April = %.2f\n", due4a);
    printf("May = %.2f\n", due5a);
    printf("June = %.2f\n", due6a);
    printf("July = %.2f\n", due7a);
    printf("August = %.2f\n", due8a);
    printf("September = %.2f\n", due9a);
    printf("October = %.2f\n", due10a);
    printf("November = %.2f\n", due11a);
    printf("December = %.2f\n", due12a);

    double refunda = due6a + due7a + due8a + due9a + due10a + due11a + due12a;
    printf("Amount of Internet Subscription Refund = %.2lf\n", refunda);
    system("pause");

    return 0;
}