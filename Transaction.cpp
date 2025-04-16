//
// Created by Leonardo on 18/03/2025.
//

#include <sstream>
#include "Transaction.h"

using namespace std;

Transaction::Transaction(const string& d, const string& desc, double a)
    : date(d), description(desc), amount(a) {}

string Transaction::getDate() const {
    return date;
}

string Transaction::getDescription() const {
    return description;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::setDate(const std::string &d) {
    date = d;
}

void Transaction::setDescription(const std::string &desc) {
    description = desc;
}

void Transaction::setAmount(double a) {
    amount = a;
}

string Transaction::toString() const {
    ostringstream oss;
    oss << date << ";" << description << ";" << amount;
    return oss.str();
}

Transaction Transaction::fromString(const std::string &line) {
    istringstream iss(line);
    string date, description, strAmount;
    getline(iss, date, ';');
    getline(iss, description, ';');
    getline(iss, strAmount, ';');
    return Transaction{date, description, stod(strAmount)};
}


