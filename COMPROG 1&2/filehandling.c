//CSV Format (Comma Separated Values)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5
// Global variables
char name[MAX][50];
float q1[MAX], q2[MAX], q3[MAX], avg[MAX];
int last= -1;

void addrec(char n[], float a, float b, float c);
void deleterec(char n[]);
void display();
int nfull();
int nempty();
int locate(char n[]);
void updaterec(char n[50]);
void savef();
void retrieve();

int main(){

    int choice;
    float a, b, c;
    char name[50];

    do
    {
        printf("\n___MENU___\n");
        printf("1. Add Record\n");
        printf("2. Delete Record\n");
        printf("3. Display Record\n");
        printf("4. Update Record\n");
        printf("5. Save to file\n");
        printf("6. Retrieve file\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            system("cls");
            printf("Input name: ");
            getchar();
            scanf(" %[^\n]", name);

            printf("Input Quiz 1: ");
            scanf("%f", &a);
            printf("Input Quiz 2: ");
            scanf("%f", &b);
            printf("Input Quiz 3: ");
            scanf("%f", &c);

            addrec(name, a, b, c);
        break;

        case 2:
            system("cls");
            printf("Input name: ");
            getchar();
            scanf(" %[^\n]", name);
            deleterec(name);
        break;

        case 3:
            system("cls");
            display();
        break;

        case 4:
            system("cls");
            printf("Input name: ");
            getchar();
            scanf(" %[^\n]", name);
            updaterec(name);
        break;

        case 5:
            system("cls");
            savef();
            printf("Records saved successfully.\n");
            system("pause");
        break;

        case 6:
            system("cls");
            retrieve();
            printf("Records retrieved.\n");
            system("pause");
        break;

        case 7:
            system("cls");
            printf("Exiting program...\n");
            system("pause");
            exit(0);
        break;

        default:
            system("cls");
            printf("Invalid input!");
            system("pause");
        }
    }
    while (choice != 7);

return 0;
}
int nfull()
{
    return(last==MAX-1);
}
int nempty()
{
    return(last== -1);

}
int locate(char n[])
{
    int i;

    for(i=0; i<=last; i++)
    {
        if(strcmp(name[i],n)==0)
        return i;
    }
    return -1;
}
void addrec(char n[], float a, float b, float c)
{
    int p;
    if(nfull())
    {
        printf("FULL");
        system("pause");
    }
    else
    {
        p = locate(n);
        if(p != -1)
        {
            printf("Record is already added!\n");
            return;
        }
        else
        {
            last++;
            strcpy(name[last],n);
            q1[last] = a;
            q2[last] = b;
            q3[last] = c;
            avg[last] = (a+b+c)/3.0;

            printf("%s added!\n", n);
        }
    }
    system("pause");
}
void deleterec(char n[])
{
    int i, p;

    if(nempty())
    {
        printf("No record to delete!\n");
        system("pause");
    }
    else
    {
        p = locate(n);
        if (p == -1)
        {
            printf("No record found.\n");
            system("pause");
        }
        else
        {
            for(i=p; i<last; i++)
            {
                strcpy(name[i], name[i+1]);
                q1[i] = q1[i+1];
                q2[i] = q2[i+1];
                q3[i] = q3[i+1];
            }
            last--;
            printf("%s removed!\n", n);
            system("pause");
        }
    }
}
void display()
{
    int i;

    system("cls");
    printf("%4s %-20s %-8s %-8s %-8s %-10s %-10s\n", "No.", "NAME", "QUIZ 1", "QUIZ 2", "QUIZ 3", "AVERAGE", "REMARKS");
    for(i=0; i<=last; i++)
    {
        printf("%4d %-20s %-8.2f %-8.2f %-8.2f %-10.2f %-10s\n", i+1, name[i], q1[i], q2[i], q3[i], avg[i], avg[i]>=75? "PASSED":"FAILED");
    }
    system("pause");
}
void savef()
{
    int i;
    FILE *fp;
    fp = fopen("EGUILLION.txt","w");
    if(fp == NULL)
    {
        printf("Error opening file!\n");
        system("pause");
    }
    else
    {
       for(i=0; i<=last; i++)
       {
           fprintf(fp,"%s, %.2f, %.2f, %.2f, %.2f\n", name[i], q1[i], q2[i], q3[i], avg[i]);

       }
    }
    fclose(fp);
}
void retrieve()
{
    char line[100];
    char n[50];
    float a, b, c, av;
    FILE *fp;
    fp = fopen("EGUILLION.txt", "r");
    if(fp==NULL)
    {
        printf("Error opening file!\n");
        system("pause");
        return;
    }
    while(fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%49[^,] %.2f %.2f %.2f %.2f", n, &a, &b, &c, &av);
        addrec(n, a, b, c);
    }
    fclose(fp);
}
void updaterec(char n[50])
{
    int pos, choice;

    if(nempty())
    {
        printf("No record to delete!\n");
        system("pause");
        return;
    }
    else
    {
        pos = locate(n);
        if (pos == -1)
        {
            printf("No record found.\n");
            system("pause");
        }
        while (1)
        {
            system("cls");
            printf("Name: %s\n", name[pos]);
            printf("Quiz 1: %.2f\n", q1[pos]);
            printf("Quiz 2: %.2f\n", q2[pos]);
            printf("Quiz 3: %.2f\n", q3[pos]);
            printf("Update:\n");
            printf("1. Quiz 1\n");
            printf("2. Quiz 2\n");
            printf("3. Quiz 3\n");
            printf("4. Return\n");
            printf("Enter selection: \n");
            scanf("%d", &choice);

            switch(choice)
            {
            case 1:
                printf("Enter new Quiz 1 score: ");
                scanf("%f", &q1[pos]);
                avg[pos] = (q1[pos] + q2[pos] + q3[pos]) / 3.0;
            break;

            case 2:
                printf("Enter new Quiz 2 score: ");
                scanf("%f", &q2[pos]);
                avg[pos] = (q1[pos] + q2[pos] + q3[pos]) / 3.0;
            break;

            case 3:
                printf("Enter new Quiz 3 score: ");
                scanf("%f", &q3[pos]);
                avg[pos] = (q1[pos] + q2[pos] + q3[pos]) / 3.0;
            break;

            case 4:
                return;
            break;

            default:
                printf("Invalid input!\n");
            }
        }
    }
}
