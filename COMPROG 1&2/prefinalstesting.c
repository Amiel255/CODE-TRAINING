#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100      // max lines
#define LEN 50       // max chars per line

// ---------- SORT RULE (qsort comparator) ----------
int compareLinesAZ(const void *a, const void *b)
{
    const char *lineA = (const char *)a;
    const char *lineB = (const char *)b;
    return strcmp(lineA, lineB);
}

// ---------- FILE LOAD ----------
int loadFile(char records[MAX][LEN], const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;

    int recordCount = 0;
    while (recordCount < MAX && fgets(records[recordCount], LEN, file))
    {
        records[recordCount][strcspn(records[recordCount], "\n")] = '\0'; // remove newline

        if (records[recordCount][0] != '\0')
            recordCount++; // skip empty lines
    }

    fclose(file);
    return recordCount;
}

// ---------- SHOW ----------
void showRecords(char records[MAX][LEN], int recordCount)
{
    if (recordCount == 0)
    {
        printf("\n(No records)\n");
        return;
    }

    printf("\nRecords:\n");
    for (int i = 0; i < recordCount; i++)
    {
        printf("%d) %s\n", i + 1, records[i]);
    }
}

// ---------- ADD ----------
void addRecord(char records[MAX][LEN], int *recordCount)
{
    if (*recordCount >= MAX)
    {
        printf("List full.\n");
        return;
    }

    printf("Enter new record (example: Amiel 95): ");
    fgets(records[*recordCount], LEN, stdin);
    records[*recordCount][strcspn(records[*recordCount], "\n")] = '\0';

    // validate format: Name Grade
    char nameCheck[LEN];
    int gradeCheck;
    if (sscanf(records[*recordCount], "%49s %d", nameCheck, &gradeCheck) != 2)
    {
        printf("Invalid format. Please use: Name Grade\n");
        return; // don't increase recordCount
    }

    (*recordCount)++;
}

// ---------- DELETE ----------
void deleteRecord(char records[MAX][LEN], int *recordCount)
{
    int itemNumber;
    showRecords(records, *recordCount);

    printf("Enter item number to delete: ");
    scanf("%d", &itemNumber);
    getchar(); // remove leftover newline

    if (itemNumber < 1 || itemNumber > *recordCount)
    {
        printf("Invalid.\n");
        return;
    }

    int deleteIndex = itemNumber - 1;

    // shift left
    for (int i = deleteIndex; i < *recordCount - 1; i++)
    {
        strcpy(records[i], records[i + 1]);
    }

    (*recordCount)--;
}

// ---------- REPLACE ----------
void replaceRecord(char records[MAX][LEN], int recordCount)
{
    int itemNumber;
    showRecords(records, recordCount);

    printf("Enter item number to replace: ");
    scanf("%d", &itemNumber);
    getchar(); // remove leftover newline

    if (itemNumber < 1 || itemNumber > recordCount)
    {
        printf("Invalid.\n");
        return;
    }

    printf("Enter new record (example: Rolly 89): ");
    fgets(records[itemNumber - 1], LEN, stdin);
    records[itemNumber - 1][strcspn(records[itemNumber - 1], "\n")] = '\0';

    // validate format: Name Grade
    char nameCheck[LEN];
    int gradeCheck;
    if (sscanf(records[itemNumber - 1], "%49s %d", nameCheck, &gradeCheck) != 2)
    {
        printf("Invalid format. Please replace again using: Name Grade\n");
    }
}

// ---------- SORT ----------
void sortAZ(char records[MAX][LEN], int recordCount)
{
    if (recordCount < 2)
    {
        printf("Need at least two records to sort.\n");
        return;
    }

    qsort(records, recordCount, sizeof(records[0]), compareLinesAZ);
    printf("\nSORTED\n");
}

// ---------- STATS (highest, lowest, average) ----------
void computeStats(char records[MAX][LEN], int recordCount,
                  int *highest, int *lowest, float *average)
{
    int sum = 0;
    int validCount = 0;

    *highest = 0;
    *lowest = 0;
    *average = 0.0f;

    for (int i = 0; i < recordCount; i++)
    {
        char name[LEN];
        int grade;

        // extract: Name Grade
        if (sscanf(records[i], "%49s %d", name, &grade) == 2)
        {
            if (validCount == 0)
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
            validCount++;
        }
    }

    if (validCount > 0)
        *average = (float)sum / validCount;
}

// ---------- SAVE REPORT (sorted list + stats) ----------
void saveSummary(char records[MAX][LEN], int recordCount, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: cannot write file.\n");
        return;
    }

    fprintf(file, "Alphabetically Sorted Names:\n\n");
    for (int i = 0; i < recordCount; i++)
    {
        fprintf(file, "%s\n", records[i]);
    }

    int highest, lowest;
    float average;
    computeStats(records, recordCount, &highest, &lowest, &average);

    fprintf(file, "\nHighest Score: %d\n", highest);
    fprintf(file, "Lowest Score: %d\n", lowest);
    fprintf(file, "Average Score: %.1f\n", average);

    fclose(file);
}

// ---------- MAIN MENU ----------
int main()
{
    char records[MAX][LEN];
    int recordCount = loadFile(records, "students.txt");
    int choice;

    while (1)
    {
        printf("\n1) Show\n2) Add\n3) Delete\n4) Replace\n5) Sort A-Z\n6) Save & Exit\nChoose: ");
        scanf("%d", &choice);
        getchar(); // remove leftover newline

        if (choice == 1)
            showRecords(records, recordCount);
        else if (choice == 2)
            addRecord(records, &recordCount);
        else if (choice == 3)
            deleteRecord(records, &recordCount);
        else if (choice == 4)
            replaceRecord(records, recordCount);
        else if (choice == 5)
            sortAZ(records, recordCount);
        else if (choice == 6)
        {
            // ensure saved file is alphabetical
            sortAZ(records, recordCount);
            saveSummary(records, recordCount, "quiz_summary.txt");
            break;
        }
        else
            printf("Invalid.\n");
    }

    return 0;
}
