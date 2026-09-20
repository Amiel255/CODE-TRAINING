#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100


char name[max][21];
int g1[max], g2[max], g3[max];
int count = 0;
char nameloc[21];

void menu();
void show(int count);
void add(char n[], int s1, int s2, int s3, int *count);
void update(char n[], int s1, int s2, int s3, int count);
void delete(char n[], int *count);
int isfull(int count);
int isempty(int count);
int locate(char name[max][21], int count, char nameloc[]);

int main () {
    menu();
    system("pause");
    return 0;
}

void show(int count) {
    system("cls");
    if (isempty(count) == 1)
    {
        printf("LIST EMPTY\n");
        return;
    }
    for (int i = 0; i < count; i++) {\
        int average = (g1[i] + g2[i] + g3[i]) / 3;
        printf("%d). Name: %-10s Score 1: %-10d Score 2: %-10d Score 3:%-10d Ave: %-10d Remarks: %-10s\n", i + 1,
            name[i], g1[i], g2[i], g3[i], average, average >=75 ? "PASSED" : "FAILED");
    }
}

void add(char n[], int s1, int s2, int s3, int *count) {
    if (isfull(*count)) {
        printf("LIST IS FULL\n");
        return;
    }
    if (locate(name, *count, n) != -1) {
        printf("Name already exists.\n");
        return;
    }
    strcpy(name[*count], n);
    g1[*count] = s1;
    g2[*count] = s2;
    g3[*count] = s3;
    (*count)++;
    printf("Record added successfully.\n");
}

void update(char n[], int s1, int s2, int s3, int count) {
    int pos;
    pos = locate(name, count, n);
    if (pos == -1) {
        printf("\nNot Found\n");
        return;
    }
    g1[pos] = s1;
    g2[pos] = s2;
    g3[pos] = s3;
    printf("Updated...\n");
}

void delete(char n[], int *count) {
    int pos = locate(name, *count, n);
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
}

int isfull(int count) {
    if (count == max)
        return 1;
    else
        return 0;
}

int isempty(int count) {
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
    int choice = 0, s1, s2, s3;
    char n[21];
    while (choice != 5) {
        system("cls");
        printf("MENU\n 1.SHOW\n 2.ADD\n 3.UPDATE\n 4.DELETE\n 5.EXIT\n");
        printf("\nEnter Choice:");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            show(count);
            break;
        case 2:
            system("cls");
            printf("Enter Name: ");
            scanf(" %20[^\n]", n);
            printf("Enter Grade No. 1: ");
            scanf("%d", &s1);
            printf("Enter Grade No. 2: ");
            scanf("%d", &s2);
            printf("Enter Grade No. 3: ");
            scanf("%d", &s3);
            add(n, s1, s2, s3, &count);
            break;
        case 3:
            system("cls");
            if (isempty(count)) {
                printf("Nothing to update.\n");
            } else {
                show(count);
                printf("\nUpdate of grade\n");
                printf("Enter name: ");
                scanf(" %20[^\n]", n);
                if (locate(name, count, n) != -1) {
                    printf("Enter Grade No. 1: ");
                    scanf("%d", &s1);
                    printf("Enter Grade No. 2: ");
                    scanf("%d", &s2);
                    printf("Enter Grade No. 3: ");
                    scanf("%d", &s3);
                    update(n, s1, s2, s3, count);
                } else {
                    printf("Not Found\n");
                }
            }
            break;
        case 4:
            system("cls");
            if (isempty(count)) {
                printf("Nothing to delete.\n");
            } else {
                show(count);
                printf("\nEnter name to locate: ");
                scanf(" %20[^\n]", n);
                delete(n, &count);
            }
            break;
        case 5:
            printf("Exiting the program\n");
            break;
        }
        system("pause");
    }
}
