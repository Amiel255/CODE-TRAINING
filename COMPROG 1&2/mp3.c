#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 5

void show(char name[max][21], int g1[max], int g2[max], int g3[max], int total[max], int ave[max], int *count, int remarks[max])
{
    system("cls");
    if (isempty(count))
    {
        printf("List Empty\n");
        system("pause");
        return;
    }
    printf("LIST OF GRADES\n");
    for (int i = 0; i < *count; i++)
    {
        printf("%d). NAME: %-10s G1: %-10d G2: %-10d G3: %-10d TOTAL: %-10d AVERAGE: %-10d REMARKS: %-10s\n", i + 1, name[i], g1[i], g2[i], g3[i], total[i], ave[i], remarks[i] ? "PASSED" : "FAILED");
    }
}

void add(char name[max][21], int g1[max], int g2[max], int g3[max], int total[max], int ave[max], int *count, int remarks[max])
{
    system("cls");
    if (isfull(count))
    {
        printf("LIST IS FULL\n");
        system("pause");
        return;
    }
    printf("Enter Name:");
    scanf("%20[^\n]", name[*count]);
    printf("Enter Grade No. 1:");
    scanf("%d", &g1[*count]);
    printf("Enter Grade No. 2:");
    scanf("%d", &g2[*count]);
    printf("Enter Grade No. 3:");
    scanf("%d", &g3[*count]);
    total[*count] = g1[*count] + g2[*count] + g3[*count];
    ave[*count] = total[*count] / 3;
    if (ave[*count] >= 75)
    {
        remarks[*count] = 1;
    }
    else
    {
        remarks[*count] = 0;
    }

    (*count)++;
}

void delete(char name[max][21], int g1[max], int g2[max], int g3[max], int total[max], int ave[max], int *count, int remarks[max])
{
    system("cls");
    if (isempty(count))
    {
        printf("Nothing to delete\n");
        system("pause");
        return;
    }
    int pos;
    show(name, g1, g2, g3, total, ave, count, remarks);
    char target[21];
    printf("Enter name to find: ");
    scanf("%20[^\n]", target);
    pos = locate(name, count, target);

    if (pos == -1)
    {
        printf("Not Found");
        return;
    }
    int newpos = pos;
    for (int i = newpos; i < *count - 1; i++)
    {
        strcpy(name[i], name[i + 1]);
        g1[i] = g1[i + 1];
        g2[i] = g2[i + 1];
        g3[i] = g3[i + 1];
        total[i] = total[i + 1];
        ave[i] = ave[i + 1];
        remarks[i] = remarks[i + 1];
    }
    printf("Deleted\n");
    (*count)--;
}

int isfull(int *count)
{
    return (*count == max);
}

int isempty(int *count)
{
    return (*count == 0);
}

int locate(char name[max][21], int *count, char target[21])
{
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(name[i], target) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    char name[max][21];
    int g1[max], g2[max], g3[max];
    int ave[max];
    int total[max];
    int count = 0;
    int remarks[max];
    int choice;

    while (1)
    {
        printf("\nMENU\n1) Show\n2) Add\n3) Delete\n4) Exit\nChoose: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
            show(name, g1, g2, g3, total, ave, &count, remarks);
        else if (choice == 2)
            add(name, g1, g2, g3, total, ave, &count, remarks);
        else if (choice == 3)
            delete(name, g1, g2, g3, total, ave, &count, remarks);
        else if (choice == 4)
            break;
        else
            printf("Invalid.\n");
    }
    system("pause");
    return 0;
}
