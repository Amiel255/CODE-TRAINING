#include <stdio.h>
#include <string.h>

int main()
{

    float hours, salaryph, subincome, newincome, salarypd, salarypm;
    float taxrate1 = 1;
    float taxrate2 = 0.85;
    float taxrate3 = 0.80;
    float sss = 0.95;

    printf("PLEASE ENTER YOUR SALARY PER HOUR: ");
    scanf("%f", &salaryph);

    printf("PLEASE ENTER YOUR NUMBER OF HOURS WORKED: ");
    scanf("%f", &hours);

    salarypd = salaryph * hours;
    salarypm = salarypd * 30;

    if (salarypm > -0)
    {
        if (salarypm >= 0 && salarypm <= 20000)
        {
            subincome = salarypm * taxrate1;
            newincome = subincome * sss;
            printf("YOUR DAILY SALARY IS %.2f\n", salarypd);
            printf("YOUR MONTHLY SALARY BEFORE TAX IS %.2f\n", salarypm);
            printf("YOUR MONTHLY SALARY AFTER TAX IS %.2f\n", newincome);
        }
        else if (salarypm >= 20001 && salarypm <= 40000)
        {
            subincome = salarypm * taxrate2;
            newincome = subincome * sss;
            printf("YOUR DAILY SALARY IS %.2f\n", salarypd);
            printf("YOUR MONTHLY SALARY BEFORE TAX IS %.2f\n", salarypm);
            printf("YOUR MONTHLY SALARY AFTER TAX IS %.2f\n", newincome);
        }
        else if (salarypm >= 40001 && salarypm <= 60000)
        {
            subincome = salarypm * taxrate3;
            newincome = subincome * sss;
            printf("YOUR DAILY SALARY IS %.2f\n", salarypd);
            printf("YOUR MONTHLY SALARY BEFORE TAX IS %.2f\n", salarypm);
            printf("YOUR MONTHLY SALARY AFTER TAX IS %.2f\n", newincome);
        }
        else
        {
        }
    }else {
        printf("INVALID NUMBER PLEASE TRY AGAIN\n");
    }
        printf("PLEASE ENTER ANOTHER NUMBER\n");

        system("pause");
        return 0;
    }