#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <random>
#include <limits>
using namespace std;

class Account
{
private:
    string accountNumber;
    string holderName;
    double balance;

public:
    Account(string acNo, string name, double balance)
    {
        this->accountNumber = acNo;
        this->holderName = name;
        this->balance = balance;
    }

    Account() {}
    ~Account() {}

    string getAccountNo() const { return accountNumber; }
    string getHolderName() const { return holderName; }
    double getBalance() const { return balance; }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount. Please enter a positive value.\n";
            return;
        }
        balance += amount;
        cout << "Amount of Rs: " << amount << " deposited successfully.\n";
        cout << "Current balance: " << balance << "\n";
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount. Please enter a positive value.\n";
            return;
        }
        if (balance < amount)
        {
            cout << "Insufficient balance.\n";
            cout << "Current balance: " << balance << "\n";
        }
        else
        {
            balance -= amount;
            cout << "Amount of Rs: " << amount << " withdrawn successfully.\n";
            cout << "Current balance: " << balance << "\n";
        }
    }

    void display() const
    {
        cout << "Account No: " << accountNumber << " | Name: " << holderName
             << " | Balance: " << balance << "\n";
    }
};

class Bank
{
private:
    unordered_map<string, Account> accounts;
    set<long long> accountNumbers;
    static int accountCount;

    string generateAccountNo()
    {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<long long> dis(1000000000000000, 1999999999999999);

        long long newAccountNo;
        do
        {
            newAccountNo = dis(gen);
        } while (accountNumbers.find(newAccountNo) != accountNumbers.end());

        accountNumbers.insert(newAccountNo);
        return to_string(newAccountNo);
    }

public:
    void createAccount()
    {
        string name;
        double balance;

        cout << "Please enter the account holder's name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Please enter the starting balance: ";
        while (!(cin >> balance) || balance < 0)
        {
            cout << "Invalid input. Please enter a non-negative value for balance: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string acNo = generateAccountNo();
        Account newAccount(acNo, name, balance);
        accounts[acNo] = newAccount;
        accountCount++;

        cout << "Account created successfully!\n";
        newAccount.display();
    }

    void displayAllAccounts() const
    {
        if (accounts.empty())
        {
            cout << "No accounts to display.\n";
            return;
        }
        for (const auto &entry : accounts)
        {
            entry.second.display();
        }
    }

    void depositMoney()
    {
        string acNo;
        double amount;

        cout << "Enter the account number: ";
        cin >> acNo;

        if (accounts.find(acNo) != accounts.end())
        {
            cout << "Enter the amount to deposit: ";
            while (!(cin >> amount))
            {
                cout << "Invalid input. Please enter a valid amount: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            accounts[acNo].deposit(amount);
        }
        else
        {
            cout << "Account not found.\n";
        }
    }

    void checkBalance() const
    {
        string acNo;
        cout << "Enter the account number: ";
        cin >> acNo;

        if (accounts.find(acNo) != accounts.end())
        {
            cout << "Account Balance: " << accounts.at(acNo).getBalance() << "\n";
        }
        else
        {
            cout << "Account not found.\n";
        }
    }

    void withdrawMoney()
    {
        string acNo;
        double amount;

        cout << "Enter the account number: ";
        cin >> acNo;

        if (accounts.find(acNo) != accounts.end())
        {
            cout << "Enter the amount to withdraw: ";
            while (!(cin >> amount))
            {
                cout << "Invalid input. Please enter a valid amount: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            accounts[acNo].withdraw(amount);
        }
        else
        {
            cout << "Account not found.\n";
        }
    }
};

int Bank::accountCount = 0;

int main()
{
    Bank bank;
    int choice;

    do
    {
        cout << "\n=== Welcome to the Bank ===\n";
        cout << "1. Create a New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Check Account Balance\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Display All Accounts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a valid option: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            bank.createAccount();
            break;
        case 2:
            bank.depositMoney();
            break;
        case 3:
            bank.checkBalance();
            break;
        case 4:
            bank.withdrawMoney();
            break;
        case 5:
            bank.displayAllAccounts();
            break;
        case 0:
            cout << "Thank you for using the Bank System. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
