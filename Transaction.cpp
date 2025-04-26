//
// Created by Leonardo on 18/03/2025.
//

#include <sstream>
#include <regex>
#include "Transaction.h"

using namespace std;

Transaction::Transaction(const string& d, const string& desc, double a, TransactionType t){

    regex dateFormat(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!regex_match(d, dateFormat)) {
        throw invalid_argument("Invalid date. Use YYYY-MM-DD format.");
    }

    int year, month, day;
    char sep1, sep2;
    istringstream iss(d);
    iss >> year >> sep1 >> month >> sep2 >> day;

    if (year <= 0 || month <= 0 || day <= 0) {
        throw invalid_argument("Date cannot contain negative numbers or zero.");
    }

    if (month > 12 || day > 31) {
        throw invalid_argument("Month or day out of valid range.");
    }

    if (desc.empty()) {
        throw invalid_argument("Error, blank description!");
    }
    if (a <= 0) {
        throw invalid_argument("Error, incorrect value!");
    }

        date = d;
        description = desc;
        amount = a;
        type = t;
}

string Transaction::getDate() const {
    return date;
}

string Transaction::getDescription() const {
    return description;
}

double Transaction::getAmount() const {
    return amount;
}

TransactionType Transaction::getType() const {
    return type;
}

void Transaction::setDate(const std::string &d) {
    regex dateFormat(R"(^\d{4}-\d{2}-\d{2}$)^)");
    if (!std::regex_match(d, dateFormat)) {
        throw std::invalid_argument("Invalid date. Use YYYY-MM-DD format.");
    }

    int year, month, day;
    char sep1, sep2;
    istringstream iss(d);
    iss >> year >> sep1 >> month  >> sep2 >> day;

    if (year <= 0 || month <= 0 || day <= 0) {
        throw invalid_argument("Date cannot contain negative numbers or zero.");
    }

    if (month > 12 || day > 31) {
        throw invalid_argument("Month or day out of valid range.");
    }
    date = d;
}

void Transaction::setDescription(const std::string &desc) {
    if(desc.empty())
        throw invalid_argument("Error, blank description!");
    description = desc;
}

void Transaction::setAmount(double a) {
    if(a < 0.0)
        throw invalid_argument("Error, incorrect value!");
    amount = a;
}

void Transaction::setType(TransactionType t) {
    type = t;
}

string Transaction::typeToString(TransactionType t) {
    return (type == TransactionType::in) ? "entrata" : "uscita";
}

TransactionType Transaction::stringToType(const std::string &typeStr) {
    if (typeStr == "in") return TransactionType::in;
    if (typeStr == "out") return TransactionType::out;
    throw invalid_argument("Invalid transaction type: " + typeStr);
}

string Transaction::toString() {
    ostringstream oss;
    oss << date << ";" << description << ";" << amount << typeToString(type) ;
    return oss.str();
}

Transaction Transaction::fromString(const std::string &line) {
    istringstream iss(line);
    string dateStr, descriptionStr, amountStr, typeStr;
    getline(iss, dateStr, ';');
    getline(iss, descriptionStr, ';');
    getline(iss, amountStr, ';');
    getline(iss, typeStr, ';');
    return Transaction(dateStr, descriptionStr, stod(amountStr), stringToType(typeStr));
}




