#include <stdio.h>
#include <stdlib.h>
#define max 100

FILE *fp1;
FILE *fp2;

int main()
{

    fp1 = fopen("prelimsfile1.txt", "r");
    fp2 = fopen("prelimsfile2.txt", "w");

    if (fp1 == NULL || fp2 == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }
    char name[max];
    int g1, g2, g3;

    while (fscanf(fp1, "%s %d %d %d", name, &g1, &g2, &g3) == 4)
    {
        int ave = (g1 + g2 + g3) / 3;
        if (ave >= 75) {
            fprintf(fp2, "%s %d %d %d AVERAGE:%d REMARKS: %s\n", name, g1, g2, g3, ave, ave ? "PASSED" : "FAILED");
        }
    }

    fclose(fp1);
    fclose(fp2);

    system("pause");
    return 0;
}