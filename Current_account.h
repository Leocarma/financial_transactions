//
// Created by Leonardo on 18/03/2025.
//

#ifndef FINANCIAL_TRANSACTIONS_CURRENT_ACCOUNT_H
#define FINANCIAL_TRANSACTIONS_CURRENT_ACCOUNT_H

#endif //FINANCIAL_TRANSACTIONS_CURRENT_ACCOUNT_H

#include <vector>
#include <sstream>
#include "Transaction.h"

using namespace std;

class Current_account {
private:
    vector<Transaction> transactions;
    string filename;

public:
    explicit Current_account(const string& fname);

    void addTransaction(const Transaction& t);

    double totalBalance() const;

    void saveFile() const;

    void loadFile();

    void printAccountStatement() const;
};