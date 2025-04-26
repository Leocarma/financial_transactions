//
// Created by Leonardo on 18/03/2025.
//

#include "Account.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

Account::Account(const string& fname, const string& accname){
    if(accname.empty())
        throw invalid_argument("Account name cannot be blank.");
    if(fname.empty())
        throw invalid_argument("File name cannot be blank.");

    filename = fname;
    accountName = accname;
}

string Account::getFileName() const {
    return filename;
}

string Account::getAccountName() const {
    return accountName;
}

void Account::setFileName(const std::string &name) {
    if(name.empty())
        throw invalid_argument("File name cannot be blank.");
    filename = name;
}

void Account::setAccountName(const std::string &account) {
    if(account.empty())
        throw invalid_argument("Account name cannot be blank.");
    accountName = account;
}

void Account::addTransaction(const Transaction &t) {
    transactions.push_back(t);
}

vector<Transaction> Account::findForDate(const std::string &date) const {
    vector<Transaction> foundTransactions;

    if(date.empty())
        return foundTransactions;

    for(const auto& t: transactions){
        if(t.getDate() == date)
            foundTransactions.push_back(t);
    }

    return foundTransactions;
}

vector<Transaction> Account::findForDescription(const std::string &desc) const {
    vector<Transaction> foundTransactions;

    if(desc.empty())
        return foundTransactions;

    for(const auto& t: transactions){
        if(t.getDescription().find(desc) != string::npos)
            foundTransactions.push_back(t);
    }

    return foundTransactions;
}

unsigned Account::totalTransactions() const {
    return transactions.size();
}

double Account::totalBalance() const {
    double total = 0;
    for (const auto& t : transactions) {
        if(t.getType() == TransactionType::in)
            total += t.getAmount();
        else
            total -= t.getAmount();
    }
    return total;
}

void Account::saveFile() const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error occurred while opening the file.\n";
        return;
    }
    for (Transaction t : transactions) {
        file << t.toString() << "\n";
    }
    file.close();
}

void Account::loadFile() {
    ifstream file(filename);
    if (!file) {
        cerr << "Error file not found.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                transactions.push_back(Transaction::fromString(line));
            } catch (const invalid_argument& e) {
                cerr << "Error during file load: " << e.what() << endl;
            }
        }
    }
    file.close();
}

void Account::printAccountStatement() const {
    cout << "Account Statement of: " << accountName << " ===\n";
    for (const auto& t : transactions) {
        string sign = (t.getType() == TransactionType::in) ? "+" : "-";
        cout << t.getDate() << " | "
             << setw(20) << t.getDescription() << " | "
             << sign << fixed << setprecision(2) << t.getAmount() << "€\n";
    }
    cout << "Total transactions: " << totalTransactions() << "€\n";
    cout << "Total balance: " << totalBalance() << "€\n";
}

