#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

FILE *fp;
FILE *fp1;

char name[max][21];
int g1[max], g2[max], g3[max];
int count = 0;
char nameloc[21];

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


int main () {
    loadfile(name, g1, g2, g3, &count);
    menu();
    system("pause");
    return 0;
}

int loadfile(char name[max][21], int g1[max], int g2[max], int g3[max], int *count) {
    fp = fopen("studentgradesmp5.txt", "r");

    if (fp == NULL) {
        printf("File Not Found\n");
        return 1;
    }
    while (fscanf(fp, "%s %d %d %d\n", name[*count], &g1[*count], &g2[*count], &g3[*count]) != EOF) {
        (*count)++;
    }

    fclose(fp);
    return 0;
}

int savefile(char name[max][21], int g1[max], int g2[max], int g3[max], int count) {
    fp = fopen("studentgradesmp5.txt", "w");

    if (fp == NULL) {
        printf("File Not Found\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %d %d\n", name[i], g1[i], g2[i], g3[i]);
    }

    fclose(fp);
    return 0;
}

void show(char name[max][21], int g1[max], int g2[max], int g3[max], int count) {
    system("cls");
    if (isempty(count) == 1)
    {
        printf("LIST EMPTY\n");
        return;
    }

    int ave;
    for (int i = 0; i < count; i++) {
        ave = (g1[i] + g2[i] + g3[i]) / 3;
        printf("%d). Name: %-10s Score 1: %-10d Score 2: %-10d Score 3: %-10d Ave: %-10d Remarks: %-10s\n", i + 1,
            name[i], g1[i], g2[i], g3[i], ave, ave >= 75 ? "PASSED" : "FAILED");
    }
}

void add(char name[max][21], int g1[max], int g2[max], int g3[max], int *count) {
    system("cls");
    if (isfull(*count)) {
        printf("LIST IS FULL\n");
        return;
    }
    printf("Enter Name:");
    scanf(" %20[^\n]", name[*count]);
    strcpy(nameloc, name[*count]);

    if (locate(name, *count, nameloc) != -1) {
        printf("Name already exists.\n");
        system("pause");
        return;
    }
    printf("Enter Grade No. 1: ");
    scanf("%d", &g1[*count]);
    printf("Enter Grade No. 2: ");
    scanf("%d", &g2[*count]);
    printf("Enter Grade No. 3: ");
    scanf("%d", &g3[*count]);
    (*count)++;
    printf("Record added successfully.\n");
    savefile(name, g1, g2, g3, *count);
}

void update(char name[max][21], int g1[max], int g2[max], int g3[max], int count) {
    system("cls");
    if (isempty(count) == 1) {
        printf("Nothing to update.\n");
        return;
    }
    int pos;
    show(name, g1, g2, g3, count);
    printf("Update of grade\n");
    printf("Enter name:");
    scanf(" %20[^\n]", nameloc);
    pos = locate(name, count, nameloc);
    if (pos == -1) {
        printf("\nNot Found\n");
        return;
    }

    printf("Enter Grade No. 1: ");
    scanf("%d", &g1[pos]);
    printf("Enter Grade No. 2: ");
    scanf("%d", &g2[pos]);
    printf("Enter Grade No. 3: ");
    scanf("%d", &g3[pos]);
    printf("Updated...\n");
    savefile(name, g1, g2, g3, count);
}

void delete(char name[max][21], int g1[max], int g2[max], int g3[max], int *count) {
    system("cls");
    if (isempty(*count) == 1) {
        printf("Nothing to delete.\n");
        return;
    }
    int pos;
    show(name, g1, g2, g3, *count);
    printf("Enter name to locate:");
    scanf(" %20[^\n]", nameloc);
    pos = locate(name, *count, nameloc);
    if (pos == -1) {
        printf("\nNot Found\n");
        return;
    }
    for (int i = pos; i < *count - 1; i++) {
        strcpy(name[i], name[i + 1]);
        g1[i] = g1[i + 1];
        g2[i] = g2[i + 1];
        g3[i] = g3[i + 1];
    }
    printf("Deleted...");
    (*count)--;
    savefile(name, g1, g2, g3, *count);
}

int isfull (int count) {
    if (count == max)
        return 1;
    else
        return 0;
}

int isempty (int count) {
    if (count == 0)
        return 1;
    else
        return 0;
}

int locate(char name[max][21], int count, char nameloc[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(name[i], nameloc) == 0) {
            return i;
        }
    }
    return -1;
}

void menu()
{
    system("cls");
    int choice = 0;
    while (choice != 5) {
        system("cls");
        printf("MENU\n 1.SHOW\n 2.ADD\n 3.UPDATE\n 4.DELETE\n 5.EXIT\n");
        printf("\nEnter Choice:");
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
        printf("Exiting the program\n");
        break;
    }
    system("pause");
    }
}
