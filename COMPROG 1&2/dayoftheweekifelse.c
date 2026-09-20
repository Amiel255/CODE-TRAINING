#include <stdio.h>
#include <string.h>

int main()
{

    char day[58];
    int dow;

    do
    {
        printf("LEGEND:0-STOP, 1-SUNDAY, 2-MONDAY, 3-TUESDAY, 4-WEDNESDAY, 5-THURSDAY, 6-FRIDAY, 7-SATURDAY\n");
        printf("PLEASE ENTER NUMBER [1-7] TO DETERMINE THE DAY OF THE WEEK: ");
        scanf("%d", &dow);

        if (dow >= 1 && dow <= 7)
        {
            if (dow == 1)
            {
                strcpy(day, "SUNDAY");
            }
            else if (dow == 2)
            {
                strcpy(day, "MONDAY");
            }
            else if (dow == 3)
            {
                strcpy(day, "TUESDAY");
            }
            else if (dow == 4)
            {
                strcpy(day, "WEDNESDAY");
            }
            else if (dow == 5)
            {
                strcpy(day, "THURSDAY");
            }
            else if (dow == 6)
            {
                strcpy(day, "FRIDAY");
            }
            else if (dow == 7)
            {
                strcpy(day, "SATURDAY");
            }
            else if (strcpy(day, "INVALID INPUT! PLEASE ENTER A NUMBER BETWEEN 1 AND 7.\n\n"))
                ;
            {
            }
            printf("THE DAY OF THE WEEK IS: %s\n\n", day);
        }
        else
        {
            printf("PLEASE TRY AGAIN\n");
        }
    } while (dow != 0);
    {
        printf("thankyou for using this");
    }

    system("pause");
    return 0;
}