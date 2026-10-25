
#include <iostream>
using namespace std;

#define SIZE 10

struct Node {
    int key;
    Node* next;

    Node(int value) {
        key = value;
        next = NULL;
    }
};

class HashTable {
private:
    Node* table[SIZE];

    int hashFunction(int key) {
        return (key % SIZE + SIZE) % SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
    }

    void insert(int key) {
        int index = hashFunction(key);

        Node* temp = table[index];

        while (temp != NULL) {
            if (temp->key == key) {
                cout << "Duplicate key.\n";
                return;
            }
            temp = temp->next;
        }

        Node* newNode = new Node(key);

        if (table[index] == NULL) {
            table[index] = newNode;
        }
        else {
            temp = table[index];

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }

        cout << "Inserted at index " << index << endl;
    }

    int search(int key) {
        int index = hashFunction(key);

        Node* temp = table[index];

        while (temp != NULL) {
            if (temp->key == key)
                return index;

            temp = temp->next;
        }

        return -1;
    }

    void remove(int key) {
        int index = hashFunction(key);

        Node* temp = table[index];
        Node* prev = NULL;

        while (temp != NULL) {
            if (temp->key == key) {
                if (prev == NULL)
                    table[index] = temp->next;
                else
                    prev->next = temp->next;

                delete temp;

                cout << "Key deleted from index "
                     << index << endl;
                return;
            }

            prev = temp;
            temp = temp->next;
        }

        cout << "Key not found.\n";
    }

    void display() {
        cout << "\nINDEX\tVALUE\n";
        cout << "-----------------------------\n";

        for (int i = 0; i < SIZE; i++) {
            cout << i << "\t";

            Node* temp = table[i];

            if (temp == NULL) {
                cout << "EMPTY";
            }
            else {
                while (temp != NULL) {
                    cout << temp->key;

                    if (temp->next != NULL)
                        cout << " -> ";

                    temp = temp->next;
                }
            }

            cout << endl;
        }
    }

    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            Node* temp = table[i];

            while (temp != NULL) {
                Node* nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }
        }
    }
};

int menu() {
    int op;

    cout << "\n===== HASH TABLE MENU =====\n";
    cout << "1. Insert Key\n";
    cout << "2. Search Key\n";
    cout << "3. Delete Key\n";
    cout << "4. Display Table\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
    cin >> op;

    return op;
}

int main() {
    HashTable h;
    int key;

    while (true) {
        switch (menu()) {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            h.insert(key);
            break;

        case 2:
            cout << "Enter key to search: ";
            cin >> key;

            {
                int pos = h.search(key);

                if (pos != -1)
                    cout << "Key found at index "
                         << pos << endl;
                else
                    cout << "Key not found.\n";
            }
            break;

        case 3:
            cout << "Enter key to delete: ";
            cin >> key;
            h.remove(key);
            break;

        case 4:
            h.display();
            break;

        case 5:
            cout << "Program terminated.\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
