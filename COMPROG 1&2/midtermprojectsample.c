#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define MAX 50
#define MAXX 5
typedef struct players  //STRUCT FOR LOGIN CREDENTIALS
{
    char user[31];  //USER ID / IGN
    char pass[31];  //USER PASSWORD
} PLAY;
PLAY rem[MAX];

typedef struct leaders  //STRUCT FOR SCORE LEADERBOARDS
{
    char ign[31];   //USER ID / IGN
    float addS;     //ADDITION SCORE
    float subS;     //SUBTRACTION SCORE
    float mulS;     //MULTIPLICATION SCORE
    float divS;     //DIVISION SCORE
    float aveS;     //OVERALL SCORE
} LEAD;
LEAD pts[MAX];

int marker;
int item = 5;   //WILL BE USED FOR THE NUMBER OF QUESTIONS PER DIFFICULTY IN ALL OPERATIONS
float aAddE, aAddM, aAddH, addAve;  //ADDITION VARIABLES FOR AVERAGE (EASY, MEDIUM, HARD, AND OVERALL AVERAGE)
float aSubE, aSubM, aSubH, subAve;  //SUBTRACTION VARIABLES FOR AVERAGE (EASY, MEDIUM, HARD, AND OVERALL AVERAGE)
float aMulE, aMulM, aMulH, mulAve;  //MULTIPLICATION VARIABLES FOR AVERAGE (EASY, MEDIUM, HARD, AND OVERALL AVERAGE)
float aDivE, aDivM, aDivH, divAve;  //DIVISION VARIABLES FOR AVERAGE (EASY, MEDIUM, HARD, AND OVERALL AVERAGE)

void init();    //INITIALIZATION OF MARKER FOR THE ARRAY OF STRUCTURE
int isFull();   //FUNCTION THAT WILL VALIDATE IF THE ARRAY IS FULL
void create(LEAD *pt);  //ACCOUNT REGISTRATION FUNCTION
void getScore(LEAD pt); //FUNCTION THAT WILL RECORD DATA IN ARRAY OF STRUCTURE
int locate(char n[31]); //USED TO LOCATE THE USER ID / IGN
void login(char n[31]); //GAME LOGIN FUNCTION
void menu(char n[31]);  //HOME GAME INTERFACE
void displayAve();  //DISPLAY OF ALL-TIME LEADERS
void displayAdd();  //DISPLAY OF ADDITION LEADERBOARDS
void displaySub();  //DISPLAY OF SUBTRACTION LEADERBOARDS
void displayMul();  //DISPLAY OF MULTIPLICATION LEADERBOARDS
void displayDiv();  //DISPLAY OF DIVISION LEADERBOARDS
void game(char n[31]);  //GAME INTERFACE WHEN THE USER STARTS THE GAME
float average(float a, float b, float c, float d);  //FUNCTION THAT WILL COMPUTE THE OVERALL AVERAGE

void addition(char n[31]);  //ADDITION INTERFACE
void addEasy();
void addMedium();
void addHard();

void subtraction(char n[31]);   //SUBTRACTION INTERFACE
void subEasy();
void subMedium();
void subHard();

void multiplication(char n[31]);    //MULTIPLICATION INTERFACE
void mulEasy();
void mulMedium();
void mulHard();

void division(char n[31]);  //DIVISION INTERFACE
void divEasy();
void divMedium();
void divHard();

void save();    //FUNCTION TO SAVE THE RECORDS OF PLAYERS TO TEXT FILE FROM THE ARRAY
void retrieve();    //FUNCTION TO RETRIEVE THE RECORDS OF PLAYERS FROM THE TEXT FILE TO THE ARRAY
void gotoxy(int x, int y);
void setColor(int ForgC);

int main()  //MAIN INTERFACE, THIS WILL DISPLAY ONCE YOU RUN THE PROGRAM.     REGISTER AND LOGIN INTERFACE
{
    LEAD y;
    int i, j, op;
    init();     //INITIALIZING THE MARKER FOR THE ARRAY
    retrieve(); //THIS WILL RETRIEVE THE RECORDS OF PLAYERS FROM THE TEXT FILE TO THE ARRAY
    while (1)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }
        gotoxy(8,23); setColor(3); printf("PROGRAMMED BY:");
        gotoxy(8,24); setColor(6); printf("JERIMI F. ORALE");
        gotoxy(8,25); setColor(6); printf("BSIT - 1A");
        gotoxy(99,23); setColor(4); printf("TECHNOLOGICAL");
        gotoxy(95,24); setColor(4); printf("UNIVERSITY OF THE");
        gotoxy(101,25); setColor(4); printf("PHILIPPINES");
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(34,8); setColor(6); printf("------------[ 1 ]");
        gotoxy(34,9); setColor(6); printf("|               |");
        gotoxy(39,9); setColor(3); printf("REGISTER");
        gotoxy(34,10); setColor(6); printf("-----------------");
        gotoxy(69,8); setColor(6); printf("[ 2 ]------------");
        gotoxy(69,9); setColor(6); printf("|               |");
        gotoxy(75,9); setColor(3); printf("LOGIN");
        gotoxy(69,10); setColor(6); printf("-----------------");
        gotoxy(50,15); setColor(6); printf("-------[ 3 ]--------");
        gotoxy(50,16); setColor(6); printf("|                  |");
        gotoxy(53,16); setColor(3); printf("CLOSE  PROGRAM");
        gotoxy(50,17); setColor(6); printf("--------------------");
        gotoxy(45,26); setColor(6); printf("Please select from (1-3) only: ");
        scanf("%d",&op);
        switch(op)
        {
            case 1: create(&y); getScore(y);     //WILL PROCEED TO ACCOUNT REGISTRATION INTERFACE
                    gotoxy(44, 23); setColor(6);
                    printf("Account is created successfully.");
                    gotoxy(47, 26); setColor(6);
                    system("pause"); break;
            case 2: login(y.ign); break;        //WILL PROCEED TO GAME LOGIN INTERFACE
            case 3: system("cls"); exit(0);     //EXIT THE PROGRAM
            default: break;
        }
    }
    return 0;
}

void init()     //INITIALIZATION OF MARKER FOR THE ARRAY OF STRUCTURE
{
    marker = -1;
}

int isFull()    //FUNCTION THAT WILL VALIDATE IF THE ARRAY IS FULL
{
    return(marker==MAX-1);
}

void create(LEAD *pt)   //ACCOUNT REGISTRATION FUNCTION
{
    system("cls");
    PLAY st;
    FILE *fp;
    FILE *point;
    float a = 0, s = 0, m = 0, d = 0, av = 0;   //INITIALIZING SCORE OF THE NEW REGISTERED PLAYER
    int i, j;
    for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }
    gotoxy(47,1); setColor(6); printf("--------------------------");
    gotoxy(47,2); setColor(6); printf("|                        |");
    gotoxy(50,2); setColor(3); printf("ACCOUNT REGISTRATION");
    gotoxy(47,3); setColor(6); printf("--------------------------");
    gotoxy(47,7); setColor(6); printf("--------------------------");
    gotoxy(47,8); setColor(6); printf("|                        |");
    gotoxy(50,8); setColor(3); printf("INPUT USER  ID | IGN");
    gotoxy(47,9); setColor(6); printf("--------------------------");
    gotoxy(47,11); setColor(7); scanf(" %s", pt->ign);                  //INPUT OF USER ID / IGN
    gotoxy(47,15); setColor(6); printf("--------------------------");
    gotoxy(47,16); setColor(6); printf("|                        |");
    gotoxy(53,16); setColor(3); printf("INPUT PASSWORD");
    gotoxy(47,17); setColor(6); printf("--------------------------");
    gotoxy(47,19); setColor(7); scanf(" %s", st.pass);                  //INPUT OF PASSWORD

    fp = fopen("player.txt","a");       //TEXT FILE FOR REGISTERED PLAYERS
    if (fp==NULL)
    {
        gotoxy(54, 23); setColor(6); printf("File error.");
        gotoxy(47, 26); setColor(6); system("pause");
    }
    else
    {
        fprintf(fp,"%s %s\n", pt->ign, st.pass);    //USER ID / IGN AND PASSWORD WILL APPPEND TO TEXT FILE  "player.txt"
    }
    fclose(fp);

    point = fopen("leaders.txt","a");   //TEXT FILE FOR PLAYERS SCORES
    if (fp==NULL)
    {
        gotoxy(54, 23); setColor(6); printf("File error.");
        gotoxy(47, 26); setColor(6); system("pause");
    }
    else
    {
        fprintf(fp,"%s\n%f %f %f %f %f\n", pt->ign, a, s, m, d, av);    //USER ID / IGN AND INITIALIZED SCORES WILL APPPEND TO TEXT FILE "leaders.txt"
    }
    fclose(point);

    pt->addS = a;       //GETTING THE INITIALIZED VALUE TO POINTER pt
    pt->subS = s;
    pt->mulS = m;
    pt->divS = s;
    pt->aveS = av;
}

void getScore(LEAD pt)  //FUNCTION THAT WILL RECORD DATA IN ARRAY OF STRUCTURE
{
    if (isFull())
    {
        gotoxy(46, 23); setColor(6); printf("The system is already full.");
        gotoxy(47, 26); setColor(6); system("pause");
    }
    else
    {
        marker ++;
        pts[marker] = pt;
    }
}

int locate(char n[31])      //LOCATING OF USER ID / IGN IN THE ARRAY
{
    int i;
    for (i=0;i<=marker;i++)
    {
        if (strcmp(pts[i].ign, n) == 0)
        return (i);
    }
    return -1;
}

void login(char n[31])      //GAME LOGIN FUNCTION
{
    system("cls");
    FILE *fp = fopen("player.txt", "rb");       //WILL READ THE TEXT FILE CONTAINING PLAYERS' USER ID AND PASSWORD
    PLAY x;
    LEAD y;
    int check = 0;
    int i, j, p;
    char pw[31];
    for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }

    fflush(stdin);
    gotoxy(52,1); setColor(6); printf("----------------");
    gotoxy(52,2); setColor(6); printf("|              |");
    gotoxy(55,2); setColor(3); printf("GAME LOGIN");
    gotoxy(52,3); setColor(6); printf("----------------");
    gotoxy(47,7); setColor(6); printf("--------------------------");
    gotoxy(47,8); setColor(6); printf("|                        |");
    gotoxy(50,8); setColor(3); printf("ENTER USER  ID | IGN");
    gotoxy(47,9); setColor(6); printf("--------------------------");
    gotoxy(47,11); setColor(7); scanf("%s", n);
    gotoxy(47,15); setColor(6); printf("--------------------------");
    gotoxy(47,16); setColor(6); printf("|                        |");
    gotoxy(53,16); setColor(3); printf("ENTER PASSWORD");
    gotoxy(47,17); setColor(6); printf("--------------------------");
    gotoxy(47,19); setColor(0); scanf("%s", pw);

    p = locate(n);      //LOCATING THE ENTERED USER ID IN ARRAY AND PASSING "n" INTO "menu(char n[31])" FUNCTION

    while(fscanf(fp, "%s %s\n", rem->user, rem->pass)!=EOF)     //SCANNING THE TEXT FILE
    {
        if(strcmp(n,rem->user)==0)
        {
            if(strcmp(pw, rem->pass)==0)
            {
                check = 1;
                gotoxy(53, 23); setColor(2); printf("Login Success!");
                gotoxy(47, 26); setColor(6); system("pause");
                menu(n);        //WILL PROCEED TO HOME GAME INTERFACE WHEN LOGIN SUCCESSFUL
                break;
            }
        }
        if(strcmp(n,rem->user)==0)
        {
            if(strcmp(pw, rem->pass)!=0)
            {
                check = 1;
                gotoxy(50, 23); setColor(4); printf("Incorrect  Password!");
                gotoxy(47, 26); setColor(6); system("pause");
                main();     //WILL RETURN TO REGISTER AND LOGIN INTERFACE IF THE PASSWORD IS INCORRECT
                break;
            }
        }
    }
    if(!check)
    {
        gotoxy(39,23); setColor(6); printf("It seems like you don't have an account yet.");
        gotoxy(40,24); setColor(6); printf("Redirecting to Account Registration Tab...");
        gotoxy(47, 26); setColor(6); system("pause");
        create(&y); getScore(y);        //WILL PROCEED TO ACCOUNT REGISTATION INTERFACE IF USER ID AND PASSWORD IS NOT DETECTED
        gotoxy(44, 23); setColor(6); printf("Account is created successfully.");
        gotoxy(47, 26); setColor(6); system("pause");
        main();
    }
    fclose(fp);
}

void menu(char n[31])       //WILL PROCEED HERE IF LOGIN SUCCESSFUL
{
    int e, i, j, p;
    LEAD y;
    p = locate(n);      //LOCATING THE "n" IN ARRAY FROM ENTERED USER ID IN LOGIN FUNCTION AND PASSING "n" INTO "game(char n[31])" FUNCTION
    while(e!=2)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }
        displayAve(); displayAdd(); displaySub(); displayMul(); displayDiv();       //DISPLAY OF LEADERBOARDS
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(6,3); setColor(3); printf("-----------------------");
        gotoxy(28,4); setColor(3); printf("|");
        gotoxy(6,4); setColor(3); printf("|     |");
        gotoxy(8,4); setColor(6); printf("IGN");
        gotoxy(14,4); setColor(7); printf("%s", n);
        gotoxy(6,5); setColor(3); printf("-----------------------");
        gotoxy(32,23); setColor(6); printf("--------------------[ 1 ]");
        gotoxy(32,24); setColor(6); printf("|                       |");
        gotoxy(39,24); setColor(3); printf("START  GAME");
        gotoxy(32,25); setColor(6); printf("-------------------------");
        gotoxy(63,23); setColor(6); printf("[ 2 ]--------------------");
        gotoxy(63,24); setColor(6); printf("|                       |");
        gotoxy(66,24); setColor(3); printf("LOGOUT | EXIT  GAME");
        gotoxy(63,25); setColor(6); printf("-------------------------");
        gotoxy(45, 26); setColor(6); printf("Please select from (1-2) only: ");
        scanf("%d",&e);
        switch(e)
        {
            case 1: game(n); break;     //PROCEED TO GAME
            case 2: save(); break;      //SAVE RECORDS IN ARRAY TO TEXT FILE
        }
    }
}

void displayAve()   //DISPLAY OF ALL-TIME LEADERS
{
    int i, j;
    LEAD y;
    gotoxy(49,4); setColor(6); printf("|                    |");
    gotoxy(52,4); setColor(3); printf("ALL-TIME LEADERS");
    gotoxy(49,5); setColor(6); printf("----------------------");
    for(i=0;i<=marker;i++)
    {
        for(j=i+1;j<=marker;j++)
        {
            if(pts[i].aveS<pts[j].aveS)     //SORTING OF ARRAY BASED ON OVERALL AVERAGE
            {
                y=pts[i];
                pts[i]=pts[j];
                pts[j]=y;
            }
        }
    }
    for (i=0;i<MAXX;i++)
    {
        gotoxy(49,6); setColor(6); printf("#1");
        gotoxy(49,7); setColor(4); printf("#2");
        gotoxy(49,8); setColor(5); printf("#3");
        gotoxy(49,9); setColor(3); printf("#4");
        gotoxy(49,10); setColor(3); printf("#5");
        gotoxy(52,6+i); setColor(7); printf("%s", pts[i].ign);
        gotoxy(64,6+i); setColor(6); printf("%6.2f%%", pts[i].aveS);
    }
}

void displayAdd()   //DISPLAY OF ADDITION LEADERBOARDS
{
    int i, j;
    LEAD y;
    gotoxy(7,12); setColor(3); printf("----------------------");
    gotoxy(7,13); setColor(3); printf("|                    |");
    gotoxy(14,13); setColor(6);printf("ADDITION");
    gotoxy(7,14); setColor(3); printf("----------------------");
    for(i=0;i<=marker;i++)
    {
        for(j=i+1;j<=marker;j++)
        {
            if(pts[i].addS<pts[j].addS)     //SORTING OF ARRAY BASED ON ADDITION OVERALL AVERAGE
            {
                y=pts[i];
                pts[i]=pts[j];
                pts[j]=y;
            }
        }
    }
    for(i=0;i<MAXX;i++)
    {
        gotoxy(7,15); setColor(6); printf("#1");
        gotoxy(7,16); setColor(4); printf("#2");
        gotoxy(7,17); setColor(5); printf("#3");
        gotoxy(7,18); setColor(3); printf("#4");
        gotoxy(7,19); setColor(3); printf("#5");
        gotoxy(10,15+i); setColor(7); printf("%s", pts[i].ign);
        gotoxy(22,15+i); setColor(6); printf("%6.2f%%", pts[i].addS);
    }
}

void displaySub()   //DISPLAY OF SUBTRACTION LEADERBOARDS
{
    int i, j;
    LEAD y;
    gotoxy(35,12); setColor(3); printf("----------------------");
    gotoxy(35,13); setColor(3); printf("|                    |");
    gotoxy(40,13); setColor(6); printf("SUBTRACTION");
    gotoxy(35,14); setColor(3); printf("----------------------");
    for(i=0;i<=marker;i++)
    {
        for(j=i+1;j<=marker;j++)
        {
            if(pts[i].subS<pts[j].subS)     //SORTING OF ARRAY BASED ON SUBTRACTION OVERALL AVERAGE
            {
                y=pts[i];
                pts[i]=pts[j];
                pts[j]=y;
            }
        }
    }
    for(i=0;i<MAXX;i++)
    {
        gotoxy(35,15); setColor(6); printf("#1");
        gotoxy(35,16); setColor(4); printf("#2");
        gotoxy(35,17); setColor(5); printf("#3");
        gotoxy(35,18); setColor(3); printf("#4");
        gotoxy(35,19); setColor(3); printf("#5");
        gotoxy(38,15+i); setColor(7); printf("%s", pts[i].ign);
        gotoxy(50,15+i); setColor(6); printf("%6.2f%%", pts[i].subS);
    }
}

void displayMul()   //DISPLAY OF MULTIPLICATION LEADERBOARDS
{
    int i, j;
    LEAD y;
    gotoxy(63,12); setColor(3); printf("----------------------");
    gotoxy(63,13); setColor(3); printf("|                    |");
    gotoxy(67,13); setColor(6); printf("MULTIPLICATION");
    gotoxy(63,14); setColor(3); printf("----------------------");
    for(i=0;i<=marker;i++)
    {
        for(j=i+1;j<=marker;j++)
        {
            if(pts[i].mulS<pts[j].mulS)     //SORTING OF ARRAY BASED ON MULTIPLICATION OVERALL AVERAGE
            {
                y=pts[i];
                pts[i]=pts[j];
                pts[j]=y;
            }
        }
    }
    for(i=0;i<MAXX;i++)
    {
        gotoxy(63,15); setColor(6); printf("#1");
        gotoxy(63,16); setColor(4); printf("#2");
        gotoxy(63,17); setColor(5); printf("#3");
        gotoxy(63,18); setColor(3); printf("#4");
        gotoxy(63,19); setColor(3); printf("#5");
        gotoxy(66,15+i); setColor(7); printf("%s", pts[i].ign);
        gotoxy(78,15+i); setColor(6); printf("%6.2f%%", pts[i].mulS);
    }
}

void displayDiv()   //DISPLAY OF DIVISION LEADERBOARDS
{
    int i, j;
    LEAD y;
    gotoxy(91,12); setColor(3); printf("----------------------");
    gotoxy(91,13); setColor(3); printf("|                    |");
    gotoxy(98,13); setColor(6); printf("DIVISION");
    gotoxy(91,14); setColor(3); printf("----------------------");
    for(i=0;i<=marker;i++)
    {
        for(j=i+1;j<=marker;j++)
        {
            if(pts[i].divS<pts[j].divS)     //SORTING OF ARRAY BASED ON DIVISION OVERALL AVERAGE
            {
                y=pts[i];
                pts[i]=pts[j];
                pts[j]=y;
            }
        }
    }
    for(i=0;i<MAXX;i++)
    {
        gotoxy(91,15); setColor(6); printf("#1");
        gotoxy(91,16); setColor(4); printf("#2");
        gotoxy(91,17); setColor(5); printf("#3");
        gotoxy(91,18); setColor(3); printf("#4");
        gotoxy(91,19); setColor(3); printf("#5");
        gotoxy(94,15+i); setColor(7); printf("%s", pts[i].ign);
        gotoxy(106,15+i); setColor(6); printf("%6.2f%%", pts[i].divS);
    }
}

void game(char n[31])   //GAME INTERFACE FUNCTION
{
    int i, j, op, p;
    p = locate(n);      //LOCATING THE "n" IN ARRAY FROM ENTERED USER ID IN LOGIN FUNCTION AND PASSING "n" INTO OPERATION FUNTIONS WITH "(char n[31])"
    while (op!=5)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }
        gotoxy(103,21); setColor(4); printf("TAKE NOTE:");
        gotoxy(84,22); setColor(6); printf("ONCE YOU CHOOSE AN OPERATION,");
        gotoxy(84,23); setColor(6); printf("YOUR EXISTING SCORE IN  THAT");
        gotoxy(84,24); setColor(6); printf("OPERATION WILL RESET BACK TO");
        gotoxy(108,25); setColor(4); printf("ZERO.");
        gotoxy(8,21); setColor(2); printf("SCORING RULE:");
        gotoxy(8,22); setColor(6); printf("YOUR AVERAGE SCORE IN  EACH");
        gotoxy(8,23); setColor(6); printf("OPERATION WILL  BE COMBINED");
        gotoxy(8,24); setColor(6); printf("TO GET YOUR  ALL-TIME SCORE");
        gotoxy(8,25); setColor(6); printf("IN ARITHMETIC PRACTICES.");
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(49,5); setColor(6); printf("----------------------");
        gotoxy(49,6); setColor(6); printf("|                    |");
        gotoxy(52,6); setColor(3); printf("CHOOSE OPERATION");
        gotoxy(49,7); setColor(6); printf("----------------------");
        gotoxy(27,10); setColor(6); printf("-----------------[ 1 ]");
        gotoxy(27,11); setColor(6); printf("|                    |");
        gotoxy(34,11); setColor(3); printf("ADDITION");
        gotoxy(27,12); setColor(6); printf("----------------------");
        gotoxy(27,15); setColor(6); printf("-----------------[ 2 ]");
        gotoxy(27,16); setColor(6); printf("|                    |");
        gotoxy(32,16); setColor(3); printf("SUBTRACTION");
        gotoxy(27,17); setColor(6); printf("----------------------");
        gotoxy(71,10); setColor(6); printf("[ 3 ]-----------------");
        gotoxy(71,11); setColor(6); printf("|                    |");
        gotoxy(75,11); setColor(3); printf("MULTIPLICATION");
        gotoxy(71,12); setColor(6); printf("----------------------");
        gotoxy(71,15); setColor(6); printf("[ 4 ]-----------------");
        gotoxy(71,16); setColor(6); printf("|                    |");
        gotoxy(78,16); setColor(3); printf("DIVISION");
        gotoxy(71,17); setColor(6); printf("----------------------");
        gotoxy(49,20); setColor(6); printf("--------[ 5 ]---------");
        gotoxy(49,21); setColor(6); printf("|                    |");
        gotoxy(54,21); setColor(3); printf("BACK TO MAIN");
        gotoxy(49,22); setColor(6); printf("----------------------");
        gotoxy(45,26); setColor(6); printf("Please select from (1-5) only: ");
        scanf("%d",&op);
        switch(op)
        {
            case 1: addition(n); break;         //PROCEED TO ADDITION INTERFACE AND PASSING "n"
            case 2: subtraction(n); break;      //PROCEED TO SUBTRACTION INTERFACE AND PASSING "n"
            case 3: multiplication(n); break;   //PROCEED TO MULTIPLICATION INTERFACE AND PASSING "n"
            case 4: division(n); break;         //PROCEED TO DIVISION INTERFACE AND PASSING "n"
            case 5: break;
        }
    }
    pts[p].aveS = average(pts[p].addS, pts[p].subS, pts[p].mulS, pts[p].divS);    /*UPDATES THE VALUE OF ARRAY OF STRUCTURE pts.aveS ONCE "p" or "n" IS LOCATED
                                                                                    AND USING float average FUNCTION TO COMPUTE THE AVERAGE*/
}

float average(float a, float b, float c, float d)   //FUNCTION TO COMPUTE OVERALL AVERAGE
{
    return((a+b+c+d)/4.0);
}

void addition(char n[31])   //ADDITION GAME INTERFACE
{
    int e, i, j, p;
    p = locate(n);      //LOCATING THE "n" IN ARRAY FROM ENTERED USER ID IN LOGIN FUNCTION
    while(e!=4)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }
        gotoxy(8,21); setColor(2); printf("SCORING RULE:");
        gotoxy(8,22); setColor(6); printf("YOUR AVERAGE SCORE IN  EACH");
        gotoxy(8,23); setColor(6); printf("DIFFICULTY WILL BE COMBINED");
        gotoxy(8,24); setColor(6); printf("TO  GET YOUR OVERALL  SCORE");
        gotoxy(8,25); setColor(6); printf("IN THIS OPERATION.");
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("ADDITION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(48,7); setColor(6); printf("------------------------");
        gotoxy(48,8); setColor(6); printf("|                      |");
        gotoxy(51,8); setColor(3); printf("CHOOSE  DIFFICULTY");
        gotoxy(48,9); setColor(6); printf("------------------------");
        gotoxy(36,12); setColor(6); printf("[ 1 ]-------");
        gotoxy(36,13); setColor(6); printf("|          |");
        gotoxy(40,13); setColor(2); printf("EASY");
        gotoxy(36,14); setColor(6); printf("------------");
        gotoxy(54,12); setColor(6); printf("---[ 2 ]----");
        gotoxy(54,13); setColor(6); printf("|          |");
        gotoxy(57,13); setColor(7); printf("MEDIUM");
        gotoxy(54,14); setColor(6); printf("------------");
        gotoxy(72,12); setColor(6); printf("-------[ 3 ]");
        gotoxy(72,13); setColor(6); printf("|          |");
        gotoxy(76,13); setColor(4); printf("HARD");
        gotoxy(72,14); setColor(6); printf("------------");
        gotoxy(49,20); setColor(6); printf("--------[ 4 ]---------");
        gotoxy(49,21); setColor(6); printf("|                    |");
        gotoxy(52,21); setColor(3); printf("CHOOSE OPERATION");
        gotoxy(49,22); setColor(6); printf("----------------------");
        gotoxy(45,26); setColor(6); printf("Please select from (1-4) only: ");
        scanf("%d",&e);
        switch(e)
        {
            case 1: addEasy(); break;
            case 2: addMedium(); break;
            case 3: addHard(); break;
            case 4: break;
        }
    }
    addAve = (aAddE+aAddM+aAddH)/3.0;       //GETS THE AVERAGE OF EASY, MEDIUM, AND HARD COMBINED
    pts[p].addS = addAve;                   //UPDATES THE VALUE OF LOCATED INDEX IN addS
}

void addEasy()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 10;
        y = rand() % 10;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("ADDITION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(2); printf("EASY");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(47,10); setColor(6); printf("--------------------------");
        gotoxy(47,11); setColor(6); printf("|                        |");
        gotoxy(48,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(54,11); setColor(2); printf("Sum of %d and %d? ", x, y);
        gotoxy(47,12); setColor(6); printf("--------------------------");
        gotoxy(53,13); setColor(6); printf("|            |");
        gotoxy(54,13); setColor(2); printf("  %d  +  %d ", x, y);
        gotoxy(53,14); setColor(6); printf("--------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(2); scanf("%d", &z);
        if(z == x+y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(46,20); setColor(4); printf("Oops! %d is the right answer.", x+y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aAddE = (float)s/item*100;      //GETS THE AVERAGE INTO GLOBAL VARIABLE aAddE TO ACCESS IT TO COMPUTE FOR THE ADDITION AVERAGE IN ADDITION INTERFACE FUNTION
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aAddE);
    gotoxy(60,23); setColor(2); printf("EASY");
    gotoxy(47,26); setColor(6); system("pause");
}

void addMedium()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 100+20;
        y = rand() % 100+20;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("ADDITION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(57,6); setColor(7); printf("MEDIUM");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(47,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(54,11); setColor(7); printf("Add  %d  and  %d", x, y);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(52,13); setColor(6); printf("|              |");
        gotoxy(53,13); setColor(7); printf("  %d  +  %d ", x, y);
        gotoxy(52,14); setColor(6); printf("----------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(7); scanf("%d", &z);
        if(z == x+y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(45,20); setColor(4); printf("Oops! %d is the right answer.", x+y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aAddM = (float)s/item*100;      //GETS THE AVERAGE INTO GLOBAL VARIABLE aAddM TO ACCESS IT TO COMPUTE FOR THE ADDITION AVERAGE IN ADDITION INTERFACE FUNTION
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(45,23); setColor(6); printf("Your Average (      ): %6.2f%%", aAddM);
    gotoxy(59,23); setColor(7); printf("MEDIUM");
    gotoxy(47,26); setColor(6); system("pause");
}

void addHard()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 9000+1000;
        y = rand() % 9000+1000;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("ADDITION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(4); printf("HARD");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(47,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(54,11); setColor(4); printf("Add %d and %d", x, y);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(51,13); setColor(6); printf("|                |");
        gotoxy(52,13); setColor(4); printf("  %d  +  %d ", x, y);
        gotoxy(51,14); setColor(6); printf("------------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(4); scanf("%d", &z);
        if(z == x+y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(44,20); setColor(4); printf("Oops! %d is the right answer.", x+y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aAddH = (float)s/item*100;  //GETS THE AVERAGE INTO GLOBAL VARIABLE aAddH TO ACCESS IT TO COMPUTE FOR THE ADDITION AVERAGE IN ADDITION INTERFACE FUNTION
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aAddH);
    gotoxy(60,23); setColor(4); printf("HARD");
    gotoxy(47,26); setColor(6); system("pause");
}

void subtraction(char n[31])    //SUBTRACTION GAME INTERFACE
{
    int e, i, j, p;
    p = locate(n);      //LOCATING THE "n" IN ARRAY FROM ENTERED USER ID IN LOGIN FUNCTION
    while(e!=4)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");     //FOR LOOP PATTERN FOR BOARDER
                }
                else
                printf("");
            }
        printf("");
        }
        gotoxy(8,21); setColor(2); printf("SCORING RULE:");
        gotoxy(8,22); setColor(6); printf("YOUR AVERAGE SCORE IN  EACH");
        gotoxy(8,23); setColor(6); printf("DIFFICULTY WILL BE COMBINED");
        gotoxy(8,24); setColor(6); printf("TO  GET YOUR OVERALL  SCORE");
        gotoxy(8,25); setColor(6); printf("IN THIS OPERATION.");
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(54,4); setColor(3); printf("SUBTRACTION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(48,7); setColor(6); printf("------------------------");
        gotoxy(48,8); setColor(6); printf("|                      |");
        gotoxy(51,8); setColor(3); printf("CHOOSE  DIFFICULTY");
        gotoxy(48,9); setColor(6); printf("------------------------");
        gotoxy(36,12); setColor(6); printf("[ 1 ]-------");
        gotoxy(36,13); setColor(6); printf("|          |");
        gotoxy(40,13); setColor(2); printf("EASY");
        gotoxy(36,14); setColor(6); printf("------------");
        gotoxy(54,12); setColor(6); printf("---[ 2 ]----");
        gotoxy(54,13); setColor(6); printf("|          |");
        gotoxy(57,13); setColor(7); printf("MEDIUM");
        gotoxy(54,14); setColor(6); printf("------------");
        gotoxy(72,12); setColor(6); printf("-------[ 3 ]");
        gotoxy(72,13); setColor(6); printf("|          |");
        gotoxy(76,13); setColor(4); printf("HARD");
        gotoxy(72,14); setColor(6); printf("------------");
        gotoxy(49,20); setColor(6); printf("--------[ 4 ]---------");
        gotoxy(49,21); setColor(6); printf("|                    |");
        gotoxy(52,21); setColor(3); printf("CHOOSE OPERATION");
        gotoxy(49,22); setColor(6); printf("----------------------");
        gotoxy(45,26); setColor(6); printf("Please select from (1-4) only: ");
        scanf("%d",&e);
        switch(e)
        {
            case 1: subEasy(); break;
            case 2: subMedium(); break;
            case 3: subHard(); break;
            case 4: break;
        }
    }
    subAve = (aSubE+aSubM+aSubH)/3.0;   //GETS THE AVERAGE OF EASY, MEDIUM, AND HARD COMBINED
    pts[p].subS = subAve;               //UPDATES THE VALUE OF LOCATED INDEX IN subS
}

void subEasy()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 10;
        y = rand() % 10;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(54,4); setColor(3); printf("SUBTRACTION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(2); printf("EASY");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(47,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(54,11); setColor(2); printf("Subtract %d from %d", y, x);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(53,13); setColor(6); printf("|            |");
        gotoxy(54,13); setColor(2); printf("  %d  -  %d ", x, y);
        gotoxy(53,14); setColor(6); printf("--------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(2); scanf("%d", &z);
        if(z == x-y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(46,20); setColor(4); printf("Oops! %d is the right answer.", x-y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aSubE = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aSubE);
    gotoxy(60,23); setColor(2); printf("EASY");
    gotoxy(47,26); setColor(6); system("pause");
}

void subMedium()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 100+20;
        y = rand() % 100+20;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(54,4); setColor(3); printf("SUBTRACTION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(57,6); setColor(7); printf("MEDIUM");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(47,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(53,11); setColor(7); printf("Subtract %d from %d", y, x);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(52,13); setColor(6); printf("|              |");
        gotoxy(53,13); setColor(7); printf("  %d  -  %d ", x, y);
        gotoxy(52,14); setColor(6); printf("----------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(7); scanf("%d", &z);
        if(z == x-y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(46,20); setColor(4); printf("Oops! %d is the right answer.", x-y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aSubM = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(45,23); setColor(6); printf("Your Average (      ): %6.2f%%", aSubM);
    gotoxy(59,23); setColor(7); printf("MEDIUM");
    gotoxy(47,26); setColor(6); system("pause");
}

void subHard()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 9000+1000;
        y = rand() % 9000+1000;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(54,4); setColor(3); printf("SUBTRACTION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(4); printf("HARD");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(44,10); setColor(6); printf("--------------------------------");
        gotoxy(44,11); setColor(6); printf("|                              |");
        gotoxy(45,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(51,11); setColor(4); printf("Subtract %d from %d", y, x);
        gotoxy(44,12); setColor(6); printf("--------------------------------");
        gotoxy(51,13); setColor(6); printf("|                |");
        gotoxy(52,13); setColor(4); printf("  %d  -  %d ", x, y);
        gotoxy(51,14); setColor(6); printf("------------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(4); scanf("%d", &z);
        if(z == x-y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(45,20); setColor(4); printf("Oops! %d is the right answer.", x-y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aSubH = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aSubH);
    gotoxy(60,23); setColor(4); printf("HARD");
    gotoxy(47,26); setColor(6); system("pause");
}

void multiplication(char n[31])     //MULTIPLICATION GAME INTERFACE
{
    int e, i, j, p;
    p = locate(n);          //LOCATING THE "n" IN ARRAY FROM ENTERED USER ID IN LOGIN FUNCTION
    while(e!=4)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");
                }
                else
                printf("");
            }
        printf("");
        }
        gotoxy(8,21); setColor(2); printf("SCORING RULE:");
        gotoxy(8,22); setColor(6); printf("YOUR AVERAGE SCORE IN  EACH");
        gotoxy(8,23); setColor(6); printf("DIFFICULTY WILL BE COMBINED");
        gotoxy(8,24); setColor(6); printf("TO  GET YOUR OVERALL  SCORE");
        gotoxy(8,25); setColor(6); printf("IN THIS OPERATION.");
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(53,4); setColor(3); printf("MULTIPLICATION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(48,7); setColor(6); printf("------------------------");
        gotoxy(48,8); setColor(6); printf("|                      |");
        gotoxy(51,8); setColor(3); printf("CHOOSE  DIFFICULTY");
        gotoxy(48,9); setColor(6); printf("------------------------");
        gotoxy(36,12); setColor(6); printf("[ 1 ]-------");
        gotoxy(36,13); setColor(6); printf("|          |");
        gotoxy(40,13); setColor(2); printf("EASY");
        gotoxy(36,14); setColor(6); printf("------------");
        gotoxy(54,12); setColor(6); printf("---[ 2 ]----");
        gotoxy(54,13); setColor(6); printf("|          |");
        gotoxy(57,13); setColor(7); printf("MEDIUM");
        gotoxy(54,14); setColor(6); printf("------------");
        gotoxy(72,12); setColor(6); printf("-------[ 3 ]");
        gotoxy(72,13); setColor(6); printf("|          |");
        gotoxy(76,13); setColor(4); printf("HARD");
        gotoxy(72,14); setColor(6); printf("------------");
        gotoxy(49,20); setColor(6); printf("--------[ 4 ]---------");
        gotoxy(49,21); setColor(6); printf("|                    |");
        gotoxy(52,21); setColor(3); printf("CHOOSE OPERATION");
        gotoxy(49,22); setColor(6); printf("----------------------");
        gotoxy(45,26); setColor(6); printf("Please select from (1-4) only: ");
        scanf("%d",&e);
        switch(e)
        {
            case 1: mulEasy(); break;
            case 2: mulMedium(); break;
            case 3: mulHard(); break;
            case 4 :break;
        }
    }
    mulAve = (aMulE+aMulM+aMulH)/3.0;       //GETS THE AVERAGE OF EASY, MEDIUM, AND HARD COMBINED
    pts[p].mulS = mulAve;                   //UPDATES THE VALUE OF LOCATED INDEX IN mulS
}

void mulEasy()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 10;
        y = rand() % 10;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(53,4); setColor(3); printf("MULTIPLICATION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(2); printf("EASY");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(47,10); setColor(6); printf("--------------------------");
        gotoxy(47,11); setColor(6); printf("|                        |");
        gotoxy(48,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(55,11); setColor(2); printf("Multiply %d by %d", x, y);
        gotoxy(47,12); setColor(6); printf("--------------------------");
        gotoxy(53,13); setColor(6); printf("|            |");
        gotoxy(54,13); setColor(2); printf("  %d  x  %d ", x, y);
        gotoxy(53,14); setColor(6); printf("--------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(2); scanf("%d", &z);
        if(z == x*y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(46,20); setColor(4); printf("Oops! %d is the right answer.", x*y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aMulE = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aMulE);
    gotoxy(60,23); setColor(2); printf("EASY");
    gotoxy(47,26); setColor(6); system("pause");
}

void mulMedium()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 50+11;
        y = rand() % 30+11;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(53,4); setColor(3); printf("MULTIPLICATION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(57,6); setColor(7); printf("MEDIUM");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(47,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(54,11); setColor(7); printf("Multiply %d by %d", x, y);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(53,13); setColor(6); printf("|            |");
        gotoxy(54,13); setColor(7); printf("  %d  x  %d ", x, y);
        gotoxy(53,14); setColor(6); printf("--------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(7); scanf("%d", &z);
        if(z == x*y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(45,20); setColor(4); printf("Oops! %d is the right answer.", x*y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aMulM = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(45,23); setColor(6); printf("Your Average (      ): %6.2f%%", aMulM);
    gotoxy(59,23); setColor(7); printf("MEDIUM");
    gotoxy(47,26); setColor(6); system("pause");
}

void mulHard()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        x = rand() % 300+100;
        y = rand() % 99+30;
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(53,4); setColor(3); printf("MULTIPLICATION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(4); printf("HARD");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(47,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(54,11); setColor(4); printf("Multiply %d by %d", x, y);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(52,13); setColor(6); printf("|              |");
        gotoxy(53,13); setColor(4); printf("  %d  x  %d ", x, y);
        gotoxy(52,14); setColor(6); printf("----------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(4); scanf("%d", &z);
        if(z == x*y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(44,20); setColor(4); printf("Oops! %d is the right answer.", x*y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aMulH = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aMulH);
    gotoxy(60,23); setColor(4); printf("HARD");
    gotoxy(47,26); setColor(6); system("pause");
}

void division(char n[31])       //MULTIPLICATION GAME INTERFACE
{
    int e, i, j, p;
    p = locate(n);      //LOCATING THE "n" IN ARRAY FROM ENTERED USER ID IN LOGIN FUNCTION
    while(e!=4)
    {
        system("cls");
        for (i=1;i<=115;i++)
        {
            for (j=1;j<=27;j++)
            {

                if(i==1||i==115||j==1||j==27)
                {
                    gotoxy(1+i,1+j); setColor(i); printf("**");
                }
                else
                printf("");
            }
        printf("");
        }
        gotoxy(8,21); setColor(2); printf("SCORING RULE:");
        gotoxy(8,22); setColor(6); printf("YOUR AVERAGE SCORE IN  EACH");
        gotoxy(8,23); setColor(6); printf("DIFFICULTY WILL BE COMBINED");
        gotoxy(8,24); setColor(6); printf("TO  GET YOUR OVERALL  SCORE");
        gotoxy(8,25); setColor(6); printf("IN THIS OPERATION.");
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("DIVISION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(48,7); setColor(6); printf("------------------------");
        gotoxy(48,8); setColor(6); printf("|                      |");
        gotoxy(51,8); setColor(3); printf("CHOOSE  DIFFICULTY");
        gotoxy(48,9); setColor(6); printf("------------------------");
        gotoxy(36,12); setColor(6); printf("[ 1 ]-------");
        gotoxy(36,13); setColor(6); printf("|          |");
        gotoxy(40,13); setColor(2); printf("EASY");
        gotoxy(36,14); setColor(6); printf("------------");
        gotoxy(54,12); setColor(6); printf("---[ 2 ]----");
        gotoxy(54,13); setColor(6); printf("|          |");
        gotoxy(57,13); setColor(7); printf("MEDIUM");
        gotoxy(54,14); setColor(6); printf("------------");
        gotoxy(72,12); setColor(6); printf("-------[ 3 ]");
        gotoxy(72,13); setColor(6); printf("|          |");
        gotoxy(76,13); setColor(4); printf("HARD");
        gotoxy(72,14); setColor(6); printf("------------");
        gotoxy(49,20); setColor(6); printf("--------[ 4 ]---------");
        gotoxy(49,21); setColor(6); printf("|                    |");
        gotoxy(52,21); setColor(3); printf("CHOOSE OPERATION");
        gotoxy(49,22); setColor(6); printf("----------------------");
        gotoxy(45,26); setColor(6); printf("Please select from (1-4) only: ");
        scanf("%d",&e);
        switch(e)
        {
            case 1: divEasy(); break;
            case 2: divMedium(); break;
            case 3: divHard(); break;
            case 4: break;
        }
    }
    divAve = (aDivE+aDivM+aDivH)/3.0;       //GETS THE AVERAGE OF EASY, MEDIUM, AND HARD COMBINED
    pts[p].divS = divAve;                   //UPDATES THE VALUE OF LOCATED INDEX IN mulS
}

void divEasy()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        y = rand() % 10+1;
        if(y==1)
        {
            x=rand() % 10;
        }
        if(y==2)
        {
            x=(rand()%10)*2;
        }
        if(y==3)
        {
            x=(rand()%10)*3;
        }
        if(y==4)
        {
            x=(rand()%10)*4;
        }
        if(y==5)
        {
            x=(rand()%10)*5;
        }
        if(y==6)
        {
            x=(rand()%10)*6;
        }
        if(y==7)
        {
            x=(rand()%10)*7;
        }
        if(y==8)
        {
            x=(rand()%10)*8;
        }
        if(y==9)
        {
            x=(rand()%10)*9;
        }
        if(y==10)
        {
            x=(rand()%10)*10;
        }
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("DIVISION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(2); printf("EASY");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(48,10); setColor(6); printf("------------------------");
        gotoxy(48,11); setColor(6); printf("|                      |");
        gotoxy(49,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(55,11); setColor(2); printf("Divide %d by %d", x, y);
        gotoxy(48,12); setColor(6); printf("------------------------");
        gotoxy(53,13); setColor(6); printf("|            |");
        gotoxy(54,13); setColor(2); printf("  %d  /  %d ", x, y);
        gotoxy(53,14); setColor(6); printf("--------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(2); scanf("%d", &z);
        if(z==x/y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(46,20); setColor(4); printf("Oops! %d is the right answer.", x/y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aDivE = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aDivE);
    gotoxy(60,23); setColor(2); printf("EASY");
    gotoxy(47,26); setColor(6); system("pause");
}

void divMedium()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        y = rand() % 10+1;
        if(y==1)
        {
            x=rand() % 100+11;
        }
        if(y==2)
        {
            x=(rand()%100)*2;
        }
        if(y==3)
        {
            x=(rand()%100)*3;
        }
        if(y==4)
        {
            x=(rand()%100)*4;
        }
        if(y==5)
        {
            x=(rand()%100)*5;
        }
        if(y==6)
        {
            x=(rand()%100)*6;
        }
        if(y==7)
        {
            x=(rand()%100)*7;
        }
        if(y==8)
        {
            x=(rand()%100)*8;
        }
        if(y==9)
        {
            x=(rand()%100)*9;
        }
        if(y==10)
        {
            x=(rand()%100)*10;
        }
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("DIVISION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(57,6); setColor(7); printf("MEDIUM");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(47,10); setColor(6); printf("--------------------------");
        gotoxy(47,11); setColor(6); printf("|                        |");
        gotoxy(48,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(55,11); setColor(7); printf("Divide %d by %d", x, y);
        gotoxy(47,12); setColor(6); printf("--------------------------");
        gotoxy(53,13); setColor(6); printf("|            |");
        gotoxy(54,13); setColor(7); printf(" %d  /  %d ", x, y);
        gotoxy(53,14); setColor(6); printf("--------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(7); scanf("%d", &z);
        if(z==x/y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(46,20); setColor(4); printf("Oops! %d is the right answer.", x/y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aDivM = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(45,23); setColor(6); printf("Your Average (      ): %6.2f%%", aDivM);
    gotoxy(59,23); setColor(7); printf("MEDIUM");
    gotoxy(47,26); setColor(6); system("pause");
}

void divHard()
{
    int i, j, k, x, y, z;
    int s = 0;
    srand(time(NULL));
    for(i=0;i<item;i++)
    {
        y = rand() % 20+1;
        if(y==1)
        {
            x=rand() % 4000+400;
        }
        if(y==2)
        {
            x=(rand()%200+100)*2;
        }
        if(y==3)
        {
            x=(rand()%200+100)*3;
        }
        if(y==4)
        {
            x=(rand()%200+100)*4;
        }
        if(y==5)
        {
            x=(rand()%200+100)*5;
        }
        if(y==6)
        {
            x=(rand()%200+100)*6;
        }
        if(y==7)
        {
            x=(rand()%200+100)*7;
        }
        if(y==8)
        {
            x=(rand()%200+100)*8;
        }
        if(y==9)
        {
            x=(rand()%200+100)*9;
        }
        if(y==10)
        {
            x=(rand()%200+100)*10;
        }
        if(y==11)
        {
            x=(rand()%200+100)*11;
        }
        if(y==12)
        {
            x=(rand()%200+100)*12;
        }
        if(y==13)
        {
            x=(rand()%200+100)*13;
        }
        if(y==14)
        {
            x=(rand()%200+100)*14;
        }
        if(y==15)
        {
            x=(rand()%200+100)*15;
        }
        if(y==16)
        {
            x=(rand()%200+100)*16;
        }
        if(y==17)
        {
            x=(rand()%200+100)*17;
        }
        if(y==18)
        {
            x=(rand()%200+100)*18;
        }
        if(y==19)
        {
            x=(rand()%200+100)*19;
        }
        if(y==20)
        {
            x=(rand()%200+100)*20;
        }
        system("cls");
        for (k=1;k<=115;k++)
        {
            for (j=1;j<=27;j++)
            {

                if(k==1||k==115||j==1||j==27)
                {
                    gotoxy(1+k,1+j); setColor(k); printf("**");
                }
                else
                printf("");
            }
            printf("");
        }
        gotoxy(47,1); setColor(6); printf("--------------------------");
        gotoxy(47,2); setColor(6); printf("|                        |");
        gotoxy(50,2); setColor(3); printf("ARITHMETIC PRACTICES");
        gotoxy(47,3); setColor(6); printf("--------------------------");
        gotoxy(50,4); setColor(6); printf("|                  |");
        gotoxy(56,4); setColor(3); printf("DIVISION");
        gotoxy(50,5); setColor(6); printf("--------------------");
        gotoxy(54,6); setColor(6); printf("|          |");
        gotoxy(58,6); setColor(4); printf("HARD");
        gotoxy(54,7); setColor(6); printf("------------");
        gotoxy(46,10); setColor(6); printf("----------------------------");
        gotoxy(46,11); setColor(6); printf("|                          |");
        gotoxy(48,11); setColor(6); printf(" %d.|", i+1);
        gotoxy(55,11); setColor(4); printf("Divide %d by %d", x, y);
        gotoxy(46,12); setColor(6); printf("----------------------------");
        gotoxy(51,13); setColor(6); printf("|                |");
        gotoxy(52,13); setColor(4); printf("   %d  /  %d ", x, y);
        gotoxy(51,14); setColor(6); printf("------------------");
        gotoxy(47,16); setColor(6); printf("Your Answer: ");
        setColor(4); scanf("%d", &z);
        if(z==x/y)
        {
            gotoxy(48,20); setColor(2); printf("Oo tama yes that's right!");
            s++;
            gotoxy(47,26); setColor(6); system("pause");
        }
        else
        {
            gotoxy(45,20); setColor(4); printf("Oops! %d is the right answer.", x/y);
            gotoxy(47,26); setColor(6); system("pause");
        }
    }
    aDivH = (float)s/item*100;
    gotoxy(50,22); setColor(6); printf("You got %d out of %d!", s, item);
    gotoxy(46,23); setColor(6); printf("Your Average (    ): %6.2f%%", aDivH);
    gotoxy(60,23); setColor(4); printf("HARD");
    gotoxy(47,26); setColor(6); system("pause");
}

void save()     //FUNCTION TO SAVE DATAS FROM ARRAY INTO TEXT FILE
{
    FILE *fp;
    int i;
    fp = fopen("leaders.txt","w+");     //TEXT FILE FOR PLAYERS SCORES
    if (fp==NULL)
    {
        gotoxy(54, 25); setColor(6); printf("File error.");
        gotoxy(47, 26); setColor(6); system("pause");
    }
    else
    {
        for (i=0;i<=marker;i++)
        fprintf(fp,"%s\n%f %f %f %f %f\n", pts[i].ign, pts[i].addS, pts[i].subS, pts[i].mulS, pts[i].divS, pts[i].aveS);
    }                                          //WRITING USER ID AND SCORES INTO TEXT FILE
    fclose(fp);
}

void retrieve()     //FUNCTION TO RETRIEVE DATAS IN ARRAY FROM TEXT FILE
{
    FILE *fp;
    LEAD y;
    fp = fopen("leaders.txt","r+");     //TEXT FILE FOR PLAYERS SCORES
    if (fp==NULL)
    {
        gotoxy(53, 25); setColor(6); printf("File Created.");
        gotoxy(47, 26); setColor(6); system("pause");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp,"%s\n%f %f %f %f %f\n", y.ign, &y.addS, &y.subS, &y.mulS, &y.divS, &y.aveS);
            getScore(y);
        }
    }
    fclose(fp);
}

void gotoxy(int x, int y)
{
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void setColor(int ForgC)    //FUNCTION FOR TEXT COLORS FOR OUTPUT
{

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}