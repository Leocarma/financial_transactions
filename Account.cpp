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

void Account::printAccountStatement() const {
    cout << "=== Account Statement of: " << accountName << " ===\n";
    cout << left << setw(12) << "Date" 
         << setw(25) << "Description" 
         << setw(10) << "Amount" 
         << "Type\n";
    cout << string(60, '-') << "\n";

    for (const auto& t : transactions) {
        string sign = (t.getType() == TransactionType::in) ? "+" : "-";
        cout << left << setw(12) << t.getDate()
             << setw(25) << t.getDescription()
             << setw(10) << sign + to_string(t.getAmount()) + "$ "
             << ((t.getType() == TransactionType::in) ? "in" : "out") << "\n";
    }

    cout << string(60, '-') << "\n";
    cout << "Total transactions: " << totalTransactions() << "\n";
    cout << "Total balance: " << fixed << setprecision(2) << totalBalance() << "$\n";
}

void Account::saveAccountToFile() const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error occurred while opening the file for saving.\n";
        return;
    }

    file << "AccountName: " << accountName << "\n";
    file << "FileName: " << filename << "\n";

    file << "Transactions:\n";
    for (auto t : transactions) {
        file << t.toString() << "\n";
    }

    file.close();
}

void Account::loadAccountFromFile(const string &fileName) {
    ifstream file(fileName);
    if (!file) {
        throw runtime_error("Error occurred while opening the file for loading.");
    }

    string line;

    if (getline(file, line) && line.substr(0, 12) == "AccountName:") {
        accountName = line.substr(13);
    } else {
        throw runtime_error("Invalid file format (missing AccountName).");
    }

    if (getline(file, line) && line.substr(0, 9) == "FileName:") {
        filename = line.substr(10);
    } else {
        throw runtime_error("Invalid file format (missing FileName).");
    }

    if (getline(file, line) && line == "Transactions:") {
        transactions.clear(); 
        while (getline(file, line)) {
            if (!line.empty()) {
                try {
                    stringstream ss(line);
                    string dateStr, descStr, amountStr, typeStr;

                    getline(ss, dateStr, ';');
                    getline(ss, descStr, ';');
                    getline(ss, amountStr, ';');
                    getline(ss, typeStr, ';');

                    double amount = stod(amountStr);
                    TransactionType type = (typeStr == "in") ? in : out;

                    Transaction t(dateStr, descStr, amount, type);
                    transactions.push_back(t);
                } catch (const exception &e) {
                    cerr << "Error: Invalid transaction format: " << e.what() << "\n";
                }
            }
        }
    } else {
        cerr << "Error: Invalid file format (missing Transactions section).\n";
    }

    file.close();
}
