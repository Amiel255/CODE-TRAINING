
#include <iostream>
using namespace std;

#define MAX 100

class Set
{
private:
    int elements[MAX];
    int count;

public:
    Set()
    {
        count = 0;
    }

    bool contains(int x)
    {
        for (int i = 0; i < count; i++)
        {
            if (elements[i] == x)
                return true;
        }
        return false;
    }

    bool add(int x)
    {
        if (contains(x) || count == MAX)
            return false;

        elements[count] = x;
        count++;
        return true;
    }

    bool remove(int x)
    {
        for (int i = 0; i < count; i++)
        {
            if (elements[i] == x)
            {
                for (int j = i; j < count - 1; j++)
                {
                    elements[j] = elements[j + 1];
                }
                count--;
                return true;
            }
        }
        return false;
    }

    void display()
    {
        cout << "{";
        for (int i = 0; i < count; i++)
        {
            cout << elements[i];
            if (i < count - 1)
                cout << ", ";
        }
        cout << "}" << endl;
    }

    Set unionSet(Set B)
    {
        Set C;

        for (int i = 0; i < count; i++)
            C.add(elements[i]);

        for (int i = 0; i < B.count; i++)
            C.add(B.elements[i]);

        return C;
    }

    Set intersection(Set B)
    {
        Set C;

        for (int i = 0; i < count; i++)
        {
            if (B.contains(elements[i]))
                C.add(elements[i]);
        }

        return C;
    }

    Set difference(Set B)
    {
        Set C;

        for (int i = 0; i < count; i++)
        {
            if (!B.contains(elements[i]))
                C.add(elements[i]);
        }

        return C;
    }
};

int main()
{
    Set A, B, C;
    int choice, setChoice, value;

    do
    {
        cout << "\n===== SET ADT MENU =====\n";
        cout << "1. Add Element\n";
        cout << "2. Remove Element\n";
        cout << "3. Display Set\n";
        cout << "4. Union\n";
        cout << "5. Intersection\n";
        cout << "6. Difference\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Choose Set (1 - A, 2 - B): ";
            cin >> setChoice;
            cout << "Enter element: ";
            cin >> value;

            if (setChoice == 1)
            {
                if (A.add(value))
                    cout << "Element added to Set A.\n";
                else
                    cout << "Element already exists or set is full.\n";
            }
            else if (setChoice == 2)
            {
                if (B.add(value))
                    cout << "Element added to Set B.\n";
                else
                    cout << "Element already exists or set is full.\n";
            }
            else
                cout << "Invalid set.\n";
            break;

        case 2:
            cout << "Choose Set (1 - A, 2 - B): ";
            cin >> setChoice;
            cout << "Enter element: ";
            cin >> value;

            if (setChoice == 1)
            {
                if (A.remove(value))
                    cout << "Element removed from Set A.\n";
                else
                    cout << "Element not found.\n";
            }
            else if (setChoice == 2)
            {
                if (B.remove(value))
                    cout << "Element removed from Set B.\n";
                else
                    cout << "Element not found.\n";
            }
            else
                cout << "Invalid set.\n";
            break;

        case 3:
            cout << "Set A: ";
            A.display();
            cout << "Set B: ";
            B.display();
            break;

        case 4:
            C = A.unionSet(B);
            cout << "Union: ";
            C.display();
            break;

        case 5:
            C = A.intersection(B);
            cout << "Intersection: ";
            C.display();
            break;

        case 6:
            C = A.difference(B);
            cout << "Difference (A - B): ";
            C.display();
            break;

        case 7:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
