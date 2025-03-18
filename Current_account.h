//
// Created by Leonardo on 18/03/2025.
//

#ifndef FINANCIAL_TRANSACTIONS_CURRENT_ACCOUNT_H
#define FINANCIAL_TRANSACTIONS_CURRENT_ACCOUNT_H

#endif //FINANCIAL_TRANSACTIONS_CURRENT_ACCOUNT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Transaction.h"

using namespace std;

class Current_account {
private:
    vector<Transaction> transactions;
    string filename;

public:
    Current_account(const string& fname); //TODO implement this

    void addTransaction(const Transaction& t); //TODO implement this

    double totalBalance() const; //TODO implement this

    void saveFile() const; //TODO implement this

    void loadFile(); //TODO implement this

    void printAccountStatement() const; //TODO implement this
};