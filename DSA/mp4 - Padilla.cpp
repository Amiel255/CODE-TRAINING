#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 5
// ARRAY IMPLEMENTATION
class StackArray
{
private:
    int data[MAX];
    int top;

public:
    StackArray();

    void push(int x);
    void pop();
    void displayTop();
    void display();

    bool isEmpty();
    bool isFull();
};

StackArray::StackArray()
{
    top = MAX; // empty stack
}

bool StackArray::isEmpty()
{
    return top == MAX;
}

bool StackArray::isFull()
{
    return top == 0;
}

void StackArray::push(int x)
{
    if (isFull())
    {
        cout << "Stack is full.\n";
        return;
    }

    top--;
    data[top] = x;
}

void StackArray::pop()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    cout << data[top] << " was removed.\n";

    top++;
}

void StackArray::displayTop()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "Top: " << data[top] << endl;
}

void StackArray::display()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "STACK\n";

    for (int i = top; i < MAX; i++)
    {
        cout << data[i] << endl;
    }
}

// POINTER IMPLEMENTATION
struct Node
{
    int data;
    Node *next;
};

class StackPointer
{
private:
    Node *top;

public:
    StackPointer();

    void push(int x);
    void pop();
    void displayTop();
    void display();

    bool isEmpty();
};

StackPointer::StackPointer()
{
    top = NULL;
}

bool StackPointer::isEmpty()
{
    return top == NULL;
}

void StackPointer::push(int x)
{
    Node *newnode = new Node;

    newnode->data = x;
    newnode->next = top;

    top = newnode;

    cout << x << " pushed into stack.\n";
}

void StackPointer::pop()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    Node *p = top;

    cout << top->data << " was removed.\n";

    top = top->next;

    delete p;
}

void StackPointer::displayTop()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "Top: " << top->data << endl;
}

void StackPointer::display()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return;
    }

    Node *p = top;

    cout << "\nSTACK\n";

    while (p != NULL)
    {
        cout << p->data << endl;

        p = p->next;
    }
}

// MAIN
int main()
{
    StackArray arrayStack;
    StackPointer pointerStack;

    int mainChoice;
    int choice;
    int x;

    while (true)
    {
        system("cls");

        cout << "STACK MENU\n\n";
        cout << "1. Array Implementation\n";
        cout << "2. Pointer Implementation\n";
        cout << "3. Exit\n";
        cout << "\nChoice: ";

        cin >> mainChoice;

        // ARRAY IMPLEMENTATION
        if (mainChoice == 1)
        {
            while (true)
            {
                system("cls");

                cout << "ARRAY IMPLEMENTATION\n\n";
                cout << "1. Push\n";
                cout << "2. Pop\n";
                cout << "3. Top\n";
                cout << "4. Display\n";
                cout << "5. Exit\n";
                cout << "\nChoice: ";

                cin >> choice;

                if (choice == 1)
                {
                    cout << "Enter number: ";
                    cin >> x;

                    arrayStack.push(x);
                }

                else if (choice == 2)
                {
                    arrayStack.pop();
                    system("pause");
                }

                else if (choice == 3)
                {
                    arrayStack.displayTop();
                    system("pause");
                }

                else if (choice == 4)
                {
                    arrayStack.display();
                    system("pause");
                }

                else if (choice == 5)
                {
                    break;
                }

                else
                {
                    cout << "Invalid choice.\n";
                    system("pause");
                }
            }
        }

        // POINTER IMPLEMENTATION
        else if (mainChoice == 2)
        {
            while (true)
            {
                system("cls");

                cout << "POINTER IMPLEMENTATION\n\n";
                cout << "1. Push\n";
                cout << "2. Pop\n";
                cout << "3. Top\n";
                cout << "4. Display\n";
                cout << "5. Exit\n";
                cout << "\nChoice: ";

                cin >> choice;

                if (choice == 1)
                {
                    cout << "Enter number: ";
                    cin >> x;

                    pointerStack.push(x);
                }

                else if (choice == 2)
                {
                    pointerStack.pop();
                    system("pause");
                }

                else if (choice == 3)
                {
                    pointerStack.displayTop();
                    system("pause");
                }

                else if (choice == 4)
                {
                    pointerStack.display();
                    system("pause");
                }

                else if (choice == 5)
                {
                    break;
                }

                else
                {
                    cout << "Invalid choice.\n";
                    system("pause");
                }
            }
        }

        else if (mainChoice == 3)
        {
            break;
        }

        else
        {
            cout << "Invalid choice.\n";
            system("pause");
        }
    }

    return 0;
}