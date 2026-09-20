#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

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

class Recordlist
{
private:
    node *head;

public:
    Recordlist() : head(NULL) {};
    ~Recordlist()
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

void Recordlist ::add(Record x)
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

void Recordlist ::del(string n)
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
        cout << "NOTHING TO DELETE";
        system("pause");
    }
    else
    {
        q->next = p->next;
        delete (p);
        cout << "Record of " << n << " has been deleted";
        system("pause");
    }
}

void Recordlist ::update(string n)
{
    node *p;
    p = head;

    while (p != NULL && p->data.name != n)
    {
        p = p->next;
    }

    if (p = NULL)
    {
        cout << "not found :<";
        system("pause");
    }
    else 
    {
        Record newrec;

        cout << "Enter new name: ";
        cin >> newrec.name;

        cout << "Enter new grade: ";
        cin >> newrec.grade;

        del(n);
        add(newrec);
    }
}

void Recordlist :: display() {
    node *p;
    p = head;

    cout << left << setw(20) << "Name"
         << setw(10) << "Grade"
         << setw(10) << "Remarks" << endl;

    while (p != NULL) {
        cout << left << setw(20) << p->data.name
         << setw(10) << p->data.grade
         << setw(10) << (p->data.grade >= 75 ? "PASSED" : "FAILED") << endl;

        p = p->next;
    }

    system("pause");
}

void Recordlist :: save() {
    ofstream file ("praclinklistDSA.csv");
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

void Recordlist :: load() {
    ifstream file ("praclinklistDSA.csv");
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
        while(getline(file, line)) {
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