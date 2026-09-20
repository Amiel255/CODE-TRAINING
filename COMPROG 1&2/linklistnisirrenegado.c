#include <stdio.h>
#include <malloc.h>
// SELF REFERENTIAL STRUCTURE
typedef struct Node
{
    char name[50];
    int age;
    struct Node *next;
} LINK;
LINK *head;
// UDFs
void init();
void add(char n[], int ag);
void del(char n[]);
void display();
int menu();

int main()
{
    int ag;
    char nm[50];
    init();
    while (1)
    {
        switch (menu())
        {
        case 1:
            printf("Input name: ");
            scanf("%s", nm);
            printf("Input age: ");
            scanf("%d", &ag);
            add(nm, ag);
            break;
        case 2:
            printf("Input name: ");
            scanf("%s", nm);
            del(nm);
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        }
    }
    return 0;
}
void init()
{
    head = NULL;
}
void add(char n[], int ag)
{
    LINK *p, *q, *newNode;
    p = q = head;
    newNode = (LINK *)malloc(sizeof(LINK));
    strcpy(newNode->name, n);
    newNode->age = ag;
    // hanapin ang position ng x
    while (p != NULL)
    {
        q = p;
        p = p->next;
    }
    if (p == head)
        head = newNode;
    else
        q->next = newNode;

    newNode->next = p;
}
void del(char n[])
{
    LINK *p, *q;
    p = q = head;
    while (p != NULL && strcmp(n, p->name) != 0)
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("Not found.\n");
        system("pause");
        return;
    }
    else
    {
        if (p == head) // first element
            head = head->next;
        else
            q->next = p->next;
        free(p);
    }
}
void display()
{
    int i = 1;
    LINK *p = head;
    system("cls");
    printf("NAME\t\tAGE\t\tREMARKS\n");
    while (p != NULL)
    {
        printf("%d.) %s\t\t%d\t\t%s\n", i++, p->name, p->age, (p->age >= 18) ? "ADULT" : "MINOR");
        p = p->next;
    }
    system("pause");
}
int menu()
{
    int op;
    system("cls");
    printf("Menu\n");
    printf("1. Add Record\n");
    printf("2. Delete Record\n");
    printf("3. Display All\n");
    printf("4. Exit\n");
    printf("Select[1-4]: ");
    scanf("%d", &op);
    return op;
}