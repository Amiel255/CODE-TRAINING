// 4 Pillars of OOP
// 1. Encapsulation - data hiding
// 2. Abstraction - show only the essentials, hide the details
// 3. Inheritance - Parent- Child relationship
// 4. Polymorphism - one interface, many forms.
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Teacherlist {
    private:
    string name;
    int age;

    public:
    void setinput (string n, int a) {
        name = n;
        age = a;
    }

    string getname () {
        return name;
    }
    int getage() {
        return age;
    }

    virtual void display () {
        cout << getname() << " " 
             << getage() << (getage() >= 18 ? " Adult" : " Minor") << endl;
    }
};

class Student : public Teacherlist {
    private:
    string course;

    public: 
    void inputcourse (string c) {
        course = c;
    }

    string getcourse () {
        return course;
    }

     void display () override { 
        cout << "I am " << getname() << " " 
        << getage() << (getage() >= 18 ? " Adult" : " Minor") 
        << " Currently Taking: " << getcourse() << endl;
    }
};

int main () {
    Teacherlist* p;
    Teacherlist teach;
    teach.setinput("Teach", 30);
    p = &teach;
    p->display();
    Teacherlist teach2;
    teach2.setinput("Teach Two", 45);
    p = &teach2;
    p->display();
    Student stude;
    stude.setinput("Amiel", 19);
    stude.inputcourse("BSIT");
    p = &stude;
    p->display();

    system("pause");
    return 0;
}