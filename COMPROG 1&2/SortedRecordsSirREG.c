// Array of Baseball Players

// Parallel Arrays

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX 50

    // GLOBAL VARIABLES

    char player[MAX][50];

int at_bats[MAX], hits[MAX];

int last = -1; // array is initially empty

// UDFs declaration

void addRecord(char n[], int a, int h);

void delRecord(char n[]);

void display();

int isfull();

void update(char n[]);

int isempty();

int locate(char n[]);

int locatePos(char n[]);

float batAve(int ab, int h);

int menu();

void save();

void retrieve();

int main()
{

    char pl[50];

    int at, ht;

    retrieve(); // populate the arrays with values from file

    while (1)
    { // infinite loop

        switch (menu())
        {

        case 1:
            printf("Input Player: ");
            getchar();
            scanf("%[^\n]", pl);

            if (locate(pl) > -1)
            {

                printf("Duplicate Record\n");

                system("pause");

                break;
            }

            printf("Input At Bats: ");
            scanf("%d", &at);

            printf("Input Hits: ");
            scanf("%d", &ht);

            addRecord(pl, at, ht);
            break;

        case 2:
            printf("Input Player: ");
            getchar();
            scanf("%[^\n]", pl);

            update(pl);
            break;

        case 3:
            printf("Input Player: ");
            getchar();
            scanf("%[^\n]", pl);

            delRecord(pl);
            break;

        case 4:
            display();
            break;

        case 5:
            printf("Saving...\n");
            system("pause");
            save();
            exit(0);

        default:
            printf("1 to 4 lang! Shunga.\n");
            system("pause");
        }
    }

    return 0;
}

// UDF definitions

void addRecord(char n[], int a, int h)
{

    int i, p;

    if (isfull())
    {

        printf("Array is full!\n");

        system("pause");
    }

    else
    {

        p = locatePos(n);

        for (i = last; i >= p; i--)
        {

            strcpy(player[i + 1], player[i]);

            at_bats[i + 1] = at_bats[i];

            hits[i + 1] = hits[i];
        }

        strcpy(player[p], n);

        at_bats[p] = a;

        hits[p] = h;

        last++;

        // printf("Record of %s was added to the array.\n",n);

        // system("pause");
    }
}

void delRecord(char n[])
{

    int p, i;

    if (isempty())
    {

        printf("Nothing to delete.\n");

        system("pause");
    }

    else
    {

        p = locate(n);

        if (p == -1)
        {

            printf("Not found.\n");

            system("pause");
        }

        else
        {

            for (i = p; i < last; i++)
            {

                strcpy(player[i], player[i + 1]);

                at_bats[i] = at_bats[i + 1];

                hits[i] = hits[i + 1];
            }

            last--;

            printf("Record of %s was deleted from the array.\n", n);

            system("pause");
        }
    }
}

void display()
{

    int i;

    float ba;

    system("cls");

    printf("%4s %-20s %-6s %-6s %-10s\n", "No.", "Player", "At_bats", "Hits", "Average");

    for (i = 0; i <= last; i++)
    {

        ba = batAve(at_bats[i], hits[i]);

        printf("%d.) %-20s %4d %4d %6.2f%%\n", i + 1, player[i], at_bats[i], hits[i], ba);
    }

    system("pause");
}

int isfull()
{

    return (last == MAX - 1);
}

int isempty()
{

    return (last == -1); // if (last==-1) return 1 else return 0;
}

int locate(char n[])
{

    for (int i = 0; i <= last; i++)

        if (strcmp(player[i], n) == 0)

            return i;

    return -1; // not found
}

int menu()
{

    int ch;

    system("cls");

    printf("Menu\n");

    printf("1. Add Record\n");

    printf("2. Update a Record\n");

    printf("3. Delete a Record\n");

    printf("4. Display All\n");

    printf("5. Exit\n");

    printf("Select[1-5]: ");

    scanf("%d", &ch);

    return ch;
}

float batAve(int ab, int h)
{

    return (float)h / ab * 100;
}

void update(char n[])
{

    int p, i, ch;

    if (isempty())
    {

        printf("Nothing to delete.\n");

        system("pause");
    }

    else
    {

        p = locate(n);

        if (p == -1)
        {

            printf("Not found.\n");

            system("pause");
        }

        else
        { // nakita ang record

            while (1)
            {

                system("cls");

                printf("Name: %s\n", player[p]);

                printf("At_Bats: %d\n", at_bats[p]);

                printf("Hits: %d\n", hits[p]);

                printf("Average: %6.2f%%", batAve(at_bats[p], hits[p]));

                printf("\n\nUpdate Options:\n");

                printf("1. At_Bats\n");

                printf("2. Hits\n");

                printf("3. Return to main\n");

                printf("Select[1-3]: ");

                scanf("%d", &ch);

                switch (ch)
                {

                case 1:
                    printf("Input new At_bats: ");
                    scanf("%d", &at_bats[p]);
                    break;

                case 2:
                    printf("Input new Hits: ");
                    scanf("%d", &hits[p]);
                    break;

                case 3:
                    return;

                default:
                    printf("1 to 3 only.\n");
                    system("pause");
                }
            }
        }

        printf("Record of %s was updated from the array.\n", n);

        system("pause");
    }
}

void save()
{

    int i;

    FILE *fp; // file pointer

    fp = fopen("bscs1ab26.csv", "w");

    if (fp == NULL)
    {

        printf("Error opening file.\n");

        system("pause");
    }

    else
    {

        for (i = 0; i <= last; i++) // write to file

            fprintf(fp, "%s,%d,%d\n", player[i], at_bats[i], hits[i]);

        fclose(fp); // close file
    }
}

void retrieve()
{

    FILE *fp;

    char line[100];

    char nm[50];

    int a, h;

    fp = fopen("bscs1ab26.csv", "r");

    if (fp == NULL)
    {

        printf("Error opening file.\n");

        system("pause");
    }

    else
    {

        while (fgets(line, sizeof(line), fp))
        {

            sscanf(line, "%[^,],%d,%d", nm, &a, &h); // string scan

            addRecord(nm, a, h);
        }

        fclose(fp);
    }
}

int locatePos(char n[])
{

    int i;

    for (i = 0; i <= last; i++)

        if (strcmp(n, player[i]) < 0)

            return i;

    return i;
}
