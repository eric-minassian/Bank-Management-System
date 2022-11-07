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
  new_account->balance = 0.00;
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

void ICS45C::BankManagementSystem::lockAccount(Record *account) {
  if (account) {
    account->locked = true;
  }
}

void ICS45C::BankManagementSystem::unlockAccount(Record *account) {
  if (account) {
    account->locked = false;
  }
}

Record *ICS45C::BankManagementSystem::searchAccount(Record *accounts,
                                                    string field,
                                                    string keyword) {
  if (field != "ID" && field != "FIRST" && field != "LAST" &&
      field != "PHONE" && field != "EMAIL") {
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
      } else if (field == "EMAIL") {
        if (accounts->email == keyword) {
          return accounts;
        }
      }
    }
    accounts = accounts->next;
  }

  return nullptr;
}

string ICS45C::BankManagementSystem::printDetails(Record *account) {
  if (account) {
    if (account->locked) {
      return "------\nAccount #" + to_string(account->id) +
             "\n------\nSorry, this account has been locked.\n------\n";
    } else {
      std::stringstream balance;
      balance << std::fixed << std::setprecision(2) << account->balance;
      return "------\nAccount #" + to_string(account->id) +
             "\n------\nStatus: OPEN\nAccount holder: " + account->fname + " " +
             account->lname + "\nContact: " + account->phone + " / " +
             account->email + "\nBalance: " + balance.str() + "\n------\n";
    }
  } else {
    return "------\nAccount UNKNOWN\n------\nSorry, this account does not "
           "exist.\n------\n";
  }
}

string ICS45C::BankManagementSystem::printDetails(Record *accounts,
                                                  unsigned int id) {
  while (accounts) {
    if (accounts->id == id) {
      return printDetails(accounts);
    }
    accounts = accounts->next;
  }
  return "------\nAccount UNKNOWN\n------\nSorry, this account does not "
         "exist.\n------\n";
}

void ICS45C::BankManagementSystem::updateAccount(Record *account,
                                                 string firstName,
                                                 string lastName, string phone,
                                                 string email, bool locked) {
  if (account) {
    account->fname = firstName;
    account->lname = lastName;
    account->phone = phone;
    account->email = email;
    account->locked = locked;
  }
}

void ICS45C::BankManagementSystem::updateAccount(Record *accounts,
                                                 unsigned int id,
                                                 string firstName,
                                                 string lastName, string phone,
                                                 string email, bool locked) {
  while (accounts) {
    if (accounts->id == id) {
      updateAccount(accounts, firstName, lastName, phone, email, locked);
    }
    accounts = accounts->next;
  }
}

double ICS45C::BankManagementSystem::deposit(Record *account, double value) {
  if (account && !account->locked) {
    if (value >= 0) {
      account->balance += value;
    }
    return account->balance;
  } else {
    return -123.45;
  }
}

double ICS45C::BankManagementSystem::deposit(Record *accounts, unsigned int id,
                                             double value) {
  while (accounts) {
    if (accounts->id == id) {
      return deposit(accounts, value);
    }

    accounts = accounts->next;
  }
  return -123.45;
}

double ICS45C::BankManagementSystem::withdrawal(Record *account, double value) {
  if (account && !account->locked) {
    if (value >= 0) {
      account->balance -= value;
    }
    return account->balance;
  } else {
    return -123.45;
  }
}

double ICS45C::BankManagementSystem::withdrawal(Record *accounts,
                                                unsigned int id, double value) {
  while (accounts) {
    if (id == accounts->id) {
      return withdrawal(accounts, value);
    }
    accounts = accounts->next;
  }
  return -123.45;
}

Record *ICS45C::BankManagementSystem::deleteAccount(Record *accounts,
                                                    unsigned int id) {
  Record *previous = accounts;
  Record *head = accounts;

  if (accounts && accounts->id == id) {
    head = accounts->next;
    delete accounts;
    return head;
  }

  while (accounts) {
    if (accounts->id == id) {
      previous->next = accounts->next;
      delete accounts;
      return head;
    }
    previous = accounts;
    accounts = accounts->next;
  }
  return head;
}

unsigned int ICS45C::BankManagementSystem::countUnlockedAccounts(
    Record *accounts) {
  unsigned int count = 0;
  while (accounts) {
    if (!accounts->locked) {
      count++;
    }
    accounts = accounts->next;
  }
  return count;
}

unsigned int ICS45C::BankManagementSystem::countLockedAccounts(
    Record *accounts) {
  unsigned int count = 0;
  while (accounts) {
    if (accounts->locked) {
      count++;
    }
    accounts = accounts->next;
  }
  return count;
}

unsigned int ICS45C::BankManagementSystem::countAllAccounts(Record *accounts) {
  unsigned int count = 0;
  while (accounts) {
    count++;
    accounts = accounts->next;
  }
  return count;
}

long double ICS45C::BankManagementSystem::getAverageBalance(Record *accounts) {
  unsigned int count = 0;
  long double total = 0.00;
  while (accounts) {
    if (!accounts->locked) {
      count++;
      total += accounts->balance;
    }
    accounts = accounts->next;
  }
  if (count == 0) {
    return 0.00;
  } else {
    return (long double)total / count;
  }
}

long double ICS45C::BankManagementSystem::getBankFunds(Record *accounts) {
  long double total = 0.00;
  while (accounts) {
    if (!accounts->locked) {
      total += accounts->balance;
    }
    accounts = accounts->next;
  }
  return total;
}

void ICS45C::BankManagementSystem::closeBank(Record *accounts) {
  Record *next_account;
  while (accounts) {
    next_account = accounts->next;
    delete accounts;
    accounts = next_account;
  }
}