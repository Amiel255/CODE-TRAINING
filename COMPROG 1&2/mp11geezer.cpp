#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>

using namespace std;


#define MAX 5
#define Grade 3

char names[MAX][50];
int grades[MAX][Grade];
int last = 0;

void add(char name[], int g[]);
void del(char name[]);
void update(char name[]);
void display();
int isfull();
int isempty();
int locate(char name[]);
int menu();

int main()
{
    while(1){
        switch(menu()){

            case 1: {
                char name[50];
                int g[Grade];

                cout << "Enter the name: "<< endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(name,50);

                cout << "Enter quiz1: " << endl;
                cin >> g[0];

                cout << "Enter quiz2: " << endl;
                cin >> g[1];

                cout << "Enter quiz3: "<< endl;
                cin >> g[2];

                add(name, g);
                break;
            }

            case 2: {
                char name[50];

                cout << "Enter the name to delete: " << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(name,50);


                del(name);

                break;
            }

            case 3:
                display();
                break;

            case 4: {
                char name[50];

                cout << "Enter the name to update: " << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(name,50);

                update(name);

                break;
            }

            case 5:
                cout << "Bye\n";

                exit(0);

            default:
                cout << "Choose 1 to 5 only\n";

        }
    }
    return 0;
}

void add(char name[], int g[]){
    if(isfull()){
        cout << "Array is full, cannot add\n";
        return;
    }

    if(locate(name) != -1){
        cout << "Student with this name already exists\n";
        return;
    }

    strcpy(names[last], name);

    grades[last][0] = g[0];
    grades[last][1] = g[1];
    grades[last][2] = g[2];

    last++;
    cout << "Student added successfully\n";
    system("pause");
    system("cls");
}

void del(char name[]){
    if(isempty()){
        cout << "Array is empty, cannot delete\n";
        return;
    }

    int i;
    for(i = 0; i < last; i++){
        if(strcmp(names[i], name) == 0)
            break;
    }

     if(i < last){
        for(int j = i; j < last - 1; j++){
            strcpy(names[j], names[j + 1]);

            grades[j][0] = grades[j + 1][0];
            grades[j][1] = grades[j + 1][1];
            grades[j][2] = grades[j + 1][2];
        }
        last--;
        cout << "Student deleted successfully\n";
    } else {
        cout << "Name not found\n";
    }
    system("pause");
    system("cls");
}

void update(char name[]){
    if(isempty()){
        cout << "Array is empty, nothing to update\n";
        return;
    }

    int pos = locate(name);

    if(pos == -1){
        cout << "Student not found\n";
        return;
    }

    cout << "Current Grades: %d %d %d\n"
        << grades[pos][0] << " "
         <<  grades[pos][1] << " "
         <<  grades[pos][2] << "\n ";

    cout << "Enter new quiz1: ";
    cin >> grades[pos][0];

    cout << "Enter new quiz2: ";
    cin >> grades[pos][1];

    cout << "Enter new quiz3: ";
    cin >> grades[pos][2];

    cout << "Grades updated successfully\n";

    system("pause");
    system("cls");
}

void display(){
    if(isempty()){
        cout << "No students to display\n";
        return;
    }

    cout << "Students list:\n";
    cout << "Name\tQ1\tQ2\tQ3\tResult\n";

    for(int i = 0; i < last; i++){
        int sum = grades[i][0] + grades[i][1] + grades[i][2];
        float avg = sum / 3.0;

        cout << names[i] << "\t "
             <<  grades[i][0] << "\t "
             <<  grades[i][1] << "\t "
             <<  grades[i][2] << "\t "
             <<  ((avg >= 50) ? "Passed" : "Failed") << "\n";
    }
    system("pause");
    system("cls");
}

int isfull(){
    return last == MAX;
}

int isempty(){
    return last == 0;
}

int locate(char name[]){
    for(int i = 0; i < last; i++){
        if(strcmp(names[i], name) == 0)
            return i;
    }
    return -1;
}

int menu(){
    int ch;

    cout << "\nMENU\n";
    cout << "1. Add\n";
    cout << "2. Delete\n";
    cout << "3. Display\n";
    cout << "4. Update Grades\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";

    cin >> ch;
    system("pause");
    system("cls");
    return ch;
}