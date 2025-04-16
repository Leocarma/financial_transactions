//
// Created by Leonardo on 18/03/2025.
//

#ifndef FINANCIAL_TRANSACTIONS_TRANSACTION_H
#define FINANCIAL_TRANSACTIONS_TRANSACTION_H

#endif //FINANCIAL_TRANSACTIONS_TRANSACTION_H

#include <sstream>

using namespace std;

class Transaction {
private:
    string date;
    string description;
    double amount{};

public:
    Transaction() = default;
    Transaction(const string&  d, const string&  desc, double a);

    string getDate() const;
    string getDescription() const;
    double getAmount() const;

    void setDate(const string& d);
    void setDescription(const string& desc);
    void setAmount(double a);

    string toString() const;

    static Transaction fromString(const string& line);
};