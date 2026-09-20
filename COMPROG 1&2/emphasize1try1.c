#include <stdio.h>
#include <stdlib.h>
int main()
{
    char name[50];
    printf("Enter your Name:");
    scanf("%s", &name);
    int birthyear;
    printf("Enter your birth year:");
    scanf("%d", &birthyear);
    int yearthisdate = 2025;
    int yourage =  yearthisdate - birthyear;


    printf("Hello %s, your age is %d\n\n", name, yourage);

    system("pause");
    return 0;
}