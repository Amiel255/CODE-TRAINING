#include <stdio.h>
int main()
{
    system("cls");
    printf("hello, my name is Amiel Keith Padilla\nand I am trying to learn how to code C+\nI am Currently 18 years of age\nand I hope I can work with you all well");
    printf("I am studying at TUP Manila, BSIT - 1C is my section\n\n");
    // create_variables
    int number = 15; // Integer (whole number)
    printf("%d\n", number);

    printf("%zu\n", sizeof(number)); // this indicates the memory size of the code

    float myFloatNum = 5.99; // Floating point number
    printf("%f\n", myFloatNum);

    printf("%zu\n", sizeof(myFloatNum)); // this indicates the memory size of the code float

    char myLetter = 'D'; // Character
    printf("%c\n", myLetter);

    float myotherfloatnumaverage = 93;
    printf("my average in grade 12 is  = %f\n", 93); // float verison

    float final_grade = 93;
    printf("my final grade is %f\n", final_grade); // float verison

    printf("My final grade for the whole s.y is %f and my initial average grade is %f", final_grade, myotherfloatnumaverage); // float verison

    int x = 10000;
    int y = 10000;
    int sum = x + y;
    printf("\n\n%d\n\n", sum);

    int date, date_today = 12;
    printf("The date today in August 2025 is:  \n\n");
    scanf("%d", &date);
    date = date + 1;
    printf("The date today is %d, and the date tomorrow is %d\n\n", date_today, date);

    float monthly; 
    float minuspercent = 0.95;
    printf("EnterMonthl payment:");
    scanf("%f", &monthly);

    float month7 = monthly * minuspercent;
    float month8 = month7 * minuspercent;
    float month9 = month8 * minuspercent;
    float month10 = month9 * minuspercent;
    float month11 = month10 * minuspercent;
    float month12 = month11 * minuspercent;
    printf("Month 6 = %f\n", monthly);
    printf("July Subscription = %f\n", month7);
    printf("August Subscription = %f\n", month8);
    printf("September Subscription = %f\n", month9);
    printf("October Subscription = %f\n", month10);
    printf("November Subscription = %f\n", month11);
    printf("December Subscription = %f\n", month12);

    system("pause");

    return 0;
}