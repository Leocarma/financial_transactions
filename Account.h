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

class Account {
private:
    vector<Transaction> transactions;
    string filename;
    string accountName;

public:
    Account(const string& fname, const string& accountName);
    string getAccountName() const;
    string getFileName() const;
    void setAccountName(const string& account);
    void setFileName(const string& name);
    void addTransaction(const Transaction& t);
    vector<Transaction> findForDate(const string& date) const;
    vector<Transaction> findForDescription(const string& desc) const;
    unsigned totalTransactions() const;
    double totalBalance() const;
    void saveFile() const;
    void loadFile();
    void printAccountStatement() const;
};