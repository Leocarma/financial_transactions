//
// Created by Leonardo on 18/03/2025.
//

#ifndef FINANCIAL_TRANSACTIONS_TRANSACTION_H
#define FINANCIAL_TRANSACTIONS_TRANSACTION_H

#endif //FINANCIAL_TRANSACTIONS_TRANSACTION_H

#include <sstream>

using namespace std;
enum class TransactionType { in, out };

class Transaction{
private:
    string date;
    string description;
    double amount;
    TransactionType type;

public:
    Transaction(const string&  d, const string&  desc, double a, TransactionType t);
    string getDate() const;
    string getDescription() const;
    double getAmount() const;
    TransactionType getType() const;
    void setDate(const string& d);
    void setDescription(const string& desc);
    void setAmount(double a);
    void setType(TransactionType t);
    string typeToString(TransactionType t);
    static TransactionType stringToType(const string& typeStr);
    string toString();
    static Transaction fromString(const string& line);
};