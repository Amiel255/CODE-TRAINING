#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

void show(char name[MAX][11], int score[MAX], int remarks[MAX], int *index)
{
    system("cls");
    if (*index == 0)
    {
        printf("LIST IS EMPTY!\n");
        return;
    }
    for (int i = 0; i < *index; i++)
    {
        printf("%d). NAME: %-30s SCORE: %-30d REMARKS: %-30s\n\n", i + 1, name[i], score[i], remarks[i] ? "PASSED" : "FAILED");
    }
}

void add(char name[MAX][11], int score[MAX], int remarks[MAX], int *index)
{
    system("cls");
    if (*index == MAX)
    {
        printf("LIST IS FULL\n");
        return;
    }
    printf("Enter Name: ");
    scanf("%10s", name[*index]);
    printf("Enter Score: ");
    scanf("%d", &score[*index]);
    if (score[*index] >= 75)
    {
        remarks[*index] = 1;
    }
    else
        remarks[*index] = 0;
    (*index)++;
}

void delete(char name[MAX][11], int score[MAX], int remarks[MAX], int *index)
{
    system("cls");
    if (*index == 0)
    {
        printf("LIST IS EMPTY\n");
        return;
    }
    int position;
    show(name, score, remarks, index);
    printf("ENTER POSITION TO DELETE: ");
    scanf("%d", &position);
    if (position < 1 || position > *index)
    {
        printf("INVALID, SELECT ANOTHER POSITION 0 UP TO %d", *index);
        return;
    }
    int delpos = position - 1;
    for (int i = delpos; i < *index - 1; i++)
    {
        strcpy(name[i], name[i + 1]);
        score[i] = score[i + 1];
        remarks[i] = remarks[i + 1];
    }
    (*index)--;
}
int main()
{
    char name[MAX][11];
    int score[MAX];
    int remarks[MAX];
    int index = 0;
    int choice;

    while (1)
    {
        printf("MENU\n1) Show\n2) Add\n3) Delete\n4) Exit\nChoose: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1)
            show(name, score, remarks, &index);
        else if (choice == 2)
            add(name, score, remarks, &index);
        else if (choice == 3)
            delete(name, score, remarks, &index);
        else if (choice == 4) {
            printf("THANK YOU FOR USING US");
        break;
        }
    }
    system("pause");
    return 0;
}