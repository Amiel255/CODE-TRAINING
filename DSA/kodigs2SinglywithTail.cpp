#include <iostream>

using namespace std;

struct Record {
    string name;
    int grade;
};

struct node {
    Record data;
    node *next;
    node(Record x) : data(x), next(NULL) {};
};

class Recordlink {
    private:
    node *head;
    node *tail;

    public:
    Recordlink() : head(NULL), tail(NULL) {};
    ~Recordlink()
    {
        node *p;
        while (head !=NULL) {
            p = head;
            head = head->next;
            delete (p);
        }
    }

    void addRec(Record x);
    void delRec(String x);
    void Display();
};

void Recordlink :: addRec (Record x) {
    node *p, *q, *newnode;
    p = q = head
    newnode = new node(x);

    while (p != NULL) {
        q = p;
        p = -> next;
    }

    if (head == NULL) {
        head = newnode;
        tail = newnode;
    }

    if (p == head) {
        newnode -> next = head;
        head == newnode;
    }

    else if (p == tail) {
        q -> next = newnode;
        tail = newnode;
    }

    else {
        newnode -> next = p;
        q -> next = newnode;
    }
}