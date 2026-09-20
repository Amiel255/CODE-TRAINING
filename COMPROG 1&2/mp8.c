#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

FILE *fp;

typedef struct
{ 
    char name[21];
    int g1;
    int g2;
    int g3;
} student;
student list[max];

int count = 0;
char nameloc[21];
int last = -1;

void menu();
void show(student list[], int count);
void add(student list[], int *count);
void update(student list[], int count);
void delete(student list[], int *count);
int isfull(int count);
int isempty(int count);
int locate(student list[], int count, char nameloc[]);
int loadfile(student list[], int *count);
int savefile(student list[], int count);
int LocatePosAve(student list[], int tg1, int tg2, int tg3);
int ave(int g1, int g2, int g3);

int main()
{
    loadfile(list, &count);
    menu();
    return 0;
}

int loadfile(student list[], int *count)
{
    fp = fopen("studentgradesmp5.txt", "r");

    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 1;
    }

    while (fscanf(fp, "%s %d %d %d", list[*count].name, &list[*count].g1, &list[*count].g2, &list[*count].g3) != EOF)
    {
        (*count)++;
        last++;
    }

    fclose(fp);
    return 0;
}

int savefile(student list[], int count)
{
    fp = fopen("studentgradesmp5.txt", "w");

    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d %d %d\n", list[i].name, list[i].g1, list[i].g2, list[i].g3);
    }

    fclose(fp);
    return 0;
}

void show(student list[], int count)
{
    system("cls");

    if (isempty(count))
    {
        printf("LIST EMPTY\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        
        int average = ave(list[i].g1, list[i].g2, list[i].g3);

        printf("%d). Name: %-10s G1:%-5d G2:%-5d G3:%-5d Ave:%-5d %s\n",
               i + 1,
               list[i].name,
               list[i].g1,
               list[i].g2,
               list[i].g3,
               average,
               average >= 75 ? "PASSED" : "FAILED");
    }
}

void add(student list[], int *count)
{
    int pos, i;
    int tg1, tg2, tg3;

    system("cls");

    if (isfull(*count))
    {
        printf("LIST IS FULL\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    if (locate(list, *count, nameloc) > -1)
    {
        printf("Duplicate Record\n");
        return;
    }

    printf("Enter Grade 1: ");
    scanf("%d", &tg1);

    printf("Enter Grade 2: ");
    scanf("%d", &tg2);

    printf("Enter Grade 3: ");
    scanf("%d", &tg3);

    pos = LocatePosAve(list, tg1, tg2, tg3);

    for (i = last; i >= pos; i--)
    {
        list[i + 1] = list[i];
    }

    strcpy(list[pos].name, nameloc);
    list[pos].g1 = tg1;
    list[pos].g2 = tg2;
    list[pos].g3 = tg3;

    last++;
    (*count)++;

    savefile(list, *count);

    printf("Record added successfully.\n");
}

void delete(student list[], int *count)
{
    int pos;

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    pos = locate(list, *count, nameloc);

    if (pos == -1)
    {
        printf("Not Found\n");
        return;
    }

    for (int i = pos; i < *count - 1; i++)
    {
        list[i] = list[i + 1];
    }

    (*count)--;
    last--;

    printf("Deleted\n");

    savefile(list, *count);
}

void update(student list[], int count)
{
    int pos;
    int tg1, tg2, tg3;
    char tempname[21];

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    pos = locate(list, count, nameloc);

    if (pos == -1)
    {
        printf("Not Found\n");
        return;
    }

    printf("Enter New Grade 1: ");
    scanf("%d", &tg1);

    printf("Enter New Grade 2: ");
    scanf("%d", &tg2);

    printf("Enter New Grade 3: ");
    scanf("%d", &tg3);

    strcpy(tempname, list[pos].name);
    
    for (int i = pos; i < last; i++)
    {
        list[i] = list[i + 1];
    }

    last--;

    int newpos = LocatePosAve(list, tg1, tg2, tg3);

    for (int i = last; i >= newpos; i--)
    {
        list[i + 1] = list[i];
    }

    strcpy(list[newpos].name, tempname);
    list[newpos].g1 = tg1;
    list[newpos].g2 = tg2;
    list[newpos].g3 = tg3;

    last++;

    savefile(list, count);

    printf("Record Updated and Re-sorted\n");
}

int locate(student list[], int count, char nameloc[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(list[i].name, nameloc) == 0)
            return i;
    }

    return -1;
}

int LocatePosAve(student list[], int tg1, int tg2, int tg3)
{
    int i;

    for (i = 0; i <= last; i++) {
        if ((ave(tg1, tg2, tg3)) > (ave(list[i].g1, list[i].g2, list[i].g3)))
            return i;
    }
    return i;
}

int isfull(int count)
{
    if (count == max)
        return 1;
    else
        return 0;
}

int isempty(int count)
{
    if (count == 0)
        return 1;
    else
        return 0;
}

int ave (int g1, int g2, int g3){ 
    return (g1 + g2 + g3) / 3;
}

void menu()
{
    int choice = 0;

    while (choice != 5)
    {
        system("cls");

        printf("MENU\n");
        printf("1. SHOW\n");
        printf("2. ADD\n");
        printf("3. UPDATE\n");
        printf("4. DELETE\n");
        printf("5. EXIT\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            show(list, count);
            break;

        case 2:
            add(list, &count);
            break;

        case 3:
            update(list, count);
            break;

        case 4:
            delete(list, &count);
            break;

        case 5:
            printf("Exiting program\n");
            break;
        }

        system("pause");
    }
}