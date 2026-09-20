#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 20 + 1
int items = 5;

int add(int items);
int subtract(int items);
int multiply(int items);
int divide(int items);
void menu();

int main()
{
    srand(time(NULL));
    menu();
    system("pause");
    return 0;
}

void menu()
{
    system("cls");
    int choice = 0, score;
    while (choice != 5)
    {
        system("cls");
        printf("MENU\n 1.ADD\n 2.SUBTRACT\n 3.MULTIPLY\n 4.DIVIDE\n 5.EXIT\n");
        printf("\nEnter Choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            score = add(items);
            printf("\nYour Score is %d out of %d\n", score, items);
            break;
        case 2:
            score = subtract(items);
            printf("\nYour Score is %d out of %d\n", score, items);
            break;
        case 3:
            score = multiply(items);
            printf("\nYour Score is %d out of %d\n", score, items);
            break;
        case 4:
            score = divide(items);
            printf("\nYour Score is %d out of %d\n", score, items);
            break;
        case 5:
            printf("Exiting the program\n");
            break;
        }
        system("pause");
    }
}

int add(int items)
{
    system("cls");
    printf("ADDITION QUIZ\n");
    int i, cor = 0, a, b, ans;
    for (i = 0; i < items; i++)
    {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        printf("ADDITION QUIZ\n");
        printf("\n%d.) What is %d + %d? ", i + 1, a, b);
        scanf("%d", &ans);
        if (ans == a + b)
        {
            printf("Correct!");
            cor++;
        }
        else
        {
            printf("Nice try! The correct answer is %d.", a + b);
        }
    }
    return cor;
}

int subtract(int items)
{
    system("cls");
    printf("SUBRACTION QUIZ\n");
    int i, cor = 0, a, b, ans;
    for (i = 0; i < items; i++) {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        if (a < b) {
            int temp = a;
            a = b;
            b = temp;
        }
        printf("\n%d.) What is %d - %d? ", i + 1, a, b);
        scanf("%d", &ans);
        if (ans == a - b)
        {
            printf("Correct!");
            cor++;
        }
        else
        {
            printf("Nice try! The correct answer is %d.", a - b);
        }
    }
    return cor;
}

int multiply (int items) {
    system("cls");
    printf("MULTIPLICATION QUIZ\n");
    int i, cor = 0, a, b, ans;
    for (i = 0; i < items; i++) {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        printf("\n%d.) What is %d * %d? ", i + 1, a, b);
        scanf("%d", &ans);
        if (ans == a * b)
        {
            printf("Correct!");
            cor++;
        }
        else
        {
            printf("Nice try! The correct answer is %d.", a * b);
        }
    }
    return cor;
}

int divide (int items) {
    system("cls");
    printf("DIVISION QUIZ\n");
    int i, cor = 0, a, b, ans;
    for (i = 0; i < items; i++) {
        b = rand() % 20 + 1;
        int check = rand() % 20 + 1;
        a = b * check;
        printf("\n%d.) What is %d / %d? ", i + 1, a, b);
        scanf("%d", &ans);
        if (ans == a / b)
        {
            printf("Correct!");
            cor++;
        }
        else
        {
            printf("Nice try! The correct answer is %d.", a / b);
        }
    }
    return cor;
}