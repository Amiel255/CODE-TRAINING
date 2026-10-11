#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;

    Node(int v)
    {
        value = v;
        left = NULL;
        right = NULL;
    }
};

struct QNode
{
    Node *item;
    QNode *next;

    QNode(Node *n)
    {
        item = n;
        next = NULL;
    }
};

class Queue
{
private:
    QNode *front;
    QNode *back;

public:
    Queue()
    {
        front = NULL;
        back = NULL;
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    void enqueue(Node *item)
    {
        QNode *added = new QNode(item);

        if (back == NULL)
        {
            front = added;
            back = added;
            return;
        }

        back->next = added;
        back = added;
    }

    Node *dequeue()
    {
        if (isEmpty())
            return NULL;

        QNode *removed = front;
        Node *item = front->item;

        front = front->next;

        if (front == NULL)
            back = NULL;

        delete removed;

        return item;
    }
};

class Btree
{
private:
    Node *root;

public:
    Btree()
    {
        root = NULL;
    }

    void inorder(Node *node)
    {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->value << " ";
        inorder(node->right);
    }

    void preorder(Node *node)
    {
        if (node == NULL)
            return;

        cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node *node)
    {
        if (node == NULL)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->value << " ";
    }

    void levelorder(Node *node)
    {
        if (node == NULL)
            return;

        Queue q;

        q.enqueue(node);

        while (!q.isEmpty())
        {
            Node *current = q.dequeue();

            cout << current->value << " ";

            if (current->left != NULL)
                q.enqueue(current->left);

            if (current->right != NULL)
                q.enqueue(current->right);
        }
    }

    void buildTree()
    {
        int val;

        cout << "Enter root: ";
        cin >> val;
        root = new Node(val);

        cout << "Enter left of " << root->value << " (-1 if none): ";
        cin >> val;

        if (val != -1)
            root->left = new Node(val);

        cout << "Enter right of " << root->value << " (-1 if none): ";
        cin >> val;

        if (val != -1)
            root->right = new Node(val);

        if (root->left != NULL)
        {
            cout << "Enter left of " << root->left->value << " (-1 if none): ";
            cin >> val;

            if (val != -1)
                root->left->left = new Node(val);

            cout << "Enter right of " << root->left->value << " (-1 if none): ";
            cin >> val;

            if (val != -1)
                root->left->right = new Node(val);
        }

        if (root->right != NULL)
        {
            cout << "Enter left of " << root->right->value << " (-1 if none): ";
            cin >> val;

            if (val != -1)
                root->right->left = new Node(val);

            cout << "Enter right of " << root->right->value << " (-1 if none): ";
            cin >> val;

            if (val != -1)
                root->right->right = new Node(val);
        }
    }

    void displayInorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }

    void displayLevelorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "Level order: ";
        levelorder(root);
        cout << endl;
    }
};

int main()
{
    Btree bt;
    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1. Inorder\n";
        cout << "2. Preorder\n";
        cout << "3. Postorder\n";
        cout << "4. Level order\n";
        cout << "5. Build tree\n";
        cout << "6. Exit\n";
        cout << "==========================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            bt.displayInorder();
            break;

        case 2:
            bt.displayPreorder();
            break;

        case 3:
            bt.displayPostorder();
            break;

        case 4:
            bt.displayLevelorder();
            break;

        case 5:
            bt.buildTree();
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
