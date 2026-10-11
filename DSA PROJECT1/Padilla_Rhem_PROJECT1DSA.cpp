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

// ============ ACCOUNT STRUCTURE ============
struct Account
{
    string accountNumber;
    string accountName;
    string birthday;
    string contactNumber;
    long long balance;
    string pin; // encrypted pin
};

// ============ DOUBLY LINKED LIST NODE ============
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

// ============ HELPER FUNCTIONS ============
void pauseScreen()
{
    cout << "\nPress ENTER to continue...";
    string temp;
    getline(cin, temp);
}

int getChoice(int minimum, int maximum);

int askAfterTransaction(string statusMessage)
{
    // parehong flow ito after successful or cancelled na transaction
    while (true)
    {
        cout << "\n"
             << statusMessage << "\n";
        cout << "[1] Make another transaction\n";
        cout << "[2] Eject card\n";
        int choice = getChoice(1, 2);
        if (choice == -2)
            continue;
        return choice;
    }
}

int askAfterCancel()
{
    return askAfterTransaction("Transaction cancelled.");
}

int askAfterSuccess()
{
    return askAfterTransaction("Transaction successful.");
}

// kumuha ng valid na menu choice
int getChoice(int minimum, int maximum)
{
    string input;
    int choice;
    while (true)
    {
        cout << "Enter choice: ";
        input.clear();
        while (true)
        {
            char ch = _getch();
            // bawat key ay chine-check para controlled ang input ng user
            if (ch == '\r')
            {
                cout << endl;
                break;
            }
            if (ch == '\b')
            {
                if (!input.empty())
                {
                    input.pop_back();
                    cout << "\b \b";
                }
            }
            else if (ch == 27)
            {
                return -2;
            }

            else if (isdigit(static_cast<unsigned char>(ch)))
            {
                // digits lang ang tinatanggap para valid ang menu choice
                input += ch;
                cout << ch;
            }
        }

        stringstream ss(input);
        if (ss >> choice && ss.eof() && choice >= minimum && choice <= maximum)
            return choice;
        cout << "Invalid choice. Please try again.\n";
    }
}

// kumuha ng valid na amount
long long getAmount(string message)
{
    string input;
    long long amount;
    while (true)
    {
        cout << message;
        input.clear();
        while (true)
        {
            char ch = _getch();
            // amount lang ang binabasa dito, kaya number at minus sign lang
            if (ch == '\r')
            {
                cout << endl;
                break;
            }
            if (ch == '\b')
            {
                if (!input.empty())
                {
                    input.pop_back();
                    cout << "\b \b";
                }
            }
            else if (ch == 27)
            {
                return -2;
            }
            else if (ch == '-' || isdigit(static_cast<unsigned char>(ch)))
            {
                input += ch;
                cout << ch;
            }
        }

        stringstream ss(input);
        if (ss >> amount && ss.eof())
            return amount;
        cout << "Invalid amount.\n";
    }
}

// check kung walang comma para di maka interfere sa ginagamit sa accounts.csv
string getText(string message)
{
    string input;
    while (true)
    {
        cout << message;
        getline(cin, input);
        if (input.empty())
            cout << "Input cannot be empty.\n";
        else if (input.find(',') != string::npos)
            cout << "Please do not use commas.\n";
        else
            return input;
    }
}

// check kung digits lang ang laman
bool digitsOnly(string value)
{
    if (value.empty())
        return false;
    for (char ch : value)
    {
        if (!isdigit(static_cast<unsigned char>(ch)))
            return false;
    }
    return true;
}

// ============ PIN INPUT (tago gamit ang *) ============
string getPinInput(string message)
{
    string pin = "";
    cout << message;
    while (true)
    {
        char ch = _getch();
        if (ch == '\r')
        { // ENTER key
            cout << endl;
            break;
        }
        if (ch == '\b')
        { // BACKSPACE
            if (!pin.empty())
            {
                pin.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 27)
        {
            return "";
        }
        else if (isdigit(static_cast<unsigned char>(ch)))
        { // digit lang
            if (pin.length() < 6)
            { // max na 6 ang PIN
                pin += ch;
                cout << "*";
            }
        }
    }
    return pin;
}

// kailangan 4 hanggang 6 digit ang PIN
bool validPin(string pin)
{
    if (pin.length() < 4 || pin.length() > 6)
        return false;
    return digitsOnly(pin);
}

// ============ SIMPLE PIN ENCRYPTION ============
// TANDAAN: para sa classroom simulation lang ito,
// mas malakas ang encryption ng mga totoong bangko.
string encryptPin(string pin)
{
    string encrypted = "";
    for (int i = 0; i < pin.length(); i++)
    {
        int digit = pin[i] - '0';
        digit = (digit + 7 + i) % 10; 
        encrypted += char('0' + digit);
    }
    reverse(encrypted.begin(), encrypted.end()); // dito ginamit algo lib para sa simple encryption kasi nireverse
    return encrypted;
}

// ============ ATM LIST CLASS ============
class ATMList
{
private:
    node *head;
    node *tail;
    string generateAccountNumber();
    string findCard();
    bool readCard(string cardPath, string &accountNumber, string &encryptedPin);
    bool writeCard(string cardPath, string accountNumber, string encryptedPin);

public:
    ATMList();
    ~ATMList();
    void insert(Account x);
    node *searchAccount(string accountNumber);
    void registerAccount();
    void transactionModule();
    void balanceInquiry(node *account);
    int withdraw(node *account);
    int deposit(node *account);
    int fundTransfer(node *account);
    int changePin(node *account, string cardPath);
    void save();
    void load();
    void Display();
};

// ============ CONSTRUCTOR ============
ATMList::ATMList()
{
    head = NULL;
    tail = NULL;
}

// ============ DESTRUCTOR ============
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

// ============ INSERT ACCOUNT (SORTED BY ACCOUNT NUMBER) ============
void ATMList::insert(Account x)
{
    // sine-sort ang accounts habang iniinsert para maayos ang linked list
    node *newnode = new node(x);
    if (head == NULL)
    { // walang laman ang list
        head = newnode;
        tail = newnode;
        return;
    }
    node *p = head;
    node *q = NULL;
    // p ang current node, habang q ang previous node na nasa likod ni p
    while (p != NULL && x.accountNumber > p->data.accountNumber)
    { // hanapin ang tamang pwesto
        q = p;
        p = p->next;
    }
    if (p == head)
    { // sa unahan
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    else if (p == NULL)
    { // sa dulo
        newnode->prev = tail;
        tail->next = newnode;
        tail = newnode;
    }
    else
    { // sa gitna
        newnode->next = p;
        newnode->prev = q;
        q->next = newnode;
        p->prev = newnode;
    }
}

// ============ SEARCH ACCOUNT ============
node *ATMList::searchAccount(string accountNumber)
{
    node *p = head;
    while (p != NULL && p->data.accountNumber != accountNumber)
        p = p->next;
    return p;
}

// ============ GENERATE 5 DIGIT ACCOUNT NUMBER ============
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
                highest = number;
        }
        catch (...)
        {
            // ignore ang maling account number
        }
        p = p->next;
    }
    highest++;
    if (highest > 99999)
        return "";
    return to_string(highest);
}

// ============ REGISTER NEW ACCOUNT ============
void ATMList::registerAccount()
{
    cout << "\n=====================================\n";
    cout << "       NEW ACCOUNT REGISTRATION\n";
    cout << "=====================================\n\n";

    Account newAccount;
    newAccount.accountNumber = generateAccountNumber(); // generate account number
    if (newAccount.accountNumber.empty())
    {
        cout << "Cannot create more accounts.\n";
        return;
    }
    newAccount.accountName = getText("Account Name: ");
    newAccount.birthday = getText("Birthday (DD/MM/YYYY): ");
    newAccount.contactNumber = getText("Contact Number: ");

    // initial deposit
    while (true)
    {
        newAccount.balance = getAmount("Initial Deposit: PHP ");
        if (newAccount.balance < 5000)
            cout << "Minimum initial deposit is PHP 5000.\n";
        else if (newAccount.balance % 100 != 0)
            cout << "Amount must be in multiples of PHP 100.\n";
        else
            break;
    }

    // kumuha ng PIN
    string pin;
    string confirmPin;
    while (true)
    {
        pin = getPinInput("Enter PIN (4-6 digits): ");
        if (pin.empty())
        {
            cout << "Registration cancelled.\n";
            return;
        }
        if (!validPin(pin))
        {
            cout << "PIN must contain 4 to 6 digits.\n";
            continue;
        }
        confirmPin = getPinInput("Confirm PIN: ");
        if (confirmPin.empty())
        {
            cout << "Registration cancelled.\n";
            return;
        }
        if (pin != confirmPin)
        {
            cout << "PINs do not match.\n";
            continue;
        }
        break;
    }

    // i-encrypt ang PIN
    newAccount.pin = encryptPin(pin);

    // ============ GUMAGAWA NG ATM CARD SA FLASH DRIVE ============
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
        if (drive.length() != 1 || !isalpha(static_cast<unsigned char>(drive[0])))
        {
            cout << "Invalid drive letter.\n";
            continue;
        }
        char letter = toupper(drive[0]);
        if (letter < 'D' || letter > 'Z')
        {
            cout << "Please enter a drive letter from D to Z.\n";
            continue;
        }
        cardPath = string(1, letter) + ":\\pin.code";
        ifstream existingCard(cardPath); // check kung may ATM card na
        if (existingCard)
        {
            existingCard.close();
            cout << "\nThis flash drive already contains ";
            cout << "an ATM card.\n";
            cout << "Please use another flash drive.\n";
            continue;
        }
        if (!writeCard(cardPath, newAccount.accountNumber, newAccount.pin))
        { // subukang i-sulat ang card
            cout << "\nCannot access the flash drive.\n";
            cout << "Check the drive letter or insert ";
            cout << "the flash drive.\n";
            continue;
        }
        break;
    }

    insert(newAccount); // ipasok sa linked list
    save();             // i-save ang database

    cout << "\n=====================================\n";
    cout << "      REGISTRATION SUCCESSFUL\n";
    cout << "=====================================\n";
    cout << "Account Number : " << newAccount.accountNumber << endl;
    cout << "Account Name   : " << newAccount.accountName << endl;
    cout << fixed << setprecision(2);
    cout << "Balance        : PHP " << static_cast<double>(newAccount.balance) << endl;
    cout << "\nATM Card created successfully.\n";
    cout << "File saved to: " << cardPath << endl;
    cout << "\nPlease remember your account number";
    cout << " and PIN.\n";
}

// ============ FIND ATM CARD (hanapin D: hanggang Z:) ============
string ATMList::findCard()
{
    for (char drive = 'D'; drive <= 'Z'; drive++)
    {
        string path = string(1, drive) + ":\\pin.code";
        ifstream file(path);
        if (file)
        {
            file.close();
            return path;
        }
    }
    return "";
}

// ============ READ ATM CARD ============
bool ATMList::readCard(string cardPath, string &accountNumber, string &encryptedPin)
{
    ifstream file(cardPath);
    if (!file)
        return false;
    getline(file, accountNumber);
    getline(file, encryptedPin);
    file.close();
    if (accountNumber.empty() || encryptedPin.empty())
        return false;
    return true;
}

// ============ WRITE ATM CARD ============
bool ATMList::writeCard(string cardPath, string accountNumber, string encryptedPin)
{
    ofstream file(cardPath);
    if (!file)
        return false;
    file << accountNumber << endl;
    file << encryptedPin << endl;
    file.close();
    return true;
}

// ============ BALANCE INQUIRY ============
void ATMList::balanceInquiry(node *account)
{
    cout << "\n=====================================\n";
    cout << "          BALANCE INQUIRY\n";
    cout << "=====================================\n";
    cout << "Account Number : " << account->data.accountNumber << endl;
    cout << "Account Name   : " << account->data.accountName << endl;
    cout << fixed << setprecision(2);
    cout << "Balance        : PHP " << static_cast<double>(account->data.balance) << endl;
}

// ============ WITHDRAW ============
int ATMList::withdraw(node *account)
{
    cout << "\n=====================================\n";
    cout << "              WITHDRAW\n";
    cout << "=====================================\n";
    cout << fixed << setprecision(2);
    cout << "Current Balance: PHP " << static_cast<double>(account->data.balance) << endl;

    long long amount;
    while (true)
    {
        amount = getAmount("Withdraw Amount: PHP ");
        if (amount == -2)
        {
            // -2 galing sa ESC; dito pinapadaan ang cancel/eject decision
            int nextChoice = askAfterCancel();
            if (nextChoice == 1)
                return 0;
            cout << "\nYou may now remove your ATM card.\n";
            return -1;
        }
        if (amount == -3)
        {
            cout << "Transaction cancelled. Returning to transaction menu.\n";
            return 0;
        }
        if (amount <= 0)
            cout << "Amount must be greater than zero.\n";
        else if (amount % 100 != 0)
            cout << "Amount must be in multiples of PHP 100.\n";
        else if (amount > account->data.balance)
            cout << "Insufficient balance.\n";
        else
            break;
    }

    account->data.balance -= amount;
    save();
    cout << "\nWithdrawal successful.\n";
    cout << "Amount Withdrawn: PHP " << static_cast<double>(amount) << endl;
    cout << "Remaining Balance: PHP " << static_cast<double>(account->data.balance) << endl;
    return 1;
}

// ============ DEPOSIT ============
int ATMList::deposit(node *account)
{
    cout << "\n=====================================\n";
    cout << "               DEPOSIT\n";
    cout << "=====================================\n";

    long long amount;
    while (true)
    {
        amount = getAmount("Deposit Amount: PHP ");
        if (amount == -2)
        {
            // kapag ESC, walang mababago sa balance
            int nextChoice = askAfterCancel();
            if (nextChoice == 1)
                return 0;
            cout << "\nYou may now remove your ATM card.\n";
            return -1;
        }
        if (amount == -3)
        {
            cout << "Transaction cancelled. Returning to transaction menu.\n";
            return 0;
        }
        if (amount <= 0)
            cout << "Amount must be greater than zero.\n";
        else if (amount % 100 != 0)
            cout << "Amount must be in multiples of PHP 100.\n";
        else
            break;
    }

    account->data.balance += amount;
    save();
    cout << fixed << setprecision(2);
    cout << "\nDeposit successful.\n";
    cout << "Amount Deposited: PHP " << static_cast<double>(amount) << endl;
    cout << "New Balance: PHP " << static_cast<double>(account->data.balance) << endl;
    return 1;
}

// ============ FUND TRANSFER ============
int ATMList::fundTransfer(node *sender)
{
    cout << "\n=====================================\n";
    cout << "           FUND TRANSFER\n";
    cout << "=====================================\n";

    string accountNumber;
    cout << "Enter destination account number: ";
    getline(cin, accountNumber);

    if (accountNumber == sender->data.accountNumber)
    { // hindi pwede mag-transfer sa sariling account
        cout << "\nYou cannot transfer money ";
        cout << "to the same account.\n";
        return 0;
    }
    node *receiver = searchAccount(accountNumber);
    if (receiver == NULL)
    { // kailangan enrolled ang account
        cout << "\nAccount not enrolled.\n";
        return 0;
    }
    cout << "\nReceiver: " << receiver->data.accountName << endl;

    long long amount;
    while (true)
    {
        amount = getAmount("Transfer Amount: PHP ");
        if (amount == -2)
        {
            int nextChoice = askAfterCancel();
            if (nextChoice == 1)
                return 0;
            cout << "\nYou may now remove your ATM card.\n";
            return -1;
        }
        if (amount <= 0)
            cout << "Amount must be greater than zero.\n";
        else if (amount % 100 != 0)
            cout << "Amount must be in multiples of PHP 100.\n";
        else if (amount > sender->data.balance)
            cout << "Insufficient balance.\n";
        else
            break;
    }

    // parehong accounts kailangang ma-update bago i-save ang transfer
    sender->data.balance -= amount; // ilipat ang pera
    receiver->data.balance += amount;
    save(); // i-save ang mga pagbabago

    cout << fixed << setprecision(2);
    cout << "\n=====================================\n";
    cout << "       TRANSFER SUCCESSFUL\n";
    cout << "=====================================\n";
    cout << "From: " << sender->data.accountName << endl;
    cout << "To: " << receiver->data.accountName << endl;
    cout << "Amount: PHP " << static_cast<double>(amount) << endl;
    cout << "Remaining Balance: PHP " << static_cast<double>(sender->data.balance) << endl;
    return 1;
}

// ============ CHANGE PIN ============
int ATMList::changePin(node *account, string cardPath)
{
    cout << "\n=====================================\n";
    cout << "             CHANGE PIN\n";
    cout << "=====================================\n";

    string currentPin = getPinInput("Enter current PIN: ");
    if (currentPin.empty())
    {
        cout << "PIN change cancelled.\n";
        return 0;
    }
    if (encryptPin(currentPin) != account->data.pin)
    {
        cout << "Incorrect PIN.\n";
        return 0;
    }

    string newPin;
    string confirmPin;
    while (true)
    {
        newPin = getPinInput("Enter new PIN (4-6 digits): ");
        if (newPin.empty())
        {
            cout << "PIN change cancelled.\n";
            return 0;
        }
        if (!validPin(newPin))
        {
            cout << "PIN must contain 4 to 6 digits.\n";
            continue;
        }
        if (encryptPin(newPin) == account->data.pin)
        {
            cout << "New PIN cannot be the same ";
            cout << "as the current PIN.\n";
            continue;
        }
        confirmPin = getPinInput("Confirm new PIN: ");
        if (confirmPin.empty())
        {
            cout << "PIN change cancelled.\n";
            return 0;
        }
        if (newPin != confirmPin)
        {
            cout << "PINs do not match.\n";
            continue;
        }
        break;
    }

    string encryptedNewPin = encryptPin(newPin);
    if (!writeCard(cardPath, account->data.accountNumber, encryptedNewPin))
    { // update muna ang flash drive
        cout << "\nUnable to update ATM card.\n";
        return 0;
    }
    // card file at linked list dapat pareho ang bagong encrypted PIN
    account->data.pin = encryptedNewPin; // i-update ang linked list
    save();                              // i-update ang database
    cout << "\nPIN changed successfully.\n";
    return 1;
}

// ============ TRANSACTION MODULE ============
void ATMList::transactionModule()
{
    cout << "\n=====================================\n";
    cout << "          ATM TRANSACTION\n";
    cout << "=====================================\n";

    cout << "\nChecking for ATM card...\n";
    string cardPath = findCard();
    if (cardPath.empty())
    { // walang card
        cout << "\nPlease insert card.\n";
        return;
    }
    cout << "ATM card detected.\n";

    string cardAccountNumber;
    string cardPin;
    if (!readCard(cardPath, cardAccountNumber, cardPin))
    { // basahin ang card
        cout << "Invalid ATM card.\n";
        return;
    }
    node *account = searchAccount(cardAccountNumber); // hanapin ang account sa linked list
    if (account == NULL)
    {
        cout << "ATM card account is not enrolled.\n";
        return;
    }
    if (cardPin != account->data.pin)
    { // i-cross-check ang PIN sa card sa PIN sa records
        cout << "\nATM card verification failed.\n";
        cout << "PIN stored in card does not match ";
        cout << "bank records.\n";
        return;
    }
    cout << "\nAccount Number: " << account->data.accountNumber << endl;

    // PIN authentication (3 attempts lang)
    bool authenticated = false;
    for (int attempt = 1; attempt <= 3; attempt++)
    {
        string enteredPin = getPinInput("Enter PIN: ");
        if (enteredPin.empty())
        {
            int nextChoice = askAfterCancel();
            if (nextChoice == 1)
                return;
            cout << "\nYou may now remove your ATM card.\n";
            return;
        }
        string encryptedEnteredPin = encryptPin(enteredPin);
        if (encryptedEnteredPin == cardPin && encryptedEnteredPin == account->data.pin)
        {
            authenticated = true;
            break;
        }
        cout << "Incorrect PIN.\n";
        cout << "Attempts remaining: " << 3 - attempt << endl;
    }
    if (!authenticated)
    {
        cout << "\nToo many incorrect attempts.\n";
        cout << "Transaction cancelled.\n";
        return;
    }
    cout << "\nLogin successful.\n";
    cout << "Welcome, " << account->data.accountName << "!\n";

    // ============ TRANSACTION MENU ============
    // tuloy-tuloy ang menu hanggang piliin ng user ang eject o exit
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

        int choice = getChoice(1, 6);
        if (choice == -2)
        {
            int nextChoice = askAfterCancel();
            if (nextChoice == 1)
                continue;
            cout << "\nYou may now remove your ATM card.\n";
            return;
        }
        if (choice == -3)
        {
            cout << "Transaction cancelled. Returning to transaction menu.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            balanceInquiry(account);
            pauseScreen();
            {
                int nextChoice = askAfterSuccess();
                if (nextChoice == 1)
                    continue;
                cout << "\nYou may now remove your ATM card.\n";
                return;
            }
            break;
        case 2:
        {
            // 1 = success, 0 = balik menu, -1 = eject card
            int result = withdraw(account);
            if (result == 0)
                continue;
            if (result == -1)
                return;
            pauseScreen();
            int nextChoice = askAfterSuccess();
            if (nextChoice == 1)
                continue;
            cout << "\nYou may now remove your ATM card.\n";
            return;
        }
        break;
        case 3:
        {
            // ginagamit ang result para hindi ma-label na successful ang cancelled transaction
            int result = deposit(account);
            if (result == 0)
                continue;
            if (result == -1)
                return;
            pauseScreen();
            int nextChoice = askAfterSuccess();
            if (nextChoice == 1)
                continue;
            cout << "\nYou may now remove your ATM card.\n";
            return;
        }
        break;
        case 4:
        {
            int result = fundTransfer(account);
            if (result == 0)
                continue;
            if (result == -1)
                return;
            pauseScreen();
            int nextChoice = askAfterSuccess();
            if (nextChoice == 1)
                continue;
            cout << "\nYou may now remove your ATM card.\n";
            return;
        }
        break;
        case 5:
        {
            int result = changePin(account, cardPath);
            if (result == 0)
                continue;
            if (result == -1)
                return;
            pauseScreen();
            int nextChoice = askAfterSuccess();
            if (nextChoice == 1)
                continue;
            cout << "\nYou may now remove your ATM card.\n";
            return;
        }
        break;
        case 6:
            cout << "\nTransaction session ended.\n";
            cout << "You may now remove your ATM card.\n";
            return;
        }
    }
}

// ============ SAVE LINKED LIST TO CSV FILE ============
void ATMList::save()
{
    ofstream file(DATABASE_FILE);
    if (!file)
    {
        cout << "\nError saving account database.\n";
        return;
    }
    // bawat node ay sinusulat sa CSV para hindi mawala ang account changes
    node *p = head;
    while (p != NULL)
    {
        file << p->data.accountNumber << ","
             << p->data.accountName << ","
             << p->data.birthday << ","
             << p->data.contactNumber << ","
             << p->data.balance << ","
             << p->data.pin << endl;
        p = p->next;
    }
    file.close();
}

// ============ LOAD CSV FILE TO LINKED LIST ============
void ATMList::load()
{
    ifstream file(DATABASE_FILE);
    if (!file)
    { // unang takbo: baka wala pang database
        return;
    }
    // binabasa ulit ang saved accounts pag-start ng program
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        Account x;
        string balanceText;
        getline(ss, x.accountNumber, ',');
        getline(ss, x.accountName, ',');
        getline(ss, x.birthday, ',');
        getline(ss, x.contactNumber, ',');
        getline(ss, balanceText, ',');
        getline(ss, x.pin);
        try
        {
            x.balance = stoll(balanceText);
        }
        catch (...)
        {
            continue;
        }
        insert(x);
    }
    file.close();
}

void ATMList::Display()
{
    node *p;
    p = head;
    system("cls");
    cout << left << setw(20) << "Name"
         << setw(10) << "Account No."
         << setw(10) << "Balance" << endl;
    while (p != NULL)
    {
        cout << left << setw(20) << p->data.accountName
             << setw(10) << p->data.accountNumber
             << setw(10) << p->data.balance << endl;

        p = p->next;
    }
}
// ============ MAIN PROGRAM ============
int main()
{
    Account acc;
    node *p;
    ATMList atm;
    atm.load(); // lo-load ang account na meron
    while (true)
    {
        cout << "\n=====================================\n";
        cout << "              ATM SYSTEM\n";
        cout << "=====================================\n";
        cout << "[1] Register New Account\n";
        cout << "[2] ATM Transaction\n";
        cout << "[3] Exit\n";
        cout << "=====================================\n";

        int choice = getChoice(1, 3);
        if (choice == -2)
        {
            continue;
        }
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