#include <iostream>
#define MAX 100
using namespace std;

// STRUCT = one student record
struct Record {
    string name;
    int g1, g2, g3;
};

// CLASS
class MyClass {
private:
    Record stude[MAX];
    int last = -1;

    bool isfull();
    bool isempty();
    int locate(string n);

public:
    void addRecord(Record x);
    void display();
    void updateRecord(string n, int s1, int s2, int s3);
    void deleteRecord(string n);
};

// CHECK FULL
bool MyClass::isfull() {
    return last == MAX - 1;
}

// CHECK EMPTY
bool MyClass::isempty() {
    return last == -1;
}

// LOCATE
int MyClass::locate(string n) {
    for (int i = 0; i <= last; i++) {
        if (stude[i].name == n)
            return i;
    }
    return -1;
}

// ADD (same style as template)
void MyClass::addRecord(Record x) {
    if (isfull()) {
        cout << "LIST IS FULL\n";
        return;
    }

    if (locate(x.name) != -1) {
        cout << "Name already exists.\n";
        return;
    }

    last++;
    stude[last] = x;

    cout << "Record added successfully.\n";
}

// DISPLAY
void MyClass::display() {
    if (isempty()) {
        cout << "LIST EMPTY\n";
        return;
    }

    for (int i = 0; i <= last; i++) {
        int avg = (stude[i].g1 + stude[i].g2 + stude[i].g3) / 3;

        cout << i + 1 << "). Name: " << stude[i].name
             << " G1: " << stude[i].g1
             << " G2: " << stude[i].g2
             << " G3: " << stude[i].g3
             << " Ave: " << avg
             << " Remarks: " << (avg >= 75 ? "PASSED" : "FAILED")
             << endl;
    }
}

// UPDATE
void MyClass::updateRecord(string n, int s1, int s2, int s3) {
    int pos = locate(n);

    if (pos == -1) {
        cout << "Not Found\n";
        return;
    }

    stude[pos].g1 = s1;
    stude[pos].g2 = s2;
    stude[pos].g3 = s3;

    cout << "Updated...\n";
}

// DELETE
void MyClass::deleteRecord(string n) {
    int pos = locate(n);

    if (pos == -1) {
        cout << "Not Found\n";
        return;
    }

    // SHIFT LEFT
    for (int i = pos; i < last; i++) {
        stude[i] = stude[i + 1];
    }

    last--;

    cout << "Deleted...\n";
}

// MAIN (simple menu like original)
int main() {
    MyClass obj;
    int choice = 0;
    string n;
    int s1, s2, s3;

    while (choice != 5) {
        cout << "\nMENU\n1.SHOW\n2.ADD\n3.UPDATE\n4.DELETE\n5.EXIT\n";
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        Record temp;

        switch (choice) {
        case 1:
            obj.display();
            break;

        case 2:
            cout << "Enter Name: ";
            getline(cin, temp.name);

            cout << "Enter Grade 1: ";
            cin >> temp.g1;
            cout << "Enter Grade 2: ";
            cin >> temp.g2;
            cout << "Enter Grade 3: ";
            cin >> temp.g3;
            cin.ignore();

            obj.addRecord(temp);
            break;

        case 3:
            obj.display();
            cout << "Enter name: ";
            getline(cin, n);

            cout << "Enter Grade 1: ";
            cin >> s1;
            cout << "Enter Grade 2: ";
            cin >> s2;
            cout << "Enter Grade 3: ";
            cin >> s3;
            cin.ignore();

            obj.updateRecord(n, s1, s2, s3);
            break;

        case 4:
            obj.display();
            cout << "Enter name to delete: ";
            getline(cin, n);

            obj.deleteRecord(n);
            break;

        case 5:
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}