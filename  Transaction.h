//
// Created by Leonardo on 18/03/2025.
//

#ifndef FINANCIAL_TRANSACTIONS_TRANSACTION_H
#define FINANCIAL_TRANSACTIONS_TRANSACTION_H

#endif //FINANCIAL_TRANSACTIONS_TRANSACTION_H

#include <iostream>
#include <sstream>

using namespace std;

class Transaction {
private:
    string date;
    string description;
    double amount{};

public:
    Transaction() = default;
    Transaction(string  d, string  desc, double a); //TODO implement constructor

    // TODO implement getters
    string getDate() const;
    string getDescription() const;
    double getAmount() const;

    // TODO implement setters
    void setDate(const string& d);
    void setDescription(const string& desc);
    void setAmount(double a);

    string toString() const; //TODO implement this method

    static Transaction fromString(const string& line); //TODO implement this method
};