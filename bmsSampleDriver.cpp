#include <iostream>
#include <string>

#include "bankManagementSystem.h"

#define MAX_ARGS 7

using std::cin;
using std::cout;
using std::string;
using namespace ICS45C::BankManagementSystem;

void parseCommand(string args[], string inputLine) {
  // Code adapted from: https://stackoverflow.com/a/14266139
  string delimiter = " ";
  size_t pos;
  for (int i = 0; i < MAX_ARGS; i++) {
    if ((i + 1 < MAX_ARGS) &&
        (pos = inputLine.find(delimiter)) != string::npos) {
      // Still have spaces in the string and more spots in the array.
      args[i] = inputLine.substr(0, pos);
      inputLine.erase(0, pos + delimiter.length());
    } else {
      // Last token in string or last index in the array.
      args[i] = inputLine;
      inputLine.clear();  // used all of it
    }
  }
}

void showCommand(string args[]) {
  cout << "command: " << args[0] << '\n';
  cout << "args:\n";
  for (int i = 1; i < MAX_ARGS && !args[i].empty(); i++) {
    cout << '\t' << i << ": " << args[i] << '\n';
  }
  cout << '\n';
}

int main() {
  string args[MAX_ARGS];
  string choice, inputLine;
  Record* head = nullptr;
  bool exit = false;

  cout << "** WELCOME TO BANK MANAGEMENT SYSTEM **\n";

  while (!exit) {
    cout << "\n** MENU **\n"
         << "01. [OP]en a bank account\n"
         << "02. [SH]ow account holder’s full details\n"
         << "03. [SE]arch for customer account\n"
         << "04. [LO]ck First account\n"
         << "05. [UN]lock First account\n"
         << "06. [UP]date bank account\n"
         << "07. [DE]posit amount for customer\n"
         << "08. [WI]thdraw amount for customer\n"
         << "09. [CL]ose bank account\n"
         << "10. [BA]nk info\n"
         << "11. [MA]rket crash\n"
         << "12. [EX]it\n";

    getline(cin, inputLine);
    parseCommand(args, inputLine);
    showCommand(args);

    choice = args[0];

    if (choice == "OP") {
      // Example usage: OP Jane Doe jdoe@email.com 555-123-6789
      head = openAccount(head, args[1], args[2], args[3], args[4]);

    } else if (choice == "SH") {
      // Example usage: SH 0
      cout << printDetails(head, stoi(args[1]));

    } else if (choice == "SE") {
      // Example usage: SE PHONE 555-123-6789
      cout << printDetails(searchAccount(head, args[1], args[2]));

    } else if (choice == "LO") {
      // Example usage: LO 0
      lockAccount(searchAccount(head, "ID", args[1]));

    } else if (choice == "UN") {
      // Example usage: UN 0
      unlockAccount(searchAccount(head, "ID", args[1]));

    } else if (choice == "UP") {
      // UP 0 Jan DOE jandoe@email.com 555-124-6789 unlocked
      updateAccount(head, stoi(args[1]), args[2], args[3], args[4], args[5],
                    args[6] == "locked");

    } else if (choice == "DE") {
      // Example usage: DE 0 145.99
      deposit(head, stoi(args[1]), stod(args[2]));

    } else if (choice == "WI") {
      // Example usage: WI 0 10.35
      withdrawal(head, stoi(args[1]), stod(args[2]));

    } else if (choice == "CL") {
      // Example usage: CL 0
      head = deleteAccount(head, stoi(args[1]));

    } else if (choice == "BA") {
      // Example usage: BA
      cout << "Accounts created: " << countAllAccounts(head) << '\n';
      cout << "Open accounts: " << countUnlockedAccounts(head) << '\n';
      cout << "Locked accounts: " << countLockedAccounts(head) << '\n';
      cout << "Average balance: " << getAverageBalance(head) << '\n';
      cout << "Total funds available: " << getBankFunds(head) << '\n';

    } else if (choice == "MA") {
      // Example usage: MA
      cout << "Closing down the bank...\n";
      closeBank(head);
      head = nullptr;
      cout << "All accounts have been deleted.\n";

    } else if (choice == "EX") {
      // Example usage: EX
      cout << "Goodbye!\n";
      exit = true;

    } else {
      cout << "Sorry, that command is invalid.\n";
    }

    cout << '\n';
  }
  return 0;
}
