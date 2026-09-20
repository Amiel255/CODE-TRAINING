#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int menu();
int add();
int Mul();
int Sub();
int Div();

int main() {
    srand(time(NULL));

    while(1) {
            system("cls");

        switch(menu()) {


            case 1: add(); system("pause"); break;
            case 2: Mul(); system("pause"); break;
            case 3: Sub(); system("pause"); break;
            case 4: Div(); system("pause"); break;
            case 5: exit(0);
            default: printf("Invalid choice kulit mo shunga\n"); system("pause"); break;
        }
    }
    return 0;
}

int add() {
    int i, cor = 0, a, b, ans;
    int items = 5;

    for (i = 0; i < items; i++) {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;

        printf("\n%d.) What is %d + %d? ", i+1, a, b);
        scanf("%d", &ans);

        if (ans == a + b) {
            printf("Correct!\n");
            cor++;
        } else {
            printf("Malasssssss!! The correct answer is %d\n", a+b);
        }
    }

    printf("\nYou got %d correct answers out of %d\n", cor, items);
    system("pause");
    return 0;

}

int Mul(){
    int i, cor = 0, a, b, ans;
    int items = 5;

    for (i = 0; i < items; i++) {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;

        printf("\n%d.) What is %d x %d? ", i+1, a, b);
        scanf("%d", &ans);

        if (ans == a * b) {
            printf("Correct!\n");
            cor++;
        } else {
            printf("Malasssssss!! The correct answer is %d\n", a*b);
        }
    }

    printf("\nYou got %d correct answers out of %d\n", cor, items);
    system("pause");
    return 0;

     }






int Sub(){
     int i, cor = 0, a, b, ans;
    int items = 5;

    for (i = 0; i < items; i++) {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;

        if(b>a){
         int temp = a;
             a=b;
            b=temp;

        }

        printf("\n%d.) What is %d - %d? ", i+1, a, b);
        scanf("%d", &ans);

        if (ans == a - b) {
            printf("Correct!\n");
            cor++;
        } else {
            printf("Malasssssss!! The correct answer is %d\n", a-b);
        }
    }

    printf("\nYou got %d correct answers out of %d\n", cor, items);
    system("pause");
    return 0;

    }


int Div(){
    int i, cor = 0, a, b, ans;
    int items = 5;
    int result;

    for (i = 0; i < items; i++) {
        b = rand() % 9 + 1;
        result = rand() % 10 + 1;
        a=b*result;

        printf("\n%d.) What is %d / %d? ", i+1, a, b);
        scanf("%d", &ans);

        if (ans == result) {
            printf("Correct!\n");
            cor++;
        } else {
            printf("Malasssssss! The correct answer is %d\n", result);
        }
    }

    printf("\nYou got %d correct answers out of %d\n", cor, items);
    system("pause");
    return 0;

    }

int menu(){
    int ch;
    printf("\n--Menu--\n");
    printf("1. Addition\n");
    printf("2. Multiplication\n");
    printf("3. Subtraction\n");
    printf("4. Division\n");
    printf("5. Exit\n");
    printf("Enter choice: ");
    scanf("%d",&ch);
    return ch;
    system("pause");
}