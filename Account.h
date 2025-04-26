//
// Created by Leonardo on 26/04/2025.
//

#ifndef LEONARDO_TRANSAZIONI_FINANZIARIE_ACCOUNT_H
#define LEONARDO_TRANSAZIONI_FINANZIARIE_ACCOUNT_H

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
    Account() {};
    string getAccountName() const;
    string getFileName() const;
    void setAccountName(const string& account);
    void setFileName(const string& name);
    void addTransaction(const Transaction& t);
    vector<Transaction> findForDate(const string& date) const;
    vector<Transaction> findForDescription(const string& desc) const;
    unsigned totalTransactions() const;
    double totalBalance() const;
    void printAccountStatement() const;
    void saveAccountToFile() const;
    void loadAccountFromFile(const string& filename);
};

#endif //LEONARDO_TRANSAZIONI_FINANZIARIE_ACCOUNT_H


