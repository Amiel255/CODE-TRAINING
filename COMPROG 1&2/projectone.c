#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 50
FILE *fp;
// functions
int loadfile();
int savefile();
void create();
void login();
void menu();
int locatepos();

// enums
enum operation
{
    add,
    sub,
    mul,
    divi
};
enum difficulty
{
    easy,
    medium,
    hard
};

typedef struct
{
    char user[21];
    char pass[21];
    float score[4]; // add, sub, mul, divi
} Player;
Player player[MAX];
int count = 0;
int currentuser = -1;

// play game funcitons
int compute(enum operation op, int x, int y);
void generate(enum operation op, enum difficulty diff, int *x, int *y);
void playgame(enum operation op, enum difficulty diff);

// leaderboard and sorting functions
float getscoreVal(Player p, int mode);
void insertionsort(int idx[], int mode);
void leaderboard(int mode);

int main()
{
    system("cls");
    srand(time(NULL));
    loadfile();
    int choice;

    while (1)
    {
        printf("\n1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            create();
            savefile();
        }
        else if (choice == 2)
            login();
        else if (choice == 3)
            break;
        else
            printf("Invalid choice\n");
    }
    system("pause");
    return 0;
}

int compute(enum operation op, int x, int y)
{
    if (op == add)
        return x + y;

    else if (op == sub)
    {
        if (x < y)
        {
            int temp = x;
            x = y;
            y = temp;
        }
        return x - y;
    }

    else if (op == mul)
        return x * y;

    else if (op == divi)
    {
        if (y == 0)
            y = 1;
        return x / y;
    }

    return 0;
}

void generate(enum operation op, enum difficulty diff, int *x, int *y)
{
    int limit;

    if (diff == easy)
        limit = 10;
    else if (diff == medium)
        limit = 100;
    else
        limit = 1000;

    if (op == divi)
    {
        *y = rand() % limit + 1;
        int k = rand() % limit + 1;
        *x = (*y) * k;
    }
    else
    {
        *x = rand() % limit + 1;
        *y = rand() % limit + 1;
    }

    if (op == sub && *x < *y)
        {
            int temp = *x;
            *x = *y;
            *y = temp;
        }
}

void playgame(enum operation op, enum difficulty diff)
{
    int x, y, ans;
    int correct = 0;

    for (int i = 0; i < 5; i++)
    {
        generate(op, diff, &x, &y);

        printf("Question %d\n", i + 1);

        if (op == add)
            printf("%d + %d = ", x, y);
        else if (op == sub)
            printf("%d - %d = ", x, y);
        else if (op == mul)
            printf("%d * %d = ", x, y);
        else if (op == divi)
            printf("%d / %d = ", x, y);

        scanf("%d", &ans);

        int correctans = compute(op, x, y);

        if (ans == correctans)
        {
            printf("Correct!\n");
            correct++;
        }
        else
        {
            printf("Wrong! The correct answer is %d\n", correctans);
        }
    }
    float score = (float)correct / 5 * 100;

    if (currentuser != -1)
    {
        player[currentuser].score[op] = score;
    }
    printf("\n--- GAME RESULT ---\n");
    printf("Score: %.2f%%\n", score);

    printf("\n--- OVERALL LEADERBOARD ---\n");
    leaderboard(-1);
    system("pause");
}

// player initializing and scoring

void create()
{
    system("cls");
    if (count >= MAX)
    {
        printf("List is full\n");
        return;
    }
    printf("Enter username: ");
    scanf(" %[^\n]", player[count].user);

    int pos = locatepos(player[count].user);

    if (pos != -1)
    {
        printf("Username already exists\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", player[count].pass);

    for (int i = 0; i < 4; i++)
    {
        player[count].score[i] = 0;
    }

    count++;
    printf("Account created successfully\n");
}

void login()
{
    system("cls");
    char username[21], password[21];
    int errortries = 5;

    printf("\nEnter username: ");
    scanf(" %[^\n]", username);

    int pos = locatepos(username);

    if (pos == -1)
    {
        printf("Username not found\n");
        return;
    }

    while (errortries != 0)
    {
        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(player[pos].pass, password) == 0)
        {
            printf("Login successful\n");
            currentuser = pos;
            menu();
            return;
        }
        else
        {
            errortries--;
            if (errortries != 0)
            {
                printf("\nIncorrect Password\n");
            }
            else
            {
                printf("Too many attempts!\n");
            }
        }
    }
}

int locatepos(char username[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(player[i].user, username) == 0)
            return i;
    }

    return -1;
}

// MENU
void menu()
{
    int choice;
    while (1)
    {
        system("cls");
        printf("\nSELECT:\n");
        printf("1. Play Game\n2. Leaderboard\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int opchoice, diffchoice;
            printf("\nChoose Operation:\n");
            printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n");
            printf("Enter choice: ");
            scanf("%d", &opchoice);
            if (opchoice < 1 || opchoice > 4)
            {
                printf("Invalid choice\n");
                return;
            }

            printf("\nChoose Difficulty:\n");
            printf("1. Easy\n2. Medium\n3. Hard\n");
            printf("Enter choice: ");
            scanf("%d", &diffchoice);

            if (diffchoice < 1 || diffchoice > 3)
            {
                printf("Invalid choice\n");
                return;
            }

            playgame(opchoice - 1, diffchoice - 1);
            savefile();
        }
        else if (choice == 2)
        {

            int type;

            printf("\nLeaderboard Type:\n");
            printf("1. Overall\n2. Addition\n3. Subtraction\n4. Multiplication\n5. Division\n");
            scanf("%d", &type);

            if (type == 1)
                leaderboard(-1);
            else if (type >= 2 && type <= 5)
                leaderboard(type - 2);
            else
                printf("Invalid choice\n");

            system("pause");
        }
        else if (choice == 3)
        {
            return;
        }
        else
        {
            printf("Invalid choice\n");
            system("pause");
        }
    }
}

// safe and load

int savefile()
{
    fp = fopen("players.txt", "w");
    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %s %.2f %.2f %.2f %.2f\n",
                player[i].user,
                player[i].pass,
                player[i].score[add],
                player[i].score[sub],
                player[i].score[mul],
                player[i].score[divi]);
    }
    fclose(fp);
    return 1;
}

int loadfile()
{
    fp = fopen("players.txt", "r");
    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 0;
    }

    count = 0;

    while (fscanf(fp, "%s %s %f %f %f %f",
                  player[count].user,
                  player[count].pass,
                  &player[count].score[add],
                  &player[count].score[sub],
                  &player[count].score[mul],
                  &player[count].score[divi]) == 6)
    {
        count++;
    }

    fclose(fp);
    return 1;
}

// leaderboard

float getscoreVal(Player p, int mode)
{
    if (mode == -1)
    {
        return (p.score[add] +
                p.score[sub] +
                p.score[mul] +
                p.score[divi]) /
               4.0;
    }
    else
    {
        return p.score[mode];
    }
}

void insertionsort(int idx[], int mode)
{
    for (int i = 1; i < count; i++)
    {
        int key = idx[i];
        float keyVal = getscoreVal(player[key], mode);

        int j = i - 1;

        while (j >= 0 && getscoreVal(player[idx[j]], mode) < keyVal)
        {
            idx[j + 1] = idx[j];
            j--;
        }

        idx[j + 1] = key;
    }
}

void leaderboard(int mode)
{
    int idx[MAX];

    // initialize indexes
    for (int i = 0; i < count; i++)
        idx[i] = i;

    insertionsort(idx, mode);

    printf("\n===================Leaderboard===================\n");

    if (mode == -1)
        printf("TOP 10 - OVERALL\n");
    else if (mode == add)
        printf("TOP 10 - ADDITION\n");
    else if (mode == sub)
        printf("TOP 10 - SUBTRACTION\n");
    else if (mode == mul)
        printf("TOP 10 - MULTIPLICATION\n");
    else if (mode == divi)
        printf("TOP 10 - DIVISION\n");

    int limit = count < 10 ? count : 10;

    for (int i = 0; i < limit; i++)
    {
        int p = idx[i]; // actual player index

        printf("%d.) %-10s | %.2f%%\n",
               i + 1,
               player[p].user,
               getscoreVal(player[p], mode));
    }
}
