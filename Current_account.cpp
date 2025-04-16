//
// Created by Leonardo on 18/03/2025.
//

#include "Current_account.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

Current_account::Current_account(const string& fname)
    : filename(fname) {}

void Current_account::addTransaction(const Transaction &t) {
    transactions.push_back(t);
}

double Current_account::totalBalance() const {
    double total = 0;
    for (const auto& t : transactions) {
        total += t.getAmount();
    }
    return total;
}

void Current_account::saveFile() const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error occurred while opening the file.\n";
        return;
    }
    for (const auto& t : transactions) {
        file << t.toString() << "\n";
    }
    file.close();
}

void Current_account::loadFile() {
    transactions.clear();
    ifstream file(filename);
    if (!file) {
        cerr << "Error file not found.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            transactions.push_back(Transaction::fromString(line));
        }
    }
    file.close();
}

void Current_account::printAccountStatement() const {
    cout << "=== Account Statement ===\n";
    for (const auto& t : transactions) {
        cout << t.getDate() << " | " << setw(20) << t.getDescription()
             << " | " << fixed << setprecision(2) << t.getAmount() << "€\n";
    }
    cout << "----------------------\n";
    cout << "Total balance: " << totalBalance() << "€\n";
}
