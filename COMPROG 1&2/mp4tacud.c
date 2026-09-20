#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

typedef struct {
    char name[50];
    int age;
} Student;

Student list[MAX];
int count = 0;

void menu();
void add();
void update();
void del();
void display();
int find(char name[]);

int main() {
    menu();
    return 0;
}

/* MENU */
void menu() {
    int choice;

    do {
        system("cls");
        printf("=====================================\n");
        printf("      STUDENT RECORD SYSTEM\n");
        printf("=====================================\n");
        printf("[1] ADD STUDENT\n");
        printf("[2] UPDATE STUDENT\n");
        printf("[3] DELETE STUDENT\n");
        printf("[4] DISPLAY RECORDS\n");
        printf("[5] EXIT\n");
        printf("=====================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add(); break;
            case 2: update(); break;
            case 3: del(); break;
            case 4: display(); break;
        }

    } while (choice != 5);
}

/* ADD */
void add() {
    system("cls");

    if (count == MAX) {
        printf("=====================================\n");
        printf(" RECORD LIST IS FULL (MAX = 3)\n");
        printf("=====================================\n");
        system("pause");
        return;
    }

    printf("=========== ADD STUDENT ============\n");

    printf("Name : ");
    scanf(" %[^\n]", list[count].name);

    printf("Age  : ");
    scanf("%d", &list[count].age);

    count++;

    printf("\nRecord added successfully!\n");
    system("pause");
}

/* UPDATE */
void update() {
    char name[50];
    system("cls");

    printf("========== UPDATE STUDENT ==========\n");
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    int pos = find(name);

    if (pos == -1) {
        printf("Student not found.\n");
        system("pause");
        return;
    }

    printf("New age: ");
    scanf("%d", &list[pos].age);

    printf("Record updated successfully!\n");
    system("pause");
}

/* DELETE */
void del() {
    char name[50];
    system("cls");

    printf("========== DELETE STUDENT ==========\n");
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    int pos = find(name);

    if (pos == -1) {
        printf("Student not found.\n");
        system("pause");
        return;
    }

    for (int i = pos; i < count - 1; i++)
        list[i] = list[i + 1];

    count--;

    printf("Record deleted successfully!\n");
    system("pause");
}

/* DISPLAY */
void display() {
    system("cls");

    printf("==============================================\n");
    printf("              STUDENT RECORD LIST\n");
    printf("==============================================\n");
    printf("NO | NAME                     | AGE | REMARKS\n");
    printf("----------------------------------------------\n");

    if (count == 0) {
        printf("No records available.\n");
    }

    for (int i = 0; i < count; i++) {
        printf("%-2d | %-24s | %-3d | %-6s\n",
               i + 1,
               list[i].name,
               list[i].age,
               list[i].age >= 18 ? "ADULT" : "MINOR");
    }

    printf("==============================================\n");
    system("pause");
}

/* FIND */
int find(char name[]) {
    for (int i = 0; i < count; i++)
        if (strcmp(list[i].name, name) == 0)
            return i;
    return -1;
}