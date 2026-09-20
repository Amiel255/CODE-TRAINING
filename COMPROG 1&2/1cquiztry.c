#include <stdio.h>
#include <stdlib.h>

int main()
{
    int kilowatts1, kilowatts2, kilowatts3, price, total;
    int oneh = 5, twoh = 7, threeh = 10;
    char name[30], agree;
    printf("Enter your name: ");
    scanf(" %s", &name);

    do
    {
        printf("Enter kilowatts used: ");
        scanf("%d", &kilowatts1);

        if (kilowatts1 < 0)
        {
            printf("Invalid input, please try again.\n");
        }
        else if (kilowatts1 <= 100)
        {
            total = kilowatts1 * oneh;
            printf("Hello %s, your total bill is %d at the rate of %d per kilowatt.\n", name, total, oneh);
        }
        else if (kilowatts1 <= 300)
        {
            kilowatts2 = kilowatts1 - 100;
            kilowatts1 = 100;
            total = (kilowatts1 * oneh) + (kilowatts2 * twoh);
            printf("Hello %s, your total bill is %d at the rate of %d per kilowatt for the first 100 kilowatts and %d per kilowatt for the next %d kilowatts.\n", name, total, oneh, twoh, kilowatts2);
        }
        else if (kilowatts1 >= 301)
        {
            kilowatts3 = kilowatts1 - 300;
            kilowatts2 = 200;
            kilowatts1 = 100;
            total = (kilowatts1 * oneh) + (kilowatts2 * twoh) + (kilowatts3 * threeh);
            printf("Hello %s, your total bill is %d at the rate of %d per kilowatt for the first 100 kilowatts, %d per kilowatt for the next 200 kilowatts, and %d per kilowatt for kilowatts 300 and above\n", name, total, oneh, twoh, threeh);
        }
        printf("Do you want to continue [y/n]: ");
        scanf(" %c", &agree);

    } while (agree == 'y' || agree == 'Y');

    system("pause");
    return 0;
}