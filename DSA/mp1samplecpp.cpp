#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

#define MAX 10
const string FILENAME = "student2.csv";


struct Student {
    string name;
    float grade;
};


class StudentList {
private:
    Student data[MAX];
    int last;

    
    int locatePos(string x);   
    void loadFromFile();       
    void saveToFile();         

public:
    StudentList();             

    void insert(Student x);
    void del(string x);
    void update(string x);
    void display();

    bool isfull();
    bool isempty();
    int locate(string x);
};


StudentList::StudentList() {
    last = -1;          
    loadFromFile();      
}



bool StudentList::isfull() {
    return (last == MAX - 1);
}

bool StudentList::isempty() {
    return (last == -1);
}

int StudentList::locate(string x) {
    for (int i = 0; i <= last; i++)
        if (x == data[i].name)
            return i;
    return -1; 
}

void StudentList::insert(Student x) {
    if (isfull()) {
        cout << "List is full.\n";
        system("pause");
        return;
    }
    if (locate(x.name) != -1) {
        cout << "Name already exists.\n";
        system("pause");
        return;
    }

    int p = locatePos(x.name);
    for (int i = last; i >= p; i--)
        data[i + 1] = data[i];

    data[p] = x;
    last++;
    saveToFile();
}

void StudentList::del(string x) {
    if (isempty()) {
        cout << "Nothing to delete.\n";
        system("pause");
        return;
    }

    int p = locate(x);
    if (p < 0) {
        cout << "Not found.\n";
        system("pause");
        return;
    }

    for (int i = p; i < last; i++)
        data[i] = data[i + 1];

    last--;
    saveToFile();
}

void StudentList::update(string x) {
    if (isempty()) {
        cout << "Nothing to update.\n";
        system("pause");
        return;
    }

    int p = locate(x);
    if (p < 0) {
        cout << "Not found.\n";
        system("pause");
        return;
    }

    float newGrade;
    cout << "Current grade of " << data[p].name << " is " << data[p].grade << "\n";
    cout << "Enter new grade: ";
    cin >> newGrade;
    data[p].grade = newGrade;
    saveToFile();
    cout << "Updated successfully.\n";
    system("pause");
}

void StudentList::display() {
    system("cls");
    cout << "The List contains:\n";
    for (int i = 0; i <= last; i++)
        cout << i + 1 << ".) " << data[i].name << " : " << data[i].grade << "\n";
    system("pause");
}




int StudentList::locatePos(string x) {
    for (int i = 0; i <= last; i++)
        if (x < data[i].name)
            return i;
    return last + 1;
}

void StudentList::loadFromFile() {
    ifstream fin(FILENAME);
    if (!fin) return; 

    string line;
    while (getline(fin, line) && !isfull()) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, gradeStr;
        getline(ss, name, ',');
        getline(ss, gradeStr, ',');

        last++;
        data[last].name = name;
        data[last].grade = stof(gradeStr);
    }
    fin.close();
}

void StudentList::saveToFile() {
    ofstream fout(FILENAME);
    for (int i = 0; i <= last; i++)
        fout << data[i].name << "," << data[i].grade << "\n";
    fout.close();
}


int menu() {
    int op;
    system("cls");
    cout << "MENU\n";
    cout << "1. Add a data\n";
    cout << "2. Delete a data\n";
    cout << "3. Update a data\n";
    cout << "4. Display\n";
    cout << "5. Quit\n";
    cout << "\nSelect(1-5): ";
    cin >> op;
    return op;
}


int main() {
    StudentList L;   
    Student x;

    while (1) { 
        switch (menu()) {
        case 1:
            system("cls");
            cout << "Input name : "; cin >> x.name;
            cout << "Input grade: "; cin >> x.grade;
            L.insert(x);
            break;

        case 2: {
            system("cls");
            string nm;
            cout << "Input name to delete: "; cin >> nm;
            L.del(nm);
            break;
        }

        case 3: {
            system("cls");
            string nm;
            cout << "Input name to update: "; cin >> nm;
            L.update(nm);
            break;
        }

        case 4:
            L.display();
            break;

        case 5:
            exit(0);

        default:
            cout << "Invalid choice.\n";
            system("pause");
        }
    }
    return 0;
}