//
// Created by Leonardo on 26/04/2025.
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

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
    int year, month, day;
    char sep1, sep2;
    istringstream iss(d);
    iss >> year >> sep1 >> month >> sep2 >> day;
    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

    if (year <= 0 || month <= 0 || day <= 0) {
        throw invalid_argument("Date cannot contain negative numbers or zero.");
    }

    if (month > 12 || day > 31) {
        throw invalid_argument("Month or day out of valid range.");
    }

    if (desc.empty()) {
        throw invalid_argument("Error, blank description!");
    }
    if (a <= 0.0) {
        throw invalid_argument("Error, incorrect value!");
    }

    if (isLeap && month == 2) {
        if (day > 29) {
            throw invalid_argument("Error, February has at most 29 days in a leap year.");
        }
    } else {
        if (day > daysInMonth[month - 1]) {
            throw invalid_argument("Invalid day for the given month.");
        }
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
    regex dateFormat(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!regex_match(d, dateFormat)) {
        throw invalid_argument("Invalid date. Use YYYY-MM-DD format.");
    }

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
    int year, month, day;
    char sep1, sep2;
    istringstream iss(d);
    iss >> year >> sep1 >> month  >> sep2 >> day;
    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

    if (year <= 0 || month <= 0 || day <= 0) {
        throw invalid_argument("Date cannot contain negative numbers or zero.");
    }

    if (month > 12 || day > 31) {
        throw invalid_argument("Month or day out of valid range.");
    }

    if (isLeap && month == 2) {
        if (day > 29) {
            throw invalid_argument("Error, February has at most 29 days in a leap year.");
        }
    } else {
        if (day > daysInMonth[month - 1]) {
            throw invalid_argument("Invalid day for the given month.");
        }
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

string Transaction::typeToString() {
    return (type == in) ? "in" : "out";
}

TransactionType Transaction::stringToType(const string &typeStr) {
    if (typeStr == "in") return in;
    if (typeStr == "out") return out;
    throw invalid_argument("Invalid transaction type: " + typeStr);
}

string Transaction::toString() {
    ostringstream oss;
    oss << date << ";" << description << ";" << amount << ";" << typeToString();
    return oss.str();
}

Transaction Transaction::fromString(const string &line) {
    istringstream iss(line);
    string dateStr, descriptionStr, amountStr, typeStr;
    getline(iss, dateStr, ';');
    getline(iss, descriptionStr, ';');
    getline(iss, amountStr, ';');
    getline(iss, typeStr, ';');
    return Transaction(dateStr, descriptionStr, stod(amountStr), stringToType(typeStr));
}
