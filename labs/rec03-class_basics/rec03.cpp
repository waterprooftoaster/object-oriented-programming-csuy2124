/*
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    int num;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account_Class {
public:
    Account_Class(const string &account_class_name, int account_class_num)
        : name(account_class_name), num(account_class_num) {
    }

    //getters
    const string &get_name() const {
        return name;
    }

    int get_num() const {
        return num;
    }

private:
    string name;
    int num;
    friend ostream &operator<<(ostream &os, const Account_Class &account);
};

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".

class Transaction {
public:
    Transaction(const string &transaction_type, int transaction_amount)
        : type(transaction_type), amount(transaction_amount) {
    }

    //getters
    const string &get_type() const {
        return type;
    }

    int get_amount() const {
        return amount;
    }

private:
    string type;
    int amount;
    friend ostream &operator<<(ostream &os, const Transaction &transaction);
};

class Account_Class2 {
public:
    Account_Class2(const string &account_class_name, int account_class_num
        ,int account_balance, const vector<Transaction>& account_transactions)
           : name2(account_class_name), num2(account_class_num)
             ,balance(account_balance), transactions(account_transactions) {
    }

    //getters
    const string &get_name2() const {
        return name2;
    }

    const int get_num2() const {
        return num2;
    }

    int get_balance() const {
        return num2;
    }

    void change_balance(int amount) {
        balance += amount;
    }

    void add_transaction(const Transaction &transaction) {
        transactions.emplace_back(transaction);
    }

private:
    string name2;
    int num2, balance;
    vector<Transaction> transactions;
};

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.

class Account_Class3 {
public:
    Account_Class3(const string &account_class_name, int account_class_num
        ,int account_balance, const vector<Transaction>& account_transactions)
           : name3(account_class_name), num3(account_class_num)
             ,balance3(account_balance), transactions3(account_transactions) {
    }

    class Transaction3 {
    public:
        Transaction3(const string &transaction_type, int transaction_amount)
            : type3(transaction_type), amount3(transaction_amount) {
        }

        //getters
        const string &get_type() const {
            return type3;
        }

        int get_amount() const {
            return amount3;
        }

    private:
        string type3;
        int amount3;
        friend ostream &operator<<(ostream &os, const Transaction3& transaction);
    };

    //getters
    const string &get_name2() const {
        return name3;
    }

    const int get_num2() const {
        return num3;
    }

    int get_balance() const {
        return num3;
    }

    void change_balance(int amount) {
        balance3 += amount;
    }

    void add_transaction(const Transaction &transaction) {
        transactions3.emplace_back(transaction);
    }

private:
    string name3;
    int num3, balance3;
    vector<Transaction> transactions3;
};

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.

ostream &operator<<(ostream &os, const Account_Class &account) {
    //os << account.get_name() << " " << account.get_num();
    os << account.name << " " << account.num;
    return os;
}

ostream &operator<<(ostream &os, const Transaction &transaction) {
    //os << account.get_name() << " " << account.get_num();
    os << transaction.type << " " << transaction.amount;
    return os;
}

ostream &operator<<(ostream &os, const Account_Class3::Transaction3& transaction) {
    os << transaction.type3 << " " << transaction.amount3 << endl;
}

int main() {
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
            << "Filling vector of struct objects, define a local struct instance\n"
            << "and set fields explicitly:\n";
    ifstream accounts_file;
    accounts_file.open("accounts.txt");
    vector<Account> accounts;

    string name;
    int num;
    while (accounts_file >> name >> num) {
        Account account;
        account.name = name;
        account.num = num;
        accounts.push_back(account);
    }

    accounts_file.close();

    for (const Account &curr: accounts) {
        cout << curr.name << " " << curr.num << endl;
    }

    //      1b
    cout << "Task1b:\n"
            << "Filling vector of struct objects, using {} initialization:\n";

    accounts.clear();
    accounts_file.open("accounts.txt");
    string name1;
    int num1;
    while (accounts_file >> name1 >> num1) {
        Account account1{name1, num1};
        accounts.push_back(account1);
    }

    for (const Account &curr: accounts) {
        cout << curr.name << " " << curr.num << endl;
    }

    accounts_file.close();

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
            << "\nFilling vector of class objects, using local class object:\n";

    vector<Account_Class> accounts2;
    accounts_file.open("accounts.txt");

    string name2;
    int num2;
    while (accounts_file >> name2 >> num2) {
        Account_Class account1{name2, num2};
        accounts2.push_back(account1);
    }

    accounts2.clear();

    /*
    for (const Account_Class &curr: accounts2) {
        string print_name = curr.get_name();
        int print_num = curr.get_num();
        cout << print_name << " " << print_num << endl;
    }
    */
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    /*
    for (const Account_Class &curr: accounts2) {
        cout << curr << endl;
    }
    */

    cout << "\nTask2c:\n"
            << "output using output operator as friend without getters\n";

    for (const Account_Class &curr: accounts2) {
        cout << curr << endl;
    }

    cout << "\nTask2d:\n"
            << "Filling vector of class objects, using temporary class object:\n";

    accounts2.clear();
    accounts_file.open("accounts.txt");

    string name3;
    int num3;
    /*
    while (accounts_file >> name3 >> num3) {
        accounts2.push_back(Account_Class{name3, num3});
    }
    */

    cout << "\nTask2e:\n"
            << "Filling vector of class objects, using emplace_back:\n";
    while (accounts_file >> name3 >> num3) {
        accounts2.emplace_back(name3, num3);
    }

    cout << "==============\n"
            << "\nTask 3:\nAccounts and Transaction:\n";

    ifstream transactions_file;
    transactions_file.open("transactions.txt");
    vector<Transaction> transactions;
    vector<Account_Class2> tran_accounts;

    string command;
    int acc_num, tran_amt;

    while (transactions_file >> command) {
        if (command == "Account") {
            string trans_name;
            transactions_file >> trans_name >> acc_num;
            tran_accounts.emplace_back(trans_name, acc_num, 0, transactions);
        }

        if (command == "Withdraw" || command == "Deposit") {
            transactions_file >> acc_num >> tran_amt;

            if (command == "Withdraw") {
                tran_amt = (tran_amt * -1);
            }

            for (Account_Class2& curr: tran_accounts) {
                if (curr.get_num2() == acc_num) {

                    if (command == "Withdraw" && curr.get_balance() <= tran_amt) {
                        cerr << "withdraw exceeds balance" << endl;

                    } else {
                        curr.change_balance(tran_amt);
                        Transaction new_transaction{command, tran_amt};
                        curr.add_transaction(new_transaction);
                    }
                }
            }
        }
    }

    cout << "==============\n"
            << "\nTask 4:\nTransaction nested in public section of Account:\n";


    cout << "==============\n"
            << "\nTask 5:\nTransaction nested in private section of Account:\n";
} // main
