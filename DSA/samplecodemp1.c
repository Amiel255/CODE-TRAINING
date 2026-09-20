#include <stdio.h>
#include <stdlib.h>
#define MAX 10
//GLOBAL
typedef struct list {
  int data[MAX];
  int last;
} LIST;
LIST L;//Structure varible with components data[] and last
//UDFs
void makenull();
void insert(int x);
void del(int x);
void display();
int isfull();
int isempty();
int locate(int x);
int locatePos(int x);
int menu();
 
int main(){
int x;
makenull();
while (1){//infinite loop
    switch(menu()){
    case 1 : system("cls");printf("Input x: ");scanf("%d",&x);insert(x);break;
    case 2 : system("cls");printf("Input x: ");scanf("%d",&x);del(x);break;
    case 3 : display();break;
    case 4 : exit(0);
    default: printf("Invalid choice.\n");system("pause");
    }
}
return 0;
}
 
void makenull(){
  L.last = -1;
}
void insert(int x){
int i,p;
if (isfull()){
    printf("List is full.\n");
    system("pause");
}
else {
    p = locatePos(x);
    for (i=L.last;i>=p;i--)
        L.data[i+1]=L.data[i];
    L.data[p]=x;
    L.last++;
}
}
void del(int x){
if (isempty()){
    printf("Nothing to delete.\n");
    system("pause");
}
else {
    int p = locate(x);
    if (p<0){
        printf("Not found.\n");
        system("pause");
    }
    else {
        for (int i=p;i<L.last;i++){
            L.data[i] = L.data[i+1];
        }
        L.last--;
    }
}
}
void display(){
system("cls");
printf("The List contains:\n");
for (int i=0;i<=L.last;i++){
    printf("%d.) %d\n",i+1,L.data[i]);
}
system("pause");
}
int isfull(){
  return (L.last==MAX-1);
}
int isempty(){
  return (L.last==-1);
}
int locate(int x){
for (int i=0;i<L.last;i++)
    if(x==L.data[i])
       return i;
return -1;//not found
}
 
int menu(){
int op;
system("cls");
printf("MENU\n");
printf("1. Add a data\n");
printf("2. Delete a data\n");
printf("3. Display\n");
printf("4. Quit\n");
printf("\nSelect(1-4): ");
scanf("%d",&op);
return op;
}
int locatePos(int x){
for (int i=0;i<=L.last;i++)
    if (x<L.data[i])
        return i;
return L.last+1;
}