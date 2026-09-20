#include <iostream>
#include <stdlib.h>
using namespace std;
int sum(int *x, int size);
int findMax(int *x, int size);
int counteven(int *x, int size);
void revers(int *x, int size);
int removedupe(int *x, int size);
int factorial(int x);
int fibonacci(int x);
int sumofarray (int *x, int size);
int main()
{
    int maxx;
    int size;
    int evencount;
    int reversing;
     cout << "enter size of array: ";
    cin >> size;
    /*
     int num[size];
    for (int i = 0; i < size; i++)
    {
        cin >> num[i];
        while (cin.fail())
        {
            cout << "Invalid input. Enter an integer: ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> num[i];
        }
    }
    size = removedupe(num, size);
    cout << "Removed Dupe" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << num[i] << " ";
    }
    */

    int n[size];
    for (int i = 0; i < size; i++) {
        cin >> n[i];
        while (cin.fail())
        {
            cout << "Invalid input. Enter an integer: ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> n[i];
        }
    }
    int total = sumofarray(n, size);
    cout << total;
    

    system("pause");
    return 0;
}

int sum(int *x, int size)
{

    int total = 0;
    for (int i = 0; i < size; i++)
    {
        total += *(x + i);
    }
    return total;
}

int findMax(int *x, int size)
{
    int largest = *(x + 0);

    for (int i = 0; i < size; i++)
    {
        if (largest < *(x + i))
        {
            largest = *(x + i);
        }
    }
    return largest;
}

int counteven(int *x, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (*(x + i) % 2 == 0)
        {
            count++;
        }
    }
    return count;
}

void revers(int *x, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        int temp = *(x + i);
        *(x + i) = *(x + (size - 1 - i));
        *(x + (size - 1 - i)) = temp;
    }
}

int removedupe(int *x, int size)
{
    int newsize = size;
    for (int i = 0; i < newsize; i++)
    {
        for (int j = i + 1; j < newsize; j++)
        {
            if (*(x + i) == *(x + j))
            {
                for (int k = j; k < newsize - 1; k++)
                {
                    *(x + k) = *(x + k + 1);
                }
                newsize--;
                j--;
            }
        }
    }
    return newsize;
}

int factorial(int x)
{
    if (x > 0)
    {
        return x * factorial(x - 1);
    }
    else
        return 1;
}

int fibonacci(int x)
{
    if (x == 0) {
        return x;
    } else if (x == 1) {
        return 1;
    } else 
    return fibonacci(x - 1) + fibonacci (x - 2);
}

int sumofarray(int *x, int size) {
    if (size == 0) {
        return 0;
    } else 
    return *x + sumofarray(x + 1, size - 1);
}
    