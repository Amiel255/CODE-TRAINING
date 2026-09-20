#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX 10

void posdelete(int arr[], int x, int *size);
void updateindex(int arr[], int pos, int size, int updatenum);
int locate (int arr[], int pos, int size);
int removedupe (int arr[], int size);

int main()
{
    int posdel;
    int posupdate;
    int numtoloc;
    int arr[] = {1,2,2,3,4,4,5};
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "Deleted Dupes:";
    size = removedupe(arr, size);
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    system("pause");
    return 0;
}

void posdelete(int arr[], int x, int *size)
{
    for (int i = x; i < *size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

void updateindex(int arr[], int pos, int size, int updatenum)
{
    arr[pos] = updatenum;
}

int locate (int arr[], int numtoloc, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == numtoloc) {
            return i;
        }
    }
    return -1;
}

int removedupe (int arr[], int size) {
    int newsize = size;
    for (int i = 0; i < newsize; i++) { 
        for (int j = i + 1; j < newsize; j++) {
            if (arr[i] == arr[j]) {
                for (int k = j; k < newsize -1; k++) {
                    arr[k] = arr[k + 1];
                }
                newsize--;
                j--;
            }
        }
    }
    return newsize;
}