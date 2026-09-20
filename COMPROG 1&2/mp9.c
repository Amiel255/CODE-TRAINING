#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

FILE *fp;

typedef struct node
{
    char name[21];
    int g1, g2, g3;
    struct node *link;
} node;

int count = 0;
int last = -1;

void menu(node **head);
void show(node *head);
void add(node **head);
void update(node *head);
void delete(node **head);
int isfull(int count);
int isempty(node *ptr);
int loadfile(node **head);
int savefile(node *head);
node *locate(node *head, char nameloc[]);



int main()
{
    node *head = NULL;
    loadfile(&head);
    menu(&head);
    return 0;
}

int loadfile(node **head)
{
    char tname[21];
    int tg1, tg2, tg3;
    fp = fopen("studentgradesmp5.txt", "r");

    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 1;
    }

    while (fscanf(fp, "%20s %d %d %d", tname, &tg1, &tg2, &tg3) == 4 )
    {
        node *newnode = malloc(sizeof(node));
        strcpy(newnode->name, tname);
        newnode->g1 = tg1;
        newnode->g2 = tg2;
        newnode->g3 = tg3;
        newnode->link = NULL;

        if (*head == NULL) {
            *head = newnode;
        }
        else 
        {
            node *ptr = *head;
            while (ptr->link !=NULL) {
                ptr = ptr->link;
            }
            ptr->link = newnode;
        }
    }

    fclose(fp);
    return 0;
}

int savefile(node *head)
{
    fp = fopen("studentgradesmp5.txt", "w");
    node *ptr = head;

    if (fp == NULL)
    {
        printf("File Not Found\n");
        return 1;
    }

    while (ptr != NULL) {
        fprintf(fp, "%s %d %d %d\n", ptr->name, ptr->g1, ptr->g2, ptr->g3);
        ptr = ptr->link;
    }
    fclose(fp);
    return 0;
}

void show(node *head)
{
    system("cls");
    int i = 1;
    node *ptr = head;

    if (isempty(ptr))
    {
        printf("LIST EMPTY\n");
        return;
    }

    while (ptr != NULL)
    {
        int ave = (ptr->g1 + ptr->g2 + ptr->g3) / 3;

        printf("%d). Name: %-10s G1:%-5d G2:%-5d G3:%-5d Ave:%-5d %s\n",
               i,
               ptr->name,
               ptr->g1,
               ptr->g2,
               ptr->g3,
               ave,
               ave >= 75 ? "PASSED" : "FAILED");
        ptr = ptr->link;
        i++;
    }
}

void add(node **head)
{
    char tname[21];
    int tg1, tg2, tg3;

    system("cls");

    printf("Enter Name:");
    scanf(" %20[^\n]", tname);
    printf("Enter Grade 1:");
    scanf("%d", &tg1);
    printf("Enter Grade 2:");
    scanf("%d", &tg2);
    printf("Enter Grade 3:");
    scanf("%d", &tg3);

    node *newnode = malloc(sizeof(node));
    strcpy(newnode->name, tname);
    newnode->g1 = tg1;
    newnode->g2 = tg2;
    newnode->g3 = tg3;
    newnode->link = NULL;

    if (*head == NULL)
    {
        *head = newnode;
    }
    else
    {
        node *ptr = *head;
        while (ptr->link != NULL)
        {
            ptr = ptr->link;
        }
        ptr->link = newnode;
    }

    printf("Record added successfully.\n");
}

void update(node *head)
{
    system("cls");
    char nameloc[21];
    node *ptr;

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    ptr = locate(head, nameloc);

    if (ptr == NULL)
    {
        printf("Not Found\n");
        return;
    }

    printf("Enter New Grade 1: ");
    scanf("%d", &ptr->g1);

    printf("Enter New Grade 2: ");
    scanf("%d", &ptr->g2);

    printf("Enter New Grade 3: ");
    scanf("%d", &ptr->g3);

    printf("Record Updated\n");
}

void delete(node **head)
{
    system("cls");
    char nameloc[21];
    node *ptr = *head, *prev = NULL;

    printf("Enter Name: ");
    scanf(" %20[^\n]", nameloc);

    while (ptr !=NULL && strcmp(ptr->name, nameloc) !=0) {
        prev = ptr;
        ptr = ptr->link;
    }

    if (isempty(ptr)) {
        printf("Not Found");
        return;
    }

    if (prev == NULL) 
    {
        *head = ptr->link;
    }
    else 
    {
        prev->link = ptr->link;
    }

    free(ptr);
    printf("Record Deleted");
}

node *locate(node *head, char nameloc[])
{
    node *ptr = head;

    while (ptr != NULL)
    {
        if (strcmp(ptr->name, nameloc) == 0)
        {
            return ptr;
        }
        ptr = ptr->link;
    }
    return NULL;
}


int isempty(node *ptr)
{
    if (ptr == NULL)
        return 1;
    else
        return 0;
}

void menu(node **head)
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
            show(*head);
            break;

        case 2:
            add(head);
            savefile(*head);
            break;

        case 3:
            update(*head);
            savefile(*head);
            break;

        case 4:
            delete(head);
            savefile(*head);
            break;

        case 5:
            printf("Exiting program\n");
            break;
        }

        system("pause");
    }
}