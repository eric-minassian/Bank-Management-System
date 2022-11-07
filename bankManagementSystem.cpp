#include "bankManagementSystem.h"

#include <iomanip>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
using std::to_string;
using namespace ICS45C::BankManagementSystem;

Record *ICS45C::BankManagementSystem::openAccount(Record *accounts,
                                                  string fname, string lname,
                                                  string email, string phone) {
  // Create account id counter
  static unsigned int account_id = 0;

  // Create new account
  Record *new_account = new Record();
  new_account->fname = fname;
  new_account->lname = lname;
  new_account->email = email;
  new_account->phone = phone;
  new_account->balance = 0.0;
  new_account->id = account_id;
  new_account->locked = false;
  new_account->next = nullptr;
  account_id++;

  if (!accounts) {
    return new_account;
  }

  Record *head = accounts;
  while (accounts->next) {
    accounts = accounts->next;
  }
  accounts->next = new_account;
  return head;
}

void lockAccount(Record *account) { account->locked = true; }

void unlockAccount(Record *account) { account->locked = false; }

Record *searchAccount(Record *accounts, string field, string keyword) {
  if (field != "ID" || field != "FIRST" || field != "LAST" ||
      field != "PHONE" || field != "EMAIL") {
    return nullptr;
  }

  while (accounts) {
    if (!accounts->locked) {
      if (field == "ID") {
        if (to_string(accounts->id) == keyword) {
          return accounts;
        }
      } else if (field == "FIRST") {
        if (accounts->fname == keyword) {
          return accounts;
        }
      } else if (field == "LAST") {
        if (accounts->lname == keyword) {
          return accounts;
        }
      } else if (field == "PHONE") {
        if (accounts->phone == keyword) {
          return accounts;
        }
      } else if (field == "EMAIl") {
        if (accounts->email == keyword) {
          return accounts;
        }
      }
    }
    accounts = accounts->next;
  }

  return nullptr;
}

string printDetails(Record *account) {
  string answer = "------\nAccount ";
  if (account) {
    if (account->locked) {
      return "------\nAccount #" + to_string(account->id) +
             "\n------\nSorry, this acount has been locked.\n------\n";
    } else {
      std::stringstream balance;
      balance << std::fixed << std::setprecision(2) << account->balance;
      return "------\nAccount #" + to_string(account->id) +
             "\n------\nStatus: OPEN\nAccount holder: " + account->fname + " " +
             account->lname + "\nContact: " + account->phone + " / " +
             account->email + "\nBalance: " + balance.str();
    }
  } else {
    return "------\nAccount UNKNOWN\n------\nSorry, this account does not "
           "exist.\n------\n";
  }
}
string printDetails(Record *accounts, unsigned int id) {}
void updateAccount(Record *account, string firstName, string lastName,
                   string phone, string email, bool locked) {}
void updateAccount(Record *accounts, unsigned int id, string firstName,
                   string lastName, string phone, string email, bool locked) {}
double deposit(Record *account, double value) {}
double deposit(Record *accounts, unsigned int id, double value) {}
double withdrawal(Record *account, double value) {}
double withdrawal(Record *accounts, unsigned int id, double value) {}
Record *deleteAccount(Record *accounts, unsigned int id) {}
unsigned int countUnlockedAccounts(Record *accounts) {}
unsigned int countLockedAccounts(Record *accounts) {}
unsigned int countAllAccounts(Record *accounts) {}
long double getAverageBalance(Record *accounts) {}
long double getBankFunds(Record *accounts) {}
void closeBank(Record *accounts) {}