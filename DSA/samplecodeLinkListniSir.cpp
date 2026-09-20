// Link list implementation of Records of Persons
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
struct Record
{
    string name;
    int age;
};
struct Node
{
    Record data;
    struct Node *next;
    Node(Record x) : data(x) {}
};
class RecordLink
{
private:
    Node *head;

public:
    // constructor
    RecordLink() : head(NULL) {}
    ~RecordLink()
    {
        Node *p;
        while (head != NULL)
        {
            p = head;
            head = head->next;
            delete (p);
        }
    }
    void add(Record x);
    void del(string n);
    void display();
    void save();
    void retrieve();
};

int menu();

int main()
{
    Record r;
    RecordLink rec; // rec is an instance of class RecordLink
    rec.retrieve();
    while (true)
    {
        switch (menu())
        {
        case 1:
            system("cls");
            cout << "Add Mode\n";
            cout << "Input Name: ";
            cin >> r.name;
            cout << "Input Age: ";
            cin >> r.age;
            rec.add(r);
            break;
        case 2:
            system("cls");
            cout << "Delete Mode\n";
            cout << "Input Name: ";
            cin >> r.name;
            rec.del(r.name);
            break;
        case 3:
            rec.display();
            break;
        case 4:
            cout << "\nThank you for using my program...\n";
            system("pause");
            rec.save();
            exit(0);
        default:
            cout << "1 to 4 only.\n";
            system("pause");
        }
    }
    return 0;
}
int menu()
{
    int op;
    system("cls");
    cout << "MENU\n";
    cout << "1. Add Record\n";
    cout << "2. Delete Record\n";
    cout << "3. Display all\n";
    cout << "4. Exit\n";
    cout << "\nSelect(1-4): ";
    cin >> op;
    return op;
}

void RecordLink::add(Record x)
{
    Node *p, *q, *newNode;
    p = q = head;
    newNode = new Node(x);
    // hanapin ang dulo
    while (p != NULL)
    {
        q = p;
        p = p->next;
    }
    if (p == head)
        head = newNode;
    else
        q->next = newNode;
    newNode->next = p;
}
void RecordLink::del(string n)
{
    Node *p, *q;
    p = q = head;
    // hanapin ang x
    while (p != NULL && p->data.name != n)
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
    {
        cout << "Not found.\n";
        system("pause");
    }
    else
    {
        if (p == head) // first element
            head = p->next;
        else
            q->next = p->next;
        delete (p);
        cout << "Record of " << n << " has been deleted.\n";
        system("pause");
    }
}
void RecordLink::display()
{
    Node *p;
    int i = 1;
    p = head;
    system("cls");
    cout << left << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(10) << "Remarks" << endl;
    while (p != NULL)
    {
        cout << left << setw(20) << p->data.name
             << setw(10) << p->data.age
             << setw(10) << (p->data.age >= 18 ? "Adult" : "Minor") << endl;

        p = p->next;
    }
    system("pause");
}
void RecordLink::save()
{
    ofstream file("it2b.csv");
    if (!file)
    {
        cout << "File error.\n";
        return;
    }
    else
    {
        Node *p = head;
        while (p != NULL)
        {
            file << p->data.name << "," << p->data.age << endl;
            p = p->next;
        }
    }
    file.close();
}
void RecordLink::retrieve()
{
    ifstream file("it2b.csv");
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
            x.age = stoi(ag);
            add(x);
        }
        file.close();
    }
}