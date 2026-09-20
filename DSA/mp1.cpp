#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
using namespace std;

#define MAX 100
const string FILENAME = "mp1DSA.csv";

struct Student
{
    string name;
    int score;
};

class Record
{
private:
    Student student[MAX];
    int last;

    int locatePos(string x);
    void loadFromFile();
    void saveToFile();

public:
    Record();

    void insert(Student x);
    void del(string x);
    void update(string x);
    void display();

    bool isfull();
    bool isempty();
    int locate(string x);
};

bool Record::isfull()
{
    return (last == MAX - 1);
}

bool Record::isempty()
{
    return (last == -1);
}

int Record::locate(string x)
{
    for (int i = 0; i <= last; i++)
        if (x == student[i].name)
            return i;
    return -1;
}

void Record::insert(Student x)
{
    if (isfull())
    {
        cout << "List is full.\n";
        system("pause");
        return;
    }
    if (locate(x.name) != -1)
    {
        cout << "Name already exists.\n";
        system("pause");
        return;
    }

    int p = locatePos(x.name);
    for (int i = last; i >= p; i--)
        student[i + 1] = student[i];

    student[p] = x;
    last++;
    saveToFile();
}

void Record::del(string x)
{
    if (isempty())
    {
        cout << "Nothing to delete.\n";
        system("pause");
        return;
    }

    int p = locate(x);
    if (p < 0)
    {
        cout << "Not found.\n";
        system("pause");
        return;
    }

    for (int i = p; i < last; i++)
        student[i] = student[i + 1];

    last--;
    saveToFile();
}

void Record::update(string x)
{
    if (isempty())
    {
        cout << "Nothing to update.\n";
        system("pause");
        return;
    }

    int p = locate(x);
    if (p < 0)
    {
        cout << "Not found.\n";
        system("pause");
        return;
    }

    int newscore;
    cout << "Current score of " << student[p].name << " is " << student[p].score << "\n";
    cout << "Enter new score: ";
    cin >> newscore;
    student[p].score = newscore;
    saveToFile();
    cout << "Updated successfully.\n";
    system("pause");
}

void Record::display()
{
    system("cls");
    cout << "The List contains:\n";
    for (int i = 0; i <= last; i++)
        cout << i + 1 << ".) " << student[i].name << " : " << student[i].score << "\n";
    system("pause");
}

int Record::locatePos(string x)
{
    for (int i = 0; i <= last; i++)
        if (x < student[i].name)
            return i;
    return last + 1;
}

void Record::loadFromFile()
{
    ifstream fin(FILENAME);
    if (!fin)
        return;

    string line;
    last = -1;
    while (getline(fin, line) && !isfull())
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string name, scoreStr;
        getline(ss, name, ',');
        getline(ss, scoreStr, ',');

        last++;
        student[last].name = name;
        student[last].score = stoi(scoreStr);
    }
    fin.close();
}

void Record::saveToFile()
{
    ofstream fout(FILENAME);
    for (int i = 0; i <= last; i++)
        fout << student[i].name << "," << student[i].score << "\n";
    fout.close();
}

int menu()
{
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

Record::Record()
{
    last = -1;
    loadFromFile();
}

int main()
{
    Record L;
    Student x;

    while (1)
    {
        switch (menu())
        {
        case 1:
            system("cls");
            cout << "Input name : ";
            cin >> x.name;
            cout << "Input score: ";
            cin >> x.score;
            L.insert(x);
            break;

        case 2:
        {
            system("cls");
            string nm;
            cout << "Input name to delete: ";
            cin >> nm;
            L.del(nm);
            break;
        }

        case 3:
        {
            
            system("cls");
            string nm;
            cout << "Input name to update: ";
            cin >> nm;
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
