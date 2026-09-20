#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

typedef struct {
    char name[50];
    int age;
} student;

student list; 
int main()
{
    int i, j, oldest = 0;
    char oldestname[50];
    fp = fopen("quiz.txt", "r");

    if (fp == NULL) {
        printf("INVALID");
        system("pause");
        return 0;
    }

    while (fscanf(fp, "%[^,], %d", list.name, &list.age)== 2) {
        printf("%s, %d", list.name, list.age);

        if (list.age > oldest) {
            oldest = list.age;
            strcpy(oldestname, list.name);
        }
    }

    fclose(fp);

    printf("\n%s Age = %d is the oldest",oldestname, oldest);
    system("pause");
    return 0;
}