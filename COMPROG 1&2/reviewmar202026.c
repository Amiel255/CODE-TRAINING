#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char name[50];
    int age;
    struct node *link;
} node;

void count_of_nodes (node *head);
void print_of_nodes (node *head);
void add_at_end (node *head, char nam[50], int ag);

int main()
{
    char nam[50];
    int ag;
    node *head = malloc(sizeof(node));
    strcpy(head->name, "Amiel");
    head->age = 18;
    head->link = NULL;

    node *current = malloc(sizeof(node));
    current->age = 19;
    strcpy(current->name, "Keith");
    current->link = NULL;
    head->link = current;

    current = malloc(sizeof(node));
    strcpy(current->name, "Padilla");
    current->age = 20;
    current->link = NULL;
    head->link->link = current;



    printf("%s %d\n", head->name, head->age);
    printf("%p %p\n", head->name, head->link);

    printf("%s %d\n", head->link->name, head->link->age);
    printf("%p %p\n", head->link->name, head->link->link);

    printf("Please enter name:");
    scanf("%[^\n]", nam);
    printf("Enter age:");
    scanf("%d", &ag);

    add_at_end(head, nam, ag);
    count_of_nodes(head);
    print_of_nodes(head);

    system("pause");
    return 0;
}

void count_of_nodes (node *head) {
    int count = 0;
    if (head == NULL) {
        printf("LIST IS EMPTY!");
    }
    node *ptr = NULL;
    ptr = head;

    while (ptr != NULL) {
        count++;
        ptr = ptr->link;
    }

    printf("\n\n%d\n", count);
}

void print_of_nodes (node *head) {
    int count = 0;
    if (head == NULL) {
        printf("LIST IS EMPTY!");
    }
    node *ptr = NULL;
    ptr = head;

    while (ptr != NULL) {
        printf("%s %d\n", ptr->name, ptr->age);
        ptr = ptr->link;
    }
}

void add_at_end (node *head, char nam[50], int ag) {
    node *temp, *ptr;
    
    temp = (node*)malloc(sizeof(node));

    strcpy(temp->name, nam);
    temp->age = ag;
    temp->link = NULL;

    while (ptr->link !=NULL) {
        ptr = ptr->link;
    }

    ptr->link = temp;
}