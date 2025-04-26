//
// Created by Leonardo on 26/04/2025.
//

#ifndef LEONARDO_TRANSAZIONI_FINANZIARIE_TRANSACTION_H
#define LEONARDO_TRANSAZIONI_FINANZIARIE_TRANSACTION_H

#include <sstream>

using namespace std;
enum TransactionType{ in, out};

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
    string typeToString();
    static TransactionType stringToType(const string& typeStr);
    string toString();
    static Transaction fromString(const string& line);
};

#endif //LEONARDO_TRANSAZIONI_FINANZIARIE_TRANSACTION_H


