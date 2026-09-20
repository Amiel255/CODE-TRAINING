#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;
#define MAX 3

struct Student
{
    string Name;
    float Grade;
};

class Record
{

private:
    Student student[MAX];
    int last = -1;
    bool isfull();
    bool isempty();
    int locate(string n);

public:
    void addstude(Student x);
    void deletestude(string n);
    void display();
    void save();
    void load();
};

bool Record::isfull()
{
    return last == MAX - 1;
}

bool Record::isempty()
{
    return last == -1;
}

int Record::locate(string n)
{
    for (int i = 0; i <= last; i++)
    {
        if (student[i].Name == n)
            return i;
    }
    return -1;
}

void Record::addstude(Student x)
{
    if (isfull())
    {
        cout << "Student list is full" << endl;
        return;
    }

    last++;
    student[last] = x;
}

void Record::deletestude(string n)
{
    int pos = locate(n);

    if (isempty())
    {
        cout << "Nothing to delete" << endl;
        return;
    }

    for (int i = pos; i < last; i++) {
        student[i] = student[i+1];
    }

    last--;
    cout << "Deleted" << endl;
}

void Record::display()
{
    cout << "\n -STUDENT RECORD- \n"
         << endl;

    for (int i = 0; i <= last; i++)
    {
        cout << "Name: " << student[i].Name << endl;
        cout << "Grade: " << student[i].Grade << endl;
        cout << "Status: " << (student[i].Grade >= 75 ? "PASSED" : "FAILED") << endl;
        cout << endl;
    }
}

void Record::save()
{
    ofstream fp("students.csv");
    if (!fp)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    fp << "Name,Grade,Status" << endl;

    for (int i = 0; i <= last; i++)
    {
        fp << student[i].Name << "," << student[i].Grade << ","
           << (student[i].Grade >= 75 ? "PASSED" : "FAILED") << endl;
    }

    fp.close();
    cout << "Records saved to students.csv" << endl;
}

void Record::load()
{
    ifstream fp("students.csv");
    if (!fp)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;

    getline(fp, line);

    last = -1;

    while (getline(fp, line) && !isfull())
    {
        stringstream ss(line);

        string name;
        string grade;

        getline(ss, name, ',');
        getline(ss, grade, ',');

        last++;
        student[last].Name = name;
        student[last].Grade = stof(grade);
    }

    fp.close();
    cout << "Records loaded from students.csv" << endl;
}

int main()
{
    Record r;
    Student s;
    int choice;
    string n;

    ifstream check("students.csv");
    if (check.good())
        r.load();
    check.close();

    do
    {
        cout << "\n___MENU___\n";
        cout << "1. Add Student\n";
        cout << "2. Display Record\n";
        cout << "3. Delete Record\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Input name: ";
            cin.ignore();
            getline(cin, s.Name);
            cout << "Input grade: ";
            cin >> s.Grade;
            r.addstude(s);
            r.save();
            break;

        case 2:
            r.display();
            break;

        case 3:
            r.display();
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, n);

            r.deletestude(n);
            r.save();
            break;

        case 4:
            cout << "Exiting program..." << endl;
            r.save();
            break;

        default:
            cout << "Invalid input!" << endl;
        }
    } while (choice != 4);

    return 0;
}
