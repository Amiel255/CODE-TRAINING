#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define LEN 50

int compare_strings_az(const void *a, const void *b)
{
    const char *student_a = (const char *)a;
    const char *student_b = (const char *)b;
    return strcmp(student_a, student_b);
}

int loadFile(char items[MAX][LEN], const char *filename)
{
    FILE *filepointer = fopen(filename, "r");
    if (filepointer == NULL)
        return 0;

    int count = 0;
    while (count < MAX && fgets(items[count], LEN, filepointer))
    {
        items[count][strcspn(items[count], "\n")] = '\0'; // to remove \n or remove newline. checks for string 2 reject to keep initial str1
        if (items[count][0] != '\0')
            count++; // skip empty lines
    }
    fclose(filepointer);
    return count;
}

void show(char items[MAX][LEN], int count)
{
    if (count == 0)
    {
        printf("\n(No items)\n");
        return;
    }
    printf("\nItems:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d) %s\n", i + 1, items[i]);
    }
}

void add(char items[MAX][LEN], int *count)
{
    if (*count >= MAX)
    {
        printf("List full.\n");
        return;
    }
    printf("Enter new item (example: Amiel 95): ");
    fgets(items[*count], LEN, stdin);
    items[*count][strcspn(items[*count], "\n")] = '\0';

    // Optional: quick validation so bad lines won't break stats
    char tempName[LEN];
    int tempGrade;
    if (sscanf(items[*count], "%49s %d", tempName, &tempGrade) != 2)
    {
        printf("Invalid format. Please use: Name Grade\n");
        return; // do not increase count
    }

    (*count)++;
}

void deleteItem(char items[MAX][LEN], int *count)
{
    int pos;
    show(items, *count);
    printf("Enter item number to delete: ");
    scanf("%d", &pos);
    getchar(); // remove leftover newline

    if (pos < 1 || pos > *count)
    {
        printf("Invalid.\n");
        return;
    }

    int index = pos - 1;
    for (int i = index; i < *count - 1; i++)
    {
        strcpy(items[i], items[i + 1]);
    }
    (*count)--;
}

void replaceItem(char items[MAX][LEN], int count)
{
    int pos;
    show(items, count);
    printf("Enter item number to replace: ");
    scanf("%d", &pos);
    getchar(); // remove leftover newline

    if (pos < 1 || pos > count)
    {
        printf("Invalid.\n");
        return;
    }

    printf("Enter new text (example: Rolly 89): ");
    fgets(items[pos - 1], LEN, stdin);
    items[pos - 1][strcspn(items[pos - 1], "\n")] = '\0';
}

void sortAZ(char items[MAX][LEN], int count)
{
    if (count < 2)
    {
        printf("Need at least two items to sort.\n");
        return;
    }

    qsort(items, count, sizeof(items[0]), compare_strings_az);
    printf("\nSORTED\n");
  
}

// NEW: compute highest, lowest, average from lines like "Name 89"
void computeStats(char items[MAX][LEN], int count, int *highest, int *lowest, float *average)
{
    int sum = 0;
    int valid = 0;

    *highest = 0;
    *lowest = 0;
    *average = 0.0f;

    for (int i = 0; i < count; i++)
    {
        char name[LEN];
        int grade;

        // Extract name + grade from the line
        if (sscanf(items[i], "%49s %d", name, &grade) == 2)
        {
            if (valid == 0)
            {
                *highest = grade;
                *lowest = grade;
            }
            else
            {
                if (grade > *highest) *highest = grade;
                if (grade < *lowest)  *lowest = grade;
            }

            sum += grade;
            valid++;
        }
    }

    if (valid > 0)
        *average = (float)sum / valid;
}

// NEW: save list + stats to file
void saveSummary(char items[MAX][LEN], int count, const char *filename)
{
    FILE *filepointer = fopen(filename, "w");
    if (filepointer == NULL)
    {
        printf("Error: cannot write file.\n");
        return;
    }

    int highest, lowest;
    float average;
    computeStats(items, count, &highest, &lowest, &average);

    // --- DISPLAY ON SCREEN ---
    printf("\nAlphabetically Sorted Names:\n\n");
    for (int i = 0; i < count; i++)
        printf("%s\n", items[i]);

    printf("\nHighest Score: %d\n", highest);
    printf("Lowest Score: %d\n", lowest);
    printf("Average Score: %.1f\n", average);

    // --- WRITE TO FILE ---
    fprintf(filepointer, "Alphabetically Sorted Names:\n\n");
    for (int i = 0; i < count; i++)
        fprintf(filepointer, "%s\n", items[i]);

    fprintf(filepointer, "\nHighest Score: %d\n", highest);
    fprintf(filepointer, "Lowest Score: %d\n", lowest);
    fprintf(filepointer, "Average Score: %.1f\n", average);

    fclose(filepointer);

    printf("\nSaved to: %s\n", filename);
}


int main()
{
    char items[MAX][LEN];
    int count = loadFile(items, "students.txt");
    int choice;

    while (1)
    {
        printf("\n1) Show\n2) Add\n3) Delete\n4) Replace\n5) Sort A-Z\n6) Save & Exit\nChoose: ");
        scanf("%d", &choice);
        getchar(); // remove leftover newline

        if (choice == 1)
            show(items, count);
        else if (choice == 2)
            add(items, &count);
        else if (choice == 3)
            deleteItem(items, &count);
        else if (choice == 4)
            replaceItem(items, count);
        else if (choice == 5)
            sortAZ(items, count);
        else if (choice == 6)
        {
            // If you want it ALWAYS saved sorted, do this before saving:
            sortAZ(items, count);

            saveSummary(items, count, "quiz_summary.txt");
            break;
        }
        else
            printf("Invalid.\n");
    }
    system("pause");
    return 0;
}
