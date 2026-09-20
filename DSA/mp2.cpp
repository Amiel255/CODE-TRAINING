#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

struct Record
{
    string name;
    int grade;
};

struct node
{
    Record data;
    node *next;
    node(Record x) : data(x), next(NULL) {};
};

class Recordlink
{
private:
    node *head;

public:
    Recordlink() : head(NULL) {};
    ~Recordlink()
    {
        node *p;
        while (head != NULL)
        {
            p = head;
            head = head->next;
            delete (p);
        }
    }
    void add(Record x);
    void del(string n);
    void update(string n);
    void display();
    void save();
    void load();
};

int menu();

int main()
{
    Record r;
    Recordlink rec;
    rec.load();
    while (true)
    {
        switch (menu())
        {
        case 1:
            system("cls");
            cout << "MODE: ADDING OF DATA\n";
            cout << "Add name:";
            cin >> r.name;
            cout << "Add grade: ";
            cin >> r.grade;
            rec.add(r);
            break;

        case 2:
            system("cls");
            cout << "MODE: UPDATE OF DATA\n";
            cout << "Update name:";
            cin >> r.name;
            rec.update(r.name);
            break;

        case 3:
            system("cls");
            cout << "MODE: DELETING OF DATA\n";
            cout << "Delete name: ";
            cin >> r.name;
            rec.del(r.name);
            break;

        case 4:
            rec.display();
            break;

        case 5:
            cout << "Thank you for using the program <3...\n";
            system("pause");
            rec.save();
            exit(0);

        default:
            cout << "You may only pick numbers from 1 to 5 only...";
            system("pause");
        }
    }

    return 0;
}

int menu()
{
    int op;
    system("cls");
    cout << "Menu\n"
         << "1. Add\n"
         << "2. Update\n"
         << "3. Delete\n"
         << "4. Display\n"
         << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> op;
    return op;
}

void Recordlink::add(Record x)
{
    node *p, *q, *newnode;
    p = q = head;
    newnode = new node(x);

    while (p != NULL && x.name > p->data.name)
    {
        q = p;
        p = p->next;
    }

    if (p == head)
    {
        newnode->next = head;
        head = newnode;
    }
    else
    {
        newnode->next = p;
        q->next = newnode;
    }
}
void Recordlink::del(string n)
{
    node *p, *q;
    p = q = head;

    while (p != NULL && p->data.name != n)
    {
        q = p;
        p = p->next;
    }

    if (p == NULL)
    {
        cout << "not found...";
        system("pause");
    }
    else
    {
        if (p == head)
        {
            head = p->next;
        }
        else
        {
            q->next = p->next;
        }
        delete (p);
        cout << "Record of " << n << " has been deleted";
        system("pause");
    }
}
void Recordlink::update(string n)
{
    node *p;
    p = head;

    while (p != NULL && p->data.name != n)
    {
        p = p->next;
    }

    if (p == NULL)
    {
        cout << "not found...";
        system("pause");
    }
    else
    {
        Record newrecord;
        cout << "Enter new name: ";
        cin >> newrecord.name;

        cout << "Enter new grade: ";
        cin >> newrecord.grade;

        del(n);
        add(newrecord);
    }
}
void Recordlink::display()
{
    node *p;
    p = head;
    system("cls");
    cout << left << setw(20) << "Name"
         << setw(10) << "Grade"
         << setw(10) << "Remarks" << endl;
    while (p != NULL)
    {
        cout << left << setw(20) << p->data.name
             << setw(10) << p->data.grade
             << setw(10) << (p->data.grade >= 75 ? "PASSED" : "FAILED") << endl;

        p = p->next;
    }
    system("pause");
}
void Recordlink::save()
{
    ofstream file("mp2.csv");
    if (!file)
    {
        cout << "File error.\n";
        return;
    }
    else
    {
        node *p;
        p = head;
        while (p != NULL)
        {
            file << p->data.name << "," << p->data.grade << endl;
            p = p->next;
        }
    }
    file.close();
}
void Recordlink::load()
{
    ifstream file("mp2.csv");
    if (!file)
    {
        cout << "File error.\n";
        return;
    }
    else
    {
        Record x;
        string line;
        string ag;
        while (getline(file, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            getline(ss, x.name, ',');
            getline(ss, ag, ',');
            x.grade = stoi(ag);
            add(x);
        }
        file.close();
    }
}