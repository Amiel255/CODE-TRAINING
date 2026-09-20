#include <stdio.h>

int main(){

FILE *fp1 = fopen("geezer1.txt", "r");
FILE *fp2 = fopen("geezer2.txt", "w");

if (fp1 == NULL || fp2 == NULL){

    printf("INVALID");
    return;
}

char name[69];
int q1, q2, q3;

while(fscanf(fp1, "%s, %d, %d, %d", name, &q1, &q2, &q3) == 4);
 int  ave = (q1+q2+q3)/ 3;

if (ave >= 75){
    fprintf(fp2, "%s, %d, %d, %d", name, q1, q2, q3);
}

fclose(fp1);
fclose(fp2);


return 0;
}
