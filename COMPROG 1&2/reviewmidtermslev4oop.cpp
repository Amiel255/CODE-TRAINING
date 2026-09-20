#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Student
{

public:
    string name;
    int age;
};

int main () {
    int size;
    cout << "How many students to store: ";
    cin >> size;
    Student person[size];
    for (int i = 0; i < size; i++) {
        cout << "Student " << i+1 << " Name: ";
        cin.ignore();
        getline (cin, person[i].name);
        cout << "Student " << i+1 << " Age: ";
        cin >> person[i].age;
    }

    for (int i = 0; i < size; i++) {
        cout << person[i].name << " " << person[i].age << (person[i].age >= 18 ? " Adult" : " Minor") << endl;
    }
    system("pause");
    return 0;
}