#include <iostream>
using namespace std;

class ATM
{
private:
    long long balance;

public:
    ATM(long long startingBalance)
    {
        balance = startingBalance;
    }

    void withdraw()
    {
        long long amount;

        cout << "PLEASE ENTER THE AMOUNT TO WITHDRAW: ";
        cin >> amount;

        while (amount <= 0 ||
               amount % 100 != 0 ||
               amount > balance)
        {
            if (amount <= 0)
                cout << "Enter an amount greater than zero!" << endl;
            else if (amount % 100 != 0)
                cout << "Only multiples of 100 are allowed!" << endl;
            else
                cout << "Insufficient balance!" << endl;

            cout << "PLEASE ENTER THE AMOUNT TO WITHDRAW: ";
            cin >> amount;
        }

        balance -= amount;

        cout << "WITHDRAWAL SUCCESSFUL!" << endl;
        cout << "AMOUNT WITHDRAWN: " << amount << endl;
        cout << "YOUR REMAINING BALANCE IS: " << balance << endl;
    }
};

int main()
{
    long long startingBalance;

    cout << "PLEASE ENTER YOUR CURRENT BALANCE: ";
    cin >> startingBalance;

    ATM account(startingBalance);
    account.withdraw();

    return 0;
}