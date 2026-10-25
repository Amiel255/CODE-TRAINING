#include <iostream>
using namespace std;

struct Node {
    char data;
    Node *left;
    Node *right;

    Node(char x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

class ExpressionTree
{
private:
    Node *root;

public:
    ExpressionTree()
    {
        root = NULL;
    }

    void preorder(Node *n)
    {
        if (n == NULL)
            return;

        cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }

    void inorder(Node *n)
    {
        if (n == NULL)
            return;

        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }

    void postorder(Node *n)
    {
        if (n == NULL)
            return;

        postorder(n->left);
        postorder(n->right);
        cout << n->data << " ";
    }

    int countOperands(Node *n)
    {
        if (n == NULL)
            return 0;

        if (!isOperator(n->data))
            return 1;

        return countOperands(n->left)
             + countOperands(n->right);
    }

    int countOperators(Node *n)
    {
        if (n == NULL)
            return 0;

        if (isOperator(n->data))
            return 1
                 + countOperators(n->left)
                 + countOperators(n->right);

        return 0;
    }
};