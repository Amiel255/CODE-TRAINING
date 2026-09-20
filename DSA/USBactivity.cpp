#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include <conio.h>

using namespace std;

const string DATABASE_FILE = "accounts.csv";

// ==========================================================
// ACCOUNT STRUCTURE
// ==========================================================

struct Account
{
    string accountNumber;
    string accountName;
    string birthday;
    string contactNumber;
    long long balance;
    string pin; // encrypted PIN
};

// ==========================================================
// NODE FOR DOUBLY LINKED LIST
// ==========================================================

struct node
{
    Account data;
    node *next;
    node *prev;

    node(Account x)
    {
        data = x;
        next = NULL;
        prev = NULL;
    }
};

// ==========================================================
// HELPER FUNCTIONS
// ==========================================================

void pauseScreen()
{
    cout << "\nPress ENTER to continue...";
    string temp;
    getline(cin, temp);
}

// Get a valid menu choice
int getChoice(int minimum, int maximum)
{
    string input;
    int choice;

    while (true)
    {
        cout << "Enter choice: ";
        getline(cin, input);

        stringstream ss(input);

        if (ss >> choice &&
            ss.eof() &&
            choice >= minimum &&
            choice <= maximum)
        {
            return choice;
        }

        cout << "Invalid choice. Please try again.\n";
    }
}

// Get valid amount
long long getAmount(string message)
{
    string input;
    long long amount;

    while (true)
    {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if (ss >> amount && ss.eof())
        {
            return amount;
        }

        cout << "Invalid amount.\n";
    }
}

// Makes sure text does not contain a comma
// because commas are used in accounts.csv
string getText(string message)
{
    string input;

    while (true)
    {
        cout << message;
        getline(cin, input);

        if (input.empty())
        {
            cout << "Input cannot be empty.\n";
        }
        else if (input.find(',') != string::npos)
        {
            cout << "Please do not use commas.\n";
        }
        else
        {
            return input;
        }
    }
}

// Check if string contains digits only
bool digitsOnly(string value)
{
    if (value.empty())
        return false;

    for (char ch : value)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
        {
            return false;
        }
    }

    return true;
}

// ==========================================================
// PIN INPUT
// PIN is hidden using *
// ==========================================================

string getPinInput(string message)
{
    string pin = "";

    cout << message;

    while (true)
    {
        char ch = _getch();

        // ENTER key
        if (ch == '\r')
        {
            cout << endl;
            break;
        }

        // BACKSPACE
        if (ch == '\b')
        {
            if (!pin.empty())
            {
                pin.pop_back();

                cout << "\b \b";
            }
        }

        // Digits only
        else if (isdigit(static_cast<unsigned char>(ch)))
        {
            // Maximum PIN length is 6
            if (pin.length() < 6)
            {
                pin += ch;
                cout << "*";
            }
        }
    }

    return pin;
}

// PIN must contain 4 to 6 digits
bool validPin(string pin)
{
    if (pin.length() < 4 || pin.length() > 6)
    {
        return false;
    }

    return digitsOnly(pin);
}

// ==========================================================
// SIMPLE PIN ENCRYPTION
//
// NOTE:
// This is ONLY for classroom simulation.
// Real banks use much stronger encryption/security.
// ==========================================================

string encryptPin(string pin)
{
    string encrypted = "";

    for (int i = 0; i < pin.length(); i++)
    {
        int digit = pin[i] - '0';

        digit = (digit + 7 + i) % 10;

        encrypted += char('0' + digit);
    }

    reverse(encrypted.begin(), encrypted.end());

    return encrypted;
}

// ==========================================================
// ATM LIST CLASS
// ==========================================================

class ATMList
{
private:
    node *head;
    node *tail;

    string generateAccountNumber();

    string findCard();

    bool readCard(
        string cardPath,
        string &accountNumber,
        string &encryptedPin);

    bool writeCard(
        string cardPath,
        string accountNumber,
        string encryptedPin);

public:
    ATMList();
    ~ATMList();

    void insert(Account x);

    node *searchAccount(string accountNumber);

    void registerAccount();

    void transactionModule();

    void balanceInquiry(node *account);

    void withdraw(node *account);

    void deposit(node *account);

    void fundTransfer(node *account);

    void changePin(
        node *account,
        string cardPath);

    void save();

    void load();
};

// ==========================================================
// CONSTRUCTOR
// ==========================================================

ATMList::ATMList()
{
    head = NULL;
    tail = NULL;
}

// ==========================================================
// DESTRUCTOR
// ==========================================================

ATMList::~ATMList()
{
    node *p = head;

    while (p != NULL)
    {
        node *temp = p;

        p = p->next;

        delete temp;
    }
}

// ==========================================================
// INSERT ACCOUNT
// SORTED BY ACCOUNT NUMBER
// ==========================================================

void ATMList::insert(Account x)
{
    node *newnode = new node(x);

    // Empty list
    if (head == NULL)
    {
        head = newnode;
        tail = newnode;

        return;
    }

    node *p = head;
    node *q = NULL;

    // Find correct location
    while (p != NULL &&
           x.accountNumber > p->data.accountNumber)
    {
        q = p;
        p = p->next;
    }

    // Insert at head
    if (p == head)
    {
        newnode->next = head;

        head->prev = newnode;

        head = newnode;
    }

    // Insert at tail
    else if (p == NULL)
    {
        newnode->prev = tail;

        tail->next = newnode;

        tail = newnode;
    }

    // Insert in middle
    else
    {
        newnode->next = p;
        newnode->prev = q;

        q->next = newnode;

        p->prev = newnode;
    }
}

// ==========================================================
// SEARCH ACCOUNT
// ==========================================================

node *ATMList::searchAccount(string accountNumber)
{
    node *p = head;

    while (p != NULL &&
           p->data.accountNumber != accountNumber)
    {
        p = p->next;
    }

    return p;
}

// ==========================================================
// GENERATE 5 DIGIT ACCOUNT NUMBER
// ==========================================================

string ATMList::generateAccountNumber()
{
    int highest = 10000;

    node *p = head;

    while (p != NULL)
    {
        try
        {
            int number = stoi(p->data.accountNumber);

            if (number > highest)
            {
                highest = number;
            }
        }
        catch (...)
        {
            // Ignore invalid account number
        }

        p = p->next;
    }

    highest++;

    if (highest > 99999)
    {
        return "";
    }

    return to_string(highest);
}

// ==========================================================
// REGISTER NEW ACCOUNT
// ==========================================================

void ATMList::registerAccount()
{
    cout << "\n=====================================\n";
    cout << "       NEW ACCOUNT REGISTRATION\n";
    cout << "=====================================\n\n";

    Account newAccount;

    // Generate account number
    newAccount.accountNumber =
        generateAccountNumber();

    if (newAccount.accountNumber.empty())
    {
        cout << "Cannot create more accounts.\n";
        return;
    }

    newAccount.accountName =
        getText("Account Name: ");

    newAccount.birthday =
        getText("Birthday: ");

    newAccount.contactNumber =
        getText("Contact Number: ");

    // Initial deposit
    while (true)
    {
        newAccount.balance =
            getAmount("Initial Deposit: PHP ");

        if (newAccount.balance < 5000)
        {
            cout << "Minimum initial deposit is PHP 5000.\n";
        }

        else if (newAccount.balance % 100 != 0)
        {
            cout << "Amount must be in multiples of PHP 100.\n";
        }

        else
        {
            break;
        }
    }

    // Get PIN
    string pin;
    string confirmPin;

    while (true)
    {
        pin =
            getPinInput(
                "Enter PIN (4-6 digits): ");

        if (!validPin(pin))
        {
            cout << "PIN must contain 4 to 6 digits.\n";
            continue;
        }

        confirmPin =
            getPinInput(
                "Confirm PIN: ");

        if (pin != confirmPin)
        {
            cout << "PINs do not match.\n";
            continue;
        }

        break;
    }

    // Encrypt PIN
    newAccount.pin =
        encryptPin(pin);

    // ======================================================
    // CREATE ATM CARD ON FLASH DRIVE
    // ======================================================

    cout << "\nInsert the flash drive that will be used";
    cout << " as the ATM card.\n";

    cout << "Check its drive letter in File Explorer.\n";

    string cardPath;

    while (true)
    {
        string drive;

        cout << "\nEnter flash drive letter ";
        cout << "(example E): ";

        getline(cin, drive);

        if (drive.length() != 1 ||
            !isalpha(
                static_cast<unsigned char>(drive[0])))
        {
            cout << "Invalid drive letter.\n";
            continue;
        }

        char letter =
            toupper(drive[0]);

        if (letter < 'D' ||
            letter > 'Z')
        {
            cout << "Please enter a drive letter from D to Z.\n";
            continue;
        }

        cardPath =
            string(1, letter) +
            ":\\pin.code";

        // Check if ATM card already exists
        ifstream existingCard(cardPath);

        if (existingCard)
        {
            existingCard.close();

            cout << "\nThis flash drive already contains ";
            cout << "an ATM card.\n";

            cout << "Please use another flash drive.\n";

            continue;
        }

        // Try writing the card
        if (!writeCard(
                cardPath,
                newAccount.accountNumber,
                newAccount.pin))
        {
            cout << "\nCannot access the flash drive.\n";
            cout << "Check the drive letter or insert ";
            cout << "the flash drive.\n";

            continue;
        }

        break;
    }

    // Insert into linked list
    insert(newAccount);

    // Save database
    save();

    cout << "\n=====================================\n";
    cout << "      REGISTRATION SUCCESSFUL\n";
    cout << "=====================================\n";

    cout << "Account Number : "
         << newAccount.accountNumber
         << endl;

    cout << "Account Name   : "
         << newAccount.accountName
         << endl;

    cout << fixed << setprecision(2);

    cout << "Balance        : PHP "
         << static_cast<double>(newAccount.balance)
         << endl;

    cout << "\nATM Card created successfully.\n";

    cout << "File saved to: "
         << cardPath
         << endl;

    cout << "\nPlease remember your account number";
    cout << " and PIN.\n";
}

// ==========================================================
// FIND ATM CARD
//
// Searches D: to Z: for pin.code
// ==========================================================

string ATMList::findCard()
{
    for (char drive = 'D';
         drive <= 'Z';
         drive++)
    {
        string path =
            string(1, drive) +
            ":\\pin.code";

        ifstream file(path);

        if (file)
        {
            file.close();

            return path;
        }
    }

    return "";
}

// ==========================================================
// READ ATM CARD
// ==========================================================

bool ATMList::readCard(
    string cardPath,
    string &accountNumber,
    string &encryptedPin)
{
    ifstream file(cardPath);

    if (!file)
    {
        return false;
    }

    getline(file, accountNumber);
    getline(file, encryptedPin);

    file.close();

    if (accountNumber.empty() ||
        encryptedPin.empty())
    {
        return false;
    }

    return true;
}

// ==========================================================
// WRITE ATM CARD
// ==========================================================

bool ATMList::writeCard(
    string cardPath,
    string accountNumber,
    string encryptedPin)
{
    ofstream file(cardPath);

    if (!file)
    {
        return false;
    }

    file << accountNumber << endl;
    file << encryptedPin << endl;

    file.close();

    return true;
}

// ==========================================================
// BALANCE INQUIRY
// ==========================================================

void ATMList::balanceInquiry(node *account)
{
    cout << "\n=====================================\n";
    cout << "          BALANCE INQUIRY\n";
    cout << "=====================================\n";

    cout << "Account Number : "
         << account->data.accountNumber
         << endl;

    cout << "Account Name   : "
         << account->data.accountName
         << endl;

    cout << fixed << setprecision(2);

    cout << "Balance        : PHP "
         << static_cast<double>(account->data.balance)
         << endl;
}

// ==========================================================
// WITHDRAW
// ==========================================================

void ATMList::withdraw(node *account)
{
    cout << "\n=====================================\n";
    cout << "              WITHDRAW\n";
    cout << "=====================================\n";

    cout << fixed << setprecision(2);

    cout << "Current Balance: PHP "
         << static_cast<double>(account->data.balance)
         << endl;

    long long amount;

    while (true)
    {
        amount =
            getAmount(
                "Withdraw Amount: PHP ");

        if (amount <= 0)
        {
            cout << "Amount must be greater than zero.\n";
        }

        else if (amount % 100 != 0)
        {
            cout << "Amount must be in multiples of PHP 100.\n";
        }

        else if (amount > account->data.balance)
        {
            cout << "Insufficient balance.\n";
        }

        else
        {
            break;
        }
    }

    account->data.balance -= amount;

    save();

    cout << "\nWithdrawal successful.\n";

    cout << "Amount Withdrawn: PHP "
         << static_cast<double>(amount)
         << endl;

    cout << "Remaining Balance: PHP "
         << static_cast<double>(account->data.balance)
         << endl;
}

// ==========================================================
// DEPOSIT
// ==========================================================

void ATMList::deposit(node *account)
{
    cout << "\n=====================================\n";
    cout << "               DEPOSIT\n";
    cout << "=====================================\n";

    long long amount;

    while (true)
    {
        amount =
            getAmount(
                "Deposit Amount: PHP ");

        if (amount <= 0)
        {
            cout << "Amount must be greater than zero.\n";
        }

        else if (amount % 100 != 0)
        {
            cout << "Amount must be in multiples of PHP 100.\n";
        }

        else
        {
            break;
        }
    }

    account->data.balance += amount;

    save();

    cout << fixed << setprecision(2);

    cout << "\nDeposit successful.\n";

    cout << "Amount Deposited: PHP "
         << static_cast<double>(amount)
         << endl;

    cout << "New Balance: PHP "
         << static_cast<double>(account->data.balance)
         << endl;
}

// ==========================================================
// FUND TRANSFER
// ==========================================================

void ATMList::fundTransfer(node *sender)
{
    cout << "\n=====================================\n";
    cout << "           FUND TRANSFER\n";
    cout << "=====================================\n";

    string accountNumber;

    cout << "Enter destination account number: ";
    getline(cin, accountNumber);

    // Cannot transfer to same account
    if (accountNumber ==
        sender->data.accountNumber)
    {
        cout << "\nYou cannot transfer money ";
        cout << "to the same account.\n";

        return;
    }

    node *receiver =
        searchAccount(accountNumber);

    // Account must be enrolled
    if (receiver == NULL)
    {
        cout << "\nAccount not enrolled.\n";
        return;
    }

    cout << "\nReceiver: "
         << receiver->data.accountName
         << endl;

    long long amount;

    while (true)
    {
        amount =
            getAmount(
                "Transfer Amount: PHP ");

        if (amount <= 0)
        {
            cout << "Amount must be greater than zero.\n";
        }

        else if (amount % 100 != 0)
        {
            cout << "Amount must be in multiples of PHP 100.\n";
        }

        else if (amount >
                 sender->data.balance)
        {
            cout << "Insufficient balance.\n";
        }

        else
        {
            break;
        }
    }

    // Transfer money
    sender->data.balance -= amount;

    receiver->data.balance += amount;

    // Save both account changes
    save();

    cout << fixed << setprecision(2);

    cout << "\n=====================================\n";
    cout << "       TRANSFER SUCCESSFUL\n";
    cout << "=====================================\n";

    cout << "From: "
         << sender->data.accountName
         << endl;

    cout << "To: "
         << receiver->data.accountName
         << endl;

    cout << "Amount: PHP "
         << static_cast<double>(amount)
         << endl;

    cout << "Remaining Balance: PHP "
         << static_cast<double>(sender->data.balance)
         << endl;
}

// ==========================================================
// CHANGE PIN
// ==========================================================

void ATMList::changePin(
    node *account,
    string cardPath)
{
    cout << "\n=====================================\n";
    cout << "             CHANGE PIN\n";
    cout << "=====================================\n";

    string currentPin =
        getPinInput(
            "Enter current PIN: ");

    if (encryptPin(currentPin) !=
        account->data.pin)
    {
        cout << "Incorrect PIN.\n";
        return;
    }

    string newPin;
    string confirmPin;

    while (true)
    {
        newPin =
            getPinInput(
                "Enter new PIN (4-6 digits): ");

        if (!validPin(newPin))
        {
            cout << "PIN must contain 4 to 6 digits.\n";
            continue;
        }

        if (encryptPin(newPin) ==
            account->data.pin)
        {
            cout << "New PIN cannot be the same ";
            cout << "as the current PIN.\n";

            continue;
        }

        confirmPin =
            getPinInput(
                "Confirm new PIN: ");

        if (newPin != confirmPin)
        {
            cout << "PINs do not match.\n";
            continue;
        }

        break;
    }

    string encryptedNewPin =
        encryptPin(newPin);

    // Update flash drive first
    if (!writeCard(
            cardPath,
            account->data.accountNumber,
            encryptedNewPin))
    {
        cout << "\nUnable to update ATM card.\n";
        return;
    }

    // Update linked list
    account->data.pin =
        encryptedNewPin;

    // Update database
    save();

    cout << "\nPIN changed successfully.\n";
}

// ==========================================================
// TRANSACTION MODULE
// ==========================================================

void ATMList::transactionModule()
{
    cout << "\n=====================================\n";
    cout << "          ATM TRANSACTION\n";
    cout << "=====================================\n";

    cout << "\nChecking for ATM card...\n";

    string cardPath =
        findCard();

    // No card
    if (cardPath.empty())
    {
        cout << "\nPlease insert card.\n";
        return;
    }

    cout << "ATM card detected.\n";

    // Read card
    string cardAccountNumber;
    string cardPin;

    if (!readCard(
            cardPath,
            cardAccountNumber,
            cardPin))
    {
        cout << "Invalid ATM card.\n";
        return;
    }

    // Search account in linked list
    node *account =
        searchAccount(cardAccountNumber);

    if (account == NULL)
    {
        cout << "ATM card account is not enrolled.\n";
        return;
    }

    // Cross-check PIN stored in card
    // against PIN stored in linked list
    if (cardPin != account->data.pin)
    {
        cout << "\nATM card verification failed.\n";
        cout << "PIN stored in card does not match ";
        cout << "bank records.\n";

        return;
    }

    cout << "\nAccount Number: "
         << account->data.accountNumber
         << endl;

    // PIN authentication
    bool authenticated = false;

    for (int attempt = 1;
         attempt <= 3;
         attempt++)
    {
        string enteredPin =
            getPinInput(
                "Enter PIN: ");

        string encryptedEnteredPin =
            encryptPin(enteredPin);

        if (encryptedEnteredPin ==
                cardPin &&
            encryptedEnteredPin ==
                account->data.pin)
        {
            authenticated = true;
            break;
        }

        cout << "Incorrect PIN.\n";

        cout << "Attempts remaining: "
             << 3 - attempt
             << endl;
    }

    if (!authenticated)
    {
        cout << "\nToo many incorrect attempts.\n";
        cout << "Transaction cancelled.\n";

        return;
    }

    cout << "\nLogin successful.\n";
    cout << "Welcome, "
         << account->data.accountName
         << "!\n";

    // ======================================================
    // TRANSACTION MENU
    // ======================================================

    while (true)
    {
        cout << "\n=====================================\n";
        cout << "          ATM TRANSACTIONS\n";
        cout << "=====================================\n";

        cout << "[1] Balance Inquiry\n";
        cout << "[2] Withdraw\n";
        cout << "[3] Deposit\n";
        cout << "[4] Fund Transfer\n";
        cout << "[5] Change PIN Code\n";
        cout << "[6] Exit\n";

        cout << "=====================================\n";

        int choice =
            getChoice(1, 6);

        switch (choice)
        {
        case 1:
            balanceInquiry(account);
            pauseScreen();
            break;

        case 2:
            withdraw(account);
            pauseScreen();
            break;

        case 3:
            deposit(account);
            pauseScreen();
            break;

        case 4:
            fundTransfer(account);
            pauseScreen();
            break;

        case 5:
            changePin(
                account,
                cardPath);

            pauseScreen();
            break;

        case 6:
            cout << "\nTransaction session ended.\n";
            cout << "You may now remove your ATM card.\n";

            return;
        }
    }
}

// ==========================================================
// SAVE LINKED LIST TO CSV FILE
// ==========================================================

void ATMList::save()
{
    ofstream file(DATABASE_FILE);

    if (!file)
    {
        cout << "\nError saving account database.\n";
        return;
    }

    node *p = head;

    while (p != NULL)
    {
        file
            << p->data.accountNumber
            << ","
            << p->data.accountName
            << ","
            << p->data.birthday
            << ","
            << p->data.contactNumber
            << ","
            << p->data.balance
            << ","
            << p->data.pin
            << endl;

        p = p->next;
    }

    file.close();
}

// ==========================================================
// LOAD CSV FILE INTO LINKED LIST
// ==========================================================

void ATMList::load()
{
    ifstream file(DATABASE_FILE);

    // First run: database may not exist yet
    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        Account x;

        string balanceText;

        getline(
            ss,
            x.accountNumber,
            ',');

        getline(
            ss,
            x.accountName,
            ',');

        getline(
            ss,
            x.birthday,
            ',');

        getline(
            ss,
            x.contactNumber,
            ',');

        getline(
            ss,
            balanceText,
            ',');

        getline(
            ss,
            x.pin);

        try
        {
            x.balance =
                stoll(balanceText);
        }

        catch (...)
        {
            continue;
        }

        insert(x);
    }

    file.close();
}

// ==========================================================
// MAIN PROGRAM
// ==========================================================

int main()
{
    ATMList atm;

    // Load existing accounts
    atm.load();

    while (true)
    {
        cout << "\n=====================================\n";
        cout << "              ATM SYSTEM\n";
        cout << "=====================================\n";

        cout << "[1] Register New Account\n";
        cout << "[2] ATM Transaction\n";
        cout << "[3] Exit\n";

        cout << "=====================================\n";

        int choice =
            getChoice(1, 3);

        switch (choice)
        {
        case 1:
            atm.registerAccount();
            pauseScreen();
            break;

        case 2:
            atm.transactionModule();
            pauseScreen();
            break;

        case 3:
            atm.save();

            cout << "\nThank you for using the ATM System.\n";

            return 0;
        }
    }

    return 0;
}