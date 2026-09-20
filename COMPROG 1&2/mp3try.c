#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 3
// CREATE A PROGRAM THAT ADDS DATA THAT CAN ADD NEW ELEMENTS, DELETE ELEMENTS, AND DISPLAY THE ELEMENTS.
// THERE WILL BE 2 SETS OF ELEMENTS THAT WILL CONTAIN THE NAMES OF STUDENTS AND THEIR TEST SCORES

void show(char name[MAX][11], int score[MAX], int *count, int *remarks)
{
    system("cls");
    if (*count == 0)
    {
        printf("LIST IS EMPTY\n");
        return;
    }
    printf("LIST OF SCORES\n");
    for (int i = 0; i < *count; i++)
    {
        printf("%d) NAME:%-30s SCORE: %-30d REMARKS: %-30s\n\n", i + 1, name[i], score[i], remarks[i] ? "PASSED" : "FAILED");
    }
}

void add(char name[MAX][11], int score[MAX], int *count, int *remarks)
{
    system("cls");
    if (*count == MAX)
    {
        printf("LIST IS FULL\n");
        return;
    }
    printf("Enter Name: ");
    scanf("%[^\n]", name[*count]);
    printf("Enter Score: ");
    scanf("%d", &score[*count]);
    if (score[*count] >= 75)
    {
        remarks[*count] = 1;
    }
    else
    {
        remarks[*count] = 0;
    }

    (*count)++;
}

void delete(char name[MAX][11], int score[MAX], int *count, int *remarks)
{
    system("cls");
    if (*count == 0)
    {
        printf("LIST IS EMPTY\n");
        return;
    }
    int position;
    show(name, score, count, remarks);
    printf("Enter position to delete: ");
    scanf("%d", &position);
    getchar();

    if (position < 1 || position > *count)
    {
        printf("Invalid position.\n");
        return;
    }
    int newpos = position - 1;
    for (int i = newpos; i < *count - 1; i++)
    {
        strcpy(name[i], name[i + 1]);
        score[i] = score[i + 1];
        remarks[i] = remarks[i + 1];
    }
    (*count)--;
}

int main()
{

    char name[MAX][21];
    int score[MAX];
    int count = 0;
    int remarks[MAX];
    int choice;
    while (1)
    {   
        printf("MENU\n1) Show\n2) Add\n3) Delete\n4) Exit\nChoose: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
            show(name, score, &count, remarks);
        else if (choice == 2)
            add(name, score, &count, remarks);
        else if (choice == 3)
            delete(name, score, &count, remarks);
        else if (choice == 4)
            break;
        else
            printf("Invalid.\n");
    }
    system("pause");
    return 0;
}