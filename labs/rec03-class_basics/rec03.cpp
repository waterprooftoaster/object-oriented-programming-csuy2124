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
struct Account{
  string name;
  int num;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account_Class {
public:
     Account_Class(string account_class_name, int account_class_num)
     : name(account_class_name), num(account_class_num){
     }

     //getters
     string get_name() const {
          return name;
     }

     int get_num() const {
          return num;
     }

private:
     string name;
     int num;
};

class Transaction {
public:
     Transaction(string transaction_type, int transaction_amount,
          vector<Transaction> transactions_history)
          : type(transaction_type), amount(transaction_amount),
          transactions(transactions_history){}

     //getters
     string get_type() const {
          return type;
     }

     int get_num() const {
          return amount;
     }

private:
     string type;
     int amount;
     vector<Transaction> transactions;
};

ostream& transaction_operator<< (ostream& os, const Transaction transaction){
     os << transaction.get_name() << " " << transaction.get_num();
     return os;
}
// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".


// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.


// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main()
{

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
    while (accounts_file >> name >> num){
      Account account;
      account.name = name;
      account.num = num;
      accounts.push_back(account);
    }

    accounts_file.close();

    for (const Account& curr : accounts){
      cout << curr.name << " " << curr.num << endl;
    }

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";

    accounts.clear();
    accounts_file.open("accounts.txt");
     string name1;
     int num1;
     while (accounts_file >> name1 >> num1){
          Account account1{name1, num1};
          accounts.push_back(account1);
     }

     for (const Account& curr : accounts){
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
     while (accounts_file >> name2 >> num2){
          Account_Class account1{name2, num2};
          accounts2.push_back(account1);
     }

     for (const Account_Class& curr : accounts2) {
          string print_name = curr.get_name();
          int print_num = curr.get_num();
          cout << print_name << " " << print_num << endl;
     }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";


    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";


    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";


    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";


    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";


    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";


} // main
