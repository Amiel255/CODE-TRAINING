#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

FILE *fp;

char name[max][21];
int g1[max], g2[max], g3[max];

int count = 0;
char nameloc[21];
int last = -1;

void menu();
void show(char name[max][21], int g1[max], int g2[max], int g3[max], int count);
void add(char name[max][21], int g1[max], int g2[max], int g3[max], int *count);
void update(char name[max][21], int g1[max], int g2[max], int g3[max], int count);
void delete(char name[max][21], int g1[max], int g2[max], int g3[max], int *count);
int isfull(int count);
int isempty(int count);
int locate(char name[max][21], int count, char nameloc[]);
int loadfile(char name[max][21], int g1[max], int g2[max], int g3[max], int *count);
int savefile(char name[max][21], int g1[max], int g2[max], int g3[max], int count);
int LocatePosAve(int g1[max], int g2[max], int g3[max], int tg1, int tg2, int tg3);
int ave(int g1, int g2, int g3);

int main()
{
    loadfile(name, g1, g2, g3, &count);
    menu();
    return 0;
}

int loadfile(char name[max][21], int g1[max], int g2[max], int g3[max], int *count)
{
    fp = fopen("studentgradesmp5.txt", "r");

    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 1;
    }

    while (fscanf(fp, "%s %d %d %d", name[*count], &g1[*count], &g2[*count], &g3[*count]) != EOF)
    {
        (*count)++;
        last++;
    }

    fclose(fp);
    return 0;
}

int savefile(char name[max][21], int g1[max], int g2[max], int g3[max], int count)
{
    fp = fopen("studentgradesmp5.txt", "w");

    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d %d %d\n", name[i], g1[i], g2[i], g3[i]);
    }

    fclose(fp);
    return 0;
}

void show(char name[max][21], int g1[max], int g2[max], int g3[max], int count)
{
    system("cls");

    if (isempty(count))
    {
        printf("LIST EMPTY\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        
        int average = ave(g1[i], g2[i], g3[i]);

        printf("%d). Name: %-10s G1:%-5d G2:%-5d G3:%-5d Ave:%-5d %s\n",
               i + 1,
               name[i],
               g1[i],
               g2[i],
               g3[i],
               average,
               average >= 75 ? "PASSED" : "FAILED");
    }
}

void add(char name[max][21], int g1[max], int g2[max], int g3[max], int *count)
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

    if (locate(name, *count, nameloc) > -1)
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

    pos = LocatePosAve(g1, g2, g3, tg1, tg2, tg3);

    for (i = last; i >= pos; i--)
    {
        strcpy(name[i + 1], name[i]);
        g1[i + 1] = g1[i];
        g2[i + 1] = g2[i];
        g3[i + 1] = g3[i];
    }

    strcpy(name[pos], nameloc);
    g1[pos] = tg1;
    g2[pos] = tg2;
    g3[pos] = tg3;

    last++;
    (*count)++;

    savefile(name, g1, g2, g3, *count);

    printf("Record added successfully.\n");
}

void delete(char name[max][21], int g1[max], int g2[max], int g3[max], int *count)
{
    int pos;

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    pos = locate(name, *count, nameloc);

    if (pos == -1)
    {
        printf("Not Found\n");
        return;
    }

    for (int i = pos; i < *count - 1; i++)
    {
        strcpy(name[i], name[i + 1]);
        g1[i] = g1[i + 1];
        g2[i] = g2[i + 1];
        g3[i] = g3[i + 1];
    }

    (*count)--;
    last--;

    printf("Deleted\n");

    savefile(name, g1, g2, g3, *count);
}

void update(char name[max][21], int g1[max], int g2[max], int g3[max], int count)
{
    int pos;
    int tg1, tg2, tg3;
    char tempname[21];

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    pos = locate(name, count, nameloc);

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

    strcpy(tempname, name[pos]);
    
    for (int i = pos; i < last; i++)
    {
        strcpy(name[i], name[i + 1]);
        g1[i] = g1[i + 1];
        g2[i] = g2[i + 1];
        g3[i] = g3[i + 1];
    }

    last--;

    int newpos = LocatePosAve(g1, g2, g3, tg1, tg2, tg3);

    for (int i = last; i >= newpos; i--)
    {
        strcpy(name[i + 1], name[i]);
        g1[i + 1] = g1[i];
        g2[i + 1] = g2[i];
        g3[i + 1] = g3[i];
    }

    strcpy(name[newpos], tempname);
    g1[newpos] = tg1;
    g2[newpos] = tg2;
    g3[newpos] = tg3;

    last++;

    savefile(name, g1, g2, g3, count);

    printf("Record Updated and Re-sorted\n");
}



int LocatePosAve(int g1[max], int g2[max], int g3[max], int tg1, int tg2, int tg3)
{
    int i;

    for (i = 0; i <= last; i++) {
        if ((ave(tg1, tg2, tg3)) > (ave(g1[i], g2[i], g3[i])))
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
            show(name, g1, g2, g3, count);
            break;

        case 2:
            add(name, g1, g2, g3, &count);
            break;

        case 3:
            update(name, g1, g2, g3, count);
            break;

        case 4:
            delete(name, g1, g2, g3, &count);
            break;

        case 5:
            printf("Exiting program\n");
            break;
        }

        system("pause");
    }
}