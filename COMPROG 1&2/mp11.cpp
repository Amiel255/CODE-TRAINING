#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define max 100

string name[max];
int g1[max], g2[max], g3[max];
int count = 0;
string nameloc;

void menu();
void show(string name[], int g1[], int g2[], int g3[], int count);
void add(string name[], int g1[], int g2[], int g3[], int *count);
void update(string name[], int g1[], int g2[], int g3[], int count);
void deleteRec(string name[], int g1[], int g2[], int g3[], int *count);
int isfull(int count);
int isempty(int count);
int locate(string name[], int count, string nameloc);

int main() {
    menu();
    return 0;
}

void show(string name[], int g1[], int g2[], int g3[], int count) {
    system("cls");

    if (isempty(count)) {
        cout << "LIST EMPTY\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        int average = (g1[i] + g2[i] + g3[i]) / 3;

        cout << i + 1 << "). Name: " << setw(10) << left << name[i]
             << " Score 1: " << setw(5) << g1[i]
             << " Score 2: " << setw(5) << g2[i]
             << " Score 3: " << setw(5) << g3[i]
             << " Ave: " << setw(5) << average
             << " Remarks: " << (average >= 75 ? "PASSED" : "FAILED") << endl;
    }
}

void add(string name[], int g1[], int g2[], int g3[], int *count) {
    system("cls");

    if (isfull(*count)) {
        cout << "LIST IS FULL\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, name[*count]);

    nameloc = name[*count];

    if (locate(name, *count, nameloc) != -1) {
        cout << "Name already exists.\n";
        system("pause");
        return;
    }

    cout << "Enter Grade No. 1: ";
    cin >> g1[*count];
    cout << "Enter Grade No. 2: ";
    cin >> g2[*count];
    cout << "Enter Grade No. 3: ";
    cin >> g3[*count];
    cin.ignore();

    (*count)++;
    cout << "Record added successfully.\n";
}

void update(string name[], int g1[], int g2[], int g3[], int count) {
    system("cls");

    if (isempty(count)) {
        cout << "Nothing to update.\n";
        return;
    }

    show(name, g1, g2, g3, count);

    cout << "Update of grade\n";
    cout << "Enter name: ";
    getline(cin, nameloc);

    int pos = locate(name, count, nameloc);

    if (pos == -1) {
        cout << "Not Found\n";
        return;
    }

    cout << "Enter Grade No. 1: ";
    cin >> g1[pos];
    cout << "Enter Grade No. 2: ";
    cin >> g2[pos];
    cout << "Enter Grade No. 3: ";
    cin >> g3[pos];
    cin.ignore();
}

void deleteRec(string name[], int g1[], int g2[], int g3[], int *count) {
    system("cls");

    if (isempty(*count)) {
        cout << "Nothing to delete.\n";
        return;
    }

    show(name, g1, g2, g3, *count);

    cout << "Enter name to locate: ";
    getline(cin, nameloc);

    int pos = locate(name, *count, nameloc);

    if (pos == -1) {
        cout << "Not Found\n";
        return;
    }

    for (int i = pos; i < *count - 1; i++) {
        name[i] = name[i + 1];
        g1[i] = g1[i + 1];
        g2[i] = g2[i + 1];
        g3[i] = g3[i + 1];
    }

    (*count)--;

    cout << "Deleted...\n";
}

int isfull(int count) {
    return count == max;
}

int isempty(int count) {
    return count == 0;
}

int locate(string name[], int count, string nameloc) {
    for (int i = 0; i < count; i++) {
        if (name[i] == nameloc) {
            return i;
        }
    }
    return -1;
}

void menu() {
    int choice = 0;

    while (choice != 5) {
        system("cls");

        cout << "MENU\n 1.SHOW\n 2.ADD\n 3.UPDATE\n 4.DELETE\n 5.EXIT\n";
        cout << "\nEnter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            show(name, g1, g2, g3, count);
            break;
        case 2:
            add(name, g1, g2, g3, &count);
            break;
        case 3:
            update(name, g1, g2, g3, count);
            break;
        case 4:
            deleteRec(name, g1, g2, g3, &count);
            break;
        case 5:
            cout << "Exiting the program\n";
            break;
        }

        system("pause");
    }
}