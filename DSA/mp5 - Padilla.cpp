#include <iostream>
using namespace std;

#define MAX 5

// CIRCULAR ARRAY QUEUE
class CircularQueue
{
private:
    int Q[MAX];
    int front;
    int rear;

public:
    CircularQueue();

    void enqueue(int x);
    void dequeue();
    void display();

    bool isEmpty();
    bool isFull();
};

CircularQueue::CircularQueue()
{
    front = -1;
    rear = -1;
}

bool CircularQueue::isEmpty()
{
    return front == -1;
}

bool CircularQueue::isFull()
{
    return !isEmpty() &&
           (rear + 1) % MAX == front;
}

void CircularQueue::enqueue(int x)
{
    if (isFull())
    {
        cout << "Queue is full.\n";
        return;
    }

    // checking kung una palang gagawin
    if (isEmpty())
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    Q[rear] = x;

    cout << x << " was added to the queue.\n";
}

void CircularQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty.\n";
        return;
    }

    cout << Q[front] << " was removed from the queue.\n";

    // checking kung mag isa lang
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

void CircularQueue::display()
{
    if (isEmpty())
    {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "\nQueue: ";

    int i = front;

    while (true)
    {
        cout << Q[i] << " ";

        if (i == rear)
            break;

        i = (i + 1) % MAX;
    }

    cout << endl;
}

// LINKED LIST QUEUE
class LinkedQueue
{
private:
    struct node
    {
        int data;
        node *next;

        node(int x)
        {
            data = x;
            next = NULL;
        }
    };

    node *front;
    node *rear;

public:
    LinkedQueue();

    void enqueue(int x);
    void dequeue();
    void display();

    bool isEmpty();
};

LinkedQueue::LinkedQueue()
{
    front = NULL;
    rear = NULL;
}

bool LinkedQueue::isEmpty()
{
    return front == NULL;
}

void LinkedQueue::enqueue(int x)
{
    node *newnode = new node(x);

    // checking kung mag isa lang
    if (isEmpty())
    {
        front = newnode;
        rear = newnode;
    }
    else
    {
        rear->next = newnode;
        rear = newnode;
    }

    cout << x << " was added to the queue.\n";
}

void LinkedQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty.\n";
        return;
    }

    node *p = front;

    cout << p->data << " was removed from the queue.\n";

    front = front->next;

    delete p;

    // kung ubos na
    if (front == NULL)
    {
        rear = NULL;
    }
}

void LinkedQueue::display()
{
    if (isEmpty())
    {
        cout << "Queue is empty.\n";
        return;
    }

    node *p = front;

    cout << "\nQueue: ";

    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
}

// MAIN PROGRAM
int main()
{
    CircularQueue circular;
    LinkedQueue linked;

    int choice;
    int option;
    int x;

    while (true)
    {
        cout << "QUEUE IMPLEMENTATION\n";
        cout << "1. Circular Array\n";
        cout << "2. Linked List\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        // CIRCULAR ARRAY
        if (choice == 1)
        {
            while (true)
            {
                cout << "\nCIRCULAR ARRAY QUEUE\n";
                cout << "1. Enqueue\n";
                cout << "2. Dequeue\n";
                cout << "3. Display\n";
                cout << "4. Exit\n";
                cout << "Choice: ";
                cin >> option;

                if (option == 1)
                {
                    cout << "Enter value: ";
                    cin >> x;

                    circular.enqueue(x);
                }

                else if (option == 2)
                {
                    circular.dequeue();
                }

                else if (option == 3)
                {
                    circular.display();
                }

                else if (option == 4)
                {
                    break;
                }

                else
                {
                    cout << "Invalid choice.\n";
                }
            }
        }

        // LINKED LIST
        else if (choice == 2)
        {
            while (true)
            {
                cout << "\nLINKED LIST QUEUE\n";
                cout << "1. Enqueue\n";
                cout << "2. Dequeue\n";
                cout << "3. Display\n";
                cout << "4. Exit\n";
                cout << "Choice: ";
                cin >> option;

                if (option == 1)
                {
                    cout << "Enter value: ";
                    cin >> x;

                    linked.enqueue(x);
                }

                else if (option == 2)
                {
                    linked.dequeue();
                }

                else if (option == 3)
                {
                    linked.display();
                }

                else if (option == 4)
                {
                    break;
                }

                else
                {
                    cout << "Invalid choice.\n";
                }
            }
        }

        else if (choice == 3)
        {
            cout << "Program terminated.\n";
            break;
        }

        else
        {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}